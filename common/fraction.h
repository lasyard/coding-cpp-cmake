#ifndef _COMMON_FRACTION_H_
#define _COMMON_FRACTION_H_

struct fraction {
    int nume;
    int deno;
};

#ifdef __cplusplus
extern "C" {
#endif

/* It is ok to pass parameters by value, for there are only two ints in the struct. */

struct fraction fraction_make(int a, int b);

struct fraction fraction_reduce(struct fraction a);

struct fraction fraction_neg(struct fraction a);
struct fraction fraction_recip(struct fraction a);

struct fraction fraction_add(struct fraction a, struct fraction b);
struct fraction fraction_sub(struct fraction a, struct fraction b);
struct fraction fraction_mul(struct fraction a, struct fraction b);
struct fraction fraction_div(struct fraction a, struct fraction b);

struct fraction int_to_fraction(int n);
int fraction_to_int(const struct fraction a);

int fraction_compare(const struct fraction a, const struct fraction b);
int fraction_compare_int(const struct fraction a, int b);

#ifdef __cplusplus
}
#endif

#endif /* _COMMON_FRACTION_H_ */
