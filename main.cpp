// main.cpp
// Created by huhaolong on 2025/4/9 18:18.

#include <bits/stdc++.h>
#include "dsa/all.hpp"

using namespace std;

int main() {
    LRUCache c(2);
    std::vector<int> res;

    c.put(1, 1);
    c.put(2, 2);
    res.push_back(c.get(1));
    c.put(3,3);
    res.push_back(c.get(2));
    c.put(4, 4);
    res.push_back(c.get(1));
    res.push_back(c.get(3));
    res.push_back(c.get(4));

    for (int x : res) {
        cout << x << endl;
    }

    return 0;
}

