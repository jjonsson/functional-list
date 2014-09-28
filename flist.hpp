// Author: James Jonsson
// Date: 9-28-2014

#include <cstddef>

#include <utility>

#ifndef CFL_FLIST_HPP
#define CFL_FLIST_HPP

namespace cfl {

  using std::size_t;


  // List is a functional, compile-time list class.
  template <class T, size_t N>
  class List;
  
  // List interface - everything needed to build Lists and access List contents
  template <class T, size_t N>
  constexpr List<T, N+1> cons(const T&, const List<T, N>&);

  template <class T, size_t N>
  constexpr T head(const List<T, N>&);

  template <class T, size_t N>
  constexpr List<T, N-1> tail(const List<T, N>&);


  // List is a functional list implementation with all functions constexpr.
  template <class T, size_t N>
  struct List {  
    const T head_;
    const List<T, N-1> tail_;
  

    constexpr List(const T& head, const List<T, N-1>& tail)
      : head_(head), tail_(tail) {};
  
    constexpr List(const List<T, N>& other)
      : head_(other.head_), tail_(other.tail_) {};
  };
  template <class T>
  struct List<T, 0> {
    constexpr List() {}
    constexpr List(const List<T, 0>& other) {};
    static constexpr List<T, 0> empty()
    {
      return List {};
    }
  };


  template <class T, size_t N>
  constexpr List<T, N+1> cons(const T& x, const List<T, N>& xs)
  {  
    return List<T, N+1>(x, xs);
  }

  template <class T, size_t N>
  constexpr T head(const List<T, N>& xs)
  {  
    return xs.head_;
  }

  template <class T, size_t N>
  constexpr List<T, N-1> tail(const List<T, N>& xs)
  {
    return xs.tail_;
  }

  template List<int, 1> cons<int, 0>(const int&, const List<int, 0>&);


  // Type of F(T);
  template <class T, class F>
  using fmap_return_t = decltype (std::declval<F>()(std::declval<T>()));

  // F is the type of a function object that provides a constexpr operator()
  //   function that takes one argument of type T.
  template <class T, size_t N, class F>
  constexpr List<fmap_return_t<T, F>, N> fmap(const F& f, const List<T, N>& xs)
  {
    return cons(f(head(xs)), fmap(f, tail(xs)));
  }
  template <class T, class F>
  constexpr List<fmap_return_t<T, F>, 0> fmap(const F& f, const List<T, 0>& xs)
  {
    return {};
  }

  // F is the type of a function object that provides a constexpr operator()
  //   function that takes an argument of type U and an argument of type T.
  template <class T, size_t N, class F, class U>
  constexpr U foldr(const F& f, const U& init, const List<T, N>& xs)
  {
    return foldr(f, f(init, head(xs)), tail(xs));
  }
  template <class T, class F, class U>
  constexpr U foldr(const F& f, const U& init, const List<T, 0>& xs)
  {
    return init;
  }

}

#endif
