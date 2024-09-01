#ifndef S21_MAP_ITERATORS_H_
#define S21_MAP_ITERATORS_H_

namespace s21 {

template <typename Key, typename Value>
class map<Key, Value>::MapIterator {
   public:
    MapIterator() noexcept;
    MapIterator(BaseNode* ptr) noexcept;
    MapIterator(Node* ptr) noexcept;
    MapIterator(const iter& other) noexcept;

    iter& operator=(const iter& other) noexcept;

    pair& operator*() noexcept;

    iter& operator++() noexcept;
    iter& operator--() noexcept;

    bool operator==(const iter& other) const noexcept;
    bool operator!=(const iter& other) const noexcept;

   private:
    BaseNode* node;

    friend class map;
};

template <typename Key, typename Value>
class map<Key, Value>::ConstMapIterator {
   public:
    ConstMapIterator() noexcept;
    ConstMapIterator(BaseNode* ptr) noexcept;
    ConstMapIterator(Node* ptr) noexcept;
    ConstMapIterator(const c_iter& other) noexcept;

    c_iter& operator=(const c_iter& other) noexcept;

    const pair& operator*() noexcept;

    c_iter& operator++() noexcept;
    c_iter& operator--() noexcept;

    bool operator==(const c_iter& other) const noexcept;
    bool operator!=(const c_iter& other) const noexcept;

   private:
    BaseNode* node;

    friend class map;
};

}  // namespace s21

#endif  // S21_MAP_ITERATORS_H_