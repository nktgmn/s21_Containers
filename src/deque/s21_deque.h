#ifndef S21_DEQUE_H
#define S21_DEQUE_H

#include <initializer_list>

#include "../iterators/s21_deque_iter.tpp"

#define N 32

namespace s21 {

template <typename T>
class deque {
   public:
    deque() noexcept;
    deque(const deque& other);
    deque(std::initializer_list<T> init);
    // deque(deque &&other) noexcept;
    ~deque() noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;

    void clear() noexcept;

    void push_back(const T& value);
    void push_back(T&& value);

   private:
    size_t ptrs_size = 0;
    T** ptrs = nullptr;
    size_t i_begin = 0;
    size_t j_begin = 0;
    size_t i_end = 0;
    size_t j_end = 0;
};

}  // namespace s21

#include "../iterators/s21_deque_iter.tpp"
#include "s21_deque.tpp"

#endif  // S21_DEQUE_H
