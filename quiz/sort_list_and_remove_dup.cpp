#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>

struct ListNode {
    int nodeValue;
    struct ListNode *next;
};

struct ListNode *makeList(int values[], int size)
{
    int i;
    struct ListNode *head, *node;
    if (size == 0) {
        return nullptr;
    }
    head = new struct ListNode;
    head->nodeValue = values[0];
    node = head;
    for (i = 1; i < size; i++) {
        node->next = new struct ListNode;
        node = node->next;
        node->nodeValue = values[i];
    }
    node->next = nullptr;
    return head;
}

void destroyList(struct ListNode *head)
{
    struct ListNode *current, *next;
    current = head;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

std::ostream &operator<<(std::ostream &os, const ListNode *head)
{
    const struct ListNode *p;
    for (p = head; p != nullptr; p = p->next) {
        os << p->nodeValue << ", ";
    }
    os << std::endl;
    return os;
}

struct ListNode *sortList(struct ListNode *head)
{
    struct ListNode *prev, *current, *end;
    if (head == nullptr) {
        return nullptr;
    }
    end = nullptr;
    while (head->next != end) {
        current = head;
        if (current->nodeValue > current->next->nodeValue) {
            head = current->next;
            current->next = current->next->next;
            head->next = current;
        } else {
            current = current->next;
        }
        prev = head;
        while (current->next != end) {
            if (current->nodeValue > current->next->nodeValue) {
                prev->next = current->next;
                current->next = current->next->next;
                prev->next->next = current;
            } else {
                current = current->next;
            }
            prev = prev->next;
        }
        end = current;
    }
    return head;
}

void removeDupInSortedList(struct ListNode *head)
{
    struct ListNode *prev, *current;
    if (head == nullptr) {
        return;
    }
    for (prev = head, current = head->next; current != nullptr; current = prev->next) {
        if (current->nodeValue == prev->nodeValue) {
            prev->next = current->next;
            delete current;
        } else {
            prev = current;
        }
    }
}

bool listEquals(struct ListNode *head, int a[])
{
    int i;
    struct ListNode *p;
    for (i = 0, p = head; p != nullptr; p = p->next) {
        if (a[i] != p->nodeValue) {
            return false;
        }
        ++i;
    }
    return true;
}

TEST_CASE("Test removeDupInSortedList()")
{
    int a[]{4, 2, 3, 0, 1, 3, 2, 1, 2, 3, 3, 4, 5};
    struct ListNode *list = makeList(a, sizeof(a) / sizeof(int));
    std::cout << "Before Sorting:" << std::endl;
    std::cout << list;
    // GNU g++ does not support this, but clang++ does.
    // CHECK(listEquals(list, (int[]){4, 2, 3, 0, 1, 3, 2, 1, 2, 3, 3, 4, 5}));
    int b[]{4, 2, 3, 0, 1, 3, 2, 1, 2, 3, 3, 4, 5};
    CHECK(listEquals(list, b));
    list = sortList(list);
    std::cout << "After Sorting, Before Dedup:" << std::endl;
    std::cout << list;
    int c[]{0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5};
    CHECK(listEquals(list, c));
    removeDupInSortedList(list);
    std::cout << "After Dedup:" << std::endl;
    std::cout << list;
    int d[]{0, 1, 2, 3, 4, 5};
    CHECK(listEquals(list, d));
    destroyList(list);
}
