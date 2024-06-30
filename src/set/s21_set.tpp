#include "s21_set.h"

namespace s21 {

template <typename T>
set<T>::set() : AVLTree<T, T>::AVLTree() {}

template <typename T>
set<T>::set(std::initializer_list<typename set<T>::value_type> const& items)
    : AVLTree<value_type, T>::AVLTree() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->insert(*i);
  }
}

template <typename T>
set<T>::set(const set& s) : AVLTree<value_type, T>::AVLTree(s.tree_) {}

template <typename T>
set<T>& set<T>::operator=(set<T>&& s) {
  if (this != &s) {
    tree_ = std::move(s.tree_);
  }
  return *this;
}

template <typename T>
set<T>::~set() {}

template <typename T>
typename set<T>::iterator set<T>::begin() {
  return AVLTree<T, T>::begin();
}

template <typename T>
typename set<T>::iterator set<T>::end() {
  return AVLTree<T, T>::end();
}

template <typename T>
bool set<T>::empty() {
  bool result = false;
  if (AVLTree<T, T>::root_ == nullptr) {
    result = true;
  }
  if (AVLTree<T, T>::root_ == 0) {
    result = true;
  }
  return result;
}

template <typename T>
typename set<T>::size_type set<T>::size() {
  return (tree_.root_ != nullptr) ? tree_.root_->size_ : 0;
}

template <typename T>
typename set<T>::size_type set<T>::max_size() {
  return pow(2, (64 - log(sizeof(T)) / log(2))) - 1;
}

template <typename T>  //
void set<T>::clear() {
  if (this->tree_.get_root()) {
    this->tree_.clear_node(this->tree_.get_root());
    this->tree_.root_ = nullptr;
  }
}

template <typename T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(const T& value) {
  std::pair<typename set<T>::iterator, bool> result;
  this->tree_.insert(value, value);
  if (this->tree_.get_inserted()) {
    result = std::pair<typename set<T>::iterator, bool>(find(value), true);
  } else {
    result = std::pair<typename set<T>::iterator, bool>(find(value), false);
  }
  return result;
}

template <typename T>
void set<T>::erase(typename set<T>::iterator pos) {
  if (pos != nullptr) {
    tree_.root_ =
        AVLTree<T, T>::remove_node(AVLTree<T, T>::root_, pos.iterator_->key_);
  }
  tree_.root_->size_--;
}

template <typename T>
void set<T>::swap(set& other) {
  tree_.Swap(other.tree_);
}

template <typename T>
void set<T>::merge(set<T>& other) {
  if (this != &other) {
    for (auto i = other.begin(); i != other.end(); i++) {
      insert(*i);
    }
  }
  other.clear();
}

template <typename T>
bool set<T>::contains(const T& key) {
  return tree_.search_for_set(key) != nullptr;
}

template <typename T>
typename set<T>::iterator set<T>::find(const T& key) {
  return iterator(tree_.search_for_set(key));
}

template <typename T>
const AVLTree<typename set<T>::value_type, T>& set<T>::get_tree() const {
  return tree_;
}

}  // namespace s21
