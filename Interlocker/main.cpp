//
//  main.cpp
//  Interlocker
//
//  Created by Grover Chen on 3/10/17.
//  Copyright © 2017 Grover Chen. All rights reserved.
//


#include "PartsGraph.h"

#include <iostream>

int main(int argc, const char * argv[]) {
    // create furniture model of Figure 3 in the paper
	PartsGraph chair(6);
    
    chair.addEdge(0, 1);
    chair.addEdge(0, 3);
    chair.addEdge(1, 2);
    chair.addEdge(1, 4);
    chair.addEdge(1, 5);
    chair.addEdge(2, 3);
    chair.addEdge(3, 4);
    chair.addEdge(4, 5);
    
    std::vector<int> tmp;
    tmp.push_back(0);tmp.push_back(1);tmp.push_back(2);tmp.push_back(3);
    chair.setLIGs(tmp);
    tmp.clear();
    tmp.push_back(1);tmp.push_back(2);tmp.push_back(3);tmp.push_back(4);
    chair.setLIGs(tmp);
    tmp.clear();
    tmp.push_back(1);tmp.push_back(4);tmp.push_back(5);
    chair.setLIGs(tmp);
    tmp.clear();
    
    chair.printLIGs();
    
	PartsGraph bedStand(8);
    
    
    
    
    return 0;
}
