#include<stdlib.h>

void b_drop(bigN n){
    bigN *pLast = n.p;
    bigN *pThis = n.p;
    while(pThis!=NULL){
        pLast = pThis;
        pThis = pThis->p;
        free(pLast);
    }
}

bigN b_add(bigN n1, bigN n2){
    if(n1.num){
        bigN n1.p = (bigN*)malloc(sizeof(bigN));
    }
    b_drop(n2);
    return n1;
}

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
