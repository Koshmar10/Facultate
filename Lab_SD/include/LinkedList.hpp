#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp" 

template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList(Node<T>* head = nullptr, Node<T>* tail = nullptr)
        : head(head), tail(tail) {}

    ~LinkedList() {
        clear();
    }

    Node<T>* getHead() { return this->head; }
    Node<T>* getTail() { return this->tail; }

    void setHead(Node<T>* newHead) {
        Node<T>* saveNext = this->head ? this->head->getNext() : nullptr;
        this->head = newHead;
        if (this->head) {
            this->head->setNext(saveNext);
        }
    }

    void setTail(Node<T>* newTail) {
        this->tail = newTail;
        if (this->tail) {
            this->tail->setNext(nullptr);
        }
    }

    void appendFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->setNext(this->head);
        this->head = newNode;
        if (!this->tail) {
            this->tail = newNode;
        }
    }

    void appendBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (this->tail) {
            this->tail->setNext(newNode);
        }
        this->tail = newNode;
        if (!this->head) {
            this->head = newNode;
        }
    }

    void insertAt(T value, int position) {
        if (position == 0) {
            appendFront(value);
        } else if (position >= this->size()) {
            appendBack(value);
        } else {
            Node<T>* current = this->head;
            int index = 0;
            while (current != nullptr && index < position - 1) {
                current = current->getNext();
                index++;
            }
            if (current != nullptr) {
                Node<T>* newNode = new Node<T>(value);
                newNode->setNext(current->getNext());
                current->setNext(newNode);
            }
        }
    }

    void remove(T value) {
        Node<T>* current = this->head;
        Node<T>* prev = nullptr;

        while (current != nullptr) {
            if (current->getValue() == value) {
                if (prev == nullptr) {
                    this->head = current->getNext();
                } else {
                    prev->setNext(current->getNext());
                }
                if (current == this->tail) {
                    this->tail = prev;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->getNext();
        }
    }

    void pop(int position) {

        if (position <= 0) {
            Node<T>* temp = this->head;
            this->head = this->head->getNext();
            if (this->head == nullptr) {
                this->tail = nullptr;
            }
            delete temp;
            return;
        }

        Node<T>* current = this->head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->getNext();
        }

        Node<T>* temp = current->getNext();
        current->setNext(temp->getNext());
        if (temp == this->tail) {
            this->tail = current;
        }
        delete temp;
    }

    void clear() {
        Node<T>* current = this->head;
        while (current != nullptr) {
            Node<T>* next = current->getNext();
            delete current;
            current = next;
        }
        this->head = nullptr;
        this->tail = nullptr;
    }

    bool isEmpty() {
        return this->head == nullptr;
    }

    int size() {
        int count = 0;
        Node<T>* current = this->head;
        while (current != nullptr) {
            count++;
            current = current->getNext();
        }
        return count;
    }

    void printList() {
        Node<T>* current = this->head;
        while (current != nullptr) {
            std::cout << current->getValue() << " ";
            current = current->getNext();
        }
        std::cout << std::endl;
    }
};;

#endif