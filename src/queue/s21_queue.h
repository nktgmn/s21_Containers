#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <initializer_list>

#include "../list/s21_list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
   public:
    queue();
    queue(const queue& other);
    queue(std::initializer_list<T> init);
    queue(queue&& other) noexcept;
    ~queue();

    queue& operator=(const queue& other);
    queue& operator=(queue&& other) noexcept;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    bool empty() const;
    size_t size() const;

    void push(const T& value);
    void push(T&& value);

    void pop();

    void swap(queue& other) noexcept;

   private:
    Container c;
};

}  // namespace s21

#include "s21_queue.tpp"

#endif  // S21_QUEUE_H
