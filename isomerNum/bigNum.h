#ifndef BIGNUM_H
#define BIGNUM_H

typedef struct bigNum{
    unsigned int num;
    struct bigNum *p;
} bigN; 

// 请不要直接访问 bigNum 的内部成员，注意 num 首位为始终零，防溢出

bigN b_add(bigN, bigN);
bigN b_mins(bigN, bigN);
bigN b_mult(bigN, bigN);
bigN b_div(bigN, bigN);

char* b_show(bigN);

void b_drop(bigN); // 必须调用

#endif // BIGNUM_H
