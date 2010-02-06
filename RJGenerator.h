/* 
 * File:   RJGenerator.h
 * Author: nooga
 *
 * Created on 4 luty 2010, 02:15
 */

#ifndef _RJGENERATOR_H
#define	_RJGENERATOR_H

#include "global.h"

class RJGenerator {
public:
    RJGenerator(int** tab, int stateno, int alphno, list<int> alph, list<int> acc, int st);
    RJGenerator(const RJGenerator& orig);
    virtual ~RJGenerator();

    void showAsm(char* name);

private:

    int** table;
    int sno;
    int ano;
    int* alfa;
    list<int> accs;
    int start;

};

#endif	/* _RJGENERATOR_H */

