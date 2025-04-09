//
// Created by huhaolong on 2024/7/16.
//

#pragma once

template <typename T> class PriorityQueue {
public:
    virtual unsigned int size() const = 0;
    virtual bool empty() const = 0;
    virtual void push(const T& e) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
};
