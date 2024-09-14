#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <initializer_list>

#include "../iterators/s21_seq_iterators.h"

namespace s21 {

template <typename T, std::size_t N>
class array {
   public:
    using iter = SequenceIterator<T>;
    using c_iter = ConstSequenceIterator<T>;

    array() noexcept;
    array(const array& other);
    array(std::initializer_list<T> init);
    array(array&& other) noexcept;

    array& operator=(const array& other);
    array& operator=(array&& other) noexcept;
    array& operator=(std::initializer_list<T> ilist);

    T& at(size_t pos);
    const T& at(size_t pos) const;
    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T* data() noexcept;
    const T* data() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;

    void fill(const T& value);
    void swap(array& other) noexcept;

    iter begin() noexcept;
    iter end() noexcept;
    c_iter cbegin() const noexcept;
    c_iter cend() const noexcept;

   private:
    T data_[N];
    size_t size_ = N;
};

template <typename T, std::size_t N>
bool operator==(const array<T, N>& left, const array<T, N>& right);

template <typename T, std::size_t N>
bool operator!=(const array<T, N>& left, const array<T, N>& right);

}  // namespace s21

#include "s21_array.tpp"

#endif  // S21_ARRAY_H
