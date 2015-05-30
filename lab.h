#ifndef _LAB_NODE
#define _LAB_NODE

#include "robot.h"
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
    //dtor
    ~lab();
    //public nodes for robot
    node *start;
    node *end;
    void findStartAndEnd();
    void printLab();
    void connectNodes();
private:
    vector<vector<node*>> labyrinth;
    int width;
    int height;
};

void startMazerun(int argc, char* argv[]);

string CharAToString(char* arr);
void print_usage(char *name);
#endif
