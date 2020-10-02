/**
 * \file
 * Combination::add()
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include <tpcc/combinations.h>

const char* output_0[] =
 {
  "4:3210",
  "3:4210",
  "2:4310",
  "1:4320",
  "0:4321"
 };

const char* output_1[] =
 {
  "40:321",  "30:421",  "20:431",  "10:432",
  "41:320",  "31:420",  "21:430",  "10:432",
  "42:310",  "32:410",  "21:430",  "20:431",
  "43:210",  "32:410",  "31:420",  "30:421",
  "43:210",  "42:310",  "41:320",  "40:321"
 };

const char* output_2[] =
 {
  "410:32",  "310:42",  "210:43",
  "420:31",  "320:41",  "210:43",
  "421:30",  "321:40",  "210:43",
  "430:21",  "320:41",  "310:42",
  "431:20",  "321:40",  "310:42",
  "432:10",  "321:40",  "320:41",
  "430:21",  "420:31",  "410:32",
  "431:20",  "421:30",  "410:32",
  "432:10",  "421:30",  "420:31",
  "432:10",  "431:20",  "430:21"
 };

const char* output_3[] =
 {
  "4210:3",  "3210:4",
  "4310:2",  "3210:4",
  "4320:1",  "3210:4",
  "4321:0",  "3210:4",
  "4310:2",  "4210:3",
  "4320:1",  "4210:3",
  "4321:0",  "4210:3",
  "4320:1",  "4310:2",
  "4321:0",  "4310:2",
  "4321:0",  "4320:1"
 };

const char* output_4[] =
 {
  "43210:", "43210:", "43210:", "43210:", "43210:",
 };

const char** output_data[] =
  { output_0, output_1, output_2, output_3, output_4 };

template <int n, int k>
void test()
{
  std::cout << "Testing n=" << n << " k=" << k << std::endl;
  TPCC::Combinations<n,k> combinations;
  for (unsigned int i=0;i<combinations.size();++i)
    {
      TPCC::Combination<n,k> c = combinations[i];
      c.print_debug(std::cout);
      std::cout << std::flush;

      for (unsigned int j=0;j<n-k;++j)
        {
          auto e = c.add(c.out(j));

	  std::stringstream os;
          e.print_debug(os);
          std::cout << "  " << os.str();
	  if (os.str() != std::string(output_data[k][i*(n-k)+j]))
	    throw std::logic_error("Combination differs");
        }
      std::cout << std::endl;
    }
  std::cout << std::endl;
}

int main()
{
  test<5,0>();
  test<5,1>();
  test<5,2>();
  test<5,3>();
  test<5,4>();
//  test<5,5>();  // Invalid, since you cannot eliminate a value from an empty combination. Tests SFINAE.
  return 0;
}
