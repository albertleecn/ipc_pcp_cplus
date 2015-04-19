//
//  ThreadArgs.cpp
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/19.
//  Copyright (c) 2015年 albert. All rights reserved.
//

#include "ThreadArgs.h"

///
ThreadArgs::ThreadArgs(){
    
}

///
ThreadArgs::~ThreadArgs(){
    
}

///
ThreadArgs& ThreadArgs::operator=( const ThreadArgs * pThreadArgs){
    this->id=pThreadArgs->id;
    this->goodCnt=pThreadArgs->goodCnt;
    this->pfinishedGood=pThreadArgs->pfinishedGood;
    this->pMutexPool=pThreadArgs->pMutexPool;
    this->pMutexStdout=pThreadArgs->pMutexStdout;
    this->pSemFull=pThreadArgs->pSemFull;
    this->pSemEmpty=pThreadArgs->pSemEmpty;
    this->pPool=pThreadArgs->pPool;
    return *this;
}
