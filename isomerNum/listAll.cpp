#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

class alkyl{
private:
    string names;
    int depths;
    alkyl *nexts;

public:
    inline alkyl(){
        this->nexts = NULL;
    }
    alkyl(string name, int depth, alkyl* last = NULL){
        this->names = name;
        this->depths = depth;
        this->nexts = NULL;
        if(last)
            last->setNext(this);
    }
    alkyl(alkyl *in1, alkyl *in2 = NULL, alkyl *in3 = NULL, alkyl* last = NULL){
        alkyl *from[3] = {in1, in2, in3};
        this->depths = from[1]->depth() + 1;
        int max = 0, whiHave[3];
        for(int i=0; i<3; i++){
            if(from[i]!=NULL && from[i]->name()!="\0"){
                whiHave[max] = i;
                max++;
                if(from[i]->depth() > this->depths-1)
                    this->depths = from[i]->depth() + 1;
            }
        }
        this->names = "C";
        for(int i=0; i<max; i++){
            if(i==max-1)
                this->names += from[whiHave[i]]->name();
            else
                this->names += "("+ from[whiHave[i]]->name() + ")";
        }
        this->nexts = NULL;
        if(last)
            last->setNext(this);
    }
    inline ~alkyl(){
        delete this->nexts;
    }
    inline void setThis(string name, int depth){
        this->names = name;
        this->depths = depth;
    }
    inline void setThis(const char* name,const int depth){
        this->names = name;
        this->depths = depth;
    }
    inline string name(){
        return this->names;
    }
    inline int depth(){
        return this->depths;
    }
    inline void setNext(alkyl* next){
        this->nexts = next;
    }
    inline alkyl* next(){
        return this->nexts;
    }
    string verName(){
        string fiName = "\0";
        int sign = 0, blokEnd = 0, blokEnd2 = 0;
        for(int i=this->names.size()-1; i>=0; i--){
            if(this->names[i]==')'){
                if(!sign)
                    if(blokEnd){
                        blokEnd2 = blokEnd;
                        blokEnd = i;
                    }
                    else
                        blokEnd = i;
                sign++;
            } else if(this->names[i]=='C' && !sign){
                fiName += "C";
                if(this->names[i+1]=='('){
                    fiName += "(" + this->names.substr(i+2,blokEnd-i-2) + ")";
                    if(blokEnd2)
                        fiName += "(" + this->names.substr(blokEnd+2,blokEnd2-blokEnd-2) + ")";
                    blokEnd = blokEnd2 = 0;
                }
            } else if(this->names[i]=='(')
                sign--;
        }
        return fiName;
    }
};

namespace lsa{

string in_lsMonosub(char* substit, alkyl *in1, alkyl *in2 = NULL, alkyl *in3 = NULL){
    alkyl *from[3] = {in1, in2, in3};
    string fiName;
    int max = 0, whiHave[3];
    for(int i=0; i<3; i++)
        if(from[i]!=NULL && from[i]->name()!="\0"){
            whiHave[max] = i;
            max++;
        }
    switch(max){
        case 1:
            fiName = substit;
            fiName += "C" + from[whiHave[0]]->name();
            break;
        case 2:
            fiName = from[whiHave[0]]->verName() + "C(" + substit + ")" + from[whiHave[1]]->name();
            break;
        case 3:
            fiName = from[0]->verName() + "C(" + substit + ")(" + from[1]->name() + ")" + from[2]->name();
    }
    return fiName;
}

void in_lsAlkylPart(alkyl* fiAlkyl, int n, alkyl* from){
    string mainChain = "\0";
    for(int i=0;i<n;i++)
        mainChain += "C";
    fiAlkyl->setThis(mainChain,n);
    alkyl* thisAlkyl = fiAlkyl;
    n--;
    if(n%3==0) // three are the same
        for(alkyl* comes = &from[n/3]; comes; comes = comes->next())
        for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
        for(alkyl* comes3 = comes2; comes3; comes3 = comes3->next())
            thisAlkyl = new alkyl(comes, comes2, comes3, thisAlkyl);
    for(int a=n/3+1;a<n;a++){
        if(a<=n/2) // biggest are the same
            for(alkyl* comes = &from[a]; comes; comes = comes->next())
            for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[n-2*a]; comes3; comes3 = comes3->next())
                thisAlkyl = new alkyl(comes, comes2, comes3, thisAlkyl);
        if((n-a)%2==0) // smallest are the same
            for(alkyl* comes = &from[(n-a)/2]; comes; comes = comes->next())
            for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[a]; comes3; comes3 = comes3->next())
                thisAlkyl = new alkyl(comes, comes2, comes3, thisAlkyl);
        int b=(n-a)/2+1;
        while(b<=n-a && b<a){
            for(alkyl* comes = &from[a]; comes; comes = comes->next())
            for(alkyl* comes2 = &from[b]; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[n-a-b]; comes3; comes3 = comes3->next())
                thisAlkyl = new alkyl(comes, comes2, comes3, thisAlkyl);
            b++;
        }
    }
}

void lsMonosub(int n, char* substit){
    alkyl *from = new alkyl[n];
    from[0].setThis("\0",0);
    from[1].setThis("C",1);
    for(int i=2;i<n;i++)
        in_lsAlkylPart(&from[i], i, from);
    string mainChain = substit;
    for(int i=0;i<n;i++)
        mainChain += "C";
    cout<<mainChain<<endl;
    n--;
    if(n%3==0) // three are the same
        for(alkyl* comes = &from[n/3]; comes; comes = comes->next())
        for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
        for(alkyl* comes3 = comes2; comes3; comes3 = comes3->next())
            cout<<in_lsMonosub(substit, comes, comes2, comes3)<<endl;
    for(int a=n/3+1;a<n;a++){
        if(a<=n/2) // biggest are the same
            for(alkyl* comes = &from[a]; comes; comes = comes->next())
            for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[n-2*a]; comes3; comes3 = comes3->next())
                cout<<in_lsMonosub(substit, comes, comes2, comes3)<<endl;
        if((n-a)%2==0) // smallest are the same
            for(alkyl* comes = &from[(n-a)/2]; comes; comes = comes->next())
            for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[a]; comes3; comes3 = comes3->next())
                cout<<in_lsMonosub(substit, comes, comes2, comes3)<<endl;
        int b=(n-a)/2+1;
        while(b<=n-a && b<a){
            for(alkyl* comes = &from[a]; comes; comes = comes->next())
            for(alkyl* comes2 = &from[b]; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[n-a-b]; comes3; comes3 = comes3->next())
                cout<<in_lsMonosub(substit, comes, comes2, comes3)<<endl;
            b++;
        }
    }
    delete []from;
}

} // namespace lsa end
