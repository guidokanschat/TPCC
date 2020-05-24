#ifndef tensor_enumeration_combination_h
#define tensor_enumeration_combination_h

#include <array>

namespace TensorEnumeration
{
/**
 * \brief Compute the binomial coefficient n over k.
 *
 * This function is constexpr, such that it can be eliminated
 * completely if #n and #k are known at compile time.
 */
  template <typename T=unsigned int>
constexpr T binomial(T n, T k)
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
 * The combinations of `k` elements out of `n` as a container.
 *
 * This class template does not contain any data, but it implements an
 * enumeration of combinations, such that any combination as an array
 * of `k` numbers from `0` to `n-1` can be obtained from its index and
 * vice versa.
 */
template <int n, int k>
struct Combinations
{
  /**
   * \brief The number of such combinations
   */
  static constexpr unsigned int size();

  /**
   * \brief A boolean array of length `n` with a `true` for each selected value
   */
  static constexpr std::array<bool,n> operator[] (unsigned int);
  
  /**
   * \brief The array of numbers (of length `k`) in the combination
   * with given index.
   */
  static std::array<unsigned int, k> value(unsigned int index);
  /**
   * \brief The array of numbers (of length `n-k`) of numbers not in
   * the combination of the given index.
   *
   * \todo This is currently implemented by computing value() and then
   * building the complement. It it is to be used often, the
   * implementation should be more efficient.
   */
  static std::array<unsigned int, n - k> dual(unsigned int index);

  /**
   * \brief The index of a combination within the lexicographic enumeration
   */
  static unsigned int index(const std::array<unsigned int, k>& combi);

  private:
  /**
   * \brief The function template computing the combination in
   * lexicographic ordering recursively.
   */
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
