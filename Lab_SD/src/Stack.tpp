#ifndef STACK_TPP
#define STACK_TPP

#include "../include/Stack.hpp"

template <typename T>
Stack<T>::Stack(Stack<T>& other) : tos(nullptr) {
    if (other.tos) {
        Node<T>* current = other.tos;
        Stack<T> tempStack;
        while (current) {
            tempStack.push(current->getValue());
            current = current->getNext();
        }
        while (!tempStack.isEmpty()) {
            this->push(tempStack.top()->getValue());
            tempStack.pop();
        }
    }
}

template <typename T>
Stack<T>::~Stack() {
    while (!this->isEmpty()) {
        this->pop();
    }
}

template <typename T>
Node<T>* Stack<T>::getTos() {
    return this->tos;
}

template <typename T>
void Stack<T>::setTos(Node<T>* newTos) {
    this->tos = newTos;
}

template <typename T>
void Stack<T>::push(T value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->setNext(this->tos);
    this->tos = newNode;
}

template <typename T>
void Stack<T>::pop() {
    if (this->isEmpty()) return;
    Node<T>* temp = this->tos;
    this->tos = this->tos->getNext();
    delete temp;
}

template <typename T>
Node<T>* Stack<T>::top() {
    return this->tos;
}

template <typename T>
bool Stack<T>::isEmpty() {
    return this->tos == nullptr;
}

template <typename T>
int Stack<T>::size() {
    int count = 0;
    Node<T>* current = this->tos;
    while (current) {
        count++;
        current = current->getNext();
    }
    return count;
}

template <typename T>
void Stack<T>::print() {
    std::cout<<"salut";
    Node<T>* current = this->tos;
    while (current) {
        std::cout << current->getValue() << " ";
        current = current->getNext();
    }
    std::cout << std::endl;
}

#endif
