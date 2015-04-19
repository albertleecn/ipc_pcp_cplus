//
//  ThreadArgs.h
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/19.
//  Copyright (c) 2015年 albert. All rights reserved.
//

#ifndef __ipc_pcp_cplus__ThreadArgs__
#define __ipc_pcp_cplus__ThreadArgs__

#include <stdio.h>
#include <mutex>
#include <string>
#include <semaphore.h>
#include "comm.h"
#include "goodPool.h"

using namespace std;

class ThreadArgs{
public:
    int id;
    ThreadType type;
    int goodCnt;
    int* pfinishedGood;
    sem_t* pMutexPool;      ///pthread_mutex_t cannot mutex in this context
    sem_t* pMutexStdout;    ///pthread_mutex_t cannot mutex in this context
    sem_t* pSemFull;
    sem_t* pSemEmpty;
    GoodPool* pPool;
public:
    ThreadArgs();
    ~ThreadArgs();
    ///
    ThreadArgs& operator=( const ThreadArgs * );

};

#endif /* defined(__ipc_pcp_cplus__ThreadArgs__) */
