//
//  comm.h
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/18.
//  Copyright (c) 2015年 albert. All rights reserved.
//

#ifndef ipc_pcp_cplus_comm_h
#define ipc_pcp_cplus_comm_h

#define INVALIDID -1

enum ThreadType{ThreadType_Producer, ThreadType_Consumer};

#define HeadMutexStdoutName "SEM_Mutex_Stdout_"
#define HeadMutexPoolName "SEM_Mutex_Pool_"
#define HeadSemFullName "SEM_FULL_PCP_"
#define HeadSemEmptyName "SEM_EMPTY_PCP_"

#endif
