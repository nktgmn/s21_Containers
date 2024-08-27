#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>

#include "../iterators/s21_list_iterators.tpp"

namespace s21 {

template <typename T>
class list {
   private:
    struct BaseNode {
        BaseNode* prev;
        BaseNode* next;
    };

    struct Node : BaseNode {
        T value;
    };

    BaseNode fake_node;
    size_t size_;

   public:
    class ListIterator {
       public:
        ListIterator() noexcept;
        ListIterator(Node* ptr) noexcept;
        ListIterator(const Node* ptr) noexcept;
        ListIterator(const ListIterator& other) noexcept;

        ListIterator& operator=(const ListIterator& other);

        T& operator*() noexcept;

        ListIterator& operator++() noexcept;
        ListIterator& operator--() noexcept;

        bool operator==(const ListIterator& other) const noexcept;
        bool operator!=(const ListIterator& other) const noexcept;

       private:
        Node* ptr_;

        template <typename>
        friend class list;
    };

    class ListConstIterator {
       public:
        ListConstIterator() noexcept;
        ListConstIterator(const Node* ptr) noexcept;
        ListConstIterator(const ListConstIterator& other) noexcept;
        ListConstIterator(const ListIterator& other) noexcept;

        ListConstIterator& operator=(const ListConstIterator& other);

        const T& operator*() const noexcept;

        ListConstIterator& operator++() noexcept;
        ListConstIterator& operator--() noexcept;

        bool operator==(const ListConstIterator& other) const noexcept;
        bool operator!=(const ListConstIterator& other) const noexcept;

       private:
        const Node* ptr_;

        template <typename>
        friend class list;
    };

    list() noexcept;
    list(const list& other);
    list(std::initializer_list<T> init);
    list(list&& other) noexcept;
    ~list() noexcept;

    list& operator=(const list& other);
    list& operator=(list&& other) noexcept;
    list& operator=(std::initializer_list<T> ilist);

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    ListIterator end();
    ListIterator begin();
    ListConstIterator cend() const;
    ListConstIterator cbegin() const;

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;

    void clear() noexcept;
    ListIterator insert(ListConstIterator pos, const T& value);
    ListIterator insert(ListConstIterator pos, size_t count, const T& value);
    ListIterator insert(ListConstIterator pos, T&& value);
    ListIterator erase(ListConstIterator pos);
    ListIterator erase(ListConstIterator first, ListConstIterator last);
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void push_front(const T& value);
    void push_front(T&& value);
    void pop_front();
    void resize(size_t count, const T& value);
    void resize(size_t count);
    void swap(list& other) noexcept;

    void merge(list& other);
    void merge(list&& other);
    void splice(ListConstIterator pos, list& other);
    void splice(ListConstIterator pos, list&& other);
    void splice(ListConstIterator pos, list& other, ListConstIterator it);
    void splice(ListConstIterator pos, list&& other, ListConstIterator it);
    void splice(ListConstIterator pos, list& other, ListConstIterator first,
                ListConstIterator last);
    void splice(ListConstIterator pos, list&& other, ListConstIterator first,
                ListConstIterator last);
    void remove(const T& value);
    void reverse();
    void unique();
    void sort();
};

template <typename T>
bool operator==(const s21::list<T>& left, const s21::list<T>& right);

};  // namespace s21

#include "s21_list.tpp"

#endif  // S21_LIST_H
