#include <iostream>
#include <iomanip>
#include <stdexcept>

#include <tpcc/combinations.h>

unsigned int pascal_data[11][11] =
  {
   {   1,  10,  45, 120, 210, 252, 210, 120,  45,  10,   1},
   {   1,   9,  36,  84, 126, 126,  84,  36,   9,   1,   0},
   {   1,   8,  28,  56,  70,  56,  28,   8,   1,   0,   0},
   {   1,   7,  21,  35,  35,  21,   7,   1,   0,   0,   0},
   {   1,   6,  15,  20,  15,   6,   1,   0,   0,   0,   0},
   {   1,   5,  10,  10,   5,   1,   0,   0,   0,   0,   0},
   {   1,   4,   6,   4,   1,   0,   0,   0,   0,   0,   0},
   {   1,   3,   3,   1,   0,   0,   0,   0,   0,   0,   0},
   {   1,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0},
   {   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0},
   {   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
  };

const char* combination_data_0[] = {"fffff"};

const char* combination_data_1[] =
  {
   "tffff",
   "ftfff",
   "fftff",
   "ffftf",
   "fffft"
  };

const char* combination_data_2[] =
  {
   "ttfff",
   "tftff",
   "fttff",
   "tfftf",
   "ftftf",
   "ffttf",
   "tffft",
   "ftfft",
   "fftft",
   "ffftt"
  };

const char* combination_data_3[] =
  {
   "tttff",
   "ttftf",
   "tfttf",
   "ftttf",
   "ttfft",
   "tftft",
   "fttft",
   "tfftt",
   "ftftt",
   "ffttt"
  };

const char* combination_data_4[] =
  {
   "ttttf",
   "tttft",
   "ttftt",
   "tfttt",
   "ftttt"
  };

const char* combination_data_5[] = { "ttttt" };

const char** combination_data[] =
  {
   combination_data_0,
   combination_data_1,
   combination_data_2,
   combination_data_3,
   combination_data_4,
   combination_data_5
  };

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, std::array<T, N> a)
{
  for (std::size_t j = 0; j < a.size(); ++j)
    os << ' ' << a[j];
  return os;
}

template <std::size_t N>
std::ostream& operator<<(std::ostream& os, std::array<bool, N> a)
{
  for (std::size_t j = 0; j < a.size(); ++j)
    os << (a[j] ? 't' : 'f');
  return os;
}

template <int n, int k>
struct print_combination
{
  static void doit()
  {
    for (unsigned int i=0;i<TPCC::Combinations<n, k>::size();++i)
      {
	TPCC::Combinations<n, k> combinations;
	auto a = combinations.value(i);
	auto b = combinations.dual(i);
	auto combi = combinations[i];
	std::array<bool,n> boolvalue;
	for (unsigned int j=0;j<k;++j)
	  {
	    if (a[j] != combi.in(j))
	      throw std::logic_error{"value() and operator[] inconsistent"};
	    if (combination_data[k][i][combi.in(j)] != 't')
	      throw std::logic_error{"Combination does not match stored data"};
	    boolvalue[a[j]] = true;
	  }
	for (unsigned int j=0;j<n-k;++j)
	  {
	    if (b[j] != combi.out(j))
	      throw std::logic_error{"dual() and operator[] inconsistent"};
	    if (combination_data[k][i][combi.out(j)] != 'f')
	      throw std::logic_error{"Combination does not match stored data"};
	    boolvalue[b[j]] = false;
	  }
	std::cout << i << ":\t";
	combi.print_debug(std::cout);
	std::cout
	    << " bools: \"" << boolvalue << "\""
	    << std::endl;
	if (combinations.index(combi) != i)
	  throw std::logic_error{"Error in index computation"};
      }
  }
};

template <int n, int k = n>
void pascal(unsigned int padding=n)
{
  const unsigned int x = TPCC::Combinations<n, k>::size();
  const unsigned int y = TPCC::binomial(n, k);
  if (x != y)
    throw std::domain_error{"Size of combination wrong"};
  char xc[x];
  char yc[y];
  
  if (k==n)
    std::cout << '{';
  else
    std::cout << ',';
  std::cout << std::setw(4) << x;
  if (x != pascal_data[10-n][k])
    throw std::logic_error{"Value in Pascal's triangle wrong"};
  if constexpr (k > 0)
    pascal<n, k-1>(padding);
  else
    {
      for (unsigned int i=n;i<padding;++i)
	std::cout << ',' << std::setw(4) << 0;
      std::cout << "}," << std::endl;
      if constexpr (n > 0)
	pascal<n-1,n-1>(padding);
    }
}


int main()
{
  //  auto a = combination<3, 5, 1, 0, 0, 7, 8, 9>::value();
  //  std::cout << a << std::endl;
  std::cout << "Pascal" << std::endl;
  pascal<10>();
  print_combination<5, 0>::doit();
  print_combination<5, 1>::doit();
  print_combination<5, 2>::doit();
  print_combination<5, 3>::doit();
  print_combination<5, 4>::doit();
  print_combination<5, 5>::doit();
  std::cout << std::endl;
  //  print_combination<6, 4, Combinations<6, 4>::size() - 1>::doit();
}
