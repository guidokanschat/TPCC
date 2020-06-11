#include <iostream>
#include <iomanip>
#include <array>

#include <tpcc/slab.h>

constexpr std::array<unsigned short, 1> dim1 {{ 2 }};
constexpr std::array<unsigned short, 2> dim2 {{ 2,3 }};
constexpr std::array<unsigned short, 3> dim3 {{ 2,3,4 }};

template<int n, int k, typename B, typename S, typename T>
void test(const TPCC::Slab<n,k,B,S,T>& slab)
{
  std::cout << "  Slab-size: " << slab.size() << std::endl;
//  if (mesh.size() != size2[k])
//    throw std::logic_error("Mesh sizes differ!");
  for (unsigned int i=0;i<TPCC::binomial(n-1,k-1);++i)
    {
      std::cout << "    Block-size " << i << ":\t" << slab.block_size(i) << std::endl;
//      if (mesh.block_size(i) != block_sizes2[k][i])
//        throw std::logic_error("Block sizes differ!");
    }
}

template <int k, class A>
void constexpr test(const A& arr)
{
  const unsigned int n = std::tuple_size<A>::value;
  typedef TPCC::Lexicographic<n,k> Mesh;
  Mesh mesh{arr};
  std::cout << "Lexicographic<" << n
            << "," << k << ">::size = "
            << mesh.size() << "\n";
  for (typename Mesh::dimension_index_t d=0;d<n;++d)
    {
      std::cout << "   Normal: " << (unsigned int) d << "\n";
      std::array<typename Mesh::dimension_index_t,n-1> directions;
      typename Mesh::dimension_index_t ii=0;
      for (typename Mesh::dimension_index_t i=0;i<directions.size();++i,++ii)
      {
        if (i==d) ++ii;
        directions[i] = ii;
      }
      std::array<bool,n-1> all_false{};
      TPCC::Slab<n,k> slab0{mesh, directions, all_false, directions.size(), 0};
      test(slab0);
    }
}


int main(int , char *[])
{
  test<1>(dim1);

  test<2>(dim2);
  test<1>(dim2);
//  test<0>(dim2);

  test<3>(dim3);
  test<2>(dim3);
  test<1>(dim3);
//  test<0>(dim3);
  return 0;
}
