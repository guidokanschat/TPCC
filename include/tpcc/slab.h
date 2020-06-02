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
 * \note The data member #superset is currently s reference, which might become outdated.
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
   const Tint normal_direction;
   const Sint normal_coordinate;
   const std::array<bool, n> reverse;
   /**
    * \brief The number of objects facing the same directions.
    */
   std::array<Bint, binomial(n,k)> block_sizes;

public:
   constexpr Slab(const Lexicographic<n,k,Bint,Sint,Tint>& from,
                  Tint normal_direction, Tint normal_coordinate, const std::array<bool,n>& reverse)
       : superset(from),
         normal_direction(normal_direction),
         normal_coordinate(normal_coordinate),
         reverse(reverse),
         block_sizes{}
   {
       Combinations<n,k> combinations;
       for (Tint i=0;i<binomial(n,k);++i)
         {
           Bint p = 1;
           auto combination = combinations[i];
           bool is_aligned = false;
           for (Tint j=0;j<k;++j)
             {
               if (normal_direction == n-1-combination.in(j))
                    is_aligned = true;
                else
                   p *= superset.fiber_dimension(n-1-combination.in(j));
             }
           if (!is_aligned)
             continue;
           for (Tint j=0;j<n-k;++j)
             p *= 1 + superset.fiber_dimension(n-1-combination.out(j));
           block_sizes[i] = p;
         }
   }

   constexpr Bint size() const
   {
     Bint sum = 0;
     for (unsigned int i=0;i<block_sizes.size();++i)
       sum += block_sizes[i];
     return sum;
   }

   /**
    * \brief The number of elements in one direction
    */
   constexpr Bint block_size (Tint block) const
   {
     return block_sizes[block];
   }

   /**
    * \brief The element at position index, in the coordinates of the whole chain complex.
    *
    * The index refers to lexicographic ordering in the local coordinates of the Slab,
    * as defined by #normal_direction and #reverse. The Element returned has its coordinates in
    * the superset. Thus, it contains a field for a coordinate #normal_direction and the value
    * of this coordinate is always #normal_coordinate.
    */
   constexpr Element<n,k,Sint,Tint> operator[] (Bint index) const;
};
}


#endif // TPCC_SLAB_H
