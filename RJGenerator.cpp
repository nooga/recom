/* 
 * File:   RJGenerator.cpp
 * Author: nooga
 * 
 * Created on 4 luty 2010, 02:15
 */

#include "RJGenerator.h"

RJGenerator::RJGenerator(int** tab, int stateno, int alphno, list<int> alph, list<int> acc, int st) {
    table = tab;
    sno = stateno;
    ano = alphno;
    alfa = (int*)malloc(sizeof(int)*ano);
    accs = acc;
    start = st;

    list<int>::iterator it;
    int a = 0;
    for(it = alph.begin(); it != alph.end(); it++)
        alfa[a++] = *it;
}

RJGenerator::RJGenerator(const RJGenerator& orig) {
}

RJGenerator::~RJGenerator() {
}

void RJGenerator::showAsm(char* name) {
    printf("global %s_match\n",name);
    printf("%s_match:\n",name);
    printf("\tmov eax,0\n");
    printf("\tmov ebx,[esp+4]\n");
    printf("\tjmp s%d\n",start);
    for(int i=0;i<sno;i++) {
        printf("s%d:\tinc ax\n\tcmp byte [ebx+eax],0\n\tjz %s\n",i,has(accs,i)?"accept":"fail");
        for(int j=0;j<ano;j++) {
            if(table[i][j] != -1)
                printf("\tcmp byte [ebx+eax],'%c'\n\tjz s%d\n",alfa[j],table[i][j]);
        }
        printf("\tjmp fail\n");
    }

    printf("accept:\tmov eax,1\n\tret\nfail:\tmov eax,0\n\tret\n");
}
