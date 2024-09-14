#ifndef S21_SET_ITERATORS_H_
#define S21_SET_ITERATORS_H_

namespace s21 {

template <typename Key>
class set<Key>::SetIterator {
   public:
    SetIterator() noexcept;
    SetIterator(BaseNode* ptr) noexcept;
    SetIterator(Node* ptr) noexcept;
    SetIterator(const iter& other) noexcept;

    iter& operator=(const iter& other) noexcept;

    key& operator*() noexcept;

    iter& operator++() noexcept;
    iter& operator--() noexcept;

    bool operator==(const iter& other) const noexcept;
    bool operator!=(const iter& other) const noexcept;

   private:
    BaseNode* node;

    friend class set;
};

template <typename Key>
class set<Key>::ConstSetIterator {
   public:
    ConstSetIterator() noexcept;
    ConstSetIterator(BaseNode* ptr) noexcept;
    ConstSetIterator(Node* ptr) noexcept;
    ConstSetIterator(const c_iter& other) noexcept;

    c_iter& operator=(const c_iter& other) noexcept;

    const key& operator*() noexcept;

    c_iter& operator++() noexcept;
    c_iter& operator--() noexcept;

    bool operator==(const c_iter& other) const noexcept;
    bool operator!=(const c_iter& other) const noexcept;

   private:
    BaseNode* node;

    friend class set;
};

}  // namespace s21

#endif  // S21_SET_ITERATORS_H_