//
//  ThreadPC.cpp
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/19.
//  Copyright (c) 2015年 albert. All rights reserved.
//

#include <iostream>
#include "ThreadPC.h"

using namespace std;
///
ThreadPC::ThreadPC(){
}

///
ThreadPC::ThreadPC(ThreadArgs* pThreadArgs):ThreadPC(){
    this->_Args=*pThreadArgs;
}

///
ThreadPC::~ThreadPC(){
}

///
ThreadPC& ThreadPC::operator=( const ThreadPC * pThreadPC){
    this->_Args=pThreadPC->_Args;
    //this->_thread=pThreadPC->_thread;
    return *this;
}



///
bool ThreadPC::execute(){
    bool isOk=false;
    switch (_Args.type) {
        case ThreadType_Producer:
           // _thread=thread(std::bind(producerExecute, _Args));
            pthread_create(&_pthread, NULL, producerExecute,(void*)&_Args);
            isOk=true;
            break;
        case ThreadType_Consumer:
            //_thread=thread(std::bind(consumerExecute, _Args) );
            pthread_create(&_pthread, NULL, consumerExecute,(void*)&_Args);
            isOk=true;
            break;
        default:
            break;
    }
    return isOk;
}

///
void* ThreadPC::producerExecute(void* pArgs){
    ThreadArgs* pThreadArgs=(ThreadArgs*)pArgs;

//    std::chrono::milliseconds timespan(500+ rand() % 2000);
//    std::this_thread::sleep_for(timespan);
    
    sem_wait(pThreadArgs->pMutexStdout);
    std::cout<<"hi, i am the "<< std::this_thread::get_id()<<"th thread(P"<<pThreadArgs->id<<")\n";
    sem_post(pThreadArgs->pMutexStdout);
    bool isFinished=false;
    int goodIndex=-1;
    while (true) {
        sem_wait(pThreadArgs->pMutexPool);
        goodIndex=*(pThreadArgs->pfinishedGood);
        if (goodIndex>=pThreadArgs->goodCnt){
            isFinished=true;
        }
        else{
            goodIndex++;
            *(pThreadArgs->pfinishedGood)=goodIndex;
        }
        
        sem_post(pThreadArgs->pMutexPool);
        if (isFinished){
            break;
        }
        
        sem_wait(pThreadArgs->pSemEmpty);
        sem_wait(pThreadArgs->pMutexPool);
        std::chrono::milliseconds timespan(500+ rand() % 2000);
        std::this_thread::sleep_for(timespan);
        Good* pGood=new Good(goodIndex,pThreadArgs->id);
        pThreadArgs->pPool->putGood(pGood);
        sem_wait(pThreadArgs->pMutexStdout);
        std::cout<<"P("<< std::this_thread::get_id()<<","<<pThreadArgs->id<<"):put["<<goodIndex<<","
        <<pGood->toString()<<"]\n";
        std::cout<<"Pool:\n"<<pThreadArgs->pPool->toString()<<"\n";
        sem_post(pThreadArgs->pMutexStdout);
        sem_post(pThreadArgs->pMutexPool);
        sem_post(pThreadArgs->pSemFull);
    }
    sem_wait(pThreadArgs->pMutexStdout);
    std::cout<<"P("<< std::this_thread::get_id()<<","<<pThreadArgs->id<<") exits!\n";
    sem_post(pThreadArgs->pMutexStdout);
    pthread_exit(NULL);
}


///
void* ThreadPC::consumerExecute(void* pArgs){
    ThreadArgs* pThreadArgs=(ThreadArgs*)pArgs;
    
//    std::chrono::milliseconds timespan(500+ rand() % 2000);
//    std::this_thread::sleep_for(timespan);
    
    sem_wait(pThreadArgs->pMutexStdout);
    std::cout<<"hi, i am the "<< std::this_thread::get_id()<<"th thread(C"<<pThreadArgs->id<<")\n";
    sem_post(pThreadArgs->pMutexStdout);
    bool isFinished=false;
    int goodIndex=-1;
    while (true) {
        sem_wait(pThreadArgs->pMutexPool);
        goodIndex=*(pThreadArgs->pfinishedGood);
        if (goodIndex>=pThreadArgs->goodCnt){
            isFinished=true;
        }
        else{
            goodIndex++;
            *(pThreadArgs->pfinishedGood)=goodIndex;
        }
        
        sem_post(pThreadArgs->pMutexPool);
        if (isFinished){
            break;
        }
        
        sem_wait(pThreadArgs->pSemFull);
        sem_wait(pThreadArgs->pMutexPool);
        std::chrono::milliseconds timespan(300+ rand() % 2000);
        std::this_thread::sleep_for(timespan);
        Good mGood;
        pThreadArgs->pPool->takeGood(&mGood);
        sem_wait(pThreadArgs->pMutexStdout);
        std::cout<<"C("<< std::this_thread::get_id()<<","<<pThreadArgs->id<<"):take["<<goodIndex<<","
        <<mGood.toString()<<"]\n";
        sem_post(pThreadArgs->pMutexStdout);
        sem_post(pThreadArgs->pMutexPool);
        sem_post(pThreadArgs->pSemEmpty);
    }
    sem_wait(pThreadArgs->pMutexStdout);
    std::cout<<"C("<< std::this_thread::get_id()<<","<<pThreadArgs->id<<") exits!\n";
    sem_post(pThreadArgs->pMutexStdout);
    pthread_exit(NULL);
}

