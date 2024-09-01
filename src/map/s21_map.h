#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <initializer_list>

namespace s21 {

template <typename Key, typename Value>
class map {
   private:
    struct BaseNode;
    struct Node;

   public:
    class MapIterator;

    using pair = std::pair<const Key, Value>;
    using iterator = typename map<Key, Value>::MapIterator;
    using const_iterator = typename map<Key, Value>::ConstMapIterator;

   private:
    struct BaseNode {
        BaseNode* left;
        BaseNode* right;
        BaseNode* parent;
        int height;
        BaseNode();
    };

    struct Node : BaseNode {
        pair kv;
        Node(const pair& value);
    };

   public:
    class MapIterator {
       public:
        MapIterator() noexcept;
        MapIterator(BaseNode* ptr) noexcept;
        MapIterator(Node* ptr) noexcept;
        MapIterator(const iterator& other) noexcept;

        iterator& operator=(const iterator& other) noexcept;

        pair& operator*() noexcept;

        iterator& operator++() noexcept;
        iterator& operator--() noexcept;

        bool operator==(const iterator& other) const noexcept;
        bool operator!=(const iterator& other) const noexcept;

       private:
        BaseNode* node;

        friend class map;
    };

    class ConstMapIterator {
       public:
        MapIterator() noexcept;
        MapIterator(BaseNode* ptr) noexcept;
        MapIterator(Node* ptr) noexcept;
        MapIterator(const iterator& other) noexcept;

        iterator& operator=(const iterator& other) noexcept;

        pair& operator*() noexcept;

        iterator& operator++() noexcept;
        iterator& operator--() noexcept;

        bool operator==(const iterator& other) const noexcept;
        bool operator!=(const iterator& other) const noexcept;

       private:
        BaseNode* node;

        friend class map;
    };

    map() noexcept;
    ~map() noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;

    std::pair<iterator, bool> insert(const pair& value);

   private:
    BaseNode* fake_node;
    BaseNode* leftmost;

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

#include "../iterators/s21_map_iterators.tpp"
#include "s21_map.tpp"

#endif  // #define S21_MAP_H_
