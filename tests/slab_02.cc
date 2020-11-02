#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>

#include <tpcc/slab.h>

constexpr std::array<unsigned short, 1> dim1{ { 2 } };
constexpr std::array<unsigned short, 2> dim2{ { 2, 3 } };
constexpr std::array<unsigned short, 3> dim3{ { 2, 3, 4 } };

template <int n, int k, typename B, typename S, typename T>
void test(const TPCC::Slab<n, k, B, S, T>& slab)
{
  std::cout << "    Slab-size: " << slab.size() << std::endl;
  unsigned int sum = 0;
  for (unsigned int i = 0; i < TPCC::binomial<unsigned int>(n - 1, k - 1); ++i)
  {
    sum += slab.block_size(i);
    std::cout << "      Block-size " << i << ":\t" << slab.block_size(i) << std::endl;
    for (B i = 0; i < slab.size(); ++i)
    {
      std::cout << "        " << std::setw(4) << i << ' ';
      slab[i].print_debug(std::cout);
      std::cout << "\n";
    }
  }
  if (slab.size() != sum)
    throw std::logic_error("Mesh size is not sum of block sizes!");
}

template <int k, class A>
void constexpr test(const A& arr)
{
  const unsigned int n = std::tuple_size<A>::value;
  typedef TPCC::Lexicographic<n, k> Mesh;
  Mesh mesh{ arr };
  std::cout << "Lexicographic<" << n << "," << k << ">::size = " << mesh.size() << "\n";
  for (typename Mesh::dimension_index_t d = 0; d < n; ++d)
  {
    std::cout << "  Normal: " << (unsigned int)d << "\n";
    std::array<typename Mesh::dimension_index_t, n - 1> directions{};
    typename Mesh::dimension_index_t ii = 0;
    for (typename Mesh::dimension_index_t i = 0; i < directions.size(); ++i, ++ii)
    {
      if (i == d)
        ++ii;
      directions[i] = ii;
    }
    do
    {
      std::cout << "    Directions:";
      for (unsigned int i = 0; i < directions.size(); ++i)
        std::cout << ' ' << (int)directions[i];
      std::cout << "\n";
      std::array<bool, n - 1> reverse{};
      TPCC::Slab<n, k> slab0{ mesh, directions, reverse, d, 0 };
      test(slab0);
    } while (std::next_permutation(directions.begin(), directions.end()));
  }
}

int main(int, char*[])
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
