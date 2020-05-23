#include <iostream>

#include <tensor_enumeration/combinations.h>

namespace TE = TensorEnumeration;

namespace Testing
{
/**
 * \brief Compute binomail coefficients and combinations in
 * lexicographical order
 */
namespace binomial
{
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, std::array<T, N> a)
{
  for (std::size_t j = 0; j < a.size(); ++j)
    os << ' ' << a[j];
  return os;
}

template <int n, int k>
struct print_combination
{
  static void doit()
  {
    for (unsigned int i=0;i<TE::Combinations<n, k>::size();++i)
      {
	auto a = TE::Combinations<n, k>::value(i);
	auto b = TE::Combinations<n, k>::dual(i);
	std::cout << i << ' ' << TE::Combinations<n, k>::index(a) << ":\t" << a << " |" << b << std::endl;
	if (TE::Combinations<n, k>::index(a) != i)
	  throw i;
      }
  }
};

template <int n, int k = n>
void pascal()
{
  const unsigned int x = TE::Combinations<n, k>::size();
  const unsigned int y = TE::binomial(n, k);
  if (x != y)
    throw y;
  char xc[x];
  char yc[y];

  std::cout << ' ' << x;
  if (k > 0)
    pascal<n, (k > 0 ? k - 1 : k)>();
  else
  {
    std::cout << std::endl;
    if (n > 0)
      pascal<(n > 0 ? n - 1 : n), (n > 0 ? n - 1 : n)>();
  }
}
}
}

using namespace Testing::binomial;

int main()
{
  //  auto a = combination<3, 5, 1, 0, 0, 7, 8, 9>::value();
  //  std::cout << a << std::endl;
  std::cout << "Pascal" << std::endl;
  pascal<10>();
  print_combination<5, 1>::doit();
  print_combination<5, 2>::doit();
  print_combination<5, 3>::doit();
  print_combination<5, 4>::doit();
  std::cout << std::endl;
  //  print_combination<6, 4, Combinations<6, 4>::size() - 1>::doit();
}
