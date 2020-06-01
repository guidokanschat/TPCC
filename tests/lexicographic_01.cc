// Unit tests:
// Lexicographic::size()
// Lexicographic::block_size()

#include <iostream>
#include <iomanip>

#include <tpcc/lexicographic.h>

// Reference output
const unsigned int size2[] = { 12, 17, 6};
const unsigned int size3[] = { 60, 133, 98, 24 };
const unsigned int block_sizes20[] = { 12 };
const unsigned int block_sizes21[] = { 8,9 };
const unsigned int block_sizes22[] = { 6 };
const unsigned int *block_sizes2[] =
{ block_sizes20, block_sizes21, block_sizes22 };
const unsigned int block_sizes30[] = { 60 };
const unsigned int block_sizes31[] = { 40,45,48 };
const unsigned int block_sizes32[] = { 30,32,36 };
const unsigned int block_sizes33[] = { 24 };
const unsigned int *block_sizes3[] =
{ block_sizes30, block_sizes31, block_sizes32, block_sizes33 };

constexpr std::array<unsigned short, 2> dim2 {{ 2,3 }};
constexpr std::array<unsigned short, 3> dim3 {{ 2,3,4 }};

template <int k>
void test_2()
{
  TPCC::Lexicographic<2,k> mesh = dim2;
  std::cout << "Mesh-dim: " << 2
            << " Element-dim: " << k
            << "\n  Mesh-size: " << mesh.size()
            << std::endl;
  if (mesh.size() != size2[k])
    throw std::logic_error("Mesh sizes differ!");
  for (unsigned int i=0;i<TPCC::binomial(2,k);++i)
    {
      std::cout << "    Block-size " << i << ":\t" << mesh.block_size(i) << std::endl;
      if (mesh.block_size(i) != block_sizes2[k][i])
        throw std::logic_error("Block sizes differ!");
    }
}

template <int k>
void test_3()
{
  TPCC::Lexicographic<3,k> mesh = dim3;
  std::cout << "Mesh-dim: " << 3
            << " Element-dim: " << k
            << "\n  Mesh-size: " << mesh.size()
            << std::endl;
  if (mesh.size() != size3[k])
    throw std::logic_error("Mesh sizes differ!");
  for (unsigned int i=0;i<TPCC::binomial(3,k);++i)
    {
      std::cout << "    Block-size " << i << ":\t" << mesh.block_size(i) << std::endl;
      if (mesh.block_size(i) != block_sizes3[k][i])
        throw std::logic_error("Block sizes differ!");
    }
}

int main()
{
  test_2<0>();
  test_2<1>();
  test_2<2>();
  test_3<0>();
  test_3<1>();
  test_3<2>();
  test_3<3>();
  return 0;
}
