#include "s21_multiset.h"

namespace s21 {
template <typename Key>
multiset<Key>::multiset() : AVLTree<Key, Key>::AVLTree() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    tree_.insert(*i, *i);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset& ms) : AVLTree<Key, Key>::AVLTree(ms.tree_) {
}
/*
template <typename Key>
multiset<Key>::multiset(multiset&& ms) {
  tree_ = std::move(ms.tree_);
}
*/
template <typename Key>
multiset<Key>::~multiset() {}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& ms) {
  if (this != &ms) {
    tree_ = std::move(ms.tree_);
  }
  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return AVLTree<Key, Key>::begin() == 0 ? tree_.begin() : AVLTree<Key, Key>::begin();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return AVLTree<Key, Key>::end() != 0 ? tree_.end() : AVLTree<Key, Key>::end();
}

template <typename Key>
bool multiset<Key>::empty() {
  return tree_.get_root() == nullptr;
}

template <typename Key>
size_t multiset<Key>::size() {
  size_t return_size = 0;
  if (tree_.root_ != nullptr) {
    return_size = tree_.root_->size_;
  } else if (AVLTree<Key, Key>::root_ != nullptr) {
    return_size = AVLTree<Key, Key>::root_->size_;
  }
  return return_size;
}

template <typename Key>
size_t multiset<Key>::max_size() {
  return (tree_.max_size() * 1.4);
}

template <typename Key>
void multiset<Key>::clear() {
  return tree_.clear();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(const_reference value) {
  std::pair<iterator, bool> iter = tree_.insert(value, value);
  return iter.first;
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  if (tree_.root_ == nullptr) {
    return;
  }
  tree_.root_ = tree_.remove_node(tree_.root_, *pos);
  tree_.root_->size_--;
}

template <typename Key>
void multiset<Key>::swap(multiset<Key>& other) {
  tree_.Swap(other.tree_);
}

template <typename Key>
void multiset<Key>::merge(multiset<Key>& other) {
  iterator other_iterator = other.begin();
  while (other_iterator != other.end()) {
    tree_.insert(other_iterator.iterator_->key_, other_iterator.iterator_->value_);
    other.erase(other_iterator);
    other_iterator++;
  }
  tree_.root_->size_ += other.tree_.root_->size_;
}

template <typename Key>
size_t multiset<Key>::count(const Key& key) {
  size_t count_match = 0;
  for (iterator iter = find(key); iter != end() && iter == key; iter++) {
    count_match++;
  }
  return count_match;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
  return tree_.find(key);
}

template <typename Key>
bool multiset<Key>::contains(const Key& key) {
  return tree_.search_for_set(key) != nullptr;
}

template <typename Key>
typename std::pair<typename multiset<Key>::iterator,
                   typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return {lower_bound(key), upper_bound(key)};
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  typename AVLTree<Key, Key>::AVLTreeNode to_return = tree_.root_;
  typename AVLTree<Key, Key>::AVLTreeNode node = tree_.root_;
  while (node != nullptr) {
    if (key < node.key_) {
      to_return = node;
      node = node.left_;
    } else if (key > node.key_) {
      node = node.right_;
    } else {
      to_return = node;
    }
  }
  return iterator(to_return);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  typename AVLTree<Key, Key>::AVLTreeNode to_return = tree_.root_;
  typename AVLTree<Key, Key>::AVLTreeNode node = tree_.root_;
  while (node != nullptr) {
    if (key < node.key_) {
      to_return = node;
      node = node.left_;
    } else if (key > node.key_) {
      node = node.right_;
    }
  }
  return iterator(to_return);
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename multiset<Key>::iterator,bool>> multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> to_return;
  for (const auto& iter : {args ...}) {
    to_return = insert(iter);
  }
  return to_return;
}

}  // namespace s21