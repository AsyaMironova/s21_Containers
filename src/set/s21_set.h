#ifndef S21_SET_H
#define S21_SET_H

#include <math.h>

#include <iostream>

#include "../AVLTree/s21_AVLTree.h"

namespace s21 {
template <class T>
class set : AVLTree<T, T> {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using iterator = typename AVLTree<value_type, T>::Iterator;
  using const_iterator = typename AVLTree<value_type, T>::ConstIterator;

  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s) = default;
  ~set();
  set<T>& operator=(set&& s);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  iterator find(const T& key);
  bool contains(const T& key);
  const AVLTree<T, T>& get_tree() const;

 private:
  AVLTree<T, T> tree_;
};
}  // namespace s21

#include "s21_set.tpp"

#endif  // S21_SET_H