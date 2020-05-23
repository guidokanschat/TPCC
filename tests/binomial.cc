#include <iostream>
#include <iomanip>

#include <tensor_enumeration/combinations.h>

namespace TE = TensorEnumeration;

namespace Testing
{
  unsigned int pascal_data[11][11] =
    {
     {   1,  10,  45, 120, 210, 252, 210, 120,  45,  10,   1},
     {   1,   9,  36,  84, 126, 126,  84,  36,   9,   1,   0},
     {   1,   8,  28,  56,  70,  56,  28,   8,   1,   0,   0},
     {   1,   7,  21,  35,  35,  21,   7,   1,   0,   0,   0},
     {   1,   6,  15,  20,  15,   6,   1,   0,   0,   0,   0},
     {   1,   5,  10,  10,   5,   1,   0,   0,   0,   0,   0},
     {   1,   4,   6,   4,   1,   0,   0,   0,   0,   0,   0},
     {   1,   3,   3,   1,   0,   0,   0,   0,   0,   0,   0},
     {   1,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0},
     {   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0},
     {   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
    };
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
void pascal(unsigned int padding=n)
{
  const unsigned int x = TE::Combinations<n, k>::size();
  const unsigned int y = TE::binomial(n, k);
  if (x != y)
    throw y;
  char xc[x];
  char yc[y];

  if (k==n)
    std::cout << '{';
  else
    std::cout << ',';
  std::cout << std::setw(4) << x;
  if (x != pascal_data[10-n][k])
    throw (n);
  if constexpr (k > 0)
    pascal<n, k-1>(padding);
  else
  {
    for (unsigned int i=n;i<padding;++i)
      std::cout << ',' << std::setw(4) << 0;
    std::cout << "}," << std::endl;
    if constexpr (n > 0)
      pascal<n-1,n-1>(padding);
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
