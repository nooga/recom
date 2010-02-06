/* 
 * File:   RJStateMachine.cpp
 * Author: nooga
 * 
 * Created on 24 grudzień 2009, 00:33
 */

#include "RJStateMachine.h"

#include <stdio.h>
#include "global.h"
#include <stack>


Tri::Tri(int x, int y, int z) {
    this->a = x;
    this->b = y;
    this->c = z;
}

Tri::~Tri() {

}

RJStateMachine::RJStateMachine() {
    nstates = 0;
}

RJStateMachine::RJStateMachine(const RJStateMachine& orig) {
}

RJStateMachine::~RJStateMachine() {
    list<Tri*>::iterator it;
    for(it = trans.begin(); it != trans.end(); it++) {
        delete (*it);
    }
    trans.clear();
    states.clear();
}

void RJStateMachine::add_trans(int a, int b, int sym) {
    trans.push_back(new Tri(a,b,sym));
}

void RJStateMachine::add_state(int a) {
    states.push_back(a);
}

int RJStateMachine::new_state() {
    int x = nstates;
    this->add_state(nstates++);
    return x;
 //   printf("* n%d\n",states.back());
}

void RJStateMachine::set_start(int a) {
    start = a;
}

void RJStateMachine::add_acc(int a) {
    acc.push_back(a);
}

void RJStateMachine::debug(char* name) {

    FILE* f = fopen(name,"w+");

    fprintf(f,"\ndigraph %s {\n",name);

    list<int>::iterator iit;

    fprintf(f,"start [shape=none]\nstart -> n%d\n",start);

    for(iit = acc.begin(); iit != acc.end(); iit++)
        fprintf(f,"n%d [shape=doublecircle]\n",(*iit));

    list<Tri*>::iterator it;
    for(it = trans.begin(); it != trans.end(); it++) {
        if((*it)->c == -1)
            fprintf(f,"n%d -> n%d [label = \"&epsilon;\"]\n",(*it)->a,(*it)->b);
        else
        if((*it)->c == AANY) 
            fprintf(f,"n%d -> n%d [label = \"&alpha;\"]\n",(*it)->a,(*it)->b);
        else
            fprintf(f,"n%d -> n%d [label = %c]\n",((Tri*)*it)->a,(*it)->b, (*it)->c);
    }
    fprintf(f,"}\n\n");
}



list<int> RJStateMachine::every_trans(int a, int sym) {
    list<Tri*>::iterator it;
    list<int> temp;

    for(it = trans.begin(); it != trans.end(); it++)
        if((*it)->a == a && (*it)->c == sym) temp.push_back((*it)->b);

    return temp;
}

list<int> RJStateMachine::every_trans(list<int> a, int sym) {
    list<Tri*>::iterator it;
    list<int>::iterator itt;
    list<int> temp;
    for(itt = a.begin(); itt != a.end(); itt++) {
        for(it = trans.begin(); it != trans.end(); it++)
            if((*it)->a == (*itt) && (*it)->c == sym) temp.push_back((*it)->b);
    }
    return temp;
}

list<int> RJStateMachine::closure(int a, int x) {
      list<int> ec;
      list<int> temp;
      stack<int> s;

      s.push(a);
      ec.push_back(a);

      list<int>::iterator it;

      while(!s.empty()) {
          int t = s.top();
          s.pop();

          temp = this->every_trans(t,x);
          for(it=temp.begin();it != temp.end(); it++) {
              if(!has(ec,*it)) {
                  ec.push_back(*it);
                  s.push(*it);
              }
          }
      }

      return ec;
}

list<int> RJStateMachine::closure(list<int> a, int x) {
      list<int> ec;
      list<int> temp;
      stack<int> s;

      list<int>::iterator it;

      for(it = a.begin(); it != a.end(); it++) {
          s.push(*it);
          ec.push_back(*it);
      }

      while(!s.empty()) {
          int t = s.top();
          s.pop();

          temp = this->every_trans(t,x);
          for(it=temp.begin();it != temp.end(); it++) {
              if(!has(ec,*it)) {
                  ec.push_back(*it);
                  s.push(*it);
              }
          }
      }

      return ec;
}


list<int> RJStateMachine::alphabet() {
    list<int> temp;

    list<Tri*>::iterator it;

    int a;
    for(it = trans.begin(); it != trans.end(); it++) {
        a = (*it)->c;
        if(!has(temp, a) && a != NIL && a != AANY)
            temp.push_back(a);
    }

    return temp;
}



int** RJStateMachine::table(int* x, int* y) {
    int a,b;

    list<int> i = this->alphabet();
    list<Tri*>::iterator itt;

    a = i.size();
    b = states.size();

    int** temp = (int**)malloc(sizeof(int*)*b);
    int* al = (int*)malloc(sizeof(int)*a);
    int* sl = (int*)malloc(sizeof(int)*b);

    list<int>::iterator ia;

    int q=0,p=0,z=0;
    for(ia = i.begin(); ia != i.end(); ia++)
        al[q++] = *ia;

    q = 0;
    for(ia = states.begin(); ia != states.end(); ia++)
        sl[q++] = *ia;

    for(int m=0;m<b;m++) {
        temp[m] = (int*)malloc(sizeof(int)*a);
        for(int j=0;j<a;j++) {
            temp[m][j] = -1;
        }

    }

    for(itt = trans.begin(); itt != trans.end(); itt++) {
        q = -1;
        for(int m=0;m<a;m++) {
            if(al[m] == (*itt)->c) {
                q = m; break;
            }
        }
        if(q == -1) continue;

        p = -1;
        for(int m=0;m<b;m++) {
            if(sl[m] == (*itt)->a) {
                p = m; break;
            }
        }
        if(p == -1) continue;

        z = -1;
        for(int m=0;m<b;m++) {
            if(sl[m] == (*itt)->b) {
                z = m; break;
            }
        }
        if(z == -1) continue;

        temp[p][q] = z;
    }

    *x = a;
    *y = b;
    return temp;
}