#ifndef S21_SEQ_ITERATORS_H
#define S21_SEQ_ITERATORS_H

#include <cstddef>

namespace s21 {

template <typename T>
class SequenceIterator {
   public:
    SequenceIterator() noexcept;
    SequenceIterator(T* ptr) noexcept;
    ~SequenceIterator() noexcept;

    T& operator*() noexcept;

    SequenceIterator& operator++() noexcept;
    SequenceIterator operator++(int) noexcept;
    SequenceIterator& operator--() noexcept;
    SequenceIterator operator--(int) noexcept;
    SequenceIterator& operator+=(std::ptrdiff_t diff) noexcept;
    SequenceIterator& operator-=(std::ptrdiff_t diff) noexcept;
    SequenceIterator operator+(std::ptrdiff_t diff) noexcept;
    SequenceIterator operator-(std::ptrdiff_t diff) noexcept;

    bool operator==(const SequenceIterator& other) const noexcept;
    bool operator!=(const SequenceIterator& other) const noexcept;
    bool operator>(const SequenceIterator& other) const noexcept;
    bool operator<(const SequenceIterator& other) const noexcept;
    bool operator>=(const SequenceIterator& other) const noexcept;
    bool operator<=(const SequenceIterator& other) const noexcept;

    std::ptrdiff_t operator-(const SequenceIterator& other) noexcept;

   private:
    T* ptr_;
};

template <typename T>
class ConstSequenceIterator {
   public:
    ConstSequenceIterator() noexcept;
    ConstSequenceIterator(const T* ptr) noexcept;
    ~ConstSequenceIterator() noexcept;

    const T& operator*() const noexcept;

    ConstSequenceIterator& operator++() noexcept;
    ConstSequenceIterator operator++(int) noexcept;
    ConstSequenceIterator& operator--() noexcept;
    ConstSequenceIterator operator--(int) noexcept;
    ConstSequenceIterator& operator+=(std::ptrdiff_t diff) noexcept;
    ConstSequenceIterator& operator-=(std::ptrdiff_t diff) noexcept;
    ConstSequenceIterator operator+(std::ptrdiff_t diff) noexcept;
    ConstSequenceIterator operator-(std::ptrdiff_t diff) noexcept;

    bool operator==(const ConstSequenceIterator& other) const noexcept;
    bool operator!=(const ConstSequenceIterator& other) const noexcept;
    bool operator>(const ConstSequenceIterator& other) const noexcept;
    bool operator<(const ConstSequenceIterator& other) const noexcept;
    bool operator>=(const ConstSequenceIterator& other) const noexcept;
    bool operator<=(const ConstSequenceIterator& other) const noexcept;

    std::ptrdiff_t operator-(const ConstSequenceIterator& other) noexcept;

   private:
    const T* ptr_;
};

}  // namespace s21

#endif  // S21_SEQ_ITERATORS_H
