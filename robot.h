#ifndef _H_ROBOT
#define _H_ROBOT

#include <iostream>
#include "node.h"
#include <vector>
#include <cmath>

using namespace std;

class robot{
public:
	robot();
	virtual ~robot();
	virtual void findPath(node* now, node* finish);
	enum orientation {NORTH, EAST, SOUTH, WEST};
	int orientation = SOUTH;
	int steps = 0;
	vector<node*> path;
private:

};

class robot_left : public robot{
public:
	robot_left();
	~robot_left();
	void findPath(node* now, node* finish);
};

class hubot : public robot{
public:
	hubot();
	~hubot();
	bool found = false;
	void findPath(node*, node*);
};

class robot_right : public robot{
public:
	robot_right();
	~robot_right();
	void findPath(node* now, node* finish);
};

#endif
