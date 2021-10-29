#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

struct node {
    int data;
    node *left, *right;
};

bool isFull(node *root)
{
    if (root == nullptr) {
        return false;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return true;
    }
    if (isFull(root->left) && isFull(root->right)) {
        return true;
    }
    return false;
}

enum Property {
    NONE,
    COMPLETE,
    PERFECT,
};

Property check(node *root, int &depth)
{
    depth = 0;
    if (root == nullptr) {
        return PERFECT;
    }
    int ld, rd;
    Property lp = check(root->left, ld);
    Property rp = check(root->right, rd);
    Property p = NONE;
    if (lp == PERFECT) {
        if (rp == PERFECT) {
            if (ld == rd) {
                p = PERFECT;
            } else if (ld == rd + 1) {
                p = COMPLETE;
            }
        } else if (rp == COMPLETE) {
            if (ld == rd) {
                p = COMPLETE;
            }
        }
    } else if (lp == COMPLETE) {
        if (rp == PERFECT && ld == rd + 1) {
            p = COMPLETE;
        }
    }
    depth = (ld >= rd ? ld : rd) + 1;
    return p;
}

node *makeBtree(int list[], int size, int current)
{
    if (current >= size || list[current] < 0) {
        return nullptr;
    }
    node *node = new struct node;
    node->data = list[current];
    int left = current + current + 1;
    int right = current + current + 2;
    node->left = makeBtree(list, size, left);
    node->right = makeBtree(list, size, right);
    return node;
}

void destroyBtree(node *root)
{
    if (root == nullptr) {
        return;
    }
    destroyBtree(root->left);
    destroyBtree(root->right);
    delete root;
}

TEST_CASE("Test isFull()")
{
    SUBCASE("empty")
    {
        CHECK_FALSE(isFull(nullptr));
    }
    SUBCASE("one node")
    {
        int list[] = {0};
        node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
        CHECK(isFull(tree));
        destroyBtree(tree);
    }
    SUBCASE("multi nodes true")
    {
        int list[] = {0, 1, 2, -1, -1, 5, 6};
        node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
        CHECK(isFull(tree));
        destroyBtree(tree);
    }
    SUBCASE("multi nodes false")
    {
        int list[] = {0, 1, 2, -1, 4, 5, 6};
        node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
        CHECK_FALSE(isFull(tree));
        destroyBtree(tree);
    }
}

TEST_CASE("Test check()")
{
    SUBCASE("left: PERFECT, right: PERFECT => PERFECT")
    {
        int list[] = {0, 1, 2, 3, 4, 5, 6};
        node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
        int depth;
        CHECK(check(tree, depth) == PERFECT);
        CHECK(depth == 3);
        destroyBtree(tree);
    }
    SUBCASE("left: PERFECT, right: PERFECT => COMPLETE")
    {
        int list[] = {0, 1, 2, 3, 4};
        node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
        int depth;
        CHECK(check(tree, depth) == COMPLETE);
        CHECK(depth == 3);
        destroyBtree(tree);
    }
    SUBCASE("left: PERFECT, right: COMPLETE => COMPLETE")
    {
        int list[] = {0, 1, 2, 3, 4, 5};
        node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
        int depth;
        CHECK(check(tree, depth) == COMPLETE);
        CHECK(depth == 3);
        destroyBtree(tree);
    }
    SUBCASE("left: COMPLETE, right: PERFECT => COMPLETE")
    {
        int list[] = {0, 1, 2, 3, 4, 5, 6, 7};
        node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
        int depth;
        CHECK(check(tree, depth) == COMPLETE);
        CHECK(depth == 4);
        destroyBtree(tree);
    }
    SUBCASE("left: COMPLETE, right: PERFECT => NONE")
    {
        int list[] = {0, 1, 2, 3, -1, 5, 6};
        node *tree = makeBtree(list, sizeof(list) / sizeof(int), 0);
        int depth;
        CHECK(check(tree, depth) == NONE);
        CHECK(depth == 3);
        destroyBtree(tree);
    }
}
