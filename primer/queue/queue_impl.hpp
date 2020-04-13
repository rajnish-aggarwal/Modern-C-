// This is an adaptation from the c++ primer 3rd editiion

// export the class template for separate compilation
#include "queue.hpp"

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
    if (head_ == tail_) {
        head_ = item;
        tail_ = item;
    } else {
        tail_->next_ = item;
        tail_ = item;
    }
}

template<typename Type>
void Queue<Type>::copy_elems(const Queue &q) {
    for (QueueItem<Type> *p = q.head; p; p = p->next) {
        push(p->item);
    }
}
