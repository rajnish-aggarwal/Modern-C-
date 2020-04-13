// This file is created from C++ primer 3rd edition.

#pragma once

// forward declaration to allow QueueItem to declare friendship.
template<typename Type> class Queue;

template<typename Type>
class QueueItem {
private:
    QueueItem(const Type &t) : item_(t), next_(nullptr) {}
    Type item_;
    QueueItem *next_{nullptr};

    // make the queue class a friend of QueueItem
    friend class Queue<Type>;
};

template<typename Type>
class Queue {
public:
    // ctor
    Queue() : head_(nullptr), tail_(nullptr) {}
    // copy ctor
    Queue(const Queue &q) : head_(nullptr), tail_(nullptr) {
        copy_elems(q);
    }
    // assignment ctor
    Queue& operator= (const Queue &q);
    // destructor
    ~Queue() { destroy(); }

public:
    Type& front() { return head_->item; }
    const Type& front() const { return head_->item; }
    void push(const Type &);
    void pop();
    bool empty() {
        return head_ == nullptr;
    }
private:
    QueueItem<Type> *head_;
    QueueItem<Type> *tail_;
    void destroy();
    void copy_elems(const Queue &q);
};
