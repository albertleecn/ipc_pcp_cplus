//
//  ThreadPC.h
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/19.
//  Copyright (c) 2015年 albert. All rights reserved.
//

#ifndef __ipc_pcp_cplus__ThreadPC__
#define __ipc_pcp_cplus__ThreadPC__

#include <stdio.h>
#include <thread>
#include <pthread.h>
#include "ThreadArgs.h"

using namespace std;

class ThreadPC{
public:
    ThreadArgs _Args;
    pthread_t _pthread;
public:
    ThreadPC();
    ThreadPC(ThreadArgs* pThreadArgs);
    ~ThreadPC();
    ///
    ThreadPC& operator=( const ThreadPC * );
    
public:
    bool execute();
    static void* producerExecute(void* pArgs);
    static void* consumerExecute(void* pArgs);
};

#endif /* defined(__ipc_pcp_cplus__ThreadPC__) */
