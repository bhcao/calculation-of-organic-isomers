// "in_" means do not use it outside

namespace qct{

int in_alkyl(int n, int* pAlkyl){
    int sum = 0;
    n--;
    if(n%3==0) // three are the same
        sum += pAlkyl[n/3]*(pAlkyl[n/3]+1)*(pAlkyl[n/3]+2)/6;
    for(int a=n/3+1;a<=n;a++){
        if(a<=n/2) // biggest are the same
            sum += pAlkyl[a]*(pAlkyl[a]+1)*pAlkyl[n-2*a]/2;
        if((n-a)%2==0) // smallest are the same
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
} // DO NOT forget to use "delete []pAlkyl"

int alkyl(int n){
    ALKYL_LIST
    int finals = pAlkyl[n];
    delete []pAlkyl;
    return finals;
}

int in_signAlkane(int n, int* pAlkyl){
    int sum = 0; --n;
    if(n%4==0) // four are the same
        sum += pAlkyl[n/4]*(pAlkyl[n/4]+1)*(pAlkyl[n/4]+2)*(pAlkyl[n/4]+3)/24;
    for(int i=0;i<=n/3;i++) // three are the same
        if(n%4!=0||i!=n/4)
            sum += pAlkyl[i]*(pAlkyl[i]+1)*(pAlkyl[i]+2)*pAlkyl[n-3*i]/6;
    if(n%2==0){
        for(int i=0;i<n/4;i++) // two group with two are the same
            sum += pAlkyl[i]*(pAlkyl[i]+1)*(pAlkyl[n/2-i]+1)*pAlkyl[n/2-i]/4;
        if(n%4!=0)
            sum += pAlkyl[n/4]*(pAlkyl[n/4]+1)*pAlkyl[n/2-n/4]*(pAlkyl[n/2-n/4]+1)/4;
    }
    for(int i=0;i<=n/2;i++) // one group with two are the same
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
    int finals = in_monoAlkene(n, pAlkyl);
    delete []pAlkyl;
    return finals;
}

int alkane(int n){
    ALKYL_LIST
    int finals;
    if(n%2==0)
        finals = in_signAlkane(n, pAlkyl)-in_monoAlkene(n, pAlkyl)+pAlkyl[n/2];
    else
        finals = in_signAlkane(n, pAlkyl)-in_monoAlkene(n, pAlkyl);
    delete []pAlkyl;
    return finals;
}

#define maxn 50005

int falc(int n){
    int mul = 1;
    for(int i=2;i<=n;i++)
        mul *= i;
    return mul;
}

int cycloAlk(int n){
    int ans = 1;
    int flag[maxn];
    for(int i=3;i<=n;i++){
        for(int j=1;j<=i;j++)
            flag[j]=1;
        int jud1=0, jud2=1, jud[maxn]={0}, jud3=i;
        do{
            for(int j=1;j<=n;j++){
                if(flag[j]==1)
                    jud1++;
                if(jud1==jud3)
                    break;
            }
            for(int z=jud1;z<=n;z++){
                if(flag[z]!=0)
                    jud[jud2]++;
                else{
                    flag[z]=0;
                    flag[z+1]=1;
                    break;
                }
            }
            jud2++;
            jud3--;//移动指针
            int swi=1;
            for(int z=1;z<=jud2;z++)
                swi+=alkyl(jud[z]);
            ans+=swi;
        } while(jud3 != 0);
    }
    return ans;
}

} // namespace end
