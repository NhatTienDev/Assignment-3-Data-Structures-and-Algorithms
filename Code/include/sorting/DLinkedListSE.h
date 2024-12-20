/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list) : DLinkedList<T>(list)
    {
        this -> copyFrom(list);
    }
    
    void sort(int (*comparator)(T&,T&)=0)
    {
        // TODO: implement this function
        // You should implement the merge sort algorithm
        if(this -> head -> next == this -> tail) return;

        if(this -> head -> next -> next == this -> tail) return;

        typename DLinkedList<T>::Node *solution = mergeSort(this -> head -> next, comparator);
        this -> head -> next = solution;
        solution -> prev = this -> head;

        while(solution -> next != this -> tail)
        {
            solution = solution -> next;
        }

        solution -> next = this -> tail;
        this -> tail -> prev = solution;
    }

private:
    typename DLinkedList<T>::Node *split(typename DLinkedList<T>::Node *head)
    {
        typename DLinkedList<T>::Node *slowPointer = head;
        typename DLinkedList<T>::Node *fastPointer = head;

        while(fastPointer -> next != this -> tail && fastPointer -> next -> next != this -> tail)
        {
            slowPointer = slowPointer -> next;
            fastPointer = fastPointer -> next -> next;
        }

        typename DLinkedList<T>::Node *result = slowPointer -> next;
        slowPointer -> next = this -> tail;
        return result;
    }

    typename DLinkedList<T>::Node *merge(typename DLinkedList<T>::Node *left,
                                         typename DLinkedList<T>::Node *right,
                                         int (*comparator)(T &, T &) = 0)
    {
        if(left == this -> tail) return right;
        if(right == this -> tail) return left;

        if(compare(left -> data, right -> data, comparator) > 0)
        {
            right -> next = merge(left, right -> next, comparator);

            if(right -> next != this -> tail)
            {
                right -> next -> prev = right;
            }
            return right;
        }
        else
        {
            left -> next = merge(left -> next, right, comparator);

            if(left -> next != this -> tail)
            {
                left -> next -> prev = left;
            }
            return left;
        }
    }

    typename DLinkedList<T>::Node *mergeSort(typename DLinkedList<T>::Node *head,
                                              int (*comparator)(T &, T &) = 0)
    {
        if(head -> next == this -> tail || head -> next -> next == this -> tail) return head;

        typename DLinkedList<T>::Node *mid = split(head);
        typename DLinkedList<T>::Node *left = mergeSort(head, comparator);
        typename DLinkedList<T>::Node *right = mergeSort(mid, comparator);
        
        return merge(left, right, comparator);
    }
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */

