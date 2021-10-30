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
            sum += part*exct_alkyl((n-a)/2)*(exct_alkyl((n-a)/2)+1)/2;
        }
        int b=(n-a)/2+1;
        while(b<=n-a && b<a){
            sum += part*exct_alkyl(b)*exct_alkyl(n-a-b);
            b++;
        }
    }
    return sum;
}

int exct_signAlkane(int n){
    int sum = 0; --n;
    if(n%4==0) { //四个均相等
        int part = exct_alkyl(n/4);
        sum += part*(part+1)*(part+2)*(part+3)/10;
    }
    for(int i=0;i<=n/3;i++){ //三个相等
        int part = exct_alkyl(i);
        if(n%4!=0||i!=n/4)
            sum += part*(part+1)*(part+2)*exct_alkyl(n-3*i)/6;
    }
    if(n%2==0){
        for(int i=0;i<n/4;i++) //两组两个相等
            sum += exct_alkyl(i)*(exct_alkyl(i)+1)*(exct_alkyl(n/2-i)+1)*exct_alkyl(n/2-i)/4;
        if(n%4!=0)
            sum += exct_alkyl(n/4)*(exct_alkyl(n/4)+1)*exct_alkyl(n/2-n/4)*(exct_alkyl(n/2-n/4)+1)/4;
    }
    for(int i=0;i<=n/2;i++) //一组两个相等
        for(int j=0;j<=n;j++)
            if(n-2*i-j<j && n-2*i-j!=i && i!=j && n-2*i-j>=0)
                sum += exct_alkyl(i)*(exct_alkyl(i)+1)*exct_alkyl(n-2*i-j)*exct_alkyl(j)/2;
    for(int a=3;a<n;a++)
        for(int b=2;b<a;b++)
            for(int c=1;c<b;c++)
                if(n-a-b-c<c && n-a-b-c>=0)
                    sum += exct_alkyl(a)*exct_alkyl(b)*exct_alkyl(c)*exct_alkyl(n-a-b-c);
    return sum;
}

int exct_signBond(int n){
    int sum = 0;
    for(int i=1;i<n/2;i++)
        sum += exct_alkyl(i)*exct_alkyl(n-i);
    if(n%2==0)
        sum += exct_alkyl(n/2)*(exct_alkyl(n/2)+1)/2;
    else
        sum += exct_alkyl(n/2)*exct_alkyl(n/2+1);
    return sum;
}

int exct_alkane(int n){
    if(n%2==0)
        return exct_signAlkane(n)-exct_signBond(n)+exct_alkyl(n/2);
    else
        return exct_signAlkane(n)-exct_signBond(n);
}
