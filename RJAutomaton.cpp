/* 
 * File:   RJAutomaton.cpp
 * Author: nooga
 * 
 * Created on 28 październik 2009, 14:45
 */

#include "RJAutomaton.h"
#include <stdlib.h>
#include "RJStateSet.h"


RJAutomaton::RJAutomaton() {
}

RJAutomaton::RJAutomaton(const RJAutomaton& orig) {
    this->input = orig.input;
}

RJAutomaton::RJAutomaton(Node* ast) {
    this->input = ast;

    NSA = new RJStateMachine();
    DSA = new RJStateMachine();
    try {
        Triple* c = compile(this->input);

        NSA->add_acc(c->b);
        NSA->set_start(c->a);

        NSA->debug("nsa");

        this->makeDSA();

    } catch(char* e) {
        printf("Error: %s !\n",e);
        exit(1);
    }
}

RJAutomaton::~RJAutomaton() {
    delete NSA;
    delete DSA;
}

///typedef enum {NONE, ATOM, ANY, ALT, CON, STAR, PLUS, OPT, RAN} NodeTyp;

Triple* RJAutomaton::compile(Node* n) {
    int a,b,c;
    Triple *p, *q;
    if(!n) return 0;
    
    switch(n->typ) {
        case ATOM:
            a = NSA->new_state();
            b = NSA->new_state();
            NSA->add_trans(a,b,n->val);
            return triple(a,b);
            break;

        case ANY:
            a = NSA->new_state();
            b = NSA->new_state();
            NSA->add_trans(a,b,AANY);
            return triple(a,b);
            break;

        case CON:
            p = compile(n->l);
            q = compile(n->r);
            NSA->add_trans(p->b,q->a,NIL);
            return triple(p->a, q->b);
            break;

        case ALT:
            p = compile(n->l);
            q = compile(n->r);
            a = NSA->new_state();
            b = NSA->new_state();

            NSA->add_trans(a,p->a, NIL);
            NSA->add_trans(a,q->a, NIL);
            NSA->add_trans(p->b,b, NIL);
            NSA->add_trans(q->b,b, NIL);
            return triple(a,b);
            break;

        case STAR:
            p = compile(n->l);
            a = NSA->new_state();
            b = NSA->new_state();

            NSA->add_trans(a,p->a, NIL);
            NSA->add_trans(p->b,b, NIL);
            NSA->add_trans(a,b, NIL);
            NSA->add_trans(p->b,p->a, NIL);
            return triple(a,b);
            break;

        case PLUS:
            p = compile(n->l);
            NSA->add_trans(p->b,p->a, NIL);
            return triple(p->a, p->b);
            break;

        case OPT:
            p = compile(n->l);
            a = NSA->new_state();
            b = NSA->new_state();

            NSA->add_trans(a,p->a, NIL);
            NSA->add_trans(a,b, NIL);
            NSA->add_trans(p->b,b, NIL);
            return triple(a,b);
            break;
        
        default:
            throw "NSA build failed";
    }

}


namespace std
{
 using namespace __gnu_cxx;
}



bool RJAutomaton::makeDSA() {

    RJStateSet* states = new RJStateSet();

    list<int>::iterator it;
    list<int>::iterator itt;

    list<int> alph = NSA->alphabet();

    list<int> v = NSA->closure(NSA->start, NIL);
    v.sort();
    states->add(v);
    DSA->add_state(h(v));

    DSA->set_start(h(v));

    list<int> t;
    list<int> u;


    while(true) {
        t.clear();
        t = states->unmarked();
        if(t.empty()) break;
        states->mark(t);

        for(it = alph.begin(); it != alph.end(); it++) {
            u = NSA->closure(NSA->every_trans(t,*it),NIL);
            u.sort();
            debug("t",t);
            debug("u",u);
            if(!states->has(u)) {
                states->add(u);

                DSA->add_state(h(u));

                for(itt=u.begin();itt != u.end();itt++) {
                    if(has(NSA->acc,*itt))
                        DSA->add_acc(h(u));
                }
            }

            DSA->add_trans(h(t),h(u),*it);
        }

    }

    DSA->debug("dsa");

    int x,y;
    int** tab = DSA->table(&x,&y);

    table = tab;
    tw = x;
    th = y;
    alpha = alph;

    int* tat = new int[th];
    int ta = 0;

    for(it = DSA->states.begin(); it != DSA->states.end(); it++) {
        tat[ta] = *it;
        if((*it) == DSA->start) starts = ta;
        ta++;
    }

    for(it = DSA->acc.begin(); it != DSA->acc.end(); it++)
        for(ta=0;ta<th;ta++)
            if((*it) == tat[ta]) accs.push_back(ta);

  /*  for(int iii=0;iii<y;iii++) {
        for(int jjj=0;jjj<x;jjj++)
            printf("%d ",tab[iii][jjj]);
        printf("\n");
    }*/

    return true; //TODO

}

bool RJAutomaton::run(char* arg) {

    return true; //TODO;
}