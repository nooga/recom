/* 
 * File:   RJAutomaton.h
 * Author: nooga
 *
 * Created on 28 październik 2009, 14:45
 */

#ifndef _RJAUTOMATON_H
#define	_RJAUTOMATON_H

#include "global.h"
#include <list>
#include <ext/hash_map>
#include "RJStateMachine.h"

using namespace std;


class RJAutomaton {
public:
    RJAutomaton();
    RJAutomaton(const RJAutomaton& orig);
    RJAutomaton(Node* ast);
    virtual ~RJAutomaton();

    Triple* compile(Node* n);
    bool makeDSA();
    bool run(char* arg);
//private:
    Node* input;

    RJStateMachine* NSA;
    RJStateMachine* DSA;
    int** table;
    int tw, th;
    int starts;
    list<int> accs;
    list<int> alpha;


    int cur;
};

#endif	/* _RJAUTOMATON_H */

