#ifndef _H_NODE
#define _H_NODE

// TODO should this be a struct? Are there any performance issues with this?
class node {
public:

	//Ctor
	node(int x, int y);

	//Position
	int x;
	int y;

	//Kanten
	node *n;
	node *e;
	node *s;
	node *w;

};

#endif
