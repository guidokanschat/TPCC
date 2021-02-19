#include <tpcc/combinations.h>

int main()
{
  constexpr TPCC::Combinations<4,2> cs;
  constexpr TPCC::Combination<4,2> c = cs[2];
  return c.in(1);
}
