#ifndef S21_STACK_H
#define S21_STACK_H

#include <initializer_list>

#include "../vector/s21_vector.h"

namespace s21 {

template <typename T, typename Container = s21::vector<T>>
class stack {
   public:
    stack();
    stack(const stack& other);
    stack(std::initializer_list<T> init);
    stack(stack&& other) noexcept;
    ~stack();

    stack& operator=(const stack& other);
    stack& operator=(stack&& other) noexcept;

    T& top();
    const T& top() const;

    bool empty() const;
    size_t size() const;

    void push(const T& value);
    void push(T&& value);

    void pop();

    void swap(stack& other) noexcept;

    template <typename... Args>
    void insert_many_back(Args&&... args);

   private:
    Container vector_;
};

}  // namespace s21

#include "s21_stack.tpp"

#endif  // S21_STACK_H
