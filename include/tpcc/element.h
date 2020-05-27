#ifndef TPCC_ELEMENT_H
#define TPCC_ELEMENT_H

#include <tpcc/combinations.h>

namespace TPCC
{
/**
 * \brief Tensor coordinates for a facet of dimension `k` in the complex of dimension `n`.
 *
 * Each element is characterized by its orientation and its
 * position in the complex. The orientation or #direction is
 * described by a combination of `k` coordinates which span the
 * element. It has no extension across these coordinates.
 *
 * The set of elements for a fixed combination of #directions
 * consists of slices of dimension `k` through the complex. These
 * slices are indexed by the coordinates <b>not</b> spanning the
 * elements. These indices are stored in
 * #position_across. Finally, they are numbered within the
 * `k`-dimensional slice in the entry #position_along. Both fields
 * are vectors of integer coordinates in all coordinate
 * directions.
 *
 * The fields #position_along and #position_across are indexed by
 * the combination of #directions and its complement,
 * respectively.
 *
 * \tparam n: The dimension of the tensor chain complex
 * \tparam k: The dimension of this element
 * \tparam Sint: The integer type used for indexing in a single fiber
 * \tparam Tint: The integer type used for indexing fibers, directions, etc.
 */
template <int n, int k, typename Sint = unsigned short, typename Tint = unsigned char>
struct Element
{
  /// A Combination enumerating the coordinate directions along which the element is aligned.
  Combination<n,k> directions;
  /// The integer coordinates within the `k`-dimensional slice of the complex this is an element of
  std::array<Sint, k> position_along;
  /// The integer coordinates of the `k`-dimensional slice itself
  std::array<Sint,n-k> position_across;

  /**
   * \brief Function for printing the data stored in the element.
   *
   * \note This function is also used in the consistency tests,
   * therefore, the comparison data must be changed if the output
   * format is changed.
   */
  void print_debug(std::ostream& os) const
  {
    directions.print_debug(os);
    os << " (";
    std::array<Sint, n> data;
    for (unsigned int i=0;i<k;++i)
      data[directions.in(i)] = position_along[i];
    for (unsigned int i=0;i<n-k;++i)
      data[directions.out(i)] = position_across[i];
    
    for (unsigned int i=0;i<n-1;++i)
      os << data[i] << ',';
    os << data[n-1] << ")";
  }

  /**
   * \brief Enumeration of the boundary facets of the element.
   *
   * Such a boundary facet shares all directions into which it
   * extends, except one. Conversely, it is orthogonal to the same
   * coordinate directions plus one. It has the same one-dimensional
   * coordinates for all shared directions. For the one direction
   * which was eliminated, the coordinate is either the same as for
   * the element for the lower boundary, or plus one for the upper.
   */
  constexpr Element<n,k-1,Sint,Tint> facet(Tint index) const
  {
    Tint i2 = index/2;
    Tint im = index%2;
    Combination<n,k-1> combi = directions.eliminate(i2);
    std::array<Sint, k-1> new_along{};
    for (unsigned int i=0;i<i2;++i)
      new_along[i] = position_along[i];
    for (unsigned int i=i2+1;i<k-1;++i)
      new_along[i] = position_along[i+1];

    std::array<Sint, n-k+1> new_across{};
    unsigned int i=0, ii=0;
    for (;i<n-k;++i,++ii)
      {
	if (combi.out(i) == directions.in(i2))
	  new_across[ii++] = position_along[i2] + ((im==0) ? 0 : 1);
	new_across[ii] = position_across[i];
      }
    if (i==ii)
      new_across[n-k+1] = position_along[i2] + ((im==0) ? 0 : 1);
  }
};
}

#endif
