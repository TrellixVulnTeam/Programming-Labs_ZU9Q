#ifndef CIRCULAR_QUEUE_H
    #define CIRCULAR_QUEUE_H

#include <memory>
#include "IQueue.h"

template<typename T, int capacity>
class CircularQueue : IQueue<T>
{
private:
    T* _data;
    int _size;
    int _head;
    int _tail;

public:
    CircularQueue();
    CircularQueue(T*, int);
    CircularQueue(std::initializer_list<T>);
    CircularQueue(const CircularQueue&);
    ~CircularQueue();

    bool empty() const noexcept override;
    std::size_t size() const noexcept override;

    T& front() override;
    const T& front() const override;
    T& back() override;
    const T& back() const override;

    void push(T&&) override;
    void push(const T&) override;
    void pop() override;
};

#include "CircularQueue.cpp"

#endif