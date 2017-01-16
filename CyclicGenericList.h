//
// Created by zahar on 15/01/17.
//

#ifndef CPPEX2_CYCLICGENERICLIST_H
#define CPPEX2_CYCLICGENERICLIST_H

#include "iostream"

template <typename T>

class genericNode{
public:
    /**
     * Generic Node
     * @param data
     */
    genericNode(T data):data(data),next(nullptr),prev(nullptr) {}
    T data;
    genericNode<T>* next;
    genericNode<T>* prev;
};

template <typename T>
class CyclicGenericList {
public:

    /**
     * Ctr
     */
    CyclicGenericList() : head(nullptr) , tail(nullptr) , listSize(0) {
    }


    /**
     * Dctr
     */
    ~CyclicGenericList() {
        deleteList();
    }

    /**
     * delete and free all the nodes
     */
    void deleteList(){
        genericNode<T> *current = head;
        for (size_t i = 0; i < listSize; i++){
            genericNode<T>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        listSize=0;
        head = nullptr;
        tail=nullptr;
    }

    /**
     *  add Node to the tail
     * @param data
     */
    void add(T data){
        genericNode<T> * newNode = new genericNode<T>(data);
        if (head == nullptr) {
            head = tail = newNode;
            head->prev = head;
            tail->next = head;
        }else {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;

            head = newNode;
        }
        listSize++;
    };


    /**
     * remove Node from the list
     * @param data
     * @return true if success
     */
    bool remove(T data){
        if (head == nullptr) {
            return false;
        }
        if (listSize == 1 && head->data == data) {
            delete head;
            head = tail = nullptr;
            listSize--;
            return true;
        }
        genericNode<T>* current = head;
        for (size_t i = 0; i < listSize; i++){
            if (current->data == data) {
                if (current == tail) {
                    tail = tail->prev;
                    tail->next = head;
                    head->prev = tail;
                    delete current;
                }
                else if (current == head) {
                    head = head->next;
                    head->prev = tail;
                    tail->next = head;
                    delete current;
                }
                else {
                    genericNode<T>* toDelete = current;
                    current->next->prev = current->prev;
                    current->prev->next = current->next;
                    delete toDelete;
                }
                listSize--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

private:
    genericNode<T>* head;
    genericNode<T>* tail;
    double listSize;

};


#endif //CPPEX2_CYCLICGENERICLIST_H
