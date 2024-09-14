#ifndef S21_QUEUE_TPP
#define S21_QUEUE_TPP

#include "s21_queue.h"

namespace s21 {

template <typename T, typename Container>
queue<T, Container>::queue() : c_() {}

template <typename T, typename Container>
queue<T, Container>::queue(const queue& other) : c_(other.c_) {}

template <typename T, typename Container>
queue<T, Container>::queue(std::initializer_list<T> init) : c_(init) {}

template <typename T, typename Container>
queue<T, Container>::queue(queue&& other) noexcept : c_(std::move(other.c_)) {}

template <typename T, typename Container>
queue<T, Container>::~queue() {}

template <typename T, typename Container>
queue<T, Container>& queue<T, Container>::operator=(const queue& other) {
    if (this != &other) {
        c_ = other.c_;
    }
    return *this;
}

template <typename T, typename Container>
queue<T, Container>& queue<T, Container>::operator=(queue&& other) noexcept {
    if (this != &other) {
        c_ = std::move(other.c_);
    }
    return *this;
}

template <typename T, typename Container>
T& queue<T, Container>::back() {
    return c_.back();
}

template <typename T, typename Container>
const T& queue<T, Container>::back() const {
    return c_.back();
}

template <typename T, typename Container>
T& queue<T, Container>::front() {
    return c_.front();
}

template <typename T, typename Container>
const T& queue<T, Container>::front() const {
    return c_.front();
}

template <typename T, typename Container>
bool queue<T, Container>::empty() const {
    return c_.empty();
}

template <typename T, typename Container>
size_t queue<T, Container>::size() const {
    return c_.size();
}

template <typename T, typename Container>
void queue<T, Container>::push(const T& value) {
    c_.push_back(value);
}

template <typename T, typename Container>
void queue<T, Container>::push(T&& value) {
    c_.push_back(std::move(value));
}

template <typename T, typename Container>
void queue<T, Container>::pop() {
    c_.pop_back();
}

template <typename T, typename Container>
void queue<T, Container>::swap(queue& other) noexcept {
    return c_.swap(other.c_);
}

template <typename T, typename Container>
template <typename... Args>
void queue<T, Container>::insert_many_back(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif  // S21_QUEUE_TPP
