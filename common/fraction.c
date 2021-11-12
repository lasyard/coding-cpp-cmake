#include "fraction.h"
#include "gcd_lcm.h"

struct fraction fraction_make(int a, int b)
{
    struct fraction tmp;
    tmp.nume = a;
    tmp.deno = b;
    return tmp;
}

struct fraction fraction_reduce(struct fraction a)
{
    int m;
    if (a.deno < 0) {
        a.nume = -a.nume;
        a.deno = -a.deno;
    }
    if (a.nume < 0) {
        m = gcd(-a.nume, a.deno);
    } else {
        m = gcd(a.nume, a.deno);
    }
    if (m != 1) {
        a.nume /= m;
        a.deno /= m;
    }
    return a;
}

struct fraction fraction_neg(struct fraction a)
{
    a.nume = -a.nume;
    return a;
}

struct fraction fraction_recip(struct fraction a)
{
    int tmp;
    tmp = a.nume;
    a.nume = a.deno;
    a.deno = tmp;
    return a;
}

struct fraction fraction_add(struct fraction a, struct fraction b)
{
    struct fraction r;
    r.nume = a.nume * b.deno + b.nume * a.deno;
    r.deno = a.deno * b.deno;
    r = fraction_reduce(r);
    return r;
}

struct fraction fraction_sub(struct fraction a, struct fraction b)
{
    struct fraction r;
    r.nume = a.nume * b.deno - b.nume * a.deno;
    r.deno = a.deno * b.deno;
    r = fraction_reduce(r);
    return r;
}

struct fraction fraction_mul(struct fraction a, struct fraction b)
{
    struct fraction r;
    r.nume = a.nume * b.nume;
    r.deno = a.deno * b.deno;
    r = fraction_reduce(r);
    return r;
}

struct fraction fraction_div(struct fraction a, struct fraction b)
{
    struct fraction r;
    r.nume = a.nume * b.deno;
    r.deno = a.deno * b.nume;
    r = fraction_reduce(r);
    return r;
}

struct fraction int_to_fraction(int n)
{
    struct fraction tmp;
    tmp.nume = n;
    tmp.deno = 1;
    return tmp;
}

int fraction_to_int(const struct fraction a)
{
    if (a.deno == 1) {
        return a.nume;
    } else if (a.nume >= 0) {
        return a.nume / a.deno;
    } else {
        return -(-a.nume / a.deno);
    }
}

int fraction_compare(const struct fraction a, const struct fraction b)
{
    int r = a.nume * b.deno - b.nume * a.deno;
    return (r == 0) ? 0 : ((r > 0) ? 1 : -1);
}

int fraction_compare_int(const struct fraction a, int b)
{
    int r = a.nume - b * a.deno;
    return (r == 0) ? 0 : ((r > 0) ? 1 : -1);
}
