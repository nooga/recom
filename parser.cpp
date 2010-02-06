
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "global.h"

#include "RJAutomaton.h"
#include "RJGenerator.h"

class RJParser {
public:
	RJParser(FILE*);
	RJParser(char*);
	RJParser();
	
	~RJParser();
	
	Node* parse();
	
private:
	char getc();
	void ungetc();
	void accept(char);
        bool is_special(char);
//metody parsowania
	Node* altexp();
	Node* conexp();
	Node* quantexp();
	Node* atom();
        Node* cclass();
//koniec mp
	int pos;
	int len;
        char cur;
	char* buffer;

    //   void parse_error(const char*);
};


RJParser::RJParser() {
	pos = 0;
}

RJParser::RJParser(FILE* f) {
	// TODO
}

RJParser::RJParser(char* string) {
	buffer = string;
	len = strlen(string);
	pos = 0;
}

RJParser::~RJParser() {
	free(buffer); //konieczne?
}


char RJParser::getc() {
	if(pos < len) return buffer[pos++];
	else		return 0;
}

void RJParser::ungetc() {
	if(pos > 0) pos -= 1;
}

void RJParser::accept(char x) {
 //   printf("%c == %c\n", cur,x);
	if(cur == x)         cur = getc();
        else                 throw "unexpected symbol";
}

inline bool RJParser::is_special(char x) {
    return (x == '*' || x == '?' || x == '+'  || x == ')' || x == '|' || x == 0);
}

Node* RJParser::altexp() {
 //   printf("alt\n");
	Node *a, *b;
	a = conexp();
	if(cur == '|') {
		accept('|');
		b = altexp();
		return node(ALT, a,b);
	} else {
		return a;
	}
}

Node* RJParser::conexp() {
  //  printf("con\n");
	Node *a, *b;
	a = quantexp();
        if(!is_special(cur)) {
            b = conexp();
            return node(CON, a,b);
        } else {
            return a;
        }
}

Node* RJParser::quantexp() {
//    printf("quant\n");
	Node *a;
	a = atom();
	switch(cur) {
	case '*': accept('*'); return node(STAR, a, 0);
	case '+': accept('+'); return node(PLUS, a, 0);
	case '?': accept('?'); return node(OPT, a, 0);
	default:
		return a;
	}
}

Node* RJParser::atom() {
   // printf("atom %c\n", buffer[pos]);
	Node* a;
        Node* b;
	if(cur == '(') {
		accept('(');
		a = altexp();
		accept(')');
		return a;
        } else if(cur == '[') {
            return cclass();
	} else if(cur == '.') {
		accept('.');
		return node(ANY, 0,0);
        } else if(cur == '\\') {
            accept('\\');
            a = node(ATOM,0,0);
            switch(cur) {
                case '\\': a->val = '\\'; break;
                case 'n': a->val = '\n'; break;
                case 't': a->val = '\t'; break;
                case 'd':
                    a->val = '0';
                    b = node(ATOM,0,0);
                    b->val = '9';
                    accept(cur);
                    return node(RAN,a,b);
                default:
                    a->val = cur;
            }
            accept(cur);
            return a;
	} else if(!is_special(cur)) {
		a = node(ATOM,0,0);
		a->val = cur;
		accept(cur);
		return a;
        } else if(cur == 0) {
            return node(NONE,0,0);
	} else {
            //TODO error
            throw "bad atom";
            return a;
        }
}
/*
Node* RJParser::quantexp() {
//    printf("quant\n");
	Node *a;
	a = atom();
	switch(cur) {
	case '*': accept('*'); return node(STAR, a, 0);
	case '+': accept('+'); return node(PLUS, a, 0);
	case '?': accept('?'); return node(OPT, a, 0);
	default:
		return a;
	}
}

Node* RJParser::atom() {
   // printf("atom %c\n", buffer[pos]);
	Node* a;
        Node* b;
	if(cur == '(') {
		accept('(');
		a = altexp();
		accept(')');
		return a;
        } else if(cur == '[') {
            return cclass();
	} else if(cur == '.') {
		accept('.');
		return node(ANY, 0,0);
        } else if(cur == '\\') {
            accept('\\');
            a = node(ATOM,0,0);
            switch(cur) {
                case '\\': a->val = '\\'; break;
                case 'n': a->val = '\n'; break;
                case 't': a->val = '\t'; break;
                case 'd':
                    a->val = '0';
                    b = node(ATOM,0,0);
                    b->val = '9';
                    accept(cur);
                    return node(RAN,a,b);
                default:
                    a->val = cur;
            }
            accept(cur);
            return a;
	} else if(!is_special(cur)) {
		a = node(ATOM,0,0);
		a->val = cur;
		accept(cur);
		return a;
        } else if(cur == 0) {
            return node(NONE,0,0);
	} else {
            //TODO error
            throw "bad atom";
            return 0;
        }
}

Node* RJParser::cclass() {
    char c;
    char accum[256];
    int i = 0;
    accept('[');
    c = cur;
    while(c != ']') {
        accum[i++] = c;
            return 0;
        }
}
*/

Node* RJParser::cclass() {
    char c;
    char accum[256];
    int i = 0;
    accept('[');
    c = cur;
    while(c != ']') {
        accum[i++] = c;
        c = getc();
    }
    accum[i] = 0;
   // printf("%s %d",accum,i);
    cur = buffer[pos-1];
    accept(']');
  //  printf("class %s\n",accum);
    return node(RAN,0,0);
}

Node* RJParser::parse() {

	Node* n = 0;
        cur = getc();
        try {
            n = altexp();
            accept(0);
        } catch(const char* e) {
            printf("Parse error: %s!\n", e);
        }

        return n;
}

/*void RJParser::parse_error(const char* err) {
    printf("Parse error: %s\n", err);
}*/



int main(int argc, char* argv[]) {

    char* rege;
    if(argc > 1)

        rege = argv[1];
    else
        rege = "a|b";


    RJParser* p = new RJParser(rege);
    Node* n;
    n = p->parse();

    FILE* f = fopen("ast","w+");

    fprintf(f,"graph \"%s\" {\n" ,rege);
    node_dot(n,f);
    fprintf(f,"}\n");
    fclose(f);

    RJAutomaton* a = new RJAutomaton(n);

    RJGenerator* g = new RJGenerator(a->table,a->th,a->tw,a->alpha,a->accs,a->starts);

    g->showAsm("test");

    return 0;
}

