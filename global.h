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

