#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "Node.hpp"
#include <string>


template <typename T>
class Stack {
    private:
        Node<T>* tos;
    public:
        Stack(): tos(nullptr) {}

        Stack(Stack<T>& other) : tos(nullptr) {
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

        ~Stack() {
            while (!this->isEmpty()) {
                this->pop();
            }
        }

        Node<T>* getTos() {
            return this->tos;
        }

        void setTos(Node<T>* newTos) {
            this->tos = newTos;
        }

        void push(T value) {
            Node<T>* newNode = new Node<T>(value);
            newNode->setNext(this->tos);
            this->tos = newNode;
        }

        void pop() {
            if (this->isEmpty()) return;
            Node<T>* temp = this->tos;
            this->tos = this->tos->getNext();
            delete temp;
        }

        Node<T>* top() {
            return this->tos;
        }

        bool isEmpty() {
            return this->tos == nullptr;
        }

        int size() {
            int count = 0;
            Node<T>* current = this->tos;
            while (current) {
                count++;
                current = current->getNext();
            }
            return count;
        }
        /*
        void print() {
            Node<T>* current = this->tos;
            while (current) {
                std::cout << current->getValue() << " ";
                current = current->getNext();
            }
            std::cout << std::endl;
        }
        */
};

#endif