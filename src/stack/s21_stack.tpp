#ifndef S21_STACK_TPP
#define S21_STACK_TPP

#include "s21_stack.h"

namespace s21 {

template <typename T, typename Container>
stack<T, Container>::stack() : vector_() {}

template <typename T, typename Container>
stack<T, Container>::stack(const stack& other) : vector_(other.vector_) {}

template <typename T, typename Container>
stack<T, Container>::stack(std::initializer_list<T> init) : vector_(init) {}

template <typename T, typename Container>
stack<T, Container>::stack(stack&& other) noexcept
    : vector_(std::move(other.vector_)) {}

template <typename T, typename Container>
stack<T, Container>::~stack() {}

template <typename T, typename Container>
stack<T, Container>& stack<T, Container>::operator=(const stack& other) {
    if (this != &other) {
        vector_ = other.vector_;
    }
    return *this;
}

template <typename T, typename Container>
stack<T, Container>& stack<T, Container>::operator=(stack&& other) noexcept {
    if (this != &other) {
        vector_ = std::move(other.vector_);
    }
    return *this;
}

template <typename T, typename Container>
T& stack<T, Container>::top() {
    return vector_.back();
}

template <typename T, typename Container>
const T& stack<T, Container>::top() const {
    return vector_.back();
}

template <typename T, typename Container>
bool stack<T, Container>::empty() const {
    return vector_.empty();
}

template <typename T, typename Container>
size_t stack<T, Container>::size() const {
    return vector_.size();
}

template <typename T, typename Container>
void stack<T, Container>::push(const T& value) {
    vector_.push_back(value);
}

template <typename T, typename Container>
void stack<T, Container>::push(T&& value) {
    vector_.push_back(std::move(value));
}

template <typename T, typename Container>
void stack<T, Container>::pop() {
    vector_.pop_back();
}

template <typename T, typename Container>
void stack<T, Container>::swap(stack& other) noexcept {
    return vector_.swap(other.vector_);
}

template <typename T, typename Container>
template <typename... Args>
void stack<T, Container>::insert_many_back(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif  // S21_STACK_TPP
