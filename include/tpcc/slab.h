#ifndef TPCC_SLAB_H
#define TPCC_SLAB_H

#include <tpcc/lexicographic.h>

namespace TPCC
{
/**
 * \brief A slab of thickness one cell cut out of a tensor product chain complex
 *
 * A slab is a submesh of (topological) codimension 1 cut out of an `n`-dimensional mesh.
 * It is characterized by its #normal_direction, the one missing from the complex, and
 * the #normal_coordinate, the position along the #normal_direction. It only consists of elements
 * which extend in the normal direction. In this respect, it differs from a CutPlane which
 * contains elements within a hyperplane characterized by the same data.
 *
 * \note The data member #superset is currently a reference, which might become outdated.
 * We could replace it by some kind of smartpointer, but this induces overhead. AS of now,
 * the focus of this project is on minimal overhead, such that we can use the functions for
 * the managing of high order cochain finite elements on each mesh cell. Thus, we trade off
 * safety for efficiency until there is a better idea.
 */
template <int n, int k, typename Bint = unsigned int, typename Sint = unsigned short, typename Tint = unsigned char>
class Slab
{
   typedef Lexicographic<n,k,Bint,Sint,Tint> super_class;
   const Lexicographic<n,k,Bint,Sint,Tint>& superset;
   const std::array<Tint,n-1> directions;
   const std::array<bool, n-1> reverse;
   const Tint normal_direction;
   const Sint normal_coordinate;
   const Lexicographic<n-1,((k>0) ? k-1:0),Bint,Sint,Tint> aux;

   /// Compute the dimensions of the auxiliary object
   static constexpr std::array<Sint,n-1>
   aux_dimensions (const Lexicographic<n,k,Bint,Sint,Tint>& from,
                   const std::array<Tint,n-1>& directions)
   {
     std::array<Sint,n-1> result;
     for (Tint i=0;i<n-1;++i)
       result[i] = from.fiber_dimension(directions[i]);
     return result;
   }

   /**
    * \brief The number of objects facing the same directions.
    */
   std::array<Bint, binomial(n,k)> block_sizes;

public:
   constexpr Slab(const Lexicographic<n,k,Bint,Sint,Tint>& from,
                  const std::array<Tint,n-1> directions,
                  const std::array<bool,n-1>& reverse,
                  Tint normal_direction,
                  Sint normal_coordinate)
       : superset(from),
         directions(directions),
         reverse(reverse),
         normal_direction(normal_direction),
         normal_coordinate(normal_coordinate),
         aux(aux_dimensions(from, directions))
   {
     static_assert(k>=1, "Element dimension of slab must be at least 1");
   }


   constexpr Bint size() const
   {
     return aux.size();
   }

   /**
    * \brief The number of elements in one direction
    */
   constexpr Bint block_size (Tint block) const
   {
     return aux.block_size(block);
   }

   /**
    * \brief The element at position index, in the coordinates of the whole chain complex.
    *
    * The index refers to lexicographic ordering in the local coordinates of the Slab,
    * as defined by #directions and #reverse. The Element returned has its coordinates in
    * the superset. Thus, it contains a field for a coordinate #normal_direction and the value
    * of this coordinate is always #normal_coordinate.
    *
    * \section3 Implementation
    *
    * Enumeration of the cells uses the object #aux, which contains a cut through the slab.
    * Thus, all elements of the slab can be constructed from elements of #aux by adding the #normal_direction
    * of the slab as a direction along the element. Its coordinate is the #normal_coordinate.
    *
    * All other coordinates of the constructed element are determined according to #directions and #reverse.
    * First, each direction `d` in #aux is mapped to the direction `directions[d]` in the #superset.
    * Then, the coordinate in this direction is computed using #reverse as either the same as the one in
    * #aux or the one obtained by subtracting this from the fiber dimension.
    */
   constexpr Element<n,k,Sint,Tint> operator[] (Bint index) const
   {
     auto local = aux[index];
     // `local` contains a cut through the elements of the slab. Thus, copy the along directions.
     std::array<Sint,n> coordinates{};
     for (Tint i=0;i<k-1;++i)
       {
         const Sint c = local.along_coordinate(i);
         const Tint d = directions[local.along_direction(i)];
         coordinates[d] = reverse[i] ? (superset.fiber_dimension(d)-c-1) : (c);
       }
     // By definition of a slab, the normal_direction is an along_direction of its elements
     coordinates[normal_direction] = normal_coordinate;
     // The remaining coordinates are just copied
     for (Tint i=0;i<n-k;++i)
       coordinates[directions[local.across_direction(i)]] = local.across_coordinate(i);
   }
};
}


#endif // TPCC_SLAB_H
