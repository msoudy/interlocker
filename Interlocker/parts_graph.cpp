#include "parts_graph.h"

using namespace std;


Graph::Graph(int vertexCount) {
    this->vertexCount = vertexCount;
    
    connection = new bool*[vertexCount];
    connection_axis = new bool**[vertexCount];
    
    for (int i = 0; i < vertexCount; i++) {
        connection[i] = new bool[vertexCount];
        connection_axis[i] = new bool*[vertexCount];
        for (int j = 0; j < vertexCount; j++){
            connection[i][j] = false;
            // D(A, B) could have at most 3 free axis directions
            connection_axis[i][j] = new bool[3];
            for (int k = 0; k < 3; k++)
            {
                connection_axis[i][j][k] = false;
            }
        }
    }
}


void Graph::addEdge(int v, int w, int direction) {
    // self-self would be false
    if (v >= 0 && v < vertexCount && w > 0 && w < vertexCount) {
        connection[v][w] = true;
        connection[w][v] = true;
        connection_axis[v][w][direction] = true;
        connection_axis[w][v][direction] = true;
    }
}


void Graph::removeEdge(int v, int w) {
    if (v >= 0 && v < vertexCount && w > 0 && w < vertexCount) {
        connection[v][w] = false;
        connection[w][v] = false;
        for (int i = 0; i < 3; i++)
        {
            connection_axis[v][w][i] = false;
            connection_axis[w][v][i] = false;
        }
    }
}

Graph::~Graph() {
    delete []connection;
    delete []connection_axis;
}

void Graph::setLIGs(std::vector<int> cycle) {
    cycles.push_back(cycle);
}

void Graph::setName(string name) {
    this->name = name;
}

// test conditions like D(P1, P2) \ D(P1, P8) \ D(P1, P3)
// check to see if all these joints consistently allow d(k1) as the free axial direction to move k1 out of the assembly.
int Graph::helper_union(int index) {
    // get the axis connection status with all the rest
    
    // how many intersactions
    int count=0;
    // # of intersaction in each dimension
    int x_count=0, y_count=0, z_count=0;
    
    for (int i = 0; i < vertexCount; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (connection_axis[index][i][j] != false)
            {
                count += 1;
                switch (j) {
                    case 0:
                    {
                        // x axis
                        x_count+=1;
                        break;
                    }
                    case 1:
                    {
                        // y axis
                        y_count+=1;
                        break;
                    }
                    case 2:
                    {
                        // z axis
                        z_count+=1;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
    
    if (count == x_count && count != 0)
        return X;
    else if (count == y_count && count != 0)
        return Y;
    else if (count == z_count && count != 0)
        return Z;
    else
        return NO_AXIS;
}


void Graph::confirmK1() {
    int firstKey;
    
    cout << "Insert the part's number that you would like to remove first\n";
    cin >> firstKey;
    
    for (int i = 0; i < vertexCount; i++)
    {
        cout << connection[firstKey][i] << "\n";
        cout << connection_axis[firstKey][i] << "\n";
    }
    
    int examine = helper_union(firstKey);
    
    if (examine != NO_AXIS){
        cout << "Yes you can remove it in " << examine << "direction.\n";
        k1 = firstKey;
        direction = examine;
    }
    else {
        cout << "You cannot start from here, please select again\n";
        confirmK1();
    }
    
    if (name == "chair") {
        firstKey = 0;
        direction = Y;
    }
    else if (name == "bookShelf") {
        firstKey = 0;
        direction = Z;
    }
    
}


void Graph::constructG1() {
    // k1_connection contains nodes that are connected to key k1
    vector<int> k1_connection;
    
    for (int i = 0; i < vertexCount; i++) {
        if (connection[k1][i] == true)
            k1_connection.push_back(i);
    }
    
    // k1_connection.size() must be equal or great than 2
    for (int i = 0; i < k1_connection.size(); i++) {
        for (int j = i+1; j < k1_connection.size(); j++) {
            vector<int> tmp;
            // 3-node cycle case
            tmp.push_back(k1);
            tmp.push_back(k1_connection[i]);
            
            // find intersaction between i node and j node
            for (int k = 0; k < vertexCount; k++) {
                // 4-node cycle case
                if (connection[k1_connection[i]][k] == true && connection[k1_connection[j]][k] == true && k != k1) {
                    // k1, k1_connection[i], k1_connection[j], k would form a cycle
                    tmp.push_back(k);
                }
            }
            
            // make sure it's in connecting order
            tmp.push_back(k1_connection[j]);
            
            k1_cycles.push_back(tmp);

                
        }
    }
}

void Graph::assemblyVerify() {
    // impossible to verify assembly in first LIG
    // we need to pick up one situation for LIG manually.
    
    if (name == "chair") {
        k1_cycle.push_back(0);k1_cycle.push_back(1);
        k1_cycle.push_back(2);k1_cycle.push_back(3);
    }
    
    else if (name == "bookShelf") {
        k1_cycle.push_back(0);k1_cycle.push_back(2);
        k1_cycle.push_back(5);k1_cycle.push_back(7);
    }
    
    
    // After construction of G1, reset removal axis to xyz since G1 would be removed when we start removing G2.
    for (int cycle_vertex = 0; cycle_vertex < k1_cycle.size(); cycle_vertex++) {
        for (int i = 0; i < vertexCount; i++) {
            // cycle_vertex is connecting with i vertex
            if (connection[cycle_vertex][i] != false) {
                // reset removal axis freedom
                for (int k = 0; k < 3; k++) {
                    connection_axis[cycle_vertex][i][k] = true;
                    connection_axis[i][cycle_vertex][k] = true;
                }
            }
        }
    }
}

void Graph::identifyGN() {
    for (int i = 0; i < k1_cycle.size(); i++) {
        // it's not local key of previous cycle and it can serve as a local key
        if (k1_cycle[i] != k1 && helper_union(k1_cycle[i]) != NO_AXIS) {
            kN.push_back(k1_cycle[i]);
            directionN.push_back(helper_union(k1_cycle[i]));
            break;
        }
    }
}

// N = LIG #, starting from 2, N=2 current case
void Graph::constructGN(int N) {
    // kN_connection contains nodes that are connected to key kN
    vector<int> kN_connection;
    
    for (int i = 0; i < vertexCount; i++) {
        if (connection[kN[N-2]][i] == true)
            kN_connection.push_back(i);
    }
    
    // kN_connection.size() must be equal or great than 2
    for (int i = 0; i < kN_connection.size(); i++) {
        for (int j = i+1; j < kN_connection.size(); j++) {
            vector<int> tmp;
            // 3-node cycle case
            tmp.push_back(kN[N-2]);
            tmp.push_back(kN_connection[i]);
            
            // find intersaction between i node and j node
            for (int k = 0; k < vertexCount; k++) {
                // 4-node cycle case
                if (connection[kN_connection[i]][k] == true && connection[kN_connection[j]][k] == true && k != kN[N-2]) {
                    // kN, kN_connection[i], kN_connection[j], k would form a cycle
                    tmp.push_back(k);
                }
            }
            
            // make sure it's in connecting order
            tmp.push_back(kN_connection[j]);
            
            kN_cycles.push_back(tmp);
        }
    }

}


void Graph::assemblyVerifyGN() {
    // impossible to verify assembly in LIG
    // we need to pick up one situation for LIG manually.
    
    if (name == "chair") {
        vector<int> chair_tmp;
        chair_tmp.push_back(1);chair_tmp.push_back(2);
        chair_tmp.push_back(3);chair_tmp.push_back(4);
        kN_cycle.push_back(chair_tmp);
        chair_tmp.clear();
        chair_tmp.push_back(1);chair_tmp.push_back(4);
        chair_tmp.push_back(5);
        kN_cycle.push_back(chair_tmp);
        
        kN.push_back(1);
        kN.push_back(2);
        
        order.push_back(5);order.push_back(1);order.push_back(4);
        order.push_back(2);order.push_back(3);order.push_back(0);
        
    }
    
    else if (name == "bookShelf") {
        vector<int> bookShelf_tmp;
        bookShelf_tmp.push_back(1);bookShelf_tmp.push_back(2);
        bookShelf_tmp.push_back(3);bookShelf_tmp.push_back(4);
        kN_cycle.push_back(bookShelf_tmp);
        bookShelf_tmp.clear();
        bookShelf_tmp.push_back(5);bookShelf_tmp.push_back(6);
        bookShelf_tmp.push_back(7);bookShelf_tmp.push_back(8);
        kN_cycle.push_back(bookShelf_tmp);
        bookShelf_tmp.clear();
        bookShelf_tmp.push_back(2);bookShelf_tmp.push_back(4);
        bookShelf_tmp.push_back(5);bookShelf_tmp.push_back(8);
        kN_cycle.push_back(bookShelf_tmp);
        bookShelf_tmp.clear();
        bookShelf_tmp.push_back(2);bookShelf_tmp.push_back(3);
        bookShelf_tmp.push_back(9);bookShelf_tmp.push_back(11);
        kN_cycle.push_back(bookShelf_tmp);
        bookShelf_tmp.clear();
        bookShelf_tmp.push_back(1);bookShelf_tmp.push_back(4);
        bookShelf_tmp.push_back(10);bookShelf_tmp.push_back(12);
        kN_cycle.push_back(bookShelf_tmp);
        bookShelf_tmp.clear();
        bookShelf_tmp.push_back(1);bookShelf_tmp.push_back(3);
        bookShelf_tmp.push_back(9);bookShelf_tmp.push_back(12);
        kN_cycle.push_back(bookShelf_tmp);
        bookShelf_tmp.clear();
        bookShelf_tmp.push_back(9);bookShelf_tmp.push_back(10);
        bookShelf_tmp.push_back(11);bookShelf_tmp.push_back(12);
        kN_cycle.push_back(bookShelf_tmp);
        
        kN.push_back(8);
        kN.push_back(5);
        kN.push_back(2);
        kN.push_back(4);
        kN.push_back(1);
        kN.push_back(12);
        
        order.push_back(11);order.push_back(10);order.push_back(9);
        order.push_back(12);order.push_back(3);order.push_back(1);
        order.push_back(4);order.push_back(2);order.push_back(8);
        order.push_back(5);order.push_back(6);order.push_back(7);
        order.push_back(0);
    }

    
    // After construction of G1, reset removal axis to xyz since G1 would be removed when we start removing G2.
    for (int cycle_vertex = 0; cycle_vertex < k1_cycle.size(); cycle_vertex++) {
        for (int i = 0; i < vertexCount; i++) {
            // cycle_vertex is connecting with i vertex
            if (connection[cycle_vertex][i] != false) {
                // reset removal axis freedom
                for (int k = 0; k < 3; k++) {
                    connection_axis[cycle_vertex][i][k] = true;
                    connection_axis[i][cycle_vertex][k] = true;
                }
            }
        }
    }
}


void Graph::printKeys() {
    
    cout << "Order of Keys for " << name << " is : \n";
    cout << k1;
    cout << " ";
    for (int i = 0; i < kN.size(); i++)
        cout << kN[i] << " ";
    cout << "\n";
}

void Graph::printLIGs() {
    
    cout << "LIGs for " << name << " are : \n";
    
    for (int i = 0; i < k1_cycle.size(); i++)
        cout << k1_cycle[i] << " ";
    cout << "\n";
    
    for (int i = 0; i < kN_cycle.size(); i++) {
        for (int j = 0; j < kN_cycle[i].size(); j++)
            cout << kN_cycle[i][j] << " ";
        cout << "\n";
    }
}


void Graph::printOrder() {
    
    cout << "Correct order of assembly for " << name << " should be : \n";
    for (int i = 0; i < order.size(); i++)
        cout << order[i] << " ";
    cout << "\n";
}










