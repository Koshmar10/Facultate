#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
class Node {
    private:
        T value;
        Node* next;
    public:
        Node(T value): value(value), next(nullptr) {}
        Node(Node<T>& other): value(other.value), next(other.next) {}
        ~Node() {}

        T getValue() {
            return value;
        }

        void setValue(T newValue) {
            value = newValue;
        }

        Node* getNext() {
            return next;
        }

        void setNext(Node* newNext) {
            next = newNext;
        }
};

#endif