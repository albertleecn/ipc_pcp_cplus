//
//  ProducerConsumerProblem.cpp
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/18.
//  Copyright (c) 2015年 albert. All rights reserved.
//
#include <iostream>
#include <sstream>
#include <semaphore.h>
#include <time.h>
#include "ProducerConsumerProblem.h"
#include "goodPool.h"
#include "ThreadPC.h"
#include "comm.h"
using namespace std;

///
ProducerConsumerProblem::ProducerConsumerProblem(){
    pPool=new GoodPool();

    ostringstream format_message;
    time_t currTime=time(NULL);
    struct tm* ptime=gmtime(&currTime);
    format_message<<ptime->tm_year+1900<<ptime->tm_mon<<ptime->tm_mday
    <<ptime->tm_hour<<ptime->tm_min<<ptime->tm_sec;

    mutexStdoutName.clear();
    mutexStdoutName.append(HeadMutexStdoutName);
    mutexStdoutName.append(format_message.str());
    mutexPoolName.clear();
    mutexPoolName.append(HeadMutexPoolName);
    mutexPoolName.append(format_message.str());
    semFullName.clear();
    semFullName.append(HeadSemFullName);
    semFullName.append(format_message.str());
    semEmptyName.clear();
    semEmptyName.append(HeadSemEmptyName);
    semEmptyName.append(format_message.str());
    
    pMutexPool=NULL;
    pMutexStdout=NULL;
    pSemFull=NULL;
    pSemEmpty=NULL;
    pListThreadP=new list<ThreadPC*>();
    pListThreadC=new list<ThreadPC*>();
    pListThreadPArgs=new list<ThreadArgs>();
    pListThreadCArgs=new list<ThreadArgs>();
    producersCnt=0;
    consumersCnt=0;
    poolSize=0;
    goodCnt=0;
}

///
ProducerConsumerProblem::ProducerConsumerProblem(int aProducersCnt, int aConsumersCnt, int aPoolSize, int aGoodCnt):ProducerConsumerProblem(){
    producersCnt=aProducersCnt;
    consumersCnt=aConsumersCnt;
    poolSize=aPoolSize;
    goodCnt=aGoodCnt;
}

///
ProducerConsumerProblem::~ProducerConsumerProblem(){
    delete pListThreadP;
    delete pListThreadC;
    delete pListThreadPArgs;
    delete pListThreadCArgs;
    destroyIPCobjs();
    delete pPool;
}

///
void ProducerConsumerProblem::destroyIPCobjs(){
    if (pSemFull!=NULL){
        sem_close(pSemFull);
        sem_unlink(semFullName.data());
        pSemFull=NULL;
    }
    if (pSemEmpty!=NULL){
        sem_close(pSemEmpty);
        sem_unlink(semEmptyName.data());
        pSemEmpty=NULL;
    }
    if (pMutexPool!=NULL){
        sem_close(pMutexPool);
        sem_unlink(mutexPoolName.data());
        pMutexPool=NULL;
    }
    
    if (pMutexStdout!=NULL){
        sem_close(pMutexStdout);
        sem_unlink(mutexStdoutName.data());
        pMutexStdout=NULL;
    }
}


///
void ProducerConsumerProblem::prepare(){
    producedGood=0;
    consumedGood=0;
    pPool->changePoolSize(poolSize);

    destroyIPCobjs();
    pSemFull=sem_open(semFullName.data(),O_CREAT|O_EXCL,S_IRUSR | S_IWUSR,0);
    pSemEmpty=sem_open(semEmptyName.data(),O_CREAT|O_EXCL,S_IRUSR | S_IWUSR,poolSize);
    pMutexPool=sem_open(mutexPoolName.data(),O_CREAT|O_EXCL,S_IRUSR | S_IWUSR,1);
    pMutexStdout=sem_open(mutexStdoutName.data(),O_CREAT|O_EXCL,S_IRUSR | S_IWUSR,1);

    srand((int)time(0));
}


///
void ProducerConsumerProblem:: execute(){
    std::cout << "Hello PCP:\n"
        <<"\tPoolSize:"<<poolSize<<"\n"
        <<"\tGoodCnt:"<<goodCnt<<"\n"
        <<"\tProducersCnt:"<<producersCnt<<"\n"
        <<"\tConsumersCnt:"<<consumersCnt<<"\n";

    ///
    pListThreadPArgs->clear();
    pListThreadP->clear();
    for (int i=0;i<producersCnt;i++){
        ThreadArgs* pArgs=new ThreadArgs();
        pArgs->type=ThreadType_Producer;
        pArgs->id=i;
        pArgs->pfinishedGood=&producedGood;
        pArgs->pMutexStdout=pMutexStdout;
        pArgs->pMutexPool=pMutexPool;
        pArgs->pSemFull=pSemFull;
        pArgs->pSemEmpty=pSemEmpty;
        pArgs->goodCnt=goodCnt;
        pArgs->pPool=pPool;
        pListThreadPArgs->push_back(*pArgs);
        ThreadPC* pThreadP=new ThreadPC(pArgs);
        pListThreadP->push_back(pThreadP);
    }

    ///
    pListThreadCArgs->clear();
    pListThreadC->clear();
    for (int i=0;i<consumersCnt;i++){
        ThreadArgs* pArgs=new ThreadArgs();
        pArgs->type=ThreadType_Consumer;
        pArgs->id=i;
        pArgs->pfinishedGood=&consumedGood;
        pArgs->pMutexStdout=pMutexStdout;
        pArgs->pMutexPool=pMutexPool;
        pArgs->pSemFull=pSemFull;
        pArgs->pSemEmpty=pSemEmpty;
        pArgs->goodCnt=goodCnt;
        pArgs->pPool=pPool;
        pListThreadPArgs->push_back(*pArgs);
        ThreadPC* pThreadP=new ThreadPC(pArgs);
        pListThreadC->push_back(pThreadP);
    }

    ///
    list<ThreadPC*>::iterator it;
    
    ///
    for (it=pListThreadP->begin();it!=pListThreadP->end();it++){
        (*it)->execute();
    }
    for (it=pListThreadC->begin();it!=pListThreadC->end();it++){
        (*it)->execute();
    }
    
    ///
    for (it=pListThreadP->begin();it!=pListThreadP->end();it++){
        pthread_join((*it)->_pthread, NULL);
    }
    for (it=pListThreadC->begin();it!=pListThreadC->end();it++){
        pthread_join((*it)->_pthread, NULL);
    }
    
}