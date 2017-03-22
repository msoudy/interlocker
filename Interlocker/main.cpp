//
//  main.cpp
//  Interlocker
//
//  Created by Grover Chen on 3/10/17.
//  Copyright © 2017 Grover Chen. All rights reserved.
//


#include "parts_graph.h"

#include <iostream>

int main(int argc, const char * argv[]) {
    // create furniture model of Figure 3 in the paper
    Graph chair(6);
    
    chair.addEdge(0, 1, Y);
    chair.addEdge(0, 3, Y);
    chair.addEdge(1, 2, X);
    chair.addEdge(1, 4, X);
    chair.addEdge(1, 5, X);
    chair.addEdge(2, 3, Z);
    chair.addEdge(3, 4, Z);
    chair.addEdge(4, 5, Y);
    
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
    
    
    
    
    return 0;
}
