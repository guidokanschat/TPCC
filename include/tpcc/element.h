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
class Element
{
  /**
   * \brief A Combination enumerating the coordinate directions along which the element is aligned.
   *
   * Since combinations are generated in falling order, coordinates usually are referenced in ascending order,
   * the directions are actually not the value in the combination or its complement.
   * The index `i` returned by the combination is immediately replaced by `n-1-i`.
   */
  Combination<n,k> directions;
  /// The integer coordinates within the `n`-dimensional complex
  std::array<Sint, n> positions;

public:
  /// Constructor with both data elements
  template <typename T>
  Element(const Combination<n,k>& combi, const std::array<T,n>& pos)
    : directions(combi), positions(pos) {}

  /// The number of facets in the boundary of this object
  static constexpr Tint n_facets()
  { return 2*k; }

  /// The index of the combination enumerating directions
  constexpr Tint direction_index () const
  { return Combinations<n,k>::index(directions); }

  /// The coordinates in the `n`-dimensional chain complex
  constexpr Sint operator[] (Tint index) const
  { return positions[index]; }

  /**
   * \brief The coordinate direction out of `n` in the complex for the coordinate direction out of `k` of the element
   *
   * The Element extends along `k` integer coordinates, which are mapped through #directions to the `n` integer coordinates of the complex.
   * This function maps the local coordinate direction of the Element to the global direction in the chain complex.
   */
  constexpr Tint along_direction(Tint index) const
  { return n-1-directions.in(index); }

  /// The coordinates in the `k`-dimensional mesh
  constexpr Sint along_coordinate(Tint index) const
  { return positions[along_direction(index)]; }

  constexpr Tint across_direction(Tint index) const
  { return n-1-directions.out(index); }

  /// The coordinate in the `k`-dimensional mesh
  constexpr Sint across_coordinate(Tint index) const
  { return positions[across_direction(index)]; }  /**
   * \brief Function for printing the data stored in the element.
   *
   * \note This function is also used in the consistency tests,
   * therefore, the comparison data must be changed if the output
   * format is changed.
   */
  void print_debug(std::ostream& os) const
  {
    os << " (";
    for (Tint i=0;i<k;++i)
      os << (unsigned int) along_direction(i);
    os << ':';
    for (Tint i=0;i<n-k;++i)
      os << (unsigned int) across_direction(i);
    os << ' ';
    for (unsigned int i=0;i<n-1;++i)
      os << positions[i] << ',';
    os << positions[n-1] << ")";
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
    Tint i2 = index/2;  // The direction index out of k
    Tint im = index%2;  // Lower or upper boundary in this direction?
    Tint gi = along_direction(i2); // The global direction out of n belonging to index
    Combination<n,k-1> combi = directions.eliminate(i2);
    std::array<Sint, n> new_positions = positions;
    if (im == 1)
      ++new_positions[gi];

    return Element<n,k-1,Sint,Tint>{combi, new_positions};
  }
};
}

#endif
