/* 
 * File:   RJStateSet.h
 * Author: nooga
 *
 * Created on 3 luty 2010, 23:29
 */

#ifndef _RJSTATESET_H
#define	_RJSTATESET_H

#include <list>

using namespace std;

class RJStateSet {
public:
    RJStateSet();
    RJStateSet(const RJStateSet& orig);
    virtual ~RJStateSet();

    void add(list<int> l);
    bool has(list<int> l);
    list<int> unmarked();
    void mark(list<int> l);

private:

    list<pair<list<int>,int> > ss;

};

#endif	/* _RJSTATESET_H */

