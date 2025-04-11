// list.hpp
// Created by huhaolong on 2025/4/11 17:03.

#pragma once

struct ListNode {
    int key;
    ListNode* prev;
    ListNode* next;

    ListNode(int _key, ListNode* _prev, ListNode* _next) : key(_key), prev(_prev), next(_next){}
};

struct List {
    ListNode* head; // dummy head
    ListNode* tail; // dummy tail

    bool empty() { return head->next == tail; }

    List() {
        head = new ListNode(-1, nullptr, nullptr);
        tail = new ListNode(-1, nullptr, nullptr);
        head->next = tail;
        tail->prev = head;
    }
    ~List() {
        delete head;
        delete tail;
    }
};