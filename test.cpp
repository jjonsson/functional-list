// This file contains some quick and simple tests. The correctness of the
//   output should be visually verified.

#include <iostream>

#include "flist.hpp"

using namespace cfl;

// This ensures that these functions are actually constexpr.
static constexpr int f()
{
  auto ls = cons(12, cons(6, List<int, 0>::empty()));
  return head(tail(ls));  // the second element
}
static constexpr int result = f();

int main()
{
  std::cout << result << std::endl;  // check the above value
  
  // Now, let's test fmap and foldr.
  auto xs = cons(12, cons(7, cons(42, List<int, 0>::empty())));
  fmap([&](int x){ std::cout << x << ' '; return 0; }, xs);  // print the list
  std::cout << std::endl;
  
  // compute the sum
  std::cout << foldr([](int x, int y){return x + y;}, 0, xs) << std::endl;
  
  // try doubles
  auto ys = cons(5.99, cons(3.5, cons(2.0, List<double, 0>::empty())));
  // product
  std::cout << foldr([](double x, double y){return x * y;}, 1.0, ys)
            << std::endl;
  
}