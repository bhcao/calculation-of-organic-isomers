#ifndef LISTALL_H
#define LISTALL_H

#include <string>
using std::string;

class alkyl{
private:
    string names;
    int depths;
    alkyl *nexts;

public:
    inline alkyl(){
        this->nexts = NULL;
    }
    inline alkyl(string name, int depth, alkyl* last = NULL){
        this->names = name;
        this->depths = depth;
        this->nexts = NULL;
        if(last)
            last->setNext(this);
    }
    inline alkyl(alkyl *in1, alkyl *in2 = NULL, alkyl *in3 = NULL, alkyl* last = NULL){
        this->setThis(in1, in2, in3);
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
    void setThis(alkyl *in1, alkyl *in2, alkyl *in3);
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
    string verName();
};

namespace lsa{
    string in_lsMonosub(char* substit, alkyl *in1, alkyl *in2, alkyl *in3);
    void in_lsAlkylPart(alkyl* fiAlkyl, int n, alkyl* from);
    void in_lsPartAlkene(alkyl* fiAlkyl, int n, alkyl* from);
}

#endif // LISTALL_H
