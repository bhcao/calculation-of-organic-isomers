#ifndef BIGNUM_H
#define BIGNUM_H

typedef struct bigNum{
    unsigned int num;
    struct bigNum *p;
} bigN;

bigN b_add(bigN, bigN);
bigN b_mins(bigN, bigN);
bigN b_mult(bigN, bigN);
bigN b_div(bigN, bigN);

void b_drop(bigN); // 必须调用

#endif // BIGNUM_H
