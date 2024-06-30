#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <math.h>

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <class T>
class VectorIterator;

template <class T>
class VectorConstIterator;

template <class T>
class vector {
  // private attributes
 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;
  // public attribures
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  using size_type = size_t;

  // private method
 private:
  void reserve_more_capacity(size_type size);
  void free_vector() {
    delete[] arr;
    arr = nullptr;
    m_size = 0;
    m_capacity = 0;
  };

  // public methods
 public:
  vector() : m_size(0U), m_capacity(0U), arr(nullptr) {}

  explicit vector(size_type n) : vector() {
    m_size = n;
    m_capacity = n;
    arr = n ? new T[n] : nullptr;
  }

  vector(std::initializer_list<value_type> const &items);

  vector(const vector &v)
      : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr){};

  vector(vector &&v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {
    v.arr = nullptr;
    v.m_size = 0;
  }

  ~vector() { free_vector(); }

  vector &operator=(vector &&v) {
    if (this != &v) {
      free_vector();
      m_size = v.m_size;
      m_capacity = v.m_capacity;
      arr = v.arr;
      v.arr = nullptr;
      v.m_capacity = 0;
      v.m_size = 0;
    }
    return *this;
  };

  // методы для доступа к элементам класса
  value_type at(size_type i);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  //  методы для итерирования по элементам класса
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // методы для доступа к информации о наполнении контейнера
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // методы для изменения контейнера
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(value_type v);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);
};

template <class T>
class VectorIterator {
  friend class vector<T>;
  friend class VectorConstIterator<T>;

  using value_type = T;
  using pointer = T *;
  using reference = T &;

 public:
  VectorIterator() { ptr_ = nullptr; }
  VectorIterator(pointer ptr) { ptr_ = ptr; }

  value_type &operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  VectorIterator &operator++() {
    ptr_++;
    return *this;
  }

  VectorIterator &operator--() {
    ptr_--;
    return *this;
  }

  VectorIterator operator++(int) {
    VectorIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  VectorIterator operator--(int) {
    VectorIterator tmp = *this;
    --(*this);
    return tmp;
  }

  VectorIterator operator+(const size_t value) {
    VectorIterator tmp(this->ptr_ + value);
    return tmp;
  }

  VectorIterator operator-(const size_t value) {
    VectorIterator tmp(this->ptr_ - value);
    return tmp;
  }

  bool operator==(const VectorIterator &other) { return ptr_ == other.ptr_; }

  bool operator!=(const VectorIterator &other) { return ptr_ != other.ptr_; }

  operator VectorConstIterator<T>() const {
    return VectorConstIterator<T>(ptr_);
  }

 private:
  pointer ptr_;
};

template <class T>
class VectorConstIterator {
  friend class vector<T>;
  friend class VectorIterator<T>;

  using value_type = T;
  using pointer = T *;
  using reference = T &;

 public:
  VectorConstIterator() { ptr_ = nullptr; };
  VectorConstIterator(pointer ptr) { ptr_ = ptr; };
  value_type operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  VectorConstIterator &operator++() {
    ptr_++;
    return *this;
  }

  VectorConstIterator &operator--() {
    ptr_--;
    return *this;
  }

  VectorConstIterator operator++(int) {
    VectorConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  VectorConstIterator operator--(int) {
    VectorConstIterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const VectorConstIterator &other) {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const VectorConstIterator &other) {
    return ptr_ != other.ptr_;
  }

  operator VectorIterator<T>() const { return VectorIterator<T>(ptr_); }

 private:
  pointer ptr_;
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  // S21_VECTOR_H
