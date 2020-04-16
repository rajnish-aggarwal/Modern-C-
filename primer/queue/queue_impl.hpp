// This is an adaptation from the c++ primer 3rd editiion

// export the class template for separate compilation
#pragma once

#include "queue.hpp"
#include <iostream>

template<typename Type>
void Queue<Type>::destroy() {
    while (!empty()) {
        pop();
    }
}

template<typename Type>
void Queue<Type>::pop() {
    if (empty()) {
        return;
    }

    QueueItem<Type> *head = head_;
    head_ = head_->next_;
    delete head;
}

template<typename Type>
void Queue<Type>::push(const Type &val) {
    QueueItem<Type> *item = new QueueItem<Type>(val);
    if (head_ == nullptr) {
        head_ = item;
        tail_ = item;
        std::cout << "Adding element in the start" << std::endl;
    } else {
        tail_->next_ = item;
        tail_ = item;
        std::cout << "Adding element in the end" << std::endl;
    }
}

template<typename Type>
void Queue<Type>::copy_elems(const Queue &q) {
    for (QueueItem<Type> *p = q.head; p; p = p->next) {
        push(p->item);
    }
}

template<typename Type>
std::ostream& operator<< (std::ostream& os, const Queue<Type>& q) {
    os << "< ";
    QueueItem<Type> *p = q.head_;
    while (p) {
        os << p->item_ << " ";
        p = p->next_;
    }

    os << " >";
    return os;
}

template<typename Type> template<typename Iter>
void Queue<Type>::assign(Iter begin, Iter end) {
    destroy();
    copy_elems(begin, end);
}

// Make sure the source and targets of the container are not the same
// otherwise, we will loose everything.
template<typename Type> template<typename Iter>
void Queue<Type>::copy_elems(Iter begin, Iter end) {
    while (begin != end) {
        push(*begin);
        ++begin;
    }
}
