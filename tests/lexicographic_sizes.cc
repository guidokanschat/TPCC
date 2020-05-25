#include <iostream>
#include <iomanip>

#include <tensor_enumeration/lexicographic.h>

namespace TE = TensorEnumeration;

constexpr std::array<unsigned short, 2> dim2 {{ 3,4 }};
constexpr std::array<unsigned short, 3> dim3 {{ 3,4,5 }};

template <int k>
void test_2()
{
  TE::Lexicographic<2,k> mesh = dim2;
  std::cout << "Mesh-Dim: " << 2 << " Element-Dim: " << k << std::endl;
  for (unsigned int i=0;i<TE::binomial(2,k);++i)
    std::cout << "Block " << i << ":\t" << mesh.block_size(i) << std::endl;
}

template <int k>
void test_3()
{
  TE::Lexicographic<3,k> mesh = dim3;
  std::cout << "Mesh-Dim: " << 3 << " Element-Dim: " << k << std::endl;
  for (unsigned int i=0;i<TE::binomial(3,k);++i)
    std::cout << "Block " << i << ":\t" << mesh.block_size(i) << std::endl;
}

int main()
{
  test_2<2>();
  test_2<1>();
  test_2<0>();
  test_3<3>();
  test_3<2>();
  test_3<1>();
  test_3<0>();
  return 0;
}
