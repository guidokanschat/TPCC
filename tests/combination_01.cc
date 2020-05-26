#include <iostream>
#include <iomanip>
#include <stdexcept>

#include <tpcc/combinations.h>

template <int n, int k>
void test()
{
  TPCC::Combinations<n,k> combinations;
  for (unsigned int i=0;i<combinations.size();++i)
    {
      TPCC::Combination<n,k> c = combinations[i];
      c.print_debug(std::cout);

      for (unsigned int j=0;j<k;++j)
        {
          auto e = c.eliminate(j);
          std::cout << "  ";
          e.print_debug(std::cout);
        }
      std::cout << std::endl;
    }
}

int main()
{
  test<5,0>();
  test<5,3>();
  test<5,5>();
  return 0;
}
