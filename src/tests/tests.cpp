#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(array_test, constructor_default) {
  const size_t size = 0;
  s21::array<int, size> s21_array;
  std::array<int, size> std_array;
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(array_test, constructor_with_no_data) {
  const size_t size = 5;
  s21::array<int, size> s21_array;
  std::array<int, size> std_array;
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(array_test, constructor_with_data) {
  const size_t size = 5;
  s21::array<int, size> s21_array = {1, 2, 3, 4, 5};
  std::array<int, size> std_array = {1, 2, 3, 4, 5};
  EXPECT_EQ(s21_array.empty(), std_array.empty());
  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.max_size(), s21_array.max_size());
}

TEST(array_test, copy_constructor) {
  const size_t size = 5;
  s21::array<int, size> s21_array{1, 2, 3, 4, 5};
  std::array<int, size> std_array{1, 2, 3, 4, 5};
  EXPECT_EQ(s21_array.size(), std_array.size());
  auto s21_iterator = s21_array.begin();
  auto std_iterator = std_array.begin();
  bool result = true;
  for (size_t i = 0; i < s21_array.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(array_test, funcTest) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> a2 = {1, 2, 3, 2, 1};
  a1.swap(a2);
  ASSERT_EQ(a2.back(), 5);
  ASSERT_EQ(a1.back(), 1);
  a1.fill(2);
  ASSERT_EQ(a1.back(), 2);
  ASSERT_EQ(a1.front(), 2);
}

TEST(array_test, elaccessorTest) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  EXPECT_TRUE(a.front() == 1);
  EXPECT_TRUE(a.back() == 5);
  EXPECT_TRUE(a.at(2) == 3);
  EXPECT_TRUE(a[1] == 2);
  s21::ArrayIterator f = a.data();
  EXPECT_TRUE(*f == 1);
}

TEST(list_test, constructor_default) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list_test, constructor_with_size) {
  s21::list<int> s21_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(list_test, constructor_with_size_throw) {}

TEST(list_test, init_constructor) {
  s21::list<int> s21_list{1, 2, 3, 4, 5, 6};
  std::list<int> std_list{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, copy_constructor) {
  s21::list<int> s21_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  s21::list<int> s21_copy(s21_list);
  std::list<int> std_copy(std_list);
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  auto s21_iterator = s21_copy.begin();
  auto std_iterator = std_copy.begin();
  bool result = true;
  for (size_t i = 0; i < s21_copy.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, copy_constructor_empty) {
  s21::list<int> s21_list;
  s21::list<int> s21_copy(s21_list);
  std::list<int> std_list;
  std::list<int> std_copy(std_list);
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  auto s21_iterator = s21_copy.begin();
  auto std_iterator = std_copy.begin();
  bool result = true;
  for (size_t i = 0; i < s21_copy.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, move_constructor_empty) {
  s21::list<int> s21_list;
  s21::list<int> s21_copy(s21_list);
  s21::list<int> s21_move(std::move(s21_list));
  std::list<int> std_list;
  std::list<int> std_copy(std_list);
  std::list<int> std_move(std::move(std_list));
  EXPECT_EQ(s21_move.size(), std_move.size());
  auto s21_iterator = s21_move.begin();
  auto std_iterator = std_move.begin();
  bool result = true;
  for (size_t i = 0; i < s21_move.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, front) {
  s21::list<int> s21_list{462, 32, 3, 4, 5};
  std::list<int> std_list{462, 32, 3, 4, 5};
  EXPECT_EQ(s21_list.front(), std_list.front());
}

TEST(list_test, back) {
  s21::list<int> s21_list{462, 32, 3, 4, 5};
  std::list<int> std_list{462, 32, 3, 4, 5};
  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(list_test, begin) {
  s21::list<int> s21_list{5, 6, 2};
  std::list<int> std_list{5, 6, 2};
  EXPECT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(list_test, begin_throw) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(*s21_list.begin(), 0);
}

TEST(list_test, end) {
  s21::list<int> s21_list{5, 6, 2};
  std::list<int> std_list{5, 6, 2};
  EXPECT_EQ(*s21_list.end(), *std_list.end());
}

TEST(list_test, end_empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(*s21_list.end(), *std_list.end());
}

TEST(list_test, empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list_test, not_empty) {
  s21::list<int> s21_list{1, 22};
  std::list<int> std_list{1, 22};
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list_test, clear) {
  s21::list<int> s21_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  s21_list.clear();
  std_list.clear();
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, insert_begin) {
  s21::list<int> s21_list{1, 9999, 20000};
  s21_list.insert(s21_list.begin(), 5);
  std::list<int> std_list{1, 9999, 20000};
  std_list.insert(std_list.begin(), 5);
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, insert_end) {
  s21::list<int> s21_list{1, 2, 3};
  s21_list.insert(s21_list.end(), 5);
  std::list<int> std_list{1, 2, 3};
  std_list.insert(std_list.end(), 5);
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, insert_random) {
  s21::list<int> s21_list{1, 2, 3};
  s21_list.insert(s21_list[2], 5);
  std::list<int> std_list{1, 2, 3};
  auto std_temp_iterator = std_list.begin();
  std_temp_iterator++;
  std_temp_iterator++;
  std_list.insert(std_temp_iterator, 5);
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, insert_empty) {
  s21::list<int> s21_list;
  s21_list.insert(s21_list.begin(), 5);
  std::list<int> std_list;
  std_list.insert(std_list.begin(), 5);
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, erase_begin) {
  s21::list<int> s21_list{1, 2, 3};
  s21_list.erase(s21_list.begin());
  std::list<int> std_list{1, 2, 3};
  std_list.erase(std_list.begin());
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, erase_throw) {
  s21::list<int> s21_list{1, 2, 3};
  EXPECT_THROW(s21_list.erase(s21_list.end()), std::invalid_argument);
}

TEST(list_test, erase_end) {
  s21::list<int> s21_list{1, 2, 3};
  s21_list.erase(--s21_list.end());
  std::list<int> std_list{1, 2, 3};
  std_list.erase(std_list.end().operator--());
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, erase_throw_end) {
  s21::list<int> s21_list;
  EXPECT_THROW(s21_list.erase(s21_list.end()--), std::invalid_argument);
}

TEST(list_test, erase_enother_end) {
  s21::list<int> s21_list(5);
  s21_list.erase(--s21_list.end());
  std::list<int> std_list(5);
  std_list.erase(std_list.end().operator--());
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, merge) {
  s21::list<int> s21_this{1, 46, 234};
  s21::list<int> s21_other{50, 357, 6028};
  s21_this.merge(s21_other);
  std::list<int> std_this{1, 46, 234};
  std::list<int> std_other{50, 357, 6028};
  std_this.merge(std_other);
  auto s21_iterator = s21_this.begin();
  auto std_iterator = std_this.begin();
  bool result = true;
  EXPECT_EQ(s21_this.size(), std_this.size());
  for (size_t i = 0; i < s21_this.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, merge_different_size) {
  s21::list<int> s21_this{1, 2, 234};
  s21::list<int> s21_other{7584, 154, 453, 9876};
  s21_this.merge(s21_other);
  std::list<int> std_this{1, 2, 234};
  std::list<int> std_other{7584, 154, 453, 9876};
  std_this.merge(std_other);
  auto s21_iterator = s21_this.begin();
  auto std_iterator = std_this.begin();
  bool result = true;
  EXPECT_EQ(s21_this.size(), std_this.size());
  for (size_t i = 0; i < s21_this.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, merge_with_this_empty) {
  s21::list<int> s21_this;
  s21::list<int> s21_other{7584, 154, 453, 9876};
  s21_this.merge(s21_other);
  std::list<int> std_this;
  std::list<int> std_other{7584, 154, 453, 9876};
  std_this.merge(std_other);
  auto s21_iterator = s21_this.begin();
  auto std_iterator = std_this.begin();
  bool result = true;
  EXPECT_EQ(s21_this.size(), std_this.size());
  for (size_t i = 0; i < s21_this.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, merge_with_other_empty) {
  s21::list<int> s21_this{7584, 154, 453, 9876};
  s21::list<int> s21_other;
  s21_this.merge(s21_other);
  std::list<int> std_this{7584, 154, 453, 9876};
  std::list<int> std_other;
  std_this.merge(std_other);
  auto s21_iterator = s21_this.begin();
  auto std_iterator = std_this.begin();
  bool result = true;
  EXPECT_EQ(s21_this.size(), std_this.size());
  for (size_t i = 0; i < s21_this.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, merge_empty) {
  s21::list<int> s21_this;
  s21::list<int> s21_other;
  s21_this.merge(s21_other);
  std::list<int> std_this;
  std::list<int> std_other;
  std_this.merge(std_other);
  auto s21_iterator = s21_this.begin();
  auto std_iterator = std_this.begin();
  bool result = true;
  EXPECT_EQ(s21_this.size(), std_this.size());
  for (size_t i = 0; i < s21_this.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, splice) {
  s21::list<int> s21_this{1, 2, 234};
  s21::list<int> s21_other{7584, 154, 453, 9876};
  s21_this.splice(s21_this.begin(), s21_other);
  std::list<int> std_this{1, 2, 234};
  std::list<int> std_other{7584, 154, 453, 9876};
  std_this.splice(std_this.begin(), std_other);
  auto s21_iterator = s21_this.begin();
  auto std_iterator = std_this.begin();
  bool result = true;
  EXPECT_EQ(s21_this.size(), std_this.size());
  for (size_t i = 0; i < s21_this.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, splice_this_empty) {
  s21::list<int> s21_this;
  s21::list<int> s21_other{7584, 154, 453, 9876};
  s21_this.splice(s21_this.begin(), s21_other);
  std::list<int> std_this;
  std::list<int> std_other{7584, 154, 453, 9876};
  std_this.splice(std_this.begin(), std_other);
  auto s21_iterator = s21_this.begin();
  auto std_iterator = std_this.begin();
  bool result = true;
  EXPECT_EQ(s21_this.size(), std_this.size());
  for (size_t i = 0; i < s21_this.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, splice_other_empty) {
  s21::list<int> s21_this{1, 2, 234};
  s21::list<int> s21_other;
  s21_this.splice(s21_this.begin(), s21_other);
  std::list<int> std_this{1, 2, 234};
  std::list<int> std_other;
  std_this.splice(std_this.begin(), std_other);
  auto s21_iterator = s21_this.begin();
  auto std_iterator = std_this.begin();
  bool result = true;
  EXPECT_EQ(s21_this.size(), std_this.size());
  for (size_t i = 0; i < s21_this.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, splice_empty) {
  s21::list<int> s21_this;
  s21::list<int> s21_other;
  s21_this.splice(s21_this.begin(), s21_other);
  std::list<int> std_this;
  std::list<int> std_other;
  std_this.splice(std_this.begin(), std_other);
  auto s21_iterator = s21_this.begin();
  auto std_iterator = std_this.begin();
  bool result = true;
  EXPECT_EQ(s21_this.size(), std_this.size());
  for (size_t i = 0; i < s21_this.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, reverse) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5, 6};
  std::list<int> std_list = {1, 2, 3, 4, 5, 6};
  s21_list.reverse();
  std_list.reverse();
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, reverse_empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21_list.reverse();
  std_list.reverse();
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, unique) {
  s21::list<int> s21_list{1, 1, 1, 2, 3, 4, 4, 5, 3, 3, 2};
  std::list<int> std_list{1, 1, 1, 2, 3, 4, 4, 5, 3, 3, 2};
  s21_list.unique();
  std_list.unique();
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(list_test, sort) {
  s21::list<int> s21_list{4, 2, 5, 1, 9, 10, 25, 392, 5};
  std::list<int> std_list{4, 2, 5, 1, 9, 10, 25, 392, 5};
  s21_list.sort();
  std_list.sort();
  auto s21_iterator = s21_list.begin();
  auto std_iterator = std_list.begin();
  bool result = true;
  for (size_t i = 0; i < s21_list.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(MapTest, Full_funcTest) {
  s21::map<int, std::string> m;
  EXPECT_EQ(int(m.size()), 0);
  EXPECT_TRUE(m.empty());
}

TEST(mapConstructorTest, CopyConstructor) {
  s21::map<int, std::string> s21_map{{1, "one"}, {2, "two"}, {3, "tree"}};
  s21::map<int, std::string> s21_copy{{1, "one"}, {2, "two"}, {3, "tree"}};
  std::map<int, std::string> std_map{{1, "one"}, {2, "two"}, {3, "tree"}};
  std::map<int, std::string> std_copy{{1, "one"}, {2, "two"}, {3, "tree"}};
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_FALSE(s21_copy.empty());
}

TEST(mapTest, InsertKeyValue) {
  s21::map<int, std::string> map;
  map.insert(1, "one");
  EXPECT_EQ(int(map.size()), 1);
  EXPECT_EQ(map.at(1), "one");
  map.insert(2, "two");
  EXPECT_EQ(int(map.size()), 2);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
}

TEST(mapTest, MaxSize) {
  s21::map<int, std::string> map;
  std::map<int, std::string> map1;
  EXPECT_GT(map.max_size(), map1.max_size());
}

TEST(mapTest, Erase) {
  s21::map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert({5, "five"});
  auto it1 = map.begin()++;
  map.erase(it1);
  EXPECT_EQ(int(map.size()), 3);
  EXPECT_TRUE(map.contains(1));
}

TEST(mapTest, Swap) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.swap(map2);

  EXPECT_EQ(int(map1.size()), 2);
  EXPECT_EQ(int(map2.size()), 2);
}

TEST(multiset_test, constructor_default) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

TEST(multiset_test, init_constructor) {
  s21::multiset<int> s21_multiset{4, 1, 5, 3};
  std::multiset<int> std_multiset{4, 1, 5, 3};
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  auto s21_iterator = s21_multiset.begin();
  auto std_iterator = std_multiset.begin();
  bool result = true;
  for (size_t i = 0; i < s21_multiset.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(multiset_test, copy_constructor) {
  s21::multiset<int> s21_multiset{6, 2};
  std::multiset<int> std_multiset{6, 2};
  s21::multiset<int> s21_copy(s21_multiset);
  std::multiset<int> std_copy(std_multiset);
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  auto s21_iterator = s21_copy.begin();
  auto std_iterator = std_copy.begin();
  bool result = true;
  for (size_t i = 0; i < s21_copy.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
  }
  EXPECT_TRUE(result);
}

TEST(multiset_test, copy_constructor_empty) {
  s21::multiset<int> s21_multiset;
  s21::multiset<int> s21_copy(s21_multiset);
  std::multiset<int> std_multiset;
  std::multiset<int> std_copy(std_multiset);
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  auto s21_iterator = s21_copy.begin();
  auto std_iterator = std_copy.begin();
  bool result = true;
  for (size_t i = 0; i < s21_copy.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(multiset_test, move_constructor) {
  s21::multiset<int> s21_multiset{1, 2, 3};
  s21::multiset<int> s21_copy(s21_multiset);
  s21::multiset<int> s21_move(std::move(s21_multiset));
  std::multiset<int> std_multiset{1, 2, 3};
  std::multiset<int> std_copy(std_multiset);
  std::multiset<int> std_move(std::move(std_multiset));
  EXPECT_EQ(s21_move.size(), std_move.size());
  auto s21_iterator = s21_move.begin();
  auto std_iterator = std_move.begin();
  bool result = true;
  for (size_t i = 0; i < s21_move.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(multiset_test, move_constructor_empty) {
  s21::multiset<int> s21_multiset;
  s21::multiset<int> s21_copy(s21_multiset);
  s21::multiset<int> s21_move(std::move(s21_multiset));
  std::multiset<int> std_multiset;
  std::multiset<int> std_copy(std_multiset);
  std::multiset<int> std_move(std::move(std_multiset));
  EXPECT_EQ(s21_move.size(), std_move.size());
  auto s21_iterator = s21_move.begin();
  auto std_iterator = std_move.begin();
  bool result = true;
  for (size_t i = 0; i < s21_move.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(multiset_test, begin) {
  s21::multiset<int> s21_multiset{5, 6, 2};
  std::multiset<int> std_multiset{5, 6, 2};
  EXPECT_EQ(*s21_multiset.begin(), *std_multiset.begin());
}

TEST(multiset_test, end_empty) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  EXPECT_EQ(*s21_multiset.end(), *std_multiset.end());
}

TEST(multiset_test, empty) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

TEST(multiset_test, not_empty) {
  s21::multiset<int> s21_multiset{1, 22};
  std::multiset<int> std_multiset{1, 22};
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

TEST(multiset_test, max_size) {
  s21::multiset<double> s21_multiset{1};
  std::multiset<double> std_multiset{1};
  // EXPECT_EQ(s21_multiset.max_size(), std_multiset.max_size());
}

TEST(multiset_test, clear) {
  s21::multiset<int> s21_multiset{1, 2, 3, 4, 5};
  std::multiset<int> std_multiset{1, 2, 3, 4, 5};
  s21_multiset.clear();
  std_multiset.clear();
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  auto s21_iterator = s21_multiset.begin();
  auto std_iterator = std_multiset.begin();
  bool result = true;
  for (size_t i = 0; i < s21_multiset.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(multiset_test, insert) {
  s21::multiset<int> s21_multiset{1, 9999, 20000};
  s21_multiset.insert(5);
  std::multiset<int> std_multiset{1, 9999, 20000};
  std_multiset.insert(5);
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  auto s21_iterator = s21_multiset.begin();
  auto std_iterator = std_multiset.begin();
  bool result = true;
  for (size_t i = 0; i < s21_multiset.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(multiset_test, insert_empty) {
  s21::multiset<int> s21_multiset;
  s21_multiset.insert(5);
  std::multiset<int> std_multiset;
  std_multiset.insert(5);
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  auto s21_iterator = s21_multiset.begin();
  auto std_iterator = std_multiset.begin();
  bool result = true;
  for (size_t i = 0; i < s21_multiset.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(multiset_test, erase_begin) {
  s21::multiset<int> s21_multiset{1, 2, 3};
  s21_multiset.erase(s21_multiset.begin());
  std::multiset<int> std_multiset{1, 2, 3};
  std_multiset.erase(std_multiset.begin());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  auto s21_iterator = s21_multiset.begin();
  auto std_iterator = std_multiset.begin();
  bool result = true;
  for (size_t i = 0; i < s21_multiset.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}

TEST(multiset_test, erase_end) {
  s21::multiset<int> s21_multiset{1, 2, 3};
  auto temp = s21_multiset.begin();
  while (*temp != *s21_multiset.end()) {
    *temp++;
  }
  s21_multiset.erase(temp);
  std::multiset<int> std_multiset{1, 2, 3};
  std_multiset.erase(std_multiset.end().operator--());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  auto s21_iterator = s21_multiset.begin();
  auto std_iterator = std_multiset.begin();
  bool result = true;
  for (size_t i = 0; i < s21_multiset.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}
/*
TEST(multiset_test, merge) {
  s21::multiset<int> s21_this{1, 46, 234};
  s21::multiset<int> s21_other{50, 357, 6028};
  s21_this.merge(s21_other);
  std::multiset<int> std_this{1, 46, 234};
  std::multiset<int> std_other{50, 357, 6028};
  std_this.merge(std_other);
  auto s21_iterator = s21_this.begin();
  auto std_iterator = std_this.begin();
  bool result = true;
  EXPECT_EQ(s21_this.size(), std_this.size());
  for (size_t i = 0; i < s21_this.size(); i++) {
    if (*s21_iterator != *std_iterator) {
      result = false;
      break;
    }
    s21_iterator++;
    std_iterator++;
  }
  EXPECT_TRUE(result);
}
*/

TEST(queue_test, constructor) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_TRUE(s21_queue.empty());
  bool result = true;
  while (!s21_queue.empty()) {
    if (s21_queue.front() != std_queue.front()) {
      result = false;
      break;
    }
    s21_queue.pop();
    std_queue.pop();
  }
  EXPECT_TRUE(result);
}

TEST(queue_test, constructor_init) {
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  s21::queue<int> s21_queue{init_list};
  std::queue<int> std_queue{init_list};
  bool result = true;
  while (!s21_queue.empty()) {
    if (s21_queue.front() != std_queue.front()) {
      result = false;
      break;
    }
    s21_queue.pop();
    std_queue.pop();
  }
  EXPECT_TRUE(result);
}

TEST(queue_test, copy) {
  std::initializer_list<int> init_list = {1, 2, 3, 7, 9};
  s21::queue<int> s21_queue{init_list};
  s21::queue<int> s21_queue_copy(s21_queue);
  std::queue<int> std_queue{init_list};
  std::queue<int> std_queue_copy(std_queue);
  bool result = true;
  while (!s21_queue_copy.empty()) {
    if (s21_queue_copy.front() != std_queue_copy.front()) {
      result = false;
      break;
    }
    s21_queue_copy.pop();
    std_queue_copy.pop();
  }
  EXPECT_TRUE(result);
}

TEST(queue_test, copy_empty) {
  s21::queue<int> s21_queue;
  s21::queue<int> s21_queue_copy(s21_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  bool result = true;
  while (!s21_queue_copy.empty()) {
    if (s21_queue_copy.front() != std_queue_copy.front()) {
      result = false;
      break;
    }
    s21_queue_copy.pop();
    std_queue_copy.pop();
  }
  EXPECT_TRUE(result);
}

TEST(queue_test, move) {
  std::initializer_list<int> init_list = {1, 2, 3, 7, 20};
  s21::queue<int> s21_queue{init_list};
  s21::queue<int> s21_queue_move(std::move(s21_queue));
  std::queue<int> std_queue{init_list};
  std::queue<int> std_queue_move(std::move(std_queue));
  bool result = true;
  while (!s21_queue_move.empty()) {
    if (s21_queue_move.front() != std_queue_move.front()) {
      result = false;
      break;
    }
    s21_queue_move.pop();
    std_queue_move.pop();
  }
  EXPECT_TRUE(result);
}

TEST(queue_test, move_empty) {
  s21::queue<int> s21_queue;
  s21::queue<int> s21_queue_move(std::move(s21_queue));
  std::queue<int> std_queue;
  std::queue<int> std_queue_move(std::move(std_queue));
  bool result = true;
  while (!s21_queue_move.empty()) {
    if (s21_queue_move.front() != std_queue_move.front()) {
      result = false;
      break;
    }
    s21_queue_move.pop();
    std_queue_move.pop();
  }
  EXPECT_TRUE(result);
}

TEST(queue_test, move_assign_operator) {
  std::initializer_list<int> init_list = {1, 2, 3, 7, 20};
  s21::queue<int> s21_queue{init_list};
  s21::queue<int> s21_queue_move = std::move(s21_queue);
  std::queue<int> std_queue{init_list};
  std::queue<int> std_queue_move = std::move(std_queue);
  bool result = true;
  while (!s21_queue_move.empty()) {
    if (s21_queue_move.front() != std_queue_move.front()) {
      result = false;
      break;
    }
    s21_queue_move.pop();
    std_queue_move.pop();
  }
  EXPECT_TRUE(result);
}

TEST(queue_test, front) {
  std::initializer_list<int> init_list = {99, 1, 3, 7, 20};
  s21::queue<int> s21_queue{init_list};
  std::queue<int> std_queue{init_list};
  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(queue_test, back) {
  std::initializer_list<int> init_list = {99, 1, 3, 5, 4, 7, 99};
  s21::queue<int> s21_queue{init_list};
  std::queue<int> std_queue{init_list};
  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(queue_test, empty) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
  s21_queue.push(2);
  std_queue.push(2);
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(queue_test, scalb) {
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::queue<int> s21_queue{init_list};
  std::queue<int> std_queue{init_list};
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(queue_test, push) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(3);
  s21_queue.push(4);
  std_queue.push(3);
  std_queue.push(4);
  bool result = true;
  while (!s21_queue.empty()) {
    if (s21_queue.front() != std_queue.front()) {
      result = false;
      break;
    }
    s21_queue.pop();
    std_queue.pop();
  }
  EXPECT_TRUE(result);
}

TEST(queue_test, pop) {
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::queue<int> s21_queue{init_list};
  std::queue<int> std_queue{init_list};
  s21_queue.pop();
  s21_queue.pop();
  std_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.front(), 3);
  bool result = true;
  while (!s21_queue.empty()) {
    if (s21_queue.front() != std_queue.front()) {
      result = false;
      break;
    }
    s21_queue.pop();
    std_queue.pop();
  }
  EXPECT_TRUE(result);
}

TEST(queue_test, swap) {
  s21::queue<int> s21_queue1{1, 2, 3, 4, 5};
  s21::queue<int> s21_queue2{6, 7, 8, 9, 10, 11};
  s21_queue1.swap(s21_queue2);

  std::initializer_list<int> il1 = {1, 2, 3, 4, 5};
  std::initializer_list<int> il2 = {6, 7, 8, 9, 10, 11};
  std::queue<int> std_queue1{il1};
  std::queue<int> std_queue2{il2};
  std_queue1.swap(std_queue2);
  bool result = true;
  while (!s21_queue1.empty()) {
    if (s21_queue1.front() != std_queue1.front()) {
      result = false;
      break;
    }
    s21_queue1.pop();
    std_queue1.pop();
  }
  EXPECT_TRUE(result);
  result = true;
  while (!s21_queue2.empty()) {
    if (s21_queue2.front() != std_queue2.front()) {
      result = false;
      break;
    }
    s21_queue2.pop();
    std_queue2.pop();
  }
  EXPECT_TRUE(result);
}

TEST(queue_test, swap_empty) {
  s21::queue<int> s21_queue1{1, 2, 99, 4, 242};
  s21::queue<int> s21_queue2;
  s21_queue1.swap(s21_queue2);

  std::initializer_list<int> il = {1, 2, 99, 4, 242};
  std::queue<int> std_queue1{il};
  std::queue<int> std_queue2;
  std_queue1.swap(std_queue2);
  bool result = true;
  while (!s21_queue1.empty()) {
    if (s21_queue1.front() != std_queue1.front()) {
      result = false;
      break;
    }
    s21_queue1.pop();
    std_queue1.pop();
  }
  EXPECT_TRUE(result);
  result = true;
  while (!s21_queue2.empty()) {
    if (s21_queue2.front() != std_queue2.front()) {
      result = false;
      break;
    }
    s21_queue2.pop();
    std_queue2.pop();
  }
  EXPECT_TRUE(result);
}

TEST(set_test, Full_funcTest) {
  s21::set<int> s1;
  s21::set<int> s2;
  EXPECT_EQ(s1.max_size(), s2.max_size());
  EXPECT_TRUE(s1.empty());
}

TEST(set_test, constructor_default) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5};
  // std::cout << "size from test: " << s1.size() << std::endl;
  s1.swap(s2);
  EXPECT_EQ(int(s1.size()), 2);
  EXPECT_TRUE(s1.contains(4));
  s1.clear();
  EXPECT_EQ(int(s1.size()), 0);
  EXPECT_TRUE(s1.empty());
}

TEST(set_test, Erase) {
  s21::set<int> s{1, 0};
  s21::set<int>::iterator it1 = s.begin();
  s.erase(it1);
  it1 = s.end();
  EXPECT_TRUE(s.contains(1));
  EXPECT_EQ(*it1, 0);
}

TEST(set_test, Find) {
  s21::set<int> s{1, 2, 3};
  s21::set<int>::iterator it1 = s.find(2);
  EXPECT_EQ(*it1, 2);
}

TEST(stack_test, constructor) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(stack_test, constructor_init) {
  std::initializer_list<int> init_stack = {1, 2, 3};
  s21::stack<int> s21_stack{init_stack};
  std::stack<int> std_stack{init_stack};
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_test, constructor_copy) {
  std::initializer_list<int> init_list_1 = {1, 2, 3};
  s21::stack<int> s21_stack{init_list_1};
  s21::stack<int> s21_stack_copy{s21_stack};
  std::stack<int> std_stack{init_list_1};
  std::stack<int> std_stack_copy{std_stack};
  EXPECT_EQ(s21_stack_copy.size(), std_stack_copy.size());
  EXPECT_EQ(s21_stack_copy.top(), std_stack_copy.top());
}

TEST(stack_test, constructor_move) {
  std::initializer_list<int> init_list_1 = {1, 2, 3};
  s21::stack<int> s21_stack{init_list_1};
  s21::stack<int> s21_stack_move{s21_stack};
  std::stack<int> std_stack{init_list_1};
  std::stack<int> std_stack_move{std_stack};
  EXPECT_EQ(s21_stack_move.size(), std_stack_move.size());
  EXPECT_EQ(s21_stack_move.top(), std_stack_move.top());
}

TEST(stack_test, top) {
  std::initializer_list<int> init_list_1 = {4, 5, 6, 7};
  s21::stack<int> s21_stack{init_list_1};
  std::stack<int> std_stack{init_list_1};
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_test, top_throw) {
  std::initializer_list<int> init_list_1;
  s21::stack<int> s21_stack{init_list_1};
  EXPECT_THROW(s21_stack.top(), std::out_of_range);
}

TEST(stack_test, empty_not_empty) {
  std::initializer_list<int> init_list_1 = {4, 5, 6, 7};
  s21::stack<int> s21_stack{init_list_1};
  std::stack<int> std_stack{init_list_1};
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack_test, empty) {
  std::initializer_list<int> init_list_1;
  s21::stack<int> s21_stack{init_list_1};
  std::stack<int> std_stack{init_list_1};
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack_test, size) {
  std::initializer_list<int> init_list_1 = {4, 5, 6, 7};
  s21::stack<int> s21_stack{init_list_1};
  std::stack<int> std_stack{init_list_1};
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(stack_test, push) {
  std::initializer_list<int> init_list_1 = {4, 5, 6, 7};
  s21::stack<int> s21_stack{init_list_1};
  std::stack<int> std_stack{init_list_1};
  s21_stack.push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_test, push_to_empty) {
  std::initializer_list<int> init_list_1;
  s21::stack<int> s21_stack{init_list_1};
  std::stack<int> std_stack{init_list_1};
  s21_stack.push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_test, pop) {
  std::initializer_list<int> init_list_1 = {4, 5, 6, 7};
  s21::stack<int> s21_stack{init_list_1};
  std::stack<int> std_stack{init_list_1};
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack_test, pop_throw) {
  std::initializer_list<int> init_list_1;
  s21::stack<int> s21_stack{init_list_1};
  EXPECT_THROW(s21_stack.pop(), length_error);
}

TEST(stack_test, swap) {
  std::initializer_list<int> init_list_1 = {4, 5, 6, 7};
  std::initializer_list<int> init_list_2 = {1, 2, 3};
  s21::stack<int> s21_stack{init_list_1};
  s21::stack<int> s21_stack_swap{init_list_2};
  std::stack<int> std_stack{init_list_1};
  std::stack<int> std_stack_swap{init_list_2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.top(), std_stack_swap.top());
}

TEST(StackTest, swap_empty) {
  std::initializer_list<int> init_list_1 = {4, 5, 6, 7};
  std::initializer_list<int> init_list_2;
  s21::stack<int> s21_stack{init_list_1};
  s21::stack<int> s21_stack_swap{init_list_2};
  std::stack<int> std_stack{init_list_1};
  std::stack<int> std_stack_swap{init_list_2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
}

TEST(StackTest, swap_full_empty) {
  std::initializer_list<int> init_list_1;
  std::initializer_list<int> init_list_2;
  s21::stack<int> s21_stack{init_list_1};
  s21::stack<int> s21_stack_swap{init_list_2};
  std::stack<int> std_stack{init_list_1};
  std::stack<int> std_stack_swap{init_list_2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
}

TEST(VectorTest, Full_funcTest) {
  s21::vector<int> emp;
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_TRUE(v.empty() == false);
  EXPECT_TRUE(int(v.size()) == 5);
  ASSERT_EQ(v.max_size(), pow(2, 62) - 1);
  v.reserve(100);
  EXPECT_TRUE(v.capacity() == 100);
  v.shrink_to_fit();
  ASSERT_EQ(v.capacity(), v.size());
}

TEST(VectorTest, funcTest) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  s21::vector<int> v2 = {1, 2, 3};
  v.push_back(6);
  EXPECT_TRUE(v[5] == 6);
  s21::VectorIterator s = &v[3];
  v.insert(s, 10);
  ASSERT_EQ(v[3], 10);
  v.erase(s);
  ASSERT_EQ(v[3], 4);
  v.pop_back();
  ASSERT_EQ(v.back(), 5);
  v.swap(v2);
  ASSERT_EQ(v2.back(), 5);
  ASSERT_EQ(v.back(), 3);
  v.clear();
  ASSERT_EQ(int(v.size()), 0);
}

TEST(VectorTest, elaccessorTest) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_TRUE(v.front() == 1);
  EXPECT_TRUE(v.back() == 5);
  EXPECT_TRUE(v.at(2) == 3);
  EXPECT_TRUE(v[1] == 2);
  int* f = v.data();
  EXPECT_TRUE(*f == 1);
}

TEST(VectorTest, beginendTest) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.insert(v.begin(), 2);
  EXPECT_TRUE(v.front() == 2);
  v.insert(v.end(), 2);
  EXPECT_TRUE(v.back() == 2);
}

int main(int argc, char* arga[]) {
  ::testing::InitGoogleTest(&argc, arga);
  return RUN_ALL_TESTS();
}
