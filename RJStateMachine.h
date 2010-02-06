/* 
 * File:   RJStateMachine.h
 * Author: nooga
 *
 * Created on 24 grudzień 2009, 00:33
 */

#ifndef _RJSTATEMACHINE_H
#define	_RJSTATEMACHINE_H

#include <list>

using namespace std;

class Tri {
public:
    Tri(int x, int y, int z);
    ~Tri();

    int a,b,c;
};

class RJStateMachine {
public:
    RJStateMachine();
    RJStateMachine(const RJStateMachine& orig);
    virtual ~RJStateMachine();

    void add_trans(int a, int b, int sym);
    void add_acc(int a);
    void add_state(int a);
    void set_start(int a);
    int new_state();

    list<int> closure(int a, int x);
    list<int> closure(list<int> l, int x);

    list<int> alphabet();
    int** table(int* x, int* y);

    void debug(char* name);
    
//private:

    list<int> every_trans(int a, int sym);
    list<int> every_trans(list<int> a, int sym);

    list<int> states;
    list<Tri*> trans;
    list<int> acc;
    int start;
    int nstates;

};

#endif	/* _RJSTATEMACHINE_H */

