int prox_alkane(int){ //TODO
    return 0;
}

int exct_alkyl(int n){
    if(n==0||n==1||n==2) //最简单的情况
        return 1;
    int sum = 0; --n;
    if(n%3==0) { //三个均相等
        int part = exct_alkyl(n/3);
        sum += part*(part+1)*(part+2)/6;
    }
    for(int a=n/3+1;a<=n;a++){
        int part = exct_alkyl(a);
        if(a<=n/2) // 最大的相等
            sum += part*(part+1)*exct_alkyl(n-2*a)/2;
        if((n-a)%2==0) {// 最小的相等
            int part2 = exct_alkyl((n-a)/2);
            sum += part*part2*(part2+1)/2;
        }
        int b=(n-a)/2+1;
        while(b<=n-a && b<a){
            sum += part*exct_alkyl(b)*exct_alkyl(n-a-b);
            b++;
        }
    }
    return sum;
}

int exct_alkane(int){ //TODO
    return 0;
}
