/* 
 * File:   RJStateSet.cpp
 * Author: nooga
 * 
 * Created on 3 luty 2010, 23:29
 */

#include "RJStateSet.h"
#include "global.h"


RJStateSet::RJStateSet() {
}

RJStateSet::RJStateSet(const RJStateSet& orig) {
}

RJStateSet::~RJStateSet() {
}

    void RJStateSet::add(list<int> l) {
        debug("adding",l);
     //   printf("hash %d\n",h(l));
        ss.push_back(pair<list<int>,int>(l,0));
    }

    bool RJStateSet::has(list<int> l) {
        list<pair<list<int>,int> >::iterator it;

        for(it=ss.begin();it != ss.end(); it++) {

            if((*it).first == l) return true;

        }
        return false;

    }

    list<int> RJStateSet::unmarked() {
        list<pair<list<int>,int> >::iterator it;

        for(it=ss.begin();it != ss.end(); it++) {

            if((*it).second == 0) return (*it).first;

        }

        return list<int>();
    }

    void RJStateSet::mark(list<int> l) {
        list<pair<list<int>,int> >::iterator it;

        for(it=ss.begin();it != ss.end(); it++) {

            if((*it).first == l) (*it).second = 1;

        }
    }