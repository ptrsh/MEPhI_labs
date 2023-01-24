#pragma once
#include <deque>
#include <iostream>
#include <memory>
#include <tuple>

namespace my_vector {
using std::allocator;
using std::construct_at;
using std::destroy_n;
using std::move;
using std::swap;

template <class T, class Allocator = allocator<T>> class vector {
  size_t v_size = 0;
  Allocator alloc = Allocator();
  T *ptr = nullptr;
  void destroy_and_alloc(size_t new_size, size_t prev_size);
  void realloc(size_t new_size, size_t prev_size);

public:
  constexpr vector(size_t size = 0, const T &value = T(),
                   Allocator alloc = Allocator());
  constexpr vector(const vector &other);
  constexpr vector(vector &&other);

  constexpr vector &operator=(const vector &other);

  constexpr vector &operator=(vector &&other);
  constexpr T &at(size_t pos);
  constexpr T &operator[](size_t pos);
  constexpr void push_back(const T &value);
  constexpr void push_back(T &&value);
  constexpr void pop_back();
  constexpr T &front();
  constexpr T &back();
  constexpr size_t size() const;
  ~vector();


  class iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

  private:
    pointer m_ptr;

  public:
    iterator(pointer ptr);

    reference operator*();
    pointer operator->();
    iterator &operator++();
    iterator operator++(int);


    bool operator==(const iterator &a);
    bool operator!=(const iterator &a);
  };

  constexpr iterator begin();
  constexpr iterator end();
};

} 

#include "container.ipp"
