#ifndef tensor_enumeration_combination_h
#define tensor_enumeration_combination_h

#include <array>

namespace TensorEnumeration
{
/**
 * \brief Compute the binomial coefficient n over k.
 */
constexpr unsigned int binomial(unsigned int n, unsigned int k)
{
  if (n < k)
    return 0;
  unsigned int result = 1;
  if (k > n / 2)
    k = n - k;
  for (unsigned int i = 1; i <= k; ++i)
  {
    result *= n + 1 - i;
    result /= i;
  }

  return result;
}

/**
 * An object representing a selection of $k$ numbers out of the
 * set $\{0,1,\ldots,n-1$.
 */
template <int n, int k>
class Combination
{
  unsigned int data[k];

public:
  constexpr Combination(unsigned int i)
    : data()
  {
  }

  Combination(const std::array<unsigned int, k>& input)
  {
    std::copy(std::begin(input), std::end(input), &data[0]);
  }

  unsigned int index() const
  {
    unsigned int result = 0;
    int j = 0;
    for (int i = 0; i < k; ++i)
      while (++j <= data[i])
        result += binomial(n - 1 - j, k - 1 - i);
    return result;
  }
};


/**
 * The combinations of `k` elements out of `n`.
 */
template <int n, int k>
struct Combinations
{
  /**
   * \brief The number of such combinations
   */
  static constexpr unsigned int size();

  static std::array<unsigned int, k> value(unsigned int index);
  static std::array<unsigned int, n - k> dual(unsigned int index);

  /**
   * \brief The index of a combination within the lexicographic enumeration
   */
  static unsigned int index(const std::array<unsigned int, k>& combi);

  private:
  template <unsigned int size, typename... I>
  static constexpr std::array<unsigned int,k> compute_recursive(unsigned int index, I ...args);
};

template <int n, int k>
constexpr unsigned int Combinations<n, k>::size()
{
  return binomial(n, k);
}

template <int n, int k>
template <unsigned int sz, typename... I>
constexpr std::array<unsigned int,k>
Combinations<n, k>::compute_recursive(unsigned int index, I ...args)
{
  if (index > size())
    abort();
  if constexpr (sz==1)
    return std::array<unsigned int,k>{args..., index};
  else
  {
    unsigned int cs = sz-1;
    unsigned int bn = 0;
    for (; cs <= n; ++cs)
      {
        unsigned int bi = binomial(cs,sz);
        if (bi>index)
            break;
        bn = bi;
      }
    --cs;
    return compute_recursive<sz-1>(index-bn, args..., cs);
  }
}



template <int n, int k>
inline unsigned int Combinations<n, k>::index(const std::array<unsigned int, k>& combi)
{
  unsigned int result = 0;
  for (unsigned int i=0;i<k;++i)
    result += binomial(combi[i],k-i);
  return result;
}

//----------------------------------------------------------------------//


template <int n, int k>
std::array<unsigned int, k> Combinations<n, k>::value(unsigned int index)
{
  if constexpr (k==0)
      return std::array<unsigned int,0>();
  else
    return compute_recursive<k>(index);
}

template <int n, int k>
std::array<unsigned int, n - k> Combinations<n, k>::dual(unsigned int index)
{
  auto v = value(index);
  std::array<unsigned int, n - k> result;
  unsigned int vpos = 0;
  unsigned int current = n-1;

  for (unsigned int i=0;i<n-k;++i,--current)
    {
      while (current==v[vpos])
	{
	  --current;
	  ++vpos;
	}
      result[i] = current;
    }
  return result;
}
}

#endif
