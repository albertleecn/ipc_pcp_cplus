//
//  GoodPool.h
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/18.
//  Copyright (c) 2015年 albert. All rights reserved.
//

#ifndef __ipc_pcp_cplus__GoodPool__
#define __ipc_pcp_cplus__GoodPool__

#include <stdio.h>
#include <list>
#include "good.h"

using namespace std;

typedef list<Good> ListGood, *PListGood;

///
class GoodPool{
private:
    PListGood pList;
public:
    GoodPool();
    GoodPool(int aPoolSize);
    ~GoodPool();
    bool changePoolSize(int aPoolSize);
    string toString();
    bool putGood(Good* pGood);
    bool takeGood(Good* pGood);
private:
    bool deleteAllGoods();
};
#endif /* defined(__ipc_pcp_cplus__GoodPool__) */
