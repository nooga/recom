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
 * File:   global.h
 * Author: nooga
 *
 * Created on 28 październik 2009, 14:49
 */

#ifndef _GLOBAL_H
#define	_GLOBAL_H

#include <stdlib.h>
#include <stdio.h>
#include <list>

using namespace std;



typedef enum {NONE, ATOM, ANY, ALT, CON, STAR, PLUS, OPT, RAN} NodeTyp;
typedef struct _Node {
	NodeTyp typ;
        int n;
	char val;
	_Node *l, *r;
} Node;


Node* node(NodeTyp typ, Node* l, Node* r);

//f-cje do podgladania struktur node w formie tekstowej i graficznej

void node_dbg(Node* n, int k = 0);
void node_dot(Node* n, FILE* f, int k = 0);

typedef struct {
    int a,b,c;
} Triple;

Triple* triple(int a, int b, int c=0);
bool has(std::list<int> i, int s);
void debug(char* p, list<int> l);

int h(list<int> i) ;




#define NIL -1
#define AANY 1000

#endif	/* _GLOBAL_H */

