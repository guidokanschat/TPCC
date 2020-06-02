#include <iostream>
#include <iomanip>

#include <tpcc/slab.h>

constexpr std::array<unsigned short, 2> dim2 {{ 2,3 }};
constexpr std::array<unsigned short, 3> dim3 {{ 2,3,4 }};

template<int n, int k, typename B, typename S, typename T>
void test(const TPCC::Slab<n,k,B,S,T>& slab)
{
  std::cout << "  Slab-size: " << slab.size() << std::endl;
//  if (mesh.size() != size2[k])
//    throw std::logic_error("Mesh sizes differ!");
  for (unsigned int i=0;i<TPCC::binomial(n,k);++i)
    {
      std::cout << "    Block-size " << i << ":\t" << slab.block_size(i) << std::endl;
//      if (mesh.block_size(i) != block_sizes2[k][i])
//        throw std::logic_error("Block sizes differ!");
    }
}

template <int k>
void test_2()
{
  const unsigned int n=2;
  TPCC::Lexicographic<n,k> mesh = dim2;
  std::cout << "Lexicographic<" << n
            << "," << k << ">::size = "
            << mesh.size() << "\n";
  std::array<bool,n> all_false{};
  TPCC::Slab<n,k> slab0{mesh, 0, 0, all_false};
  test(slab0);
  TPCC::Slab<n,k> slab1{mesh, 1, 0, all_false};
  test(slab1);
}


template <int k>
void test_3()
{
  const unsigned int n=3;
  TPCC::Lexicographic<n,k> mesh = dim3;
  std::cout << "Lexicographic<" << n
            << "," << k << ">::size = "
            << mesh.size() << "\n";
  std::array<bool,n> all_false{};
  TPCC::Slab<n,k> slab0{mesh, 0, 0, all_false};
  test(slab0);
  TPCC::Slab<n,k> slab1{mesh, 1, 0, all_false};
  test(slab1);
  TPCC::Slab<n,k> slab2{mesh, 2, 0, all_false};
  test(slab2);
}

int main(int , char *[])
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
