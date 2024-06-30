#include "s21_vector.h"

/*
IMPLEMENTATION FILE
*/
namespace s21 {
template <typename T>
void vector<T>::reserve_more_capacity(size_t size) {
  if (size >= m_size) {
    value_type* buff = new value_type[size];
    for (size_t i = 0; i < m_size; ++i) buff[i] = std::move(arr[i]);
    delete[] arr;
    arr = buff;
    m_capacity = size;
  }
}

// initializer list constructor (allows creating lists with initializer lists,
// see main.cpp)
template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items) {
  arr = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr[i] = *it;
    i++;
  }
  m_size = items.size();
  m_capacity = items.size();
};

template <typename T>
bool vector<T>::empty() {
  return (m_size == 0) ? true : false;
}

template <typename T>
size_t vector<T>::size() {
  return m_size;
}

template <typename T>
size_t vector<T>::max_size() {
  size_t result = pow(2, (64 - log(sizeof(T)) / log(2))) - 1;
  return result;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  reserve_more_capacity(size);
}

template <typename T>
size_t vector<T>::capacity() {
  return m_capacity;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  reserve_more_capacity(m_size);
}

template <typename T>
T vector<T>::at(size_type i) {
  if (m_size <= i) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  return arr[i];
}

template <typename T>
T& vector<T>::operator[](size_type pos) {
  if (m_size <= pos) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  return arr[pos];
}

template <typename T>
const T& vector<T>::front() {
  if (m_size <= 0) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  return arr[0];
}

template <typename T>
const T& vector<T>::back() {
  if (m_size <= 0) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  return arr[m_size - 1];
}

template <typename T>
T* vector<T>::data() {
  return arr;
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return iterator(arr);
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return iterator(arr + m_size);
}

template <class value_type>
typename vector<value_type>::const_iterator vector<value_type>::begin() const {
  return const_iterator(arr);
}

template <class value_type>
typename vector<value_type>::const_iterator vector<value_type>::end() const {
  return const_iterator(arr + m_size);
}

template <typename T>
void vector<T>::clear() {
  m_size = 0;
}

template <typename T>
void vector<T>::push_back(T v) {
  if (m_size == m_capacity) {
    reserve_more_capacity(m_size * 2);
  }
  arr[m_size++] = v;
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_type position = &(*pos) - arr;
  size_type zero = 0;
  if (zero > position || position > m_size) {
    throw std::out_of_range("Index out ot range");
  }
  if (m_size + 1 >= m_capacity) {
    reserve_more_capacity(m_capacity * 2);
  }
  value_type replace = arr[position];
  m_size++;
  arr[position] = value;
  for (size_type i = position + 1; i < m_size; ++i) {
    value_type next = arr[i];
    arr[i] = replace;
    replace = next;
  }
  return arr + position;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type position = &(*pos) - arr;
  size_type zero = 0;
  if (zero > position || position > m_size) {
    throw std::out_of_range("Index out ot range");
  }
  for (size_type i = position + 1; i < m_size; i++) {
    arr[i - 1] = arr[i];
  }
  m_size -= 1;
}

template <typename T>
void vector<T>::pop_back() {
  m_size -= 1;
}

template <typename T>
void vector<T>::swap(vector& other) {
  std::swap(other.m_size, m_size);
  std::swap(other.m_capacity, m_capacity);
  std::swap(other.arr, arr);
}

template class vector<int>;

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(
    vector<T>::const_iterator pos, Args&&... args) {
  for (const auto& iter : {args...}) {
    insert(pos, iter);
  }
  return pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  for (auto iter : {args...}) {
    push_back(iter);
  }
}

}  // namespace s21
