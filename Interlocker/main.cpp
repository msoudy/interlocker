//
//  main.cpp
//  Interlocker
//
//  Created by Grover Chen on 3/10/17.
//  Copyright © 2017 Grover Chen. All rights reserved.
//


#include "parts_graph.h"
#include <iostream>

// for intergration
enum Mobility {
    NONE = 0,
    X_PLUS = 1 << 0,
    X_MINUS = 1 << 1,
    Y_PLUS = 1 << 2,
    Y_MINUS = 1 << 3,
    Z_PLUS = 1 << 4,
    Z_MINUS = 1 << 5,
    ALL = X_PLUS | X_MINUS | Y_PLUS | Y_MINUS | Z_PLUS | Z_MINUS
};

int main(int argc, const char * argv[]) {
    // 1. desk(too verbose)
    Graph desk(6);
    
    desk.setName("desk");
    desk.addEdge(0, 1, Y);
    desk.addEdge(0, 3, Y);
    desk.addEdge(1, 2, X);
    desk.addEdge(1, 4, X);
    desk.addEdge(1, 5, X);
    desk.addEdge(2, 3, Z);
    desk.addEdge(3, 4, Z);
    desk.addEdge(4, 5, Y);
    
    std::vector<int> tmp;
    tmp.push_back(0);tmp.push_back(1);tmp.push_back(2);tmp.push_back(3);
    desk.setLIGs(tmp);
    tmp.clear();
    tmp.push_back(1);tmp.push_back(2);tmp.push_back(3);tmp.push_back(4);
    desk.setLIGs(tmp);
    tmp.clear();
    tmp.push_back(1);tmp.push_back(4);tmp.push_back(5);
    desk.setLIGs(tmp);
    tmp.clear();

    desk.assemblyVerify();
    desk.assemblyVerifyGN();
    
    for (int i = 1; i <= 6; i++)
        desk.assembly_order.push_back(i);
    
    desk.assembly_axis.push_back(ALL);
    desk.assembly_axis.push_back(X_PLUS);
    desk.assembly_axis.push_back(Y_MINUS);
    desk.assembly_axis.push_back(X_MINUS);
    desk.assembly_axis.push_back(Z_MINUS);
    desk.assembly_axis.push_back(Y_MINUS);
    
    
    // 2. bedstand
    Graph bedstand(6);
    bedstand.setName("bedstand");
    for (int i = 1; i <= 6; i++)
        bedstand.assembly_order.push_back(i);
    bedstand.assembly_axis.push_back(ALL);
    bedstand.assembly_axis.push_back(Y_MINUS);
    bedstand.assembly_axis.push_back(X_PLUS);
    bedstand.assembly_axis.push_back(Z_MINUS);
    bedstand.assembly_axis.push_back(X_PLUS);
    bedstand.assembly_axis.push_back(Z_MINUS);
    
    Graph shoerack(9);
    shoerack.setName("shoerack");
    for (int i = 1; i <= 9; i++)
        shoerack.assembly_order.push_back(i);
    shoerack.assembly_axis.push_back(ALL);//1
    shoerack.assembly_axis.push_back(X_PLUS);//2
    shoerack.assembly_axis.push_back(Y_PLUS);//3
    shoerack.assembly_axis.push_back(Z_MINUS);//4
    shoerack.assembly_axis.push_back(X_MINUS);//5
    shoerack.assembly_axis.push_back(Y_MINUS);//6
    shoerack.assembly_axis.push_back(X_MINUS);//7
    shoerack.assembly_axis.push_back(Z_PLUS);//8
    shoerack.assembly_axis.push_back(Y_MINUS);//9
    
    Graph chair(12);
    chair.setName("chair");
    for (int i = 1; i <= 12; i++)
        chair.assembly_order.push_back(i);
    chair.assembly_axis.push_back(ALL);//1
    chair.assembly_axis.push_back(Z_MINUS);//2
    chair.assembly_axis.push_back(Y_MINUS);//3
    chair.assembly_axis.push_back(Z_PLUS);//4
    chair.assembly_axis.push_back(X_MINUS);//5
    chair.assembly_axis.push_back(X_PLUS);//6
    chair.assembly_axis.push_back(Z_PLUS);//7
    chair.assembly_axis.push_back(Y_PLUS);//8
    chair.assembly_axis.push_back(X_PLUS);//9
    chair.assembly_axis.push_back(Y_PLUS);//10
    chair.assembly_axis.push_back(Z_MINUS);//11
    chair.assembly_axis.push_back(X_MINUS);//12


    Graph bookShelf(12);
    
    bookShelf.setName("bookShelf");
    bookShelf.addEdge(0, 1, Z);
    bookShelf.addEdge(0, 2, Z);
    bookShelf.addEdge(0, 7, Z);
    bookShelf.addEdge(1, 3, X);
    bookShelf.addEdge(1, 4, Y);
    bookShelf.addEdge(1, 6, Z);
    bookShelf.addEdge(1, 12, X);
    bookShelf.addEdge(2, 3, Z);
    bookShelf.addEdge(2, 4, Z);
    bookShelf.addEdge(2, 5, Y);
    bookShelf.addEdge(2, 11, Z);
    bookShelf.addEdge(3, 9, Y);
    bookShelf.addEdge(4, 8, X);
    bookShelf.addEdge(4, 10, Y);
    bookShelf.addEdge(5, 7, X);
    bookShelf.addEdge(5, 8, Y);
    bookShelf.addEdge(6, 7, X);
    bookShelf.addEdge(6, 8, Z);
    bookShelf.addEdge(9, 11, X);
    bookShelf.addEdge(9, 12, Z);
    bookShelf.addEdge(10, 11, Y);
    bookShelf.addEdge(10, 12, Z);
    
    bookShelf.assemblyVerify();
    bookShelf.assemblyVerifyGN();
    
    for (int i = 1; i <= 13; i++)
        bookShelf.assembly_order.push_back(i);
    bookShelf.assembly_axis.push_back(ALL);//1
    bookShelf.assembly_axis.push_back(Z_PLUS);//2
    bookShelf.assembly_axis.push_back(Y_MINUS);//3
    bookShelf.assembly_axis.push_back(Z_MINUS);//4
    bookShelf.assembly_axis.push_back(X_PLUS);//5
    bookShelf.assembly_axis.push_back(Y_MINUS);//6
    bookShelf.assembly_axis.push_back(X_MINUS);//7
    bookShelf.assembly_axis.push_back(Z_MINUS);//8
    bookShelf.assembly_axis.push_back(X_PLUS);//9
    bookShelf.assembly_axis.push_back(Z_MINUS);//10
    bookShelf.assembly_axis.push_back(Y_MINUS);//11
    bookShelf.assembly_axis.push_back(X_MINUS);//12
    bookShelf.assembly_axis.push_back(Z_MINUS);//13
    
    
    Graph sofa(13);
    sofa.setName("sofa");
    for (int i = 1; i <= 13; i++)
        sofa.assembly_order.push_back(i);
    sofa.assembly_axis.push_back(ALL);//1
    sofa.assembly_axis.push_back(Z_PLUS);//2
    sofa.assembly_axis.push_back(Z_PLUS);//3
    sofa.assembly_axis.push_back(Z_PLUS);//4
    sofa.assembly_axis.push_back(Z_PLUS);//5
    sofa.assembly_axis.push_back(Z_PLUS);//6
    sofa.assembly_axis.push_back(X_MINUS);//7
    sofa.assembly_axis.push_back(Y_MINUS);//8
    sofa.assembly_axis.push_back(X_PLUS);//9
    sofa.assembly_axis.push_back(Y_PLUS);//10
    sofa.assembly_axis.push_back(X_PLUS);//11
    sofa.assembly_axis.push_back(Z_PLUS);//12
    sofa.assembly_axis.push_back(Y_MINUS);//13
    
    Graph babybed(10);
    babybed.setName("babybed");
    for (int i = 1; i <= 10; i++)
        babybed.assembly_order.push_back(i);
    babybed.assembly_axis.push_back(ALL);//1
    babybed.assembly_axis.push_back(Z_MINUS);//2
    babybed.assembly_axis.push_back(Y_MINUS);//3
    babybed.assembly_axis.push_back(Y_MINUS);//4
    babybed.assembly_axis.push_back(X_PLUS);//5
    babybed.assembly_axis.push_back(Y_MINUS);//6
    babybed.assembly_axis.push_back(Z_PLUS);//7
    babybed.assembly_axis.push_back(Y_MINUS);//8
    babybed.assembly_axis.push_back(Y_MINUS);//9
    babybed.assembly_axis.push_back(X_MINUS);//10
    
    Graph bed(20);
    bed.setName("bed");
    for (int i = 1; i <= 20; i++)
        bed.assembly_order.push_back(i);
    bed.assembly_axis.push_back(ALL);//1
    bed.assembly_axis.push_back(X_MINUS);//2
    bed.assembly_axis.push_back(X_MINUS);//3
    bed.assembly_axis.push_back(X_MINUS);//4
    bed.assembly_axis.push_back(Z_PLUS);//5
    bed.assembly_axis.push_back(Y_MINUS);//6
    bed.assembly_axis.push_back(X_MINUS);//7
    bed.assembly_axis.push_back(Z_MINUS);//8
    bed.assembly_axis.push_back(Y_MINUS);//9
    bed.assembly_axis.push_back(Z_PLUS);//10
    bed.assembly_axis.push_back(Y_MINUS);//11
    bed.assembly_axis.push_back(X_MINUS);//12
    bed.assembly_axis.push_back(X_MINUS);//13
    bed.assembly_axis.push_back(X_MINUS);//14
    bed.assembly_axis.push_back(Z_MINUS);//15
    bed.assembly_axis.push_back(X_MINUS);//16
    bed.assembly_axis.push_back(Y_MINUS);//17
    bed.assembly_axis.push_back(X_MINUS);//18
    bed.assembly_axis.push_back(X_MINUS);//19
    bed.assembly_axis.push_back(Y_MINUS);//20
    
    cout << "Input the furniture type: " << "\n";
    cout << "1 -- desk, 2 -- bed stand, 3 -- shoe rack, 4 -- chair, 5 -- book shelf, \
    6 -- sofa, 7 -- baby bed, 8 -- bed" << "\n";
    int input;
    cin >> input;
    
    if (input == 1) {
        desk.printKeys();
        desk.printLIGs();
        desk.printOrder();
    }
    else if (input == 2) {
        cout << "Assembly Axis is: \n";
        for (int i = 0; i < bedstand.assembly_axis.size(); i++)
            cout << bedstand.assembly_axis[i] << " ";
    }
    else if (input == 3) {
        cout << "Assembly Axis is: \n";
        for (int i = 0; i < shoerack.assembly_axis.size(); i++)
            cout << shoerack.assembly_axis[i] << " ";
    }
    else if (input == 4) {
        cout << "Assembly Axis is: \n";
        for (int i = 0; i < chair.assembly_axis.size(); i++)
            cout << chair.assembly_axis[i] << " ";
    }
    else if (input == 5) {
        cout << "Assembly Axis is: \n";
        for (int i = 0; i < bookShelf.assembly_axis.size(); i++)
            cout << bookShelf.assembly_axis[i] << " ";
    }
    else if (input == 6) {
        cout << "Assembly Axis is: \n";
        for (int i = 0; i < sofa.assembly_axis.size(); i++)
            cout << sofa.assembly_axis[i] << " ";
    }
    else if (input == 7) {
        cout << "Assembly Axis is: \n";
        for (int i = 0; i < babybed.assembly_axis.size(); i++)
            cout << babybed.assembly_axis[i] << " ";
    }
    else if (input == 8) {
        cout << "Assembly Axis is: \n";
        for (int i = 0; i < bed.assembly_axis.size(); i++)
            cout << bed.assembly_axis[i] << " ";
    }
    
    
    
    return 0;
}
