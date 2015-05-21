#ifndef _LAB_NODE
#define _LAB_NODE

#include "node.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class lab{
public:
    //ctor
    lab(string filename);
    //public nodes for robot
    node *start;
    node *end;

private:
    vector<vector<node*>> laby;


}

#endif
