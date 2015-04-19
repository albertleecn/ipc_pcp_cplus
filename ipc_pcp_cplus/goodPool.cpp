//
//  GoodPool.cpp
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/18.
//  Copyright (c) 2015年 albert. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "comm.h"
#include "goodPool.h"

GoodPool::GoodPool(){
    pList=new ListGood();
}

GoodPool::GoodPool(int aPoolSize):GoodPool(){
    changePoolSize(aPoolSize);
}

GoodPool::~GoodPool(){
    deleteAllGoods();
    delete pList;
}

///
bool GoodPool::deleteAllGoods(){
    bool isOk=false;
    if (!pList)
        return isOk;
    while (!pList->empty()){
        pList->pop_back();
    }
    isOk=true;
    return isOk;
}

///
bool GoodPool::changePoolSize(int aPoolSize){
    bool isOk=false;
    if (aPoolSize<0)
        return isOk;
    deleteAllGoods();
    Good* pGood;
    for (int i=0;i<aPoolSize;i++){
        pGood=new Good();
        pList->push_back(*pGood);
    }
    isOk=true;
    return isOk;
}

///
string GoodPool::toString(){
    ostringstream format_message;
    ListGood::iterator i;
    int index=0;
    for (i=pList->begin();i!=pList->end();i++){
        index++;
        format_message<<index << ":" << i->toString()<<"\n";
    }
    return format_message.str();
}

///
bool GoodPool::putGood(Good* pGood){
    bool isOk=false;
    ListGood::iterator i;
    for (i=pList->begin();i!=pList->end();i++){
        if (i->getID()==INVALIDID){
            isOk=i->setGood(pGood);
            //*i=*pGood;
            break;
        }
    }
    return isOk;
}

///
bool GoodPool::takeGood(Good* pGood){
    bool isOk=false;
    ListGood::iterator i;
    for (i=pList->begin();i!=pList->end();i++){
        if (i->getID()!=INVALIDID){
            *pGood=*i;
            i->clear();
            isOk=true;
            break;
        }
    }
    return isOk;
}



