#ifndef S21_MAP_H
#define S21_MAP_H

#include <math.h>

#include <iostream>

#include "../AVLTree/s21_AVLTree.h"

namespace s21 {
template <class Key, class T>
class map : AVLTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename AVLTree<Key, T>::Iterator;
  using const_iterator = typename AVLTree<Key, T>::ConstIterator;
  using size_type = size_t;

  // Функции-члены карты
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m) = default;
  ~map();
  map<Key, T> operator=(map&& m);

  // Доступ к элементу карты
  mapped_type& at(const Key& key);
  mapped_type& operator[](const Key& key);

  // Итераторы карт
  iterator begin();
  iterator end();

  // Вместимость карты
  bool empty();
  size_type size();
  size_type max_size();

  // Модификаторы карт
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  // Поиск по карте
  bool contains(const Key& key);
  const AVLTree<value_type, T>& get_tree() const;

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  AVLTree<value_type, T> tree_;
  mapped_type& operatorHelper(const Key& key, int flag);
  bool check_duplicates(const value_type& value);
};
}  // namespace s21

#include "s21_map.tpp"

#endif  // S21_MAP_H