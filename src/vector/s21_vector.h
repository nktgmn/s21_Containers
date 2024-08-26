#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <initializer_list>

#include "../iterators/s21_seq_iterators.tpp"

namespace s21 {

template <typename T>
class vector {
   public:
    vector() noexcept;
    vector(const vector &other);
    vector(std::initializer_list<T> init);
    vector(vector &&other) noexcept;
    ~vector();

    using Iterator = SequenceIterator<T>;
    using ConstIterator = ConstSequenceIterator<T>;

    vector &operator=(const vector &other);
    vector &operator=(vector &&other) noexcept;
    vector &operator=(std::initializer_list<T> ilist);

    T &at(size_t pos);
    const T &at(size_t pos) const;
    T &operator[](size_t pos);
    const T &operator[](size_t pos) const;
    T &front();
    const T &front() const;
    T &back();
    const T &back() const;
    T *data() noexcept;
    const T *data() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;
    void reserve(size_t new_cap);
    size_t capacity() const noexcept;
    void shrink_to_fit();

    void clear() noexcept;
    Iterator insert(ConstIterator pos, const T &value);
    Iterator insert(ConstIterator pos, T &&value);
    Iterator insert(ConstIterator pos, size_t count, const T &value);
    Iterator erase(ConstIterator pos);
    Iterator erase(ConstIterator first, ConstIterator last);
    void push_back(const T &value);
    void push_back(T &&value);
    void pop_back() noexcept;
    void resize(size_t count);
    void resize(size_t count, const T &value);
    void swap(vector &other) noexcept;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

   private:
    T *data_;
    size_t size_;
    size_t capacity_;
};

template <typename T>
bool operator==(const s21::vector<T> &left, const s21::vector<T> &right);

}  // namespace s21

#include "s21_vector.tpp"

#endif  // S21_VECTOR_H
