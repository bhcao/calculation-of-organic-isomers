int in_alkyl(int n, int* pAlkyl){
    int sum = 0;
    n--;
    if(n%3==0) //三个均相等
        sum += pAlkyl[n/3]*(pAlkyl[n/3]+1)*(pAlkyl[n/3]+2)/6;
    for(int a=n/3+1;a<=n;a++){
        if(a<=n/2) // 最大的相等
            sum += pAlkyl[a]*(pAlkyl[a]+1)*pAlkyl[n-2*a]/2;
        if((n-a)%2==0) // 最小的相等
            sum += pAlkyl[a]*pAlkyl[(n-a)/2]*(pAlkyl[(n-a)/2]+1)/2;
        int b=(n-a)/2+1;
        while(b<=n-a && b<a){
            sum += pAlkyl[a]*pAlkyl[b]*pAlkyl[n-a-b];
            b++;
        }
    }
    return sum;
}

#define ALKYL_LIST \
int *pAlkyl = new int[n+1]; \
for(int i=0; i<=n; i++){ \
    if(i==0 || i==1 || i==2) \
        pAlkyl[i] = 1; \
    else \
        pAlkyl[i] = in_alkyl(i, pAlkyl); \
} // 必须与 delete []pAlkyl 配合使用

int alkyl(int n){
    ALKYL_LIST
    int final = pAlkyl[n];
    delete []pAlkyl;
    return final;
}

int in_signAlkane(int n, int* pAlkyl){
    int sum = 0; --n;
    if(n%4==0) //四个均相等
        sum += pAlkyl[n/4]*(pAlkyl[n/4]+1)*(pAlkyl[n/4]+2)*(pAlkyl[n/4]+3)/24;
    for(int i=0;i<=n/3;i++) //三个相等
        if(n%4!=0||i!=n/4)
            sum += pAlkyl[i]*(pAlkyl[i]+1)*(pAlkyl[i]+2)*pAlkyl[n-3*i]/6;
    if(n%2==0){
        for(int i=0;i<n/4;i++) //两组两个相等
            sum += pAlkyl[i]*(pAlkyl[i]+1)*(pAlkyl[n/2-i]+1)*pAlkyl[n/2-i]/4;
        if(n%4!=0)
            sum += pAlkyl[n/4]*(pAlkyl[n/4]+1)*pAlkyl[n/2-n/4]*(pAlkyl[n/2-n/4]+1)/4;
    }
    for(int i=0;i<=n/2;i++) //一组两个相等
        for(int j=0;j<=n;j++)
            if(n-2*i-j<j && n-2*i-j!=i && i!=j && n-2*i-j>=0)
                sum += pAlkyl[i]*(pAlkyl[i]+1)*pAlkyl[n-2*i-j]*pAlkyl[j]/2;
    for(int a=3;a<n;a++)
        for(int b=2;b<a;b++)
            for(int c=1;c<b;c++)
                if(n-a-b-c<c && n-a-b-c>=0)
                    sum += pAlkyl[a]*pAlkyl[b]*pAlkyl[c]*pAlkyl[n-a-b-c];
    return sum;
}

int in_monoAlkene(int n, int *pAlkyl){
    int sum = 0;
    for(int i=1;i<n/2;i++)
        sum += pAlkyl[i]*pAlkyl[n-i];
    if(n%2==0)
        sum += pAlkyl[n/2]*(pAlkyl[n/2]+1)/2;
    else
        sum += pAlkyl[n/2]*pAlkyl[n/2+1];
    return sum;
}

int monoAlkene(int n){
    ALKYL_LIST
    int final = in_monoAlkene(n, pAlkyl);
    delete []pAlkyl;
    return final;
}

int alkane(int n){
    ALKYL_LIST
    int final;
    if(n%2==0)
        final = in_signAlkane(n, pAlkyl)-in_monoAlkene(n, pAlkyl)+pAlkyl[n/2];
    else
        final = in_signAlkane(n, pAlkyl)-in_monoAlkene(n, pAlkyl);
    delete []pAlkyl;
    return final;
}
