//
//  good.cpp
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/18.
//  Copyright (c) 2015年 albert. All rights reserved.
//

#include <time.h>
#include <iostream>
#include <sstream>
#include "comm.h"
#include "good.h"

using namespace std;

///
Good::Good(){
    clear();
}

///
Good::~Good(){
}

///
Good::Good(int aid, int aproducer_id):Good(){
    this->_id=aid;
    this->_producer_id=aproducer_id;
    this->_produce_time=time(NULL);
}

///
Good::Good(int aid, int aproducer_id, time_t aproduce_time){
    this->_id=aid;
    this->_producer_id=aproducer_id;
    this->_produce_time=aproduce_time;
}

///
Good& Good::operator=( const Good * pGood){
    if (!pGood)
    {
        clear();
    }
    else
    {
        this->_id=pGood->_id;
        this->_producer_id=pGood->_producer_id;
        this->_produce_time=pGood->_produce_time;
        this->_content=pGood->_content;
    }
    return *this;
}

///
bool Good::setGood(const Good *pGood){
    bool isOk=false;
    if (pGood==NULL)
    {
        this->_id=INVALIDID;
        this->_producer_id=INVALIDID;
        this->_produce_time=0;
    }
    else
    {
        this->_id=pGood->_id;
        this->_producer_id=pGood->_producer_id;
        this->_produce_time=pGood->_produce_time;
        isOk=true;
    }
    return isOk;
}


///
string Good::toString(){
    ostringstream format_message;
    struct tm* ptime=gmtime(&_produce_time);
    format_message<<"G:id("<<_id<<"),p_id("<<_producer_id<<")";
    if (ptime!=NULL){
        format_message<<",time("
              <<ptime->tm_year+1900<<"-"<<ptime->tm_mon<<"-"<<ptime->tm_mday
              <<" "<<ptime->tm_hour<<":"<<ptime->tm_min
              <<":"<<ptime->tm_sec<<")";
    }
    return format_message.str();
}

///
int Good::getID(){
    return _id;
}

///
void Good::clear(){
    this->_id=INVALIDID;
    this->_producer_id=INVALIDID;
    this->_content.clear();
    this->_produce_time=0;
}

