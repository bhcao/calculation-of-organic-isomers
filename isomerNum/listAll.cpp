#include "listAll.h"

void alkyl::setThis(alkyl *in1, alkyl *in2 = NULL, alkyl *in3 = NULL){
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
}

string alkyl::verName(){
    string fiName = "\0";
    int sign = 0, blokEnd = 0, blokEnd2 = 0;
    for(int i=this->names.size()-1; i>=0; i--){
        if(this->names[i]==')'){
            if(!sign){
                if(blokEnd)
                    blokEnd2 = blokEnd;
                blokEnd = i;
            }
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
    alkyl* thisAlkyl = fiAlkyl;
    n--;
    bool first = true;
    if(n%3==0) // three are the same
        for(alkyl* comes = &from[n/3]; comes; comes = comes->next())
        for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
        for(alkyl* comes3 = comes2; comes3; comes3 = comes3->next()){
            if(first){
                fiAlkyl->setThis(comes, comes2, comes3);
                first = false;
            } else
                thisAlkyl = new alkyl(comes, comes2, comes3, thisAlkyl);
        }
    for(int a=n/3+1;a<=n;a++){
        if(a<=n/2) // biggest are the same
            for(alkyl* comes = &from[a]; comes; comes = comes->next())
            for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[n-2*a]; comes3; comes3 = comes3->next()){
                if(first){
                    fiAlkyl->setThis(comes, comes2, comes3);
                    first = false;
                } else
                    thisAlkyl = new alkyl(comes, comes2, comes3, thisAlkyl);
            }
        if((n-a)%2==0) // smallest are the same
            for(alkyl* comes = &from[(n-a)/2]; comes; comes = comes->next())
            for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[a]; comes3; comes3 = comes3->next()){
                if(first){
                    fiAlkyl->setThis(comes, comes2, comes3);
                    first = false;
                } else
                    thisAlkyl = new alkyl(comes, comes2, comes3, thisAlkyl);
            }
        int b=(n-a)/2+1;
        while(b<=n-a && b<a){
            for(alkyl* comes = &from[a]; comes; comes = comes->next())
            for(alkyl* comes2 = &from[b]; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[n-a-b]; comes3; comes3 = comes3->next()){
                if(first){
                    fiAlkyl->setThis(comes, comes2, comes3);
                    first = false;
                } else
                    thisAlkyl = new alkyl(comes, comes2, comes3, thisAlkyl);
            }
            b++;
        }
    }
}

void in_lsPartAlkene(alkyl* fiAlkyl, int n, alkyl* from){
    alkyl* thisAlkyl = fiAlkyl;
    n--;
    bool first = true;
    for(int i=0;i<n/2;i++)
        for(alkyl* comes = &from[i]; comes; comes = comes->next())
        for(alkyl* comes2 = &from[n-i]; comes2; comes2 = comes2->next()){
            if(first){
                fiAlkyl->setThis(comes, comes2);
                first = false;
            } else 
                thisAlkyl = new alkyl(comes, comes2, NULL, thisAlkyl);
        }
    if(n%2==0)
        for(alkyl* comes = &from[n/2]; comes; comes = comes->next())
        for(alkyl* comes2 = comes; comes2; comes2 = comes2->next()){
            if(first){
                fiAlkyl->setThis(comes, comes2);
                first = false;
            } else 
                thisAlkyl = new alkyl(comes, comes2, NULL, thisAlkyl);
        }
    else
        for(alkyl* comes = &from[n/2]; comes; comes = comes->next())
        for(alkyl* comes2 = &from[n/2+1]; comes2; comes2 = comes2->next()){
            if(first){
                fiAlkyl->setThis(comes, comes2);
                first = false;
            } else 
                thisAlkyl = new alkyl(comes, comes2, NULL, thisAlkyl);
        }
}

} // namespace lsa end
