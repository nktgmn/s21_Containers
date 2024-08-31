#ifndef S21_AVLTREE_H
#define S21_AVLTREE_H

#include <initializer_list>

namespace s21 {

template <typename T>
class AVL {
   private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value);
        ~Node();
    };

    Node* head;

    int get_balance_factor(Node* node);
    int get_height(Node* node);

    Node* insert_private(Node* node, const T& value);
    // T* search(Node* node, const T& value);

    Node* rotate_right(Node* node);
    Node* rotate_left(Node* node);

    void delete_node(Node* node);

    Node* erase_private(Node* node, const T& value);

    Node* min_value_node(Node* node);

    T* search_private(Node* node, const T& value) const;

   public:
    AVL();
    ~AVL();

    void insert(const T& value);
    void erase(const T& value);

    T* search(const T& value) const;
};

}  // namespace s21

#include "s21_avl.tpp"

#endif  // S21_AVLTREE_H