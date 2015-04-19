//
//  main.cpp
//  ipc_pcp_cplus
//
//  Created by albert on 15/4/18.
//  Copyright (c) 2015 albert. All rights reserved.
//

#include <iostream>
#include "ProducerConsumerProblem.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "This program is running\n";
    
    ProducerConsumerProblem* pProducerConsumerProblem;
    pProducerConsumerProblem=new ProducerConsumerProblem(4,3,2,6);
    pProducerConsumerProblem->prepare();
    pProducerConsumerProblem->execute();
    delete pProducerConsumerProblem;
    
    std::cout << "This program exits!\n";
    return 0;
}
