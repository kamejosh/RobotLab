#ifndef _H_ROBOT
#define _H_ROBOT

#include <iostream>

#include "node.h"

class robot {
	
	virtual vector<node*> findPath(node*, node*);
	
};

class robot_dumb : public robot {
	
};

#endif
