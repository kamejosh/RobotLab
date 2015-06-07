#ifndef _LAB_NODE
#define _LAB_NODE

#include "robot.h"
#include "node.h"
#include <string>
#include <fstream>

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
    void printLab(vector<node*> path);
    void connectNodes();
    void startRobots(int type);
    void startRunning(int robo[3]);
private:
    vector<vector<node*>> labyrinth;
	vector<robot*> robots;
    int width;
    int height;
};

void startMazerun(string mazefile, int robo[3]);

string CharAToString(char* arr);
void print_usage(char *name);

#endif
