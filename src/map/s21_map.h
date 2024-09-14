#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <algorithm>
#include <initializer_list>
#include <utility>

namespace s21 {

template <typename Key, typename Value>
class map {
   public:
    class MapIterator;
    class ConstMapIterator;

    using pair = std::pair<const Key, Value>;
    using iter = typename map<Key, Value>::MapIterator;
    using c_iter = typename map<Key, Value>::ConstMapIterator;

    map() noexcept;
    map(const map& other);
    map(std::initializer_list<pair> init);
    map(map&& other);
    ~map() noexcept;

    map& operator=(const map& other);
    map& operator=(map&& other) noexcept;
    map& operator=(std::initializer_list<pair> ilist);

    Value& at(const Key& key);
    const Value& at(const Key& key) const;
    Value& operator[](const Key& key);

    iter begin() noexcept;
    iter end() noexcept;
    c_iter cbegin() const noexcept;
    c_iter cend() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;

    void clear() noexcept;
    std::pair<iter, bool> insert(const pair& value);
    std::pair<iter, bool> insert(pair&& value);
    std::pair<iter, bool> insert_or_assign(const Key& k, Value&& obj);
    iter erase(iter pos);
    iter erase(c_iter pos);
    iter erase(c_iter first, c_iter last);
    size_t erase(const Key& key);
    void swap(map& other) noexcept;
    void merge(map& source);

    size_t count(const Key& key) const;
    iter find(const Key& key);
    c_iter find(const Key& key) const;
    bool contains(const Key& key) const;

    template <typename... Args>
    std::vector<std::pair<iter, bool>> insert_many(Args&&... args);

   private:
    struct BaseNode;
    struct Node;

    BaseNode* fake_node;
    BaseNode* leftmost;
    size_t size_;

    int get_height(BaseNode* node);
    int get_balance_factor(BaseNode* node);
    void delete_node(Node* node);
    BaseNode* rebalance_node(BaseNode* node);
    BaseNode* min_value_node(BaseNode* node);
    BaseNode* rotate_right(BaseNode* node);
    BaseNode* rotate_left(BaseNode* node);
    iter erase_private(iter pos, bool del);
    std::pair<BaseNode*, bool> insert_private(BaseNode* node, const pair& value);
    std::pair<BaseNode*, bool> insert_private(BaseNode* node, pair&& value);
    BaseNode* merge_insert(BaseNode* node, BaseNode* src, map& source);
};

}  // namespace s21

#include "../iterators/s21_map_iterators.h"
#include "../iterators/s21_map_iterators.tpp"
#include "s21_map.tpp"

#endif  // #define S21_MAP_H_
