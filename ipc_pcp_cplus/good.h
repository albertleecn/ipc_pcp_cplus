//
//  good.h
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/18.
//  Copyright (c) 2015年 albert. All rights reserved.
//

#ifndef ipc_pcp_cplus_good_h
#define ipc_pcp_cplus_good_h

class Good{
    int _id;
    int _producer_id;
    time_t _produce_time;
    
public:
    ///
    Good();
    ///
    ~Good();
    ///
    Good(int aid, int aproducer_id);
    ///
    Good(int aid, int aproducer_id, time_t aproduce_time);
    ///
    Good& operator=( const Good * );
    ///
    bool setGood(const Good *);
    ///
    std::string toString();
    ///
    int getID();
    ///
    void clear();
};

#endif
