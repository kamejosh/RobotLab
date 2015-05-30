#ifndef _H_ROBOT
#define _H_ROBOT

#include <iostream>
#include "node.h"
#include <vector>

using namespace std;

class robot {

	virtual vector<node*> findPath(node*, node*);

};

class robot_left : public robot{
	
};

class hubot : public robot{

};

class joshbot : public robot{

};

#endif
