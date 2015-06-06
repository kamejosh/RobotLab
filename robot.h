#ifndef _H_ROBOT
#define _H_ROBOT

#include <iostream>
#include "node.h"
#include <vector>

using namespace std;

class robot{
public:
	robot();
	virtual ~robot();
	virtual void findPath(node* now, node* finish);
	enum orientation {NORTH, EAST, WEST, SOUTH};
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
	void findPath(node*, node*);
};

class joshbot : public robot{
public:
	joshbot();
	~joshbot();
	//vector<node*> findPath(node*, node*);
};

#endif
