#include <iostream>
#include <iomanip>
#include <stdexcept>

#include <tpcc/combinations.h>

const char* output_1[] =
  {
   ":43210",
   ":43210",
   ":43210",
   ":43210",
   ":43210"
  };

const char* output_3[] =
  {
   "10:432",  "20:431",  "21:430",
   "10:432",  "30:421",  "31:420",
   "20:431",  "30:421",  "32:410",
   "21:430",  "31:420",  "32:410",
   "10:432",  "40:321",  "41:320",
   "20:431",  "40:321",  "42:310",
   "21:430",  "41:320",  "42:310",
   "30:421",  "40:321",  "43:210",
   "31:420",  "41:320",  "43:210",
   "32:410",  "42:310",  "43:210"
  };

const char* output_5[] =
  {"3210:4",  "4210:3",  "4310:2", "4320:1",  "4321:0"};

const char** output_data[] =
  { 0, output_1, 0, output_3, 0, output_5 };

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

	  std::stringstream os;
          e.print_debug(os);
          std::cout << "  " << os.str();
	  if (os.str() != std::string(output_data[k][i*k+j]))
	    throw std::logic_error("Combination differs");
        }
      std::cout << std::endl;
    }
  std::cout << std::endl;
}

int main()
{
  // test<5,0>(); // Invalid, since you cannot eliminate a value from an empty combination. Tests SFINAE.
  test<5,1>();
  test<5,3>();
  test<5,5>();
  return 0;
}
