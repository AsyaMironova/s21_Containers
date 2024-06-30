#ifndef S21_AVLTREE_H
#define S21_AVLTREE_H

#include <iostream>

template <typename Key, typename T>
class AVLTree {
 public:
  struct AVLTreeNode;

 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
    friend class AVLTree<Key, T>;

   public:
    Iterator();
    Iterator(AVLTreeNode *node, AVLTreeNode *past_node = nullptr);
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    reference operator*();
    bool operator==(const iterator &it);
    AVLTreeNode &operator=(AVLTreeNode &other) noexcept;
    friend class AVLTree<Key, T>;
    bool operator!=(const iterator &it);
    value_type &return_value();

   public:
    AVLTreeNode *iterator_;
    AVLTreeNode *past_iterator_;
    AVLTreeNode *move_forward(AVLTreeNode *node);
    AVLTreeNode *move_back(AVLTreeNode *node);
  };
  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    const_reference operator*() const { return Iterator::operator*(); };
  };

  AVLTree();
  ~AVLTree();
  AVLTree(const AVLTree &other);
  AVLTree(std::initializer_list<value_type> const &items);
  AVLTreeNode *copy_tree(AVLTreeNode *node);
  AVLTree &operator=(AVLTree &&other) noexcept;
  AVLTree &operator=(const AVLTree &other);
  iterator begin();
  iterator end();
  void clear();
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_node(AVLTreeNode *node);
  AVLTreeNode *remove_node(AVLTreeNode *node, Key key);
  AVLTreeNode *get_root();
  AVLTreeNode *search_for_set(Key key);
  AVLTreeNode *search_node(AVLTreeNode *node, Key key);
  bool get_inserted();
  void Swap(AVLTree &other);
  size_type size(AVLTreeNode *node);
  size_type max_size();
  void upper_size();

 public:
  iterator find_key(const Key &key);
  struct AVLTreeNode {
    Key key_;
    value_type value_;
    AVLTreeNode *left_ = nullptr;
    AVLTreeNode *right_ = nullptr;
    AVLTreeNode *parent_ = nullptr;
    int height_ = 0;
    size_type size_ = 0;
    AVLTreeNode(Key key, value_type value);
    AVLTreeNode(Key key, value_type value, AVLTreeNode *parent);
    friend class AVLTree<Key, T>;
  };
  bool inserted_ = false;
  AVLTreeNode *root_;

  void clear_node(AVLTreeNode *node);

  void swap_value(AVLTreeNode *a, AVLTreeNode *b);
  void right_rotation(AVLTreeNode *node);
  void left_rotation(AVLTreeNode *node);
  void balance(AVLTreeNode *node);
  int balance_factor(AVLTreeNode *node);
  int height(AVLTreeNode *node);
  void fix_height(AVLTreeNode *node);

  static AVLTreeNode *min_node(AVLTreeNode *node);
  static AVLTreeNode *max_node(AVLTreeNode *node);

  bool insert_with_balance(AVLTreeNode *node, const Key &key,
                           const value_type &value);
  AVLTreeNode *recurs_find(AVLTreeNode *node, const Key &key);
};

#include "s21_AVLTree.tpp"

#endif  // S21_AVLTREE_H