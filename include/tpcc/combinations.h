#ifndef TPCC_COMBINATIONS_H
#define TPCC_COMBINATIONS_H

#include <array>
#include <ostream>

namespace TPCC
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
  T result = 1;
  if (k > n / 2)
    k = n - k;
  for (T i = 1; i <= k; ++i)
  {
    result *= n + 1 - i;
    result /= i;
  }

  return result;
}

  /**
   * Given a combination as an array, compute its complement in the set of numbers
   * from `0` to `n-1`.
   *
   * \todo Make this constexpr
   */
  template < typename T=unsigned int, T n, T k>
  std::array<T,n-k>
  compute_complement(std::array<T,k> combi)
  {
      std::array<unsigned int, n - k> result;
      unsigned int vpos = 0;
      unsigned int current = n-1;
      
      for (unsigned int i=0;i<n-k;++i,--current)
	{
	  while (current==combi[vpos] && vpos<k)
	    {
	      --current;
	      ++vpos;
	    }
	  result[i] = current;
	}
      return result;   
  }

/**
 * \brief Dataset for a combination k out of n
 */
  template <int n, int k, typename T=unsigned int>
class Combination
{
  /// The array of members
  std::array<T, k> data;
  /// The array of non-members
  std::array<T,n-k> cdata;
public:
  Combination(const std::array<T, k>& combi,
	      const std::array<T,n-k>& comp)
    : data(combi), cdata(comp)
  {}
  /**
   * \brief The `i`th element which is part of the combination in
   * descending order.
   */
  T in(unsigned int i) const
  {
    return data[i];
  }
  /**
   * \brief The `i`th element which is <b>not</b> part of the combination in
   * descending order.
   */
  T out(unsigned int i) const
  {
    return cdata[i];
  }

  /**
   * \brief Return the complement of this combination.
   */
  Combination<n,n-k,T> complement() const
  {
    return Combination<n,n-k,T> (cdata, data);
  }
  
  /**
   * \brief The combination obtained by eliminating the `i`th element
   */
  template <int kk=k>
  constexpr typename std::enable_if<(kk>0),Combination<n,k-1,T> >::type
  eliminate (unsigned int i) const
  {
      std::array<T,k-1> outdata{};
      for (unsigned int j=0;j<i;++j)
          outdata[j] = data[j];
      const T tmp = data[i];
      for (unsigned int j=i;j<k-1;++j)
        outdata[j] = data[j+1];
      std::array<T,n-k+1> outcdata{};
      unsigned int jj=0,j=0;
      for (;j<n-k;++j,++jj)
          {
            if (jj==j && cdata[j]<tmp)
                {
                    outcdata[j] = tmp;
                    ++jj;
                }
            outcdata[jj] = cdata[j];
          }
      if (jj==j)
          outcdata[n-k] = tmp;
      return Combination<n,k-1>{outdata, outcdata};
  }

  /**
   * \brief Print the content of this object for debugging.
   */
  void print_debug(std::ostream& os) const
  {
    for (unsigned int i=0;i<k;++i)
      os << in(i);
    os << ':';
    for (unsigned int i=0;i<n-k;++i)
      os << out(i);
  }
  
  };


  
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
  constexpr Combination<n,k> operator[] (unsigned int);
  
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
  template <typename T>
  static constexpr unsigned int index(const Combination<n,k,T>& combi);

  private:
  /**
   * \brief The function template computing the combination in
   * lexicographic ordering recursively.
   */
  template <unsigned int size, typename... I>
  static constexpr std::array<unsigned int,k> compute_value(unsigned int index, I ...args);
};

  //----------------------------------------------------------------------//

template <int n, int k>
constexpr unsigned int Combinations<n, k>::size()
{
  return binomial(n, k);
}

template <int n, int k>
template <unsigned int sz, typename... I>
constexpr std::array<unsigned int,k>
Combinations<n, k>::compute_value(unsigned int index, I ...args)
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
    return compute_value<sz-1>(index-bn, args..., cs);
  }
}


template <int n, int k>
template <typename T>
inline constexpr unsigned int Combinations<n, k>::index(const Combination<n,k,T>& combi)
{
  unsigned int result = 0;
  for (unsigned int i=0;i<k;++i)
    result += binomial(combi.in(i),k-i);
  return result;
}

//----------------------------------------------------------------------//


template <int n, int k>
std::array<unsigned int, k> Combinations<n, k>::value(unsigned int index)
{
  if constexpr (k==0)
  {
      ++index; // Avoid warning about unused variable
      return std::array<unsigned int,0>();
  }
  else
    return compute_value<k>(index);
}

template <int n, int k>
std::array<unsigned int, n - k> Combinations<n, k>::dual(unsigned int index)
{
  if constexpr (k==0)
    return Combinations<n,n>::value(index);
  auto v = value(index);
  return compute_complement<unsigned int,n,k>(v);
}

template <int n, int k>
constexpr Combination<n,k> Combinations<n, k>::operator[] (unsigned int index)
{
  return Combination<n,k>(value(index), dual(index));
}
}

#endif
