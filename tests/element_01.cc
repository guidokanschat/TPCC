#include <iostream>
#include <iomanip>

#include <tpcc/element.h>

template <int n, int k, typename T1, typename T2>
void test(const TPCC::Element<n,k,T1,T2>& e)
{
    e.print_debug(std::cout);

    for (unsigned int i=0;i<2*k;++i)
        {
            std::cout << "\n   " << i << ": ";
            auto b = e.facet(i);
            b.print_debug(std::cout);
        }
    std::cout << std::endl;
}

constexpr unsigned int fibonacci(unsigned int i)
{
    if (i==0 || i==1)
        return i;

    unsigned int i0 = 1;
    unsigned int i1 = 1;
    for (unsigned int j=1;j<i;++j)
        {
            unsigned int in = i0+i1;
            i0=i1;
            i1=in;
        }
    return i1;
}

template <int n, int k>
void test()
{
    TPCC::Combinations<n,k> combinations;
    std::array<unsigned int, n> positions;
    for (unsigned int i=0;i<n;++i)
        positions[i] = fibonacci(k+i);

    TPCC::Element<n,k,unsigned int, unsigned short> e{combinations[combinations.size()/3], positions};
    test(e);
}

int main()
{
  test<2,2>();
  test<5,3>();
    return 0;
}
