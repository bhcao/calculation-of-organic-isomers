#include<stdlib.h>
#include<limits.h>
#include<stdio.h>

typedef struct bigNum{
    unsigned long num;
    struct bigNum *p;
} bigN;

void b_drop(bigN* n){
    bigN *pLast, *pThis = n->p;
    while(pThis != NULL){
        pLast = pThis;
        pThis = pThis->p;
        free(pLast);
    }
}

void b_add(bigN* n1, bigN* n2){
    bigN* n3 = n2;
    short carry = 0;
    while(n1 != NULL){
        n1->num += n2->num + carry;
        if(n1->num > LONG_MAX){
            n1->num -= LONG_MAX;
            n1->num--;
            carry = 1;
        } else 
            carry = 0;
        if(n1->p == NULL && (carry || n2->p != NULL)){
            n1->p = (bigN*)malloc(sizeof(bigN));
            n1->p->num = 0;
            n1->p->p = NULL;
        }
        n1 = n1->p;
        n2 = n2->p;
    }
    b_drop(n3);
}

/*
bigN b_mins(bigN n1, bigN n2){
    b_drop(n2);
    return n1;
}

bigN b_mult(bigN n1, bigN n2){
    b_drop(n2);
    return n1;
}

bigN b_div(bigN n1, bigN n2){
    b_drop(n2);
    return n1;
}

char* b_show(){
    return ;
}
*/

int main(){
    bigN test1 = {LONG_MAX, NULL}, test2 = {LONG_MAX, NULL};
    
    //test1.p = &test2;
    //test1.num += test2.num + 1;
    b_add(&test1, &test2);
    //if(&test1!=NULL)
    //printf("%li,%li", test1.num, (long int)test1.p);
    b_drop(&test1);
    return 0;
}
