//
// Created by huhaolong on 2024/7/16.
//

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "../priority_queue/priority_queue.h"
#include <vector>
#include <algorithm>
#include <cstdio>

template <typename T> class BinaryHeap : public PriorityQueue<T> {
protected:
    std::vector<T> _heap;

    //pidx=floor((idx-1)/2)
    static int parentIndexOf(int idx) {
        if (idx == 0) {
            return -1;
        }
        return (idx - 1) / 2;
    }

    static int leftChildIndexOf(int idx) { return 2 * idx + 1; }

    static int rightChildIndexOf(int idx) { return 2 * idx + 2; }

    bool indexInHeap(int idx) const {
        int sz = _heap.size();
        return 0 <= idx && idx < sz;
    }

    bool hasChild(int idx) const {
        return indexInHeap(leftChildIndexOf(idx)) || indexInHeap(rightChildIndexOf(idx));
    }

    int greaterChildIndexOf(int idx) const {
        auto lci = leftChildIndexOf(idx);
        auto rci = rightChildIndexOf(idx);
        if (!indexInHeap(lci)) {
            return -1;
        }
        if (!indexInHeap(rci)) {
            return lci;
        }
        return _heap[lci] > _heap[rci] ? lci : rci;
    }

    int percolateUp(int idx) {
        while (0 < idx) {
            auto pidx = parentIndexOf(idx);
            if (_heap[idx] < _heap[pidx]) {
                break;
            }
            std::swap(_heap[idx], _heap[pidx]);
            idx = pidx;
        }
        return idx;
    }

    int percolateDown(int idx) {
        while (hasChild(idx)) {
            auto cidx = greaterChildIndexOf(idx);
            if (_heap[idx] > _heap[cidx]) {
                break;
            }
            std::swap(_heap[idx], _heap[cidx]);
            idx = cidx;
        }
        return idx;
    }
public:
    BinaryHeap() { _heap = std::vector<T>(0); }
    BinaryHeap(unsigned int n) {}

    unsigned int size() const override {
        return _heap.size();
    }

    bool empty() const override {
        return _heap.empty();
    }

    void push(const T& e) override {
        _heap.push_back(e);
        percolateUp(_heap.size() - 1);
    }

    T pop() override {
        auto top = _heap.front();
        _heap.front() = _heap.back();
        _heap.pop_back();
        percolateDown(0);
        return top;
    }

    T top() const override {
        return _heap.front();
    }
};

#endif //BINARY_HEAP_H