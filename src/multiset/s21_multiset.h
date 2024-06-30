#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <iostream>

#include "../AVLTree/s21_AVLTree.h"

namespace s21 {
template <class Key>
class multiset : AVLTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using referense = value_type&;
  using const_reference = const value_type&;
  using iterator = typename AVLTree<Key, Key>::Iterator;
  using const_iterator = typename AVLTree<Key, Key>::ConstIterator;
  using size_type = size_t;

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms) = default;
  ~multiset();
  multiset& operator=(multiset&& ms);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  size_type count(const Key& key);
  iterator find(const Key& key);
  bool contains(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

  template <typename... Args>
  std::vector<std::pair<iterator,bool>> insert_many(Args&&... args);

 private:
  AVLTree<Key, Key> tree_;
};
};  // namespace s21

#include "s21_multiset.tpp"

#endif  // S21_MULTISET_H