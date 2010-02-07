//  Copyright (c) 2010, Marcin Gasperowicz All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//  
//  Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer. Redistributions in binary
//  form must reproduce the above copyright notice, this list of conditions and
//  the following disclaimer in the documentation and/or other materials
//  provided with the distribution.
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
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

