#ifndef TPCC_ELEMENT_H
#define TPCC_ELEMENT_H

#include <tpcc/combinations.h>

namespace TPCC
{
/**
 * \brief Descriptor for a facet of dimension `k` in the complex.
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
};
}

#endif
