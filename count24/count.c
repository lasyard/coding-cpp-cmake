#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/fraction.h"

#define NUM 4

typedef struct fraction (*OP)(struct fraction, struct fraction);

struct number {
    struct fraction value;
    struct number *left, *right;
    OP op;
};

/* forward declaration */
static void count(int target, int num, struct number *numbers);
static void output_tree(const struct number *root);

static bool is_equal(struct fraction a, struct fraction b)
{
    return fraction_compare(a, b) == 0;
}

static bool is_equal_int(struct fraction a, int b)
{
    return fraction_compare_int(a, b) == 0;
}

static bool is_zero(struct fraction num)
{
    return is_equal_int(num, 0);
}

static struct fraction reverse_sub(struct fraction left, struct fraction right)
{
    return fraction_sub(right, left);
}

static struct fraction reverse_div(struct fraction left, struct fraction right)
{
    return fraction_div(right, left);
}

static bool is_add_sub(OP op)
{
    return op == fraction_add || op == fraction_sub || op == reverse_sub;
}

static bool is_op(OP op)
{
    return op != NULL;
}

static OP ops[] = {fraction_add, fraction_sub, reverse_sub, fraction_mul, fraction_div, reverse_div};

static void init_number(struct number *number, struct fraction value)
{
    number->value = value;
    number->left = number->right = NULL;
    number->op = NULL;
}

static void cal_number(struct number *number)
{
    number->value = number->op(number->left->value, number->right->value);
}

static void try_combination(int target, int num, struct number *numbers, int left, int right, OP op)
{
    if ((op == fraction_div && is_zero(numbers[right].value)) || (op == reverse_div && is_zero(numbers[left].value))) {
        return;
    }
    struct number *numbers_copy = (struct number *)malloc((num - 1) * sizeof(struct number));
    for (int i = 0; i < left; i++) {
        numbers_copy[i] = numbers[i];
    }
    for (int i = left + 1; i < right; i++) {
        numbers_copy[i] = numbers[i];
    }
    for (int i = right; i < num - 1; i++) {
        numbers_copy[i] = numbers[i + 1];
    }
    numbers_copy[left].op = op;
    numbers_copy[left].left = &numbers[left];
    numbers_copy[left].right = &numbers[right];
    cal_number(&numbers_copy[left]);
    count(target, num - 1, numbers_copy);
    free(numbers_copy);
}

static void output_tree_with_para(const struct number *root)
{
    printf("(");
    output_tree(root);
    printf(")");
}

static void output_tree_cond(const struct number *root, bool (*cond)(const OP op))
{
    if (cond(root->op)) {
        output_tree_with_para(root);
    } else {
        output_tree(root);
    }
}

static void output_tree(const struct number *root)
{
    if (!is_op(root->op)) {
        assert(root->left == NULL && root->right == NULL);
        printf("%d", fraction_to_int(root->value));
        return;
    }
    assert(root->left != NULL && root->right != NULL);
    OP op = root->op;
    struct number *left, *right;
    if (op == reverse_sub || op == reverse_div) {
        left = root->right;
        right = root->left;
    } else {
        left = root->left;
        right = root->right;
    }
    if (op == fraction_add) {
        output_tree(left);
        printf(" + ");
        output_tree(right);
    } else if (op == fraction_sub || op == reverse_sub) {
        output_tree(left);
        printf(" - ");
        output_tree_cond(right, is_add_sub);
    } else if (op == fraction_mul) {
        output_tree_cond(left, is_add_sub);
        printf(" * ");
        output_tree_cond(right, is_add_sub);
    } else if (op == fraction_div || op == reverse_div) {
        output_tree_cond(left, is_add_sub);
        printf(" / ");
        output_tree_cond(right, is_op);
    }
}

static void output_solution(const struct number *root)
{
    output_tree(root);
    printf("\n");
}

static bool exists(struct number numbers[], int start, int end, struct number target)
{
    for (; start < end; ++start) {
        if (is_equal(numbers[start].value, target.value)) {
            return true;
        }
    }
    return false;
}

static void count(int target, int num, struct number *numbers)
{
    if (num == 1) {
        if (is_equal_int(numbers[0].value, target)) {
            struct number *root = &numbers[0];
            assert(root != NULL);
            output_solution(root);
        }
        return;
    }
    for (int i = 0; i < num - 1; i++) {
        // Dedup, if the same value has been selected, skip it
        if (exists(numbers, 0, i, numbers[i])) {
            continue;
        }
        for (int j = i + 1; j < num; j++) {
            if (exists(numbers, 0, i, numbers[j]) || exists(numbers, i + 1, j, numbers[j])) {
                continue;
            }
            for (unsigned int k = 0; k < sizeof(ops) / sizeof(OP); k++) {
                try_combination(target, num, numbers, i, j, ops[k]);
            }
        }
    }
}

int main(void)
{
    printf("Please input four numbers: ");
    int num[NUM];
    scanf("%d %d %d %d", num, num + 1, num + 2, num + 3);
    struct number numbers[NUM];
    for (int i = 0; i < NUM; ++i) {
        init_number(&numbers[i], int_to_fraction(num[i]));
    }
    count(24, 4, numbers);
    return 0;
}
