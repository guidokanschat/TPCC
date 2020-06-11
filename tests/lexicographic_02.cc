// Unit test:
// Lexicographic::index()
// Lexicographic::operator[]

#include <iostream>
#include <iomanip>

#include <tpcc/lexicographic.h>

constexpr std::array<unsigned short, 1> dim1 {{ 5 }};
constexpr std::array<unsigned short, 2> dim2 {{ 2,3 }};
constexpr std::array<unsigned short, 3> dim3 {{ 2,3,4 }};
constexpr std::array<unsigned short, 4> dim4 {{ 1,2,3,4 }};

template <class MESH>
void print_mesh(const MESH& mesh)
{
  for (unsigned int i=0;i<mesh.size();++i)
    {
      auto element = mesh[i];
      std::cout << std::setw(4) << i << " ";
      element.print_debug(std::cout);
      std::cout << std::endl;
      if (mesh.index(element) != i)
	throw(i);
    }
}

template <unsigned int k>
void test_1()
{
  TPCC::Lexicographic<1u,k> mesh = dim1;
  std::cout << "Mesh-Dim: " << 1 << " Element-Dim: " << k << std::endl;
  print_mesh(mesh);
}

template <unsigned int k>
void test_2()
{
  TPCC::Lexicographic<2u,k> mesh = dim2;
  std::cout << "Mesh-Dim: " << 2 << " Element-Dim: " << k << std::endl;
  print_mesh(mesh);
}

template <unsigned int k>
void test_3()
{
  TPCC::Lexicographic<3u,k> mesh = dim3;
  std::cout << "Mesh-Dim: " << 3 << " Element-Dim: " << k << std::endl;
  print_mesh(mesh);
}

template <unsigned int k>
void test_4()
{
  TPCC::Lexicographic<4u,k> mesh = dim4;
  std::cout << "Mesh-Dim: " << 4 << " Element-Dim: " << k << std::endl;
  print_mesh(mesh);
}

int main()
{
  test_1<1>();
  test_1<0>();

  test_2<2>();
  test_2<1>();
  test_2<0>();

  test_3<3>();
  test_3<2>();
  test_3<1>();
  test_3<0>();

  test_4<4>();
  test_4<3>();
  test_4<2>();
  test_4<1>();
  test_4<0>();

  return 0;
}
