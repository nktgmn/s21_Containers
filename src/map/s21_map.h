#ifndef S21_MAP_H_
#define S21_MAP_H_

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

    iter begin() noexcept;
    iter end() noexcept;
    c_iter cbegin() const noexcept;
    c_iter cend() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;

    void clear() noexcept;
    std::pair<iter, bool> insert(const pair& value);

   private:
    struct BaseNode;
    struct Node;

    BaseNode* fake_node;
    BaseNode* leftmost;
    size_t size_;

    int get_height(BaseNode* node);
    int get_balance_factor(BaseNode* node);
    void delete_node(Node* node);
    BaseNode* min_value_node(BaseNode* node);
    BaseNode* rotate_right(BaseNode* node);
    BaseNode* rotate_left(BaseNode* node);
    std::pair<BaseNode*, bool> insert_private(BaseNode* node, const pair& value);
    // Node* erase_private(Node* node, const T& value);
    // std::pair<Key, Value>* search_private(Node* node, const T& value) const;
};

}  // namespace s21

#include "../iterators/s21_map_iterators.h"
#include "../iterators/s21_map_iterators.tpp"
#include "s21_map.tpp"

#endif  // #define S21_MAP_H_
