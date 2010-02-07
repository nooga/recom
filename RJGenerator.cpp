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
