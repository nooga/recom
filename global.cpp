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
#include "global.h"




int nodec;

Node* node(NodeTyp typ, Node* l, Node* r) {
	Node* a = (Node*)malloc(sizeof(Node));
	a->l = l;
	a->r = r;
	a->typ = typ;
	a->val = '#';
        a->n = nodec++;
	return a;
}



Triple* triple(int a, int b, int c) {
    Triple* temp = (Triple*)malloc(sizeof(Triple));
    temp->a = a;
    temp->b = b;
    temp->c = c;
    //printf("triple %d %d %d\n",a,b,c);
    return temp;
}

const char* dbg_data[9] = {"none","atom","any","alt","con","star","plus","opt","ran"};
const char* dbg_data_dot[9] = {"none","atom",".","|",":","*","+","?","..."};

void node_dbg(Node* n, int k) {
        if(n == 0) return;
	for(int i=0;i<k;i++) printf("\t");
	printf("%s (%c)\n", dbg_data[n->typ], n->val);
	if(n->l != 0) node_dbg(n->l,k+1);
	if(n->r != 0) node_dbg(n->r,k+1);
}


void node_dot(Node* n, FILE* f, int k) {
    if(n == 0) return;


    if(n->typ != ATOM)
        fprintf(f, "n%d [label = \"%s\"];\n",n->n,dbg_data_dot[n->typ]);
    else
        fprintf(f, "n%d [label = \"%c\"];\n",n->n,n->val);


    if(n->l != 0) {
        fprintf(f,"n%d -- n%d;\n", n->n, n->l->n);
        node_dot(n->l,f,k+1);
    }
    if(n->r != 0) {
        fprintf(f,"n%d -- n%d;\n", n->n, n->r->n);
        node_dot(n->r,f,k+100);
    }
}


#include <list>

bool has(list<int> i, int s) {
    list<int>::iterator it;
    for(it=i.begin();it != i.end(); it++)
        if((*it) == s) return true;
    return false;
}

void debug(char* p, list<int> l) {
  /*  printf("DBG %s ",p);
    list<int>::iterator it;
    for(it = l.begin(); it != l.end(); it++) {
        printf("%d ",*it);
    }
    printf("\n");*/
}

int h(list<int> i) {
    return (i.front()+i.back())*i.size();
}


