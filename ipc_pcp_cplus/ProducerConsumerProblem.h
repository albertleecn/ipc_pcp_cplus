//
//  ProducerConsumerProblem.h
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/18.
//  Copyright (c) 2015年 albert. All rights reserved.
//

#ifndef __ipc_pcp_cplus__ProducerConsumerProblem__
#define __ipc_pcp_cplus__ProducerConsumerProblem__

#include <stdio.h>
#include <mutex>
#include <thread>
#include <list>
#include <semaphore.h>
#include "goodPool.h"
#include "ThreadArgs.h"
#include "ThreadPC.h"


using namespace std;
/*
 */
class ProducerConsumerProblem{
public:
    int producersCnt;
    int consumersCnt;
    int poolSize;
    int goodCnt;
    int producedGood;   ///has produced goods
    int consumedGood;   ///has comsumed goods
private:
    GoodPool* pPool;
    string mutexPoolName;
    string mutexStdoutName;
    string semFullName;
    string semEmptyName;
    sem_t* pMutexPool;      ///pthread_mutex_t cannot mutex in this context! Why? I don't know.
    sem_t* pMutexStdout;    ///pthread_mutex_t cannot mutex in this context
    sem_t* pSemFull;
    sem_t* pSemEmpty;
    list<ThreadPC*> *pListThreadP;
    list<ThreadPC*> *pListThreadC;
    list<ThreadArgs> *pListThreadPArgs;
    list<ThreadArgs> *pListThreadCArgs;
private:
    void destroyIPCobjs();
public:
    ProducerConsumerProblem();
    ProducerConsumerProblem(int aProducersCnt, int aConsumersCnt, int aPoolSize, int aGoodCnt);
    ~ProducerConsumerProblem();
    void prepare();
    void execute();
};

#endif /* defined(__ipc_pcp_cplus__ProducerConsumerProblem__) */
