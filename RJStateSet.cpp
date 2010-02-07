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