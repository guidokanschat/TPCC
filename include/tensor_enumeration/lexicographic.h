#ifndef TENSOR_ENUMERATION_LEXICOGRAPHIC_H
#define TENSOR_ENUMERATION_LEXICOGRAPHIC_H

#include <tensor_enumeration/combinations.h>

namespace TensorEnumeration
{
  /**
   * \brief The `k`-dimensional faces in a tensor product grid of dimension `n`.
   *
   * \tparam n: The dimension of the tensor product (the order of the tensor)
   * \tparam k: The dimensions of the object considered
   * \tparam Bint: The big integer used for addressing in the whole tensor product
   * \tparam Sint: The small integer used for addressing in each component
   * \tparam Tint: The tiny integer with values addressing the components
   */
  template <int n, int k, typename Bint = unsigned int, typename Sint = unsigned short, typename Tint = unsigned char>
  class Lexicographic
  {
    /**
     * \brief The dimension of the fibers in each direction.
     */
    std::array<Sint, n> dimensions;
    /**
     * \brief The number of objects facing the same directions.
     */
    std::array<Bint, binomial(n,k)> block_sizes;
  public:
    
    constexpr Lexicographic(const std::array<Sint, n>& d)
      : dimensions(d)
    {
      for (Tint i=0;i<binomial(n,k);++i)
	{
	  Bint p = 1;
	  auto combination = Combinations<n, k>::value(i);
	  auto complement = Combinations<n, k>::dual(i);
	  for (Tint j=0;j<k;++j)
	    p *= dimensions[combination[j]];
	  for (Tint j=0;j<n-k;++j)
	    p *= 1 + dimensions[complement[j]];
	  block_sizes[i] = p;
	}
    }
    
    /**
     * \brief The number of elements in this set.
     */
    constexpr Bint size () const;

    /**
     * \brief The number of elements in one direction
     */
    constexpr Bint block_size (Tint block) const
    {
      return block_sizes[block];
    }
  };
    
  // template <int n, int k, typename Bint, typename Sint>
  // inline constexpr Lexicographic<n,k,Bint,Sint,Tint>::size() const
  // {
  //   for (Tint )
  // }
}


#endif
