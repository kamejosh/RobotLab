#include "robot.h"

using namespace std;

robot::robot(){}
robot::~robot(){}

void robot::findPath(node* now, node* finish){
	vector<node*> path;
	return;
}

robot_left::robot_left(){}
robot_left::~robot_left(){}

void robot_left::findPath(node* now, node* finish){
	this->path.push_back(now);
	if(now == finish){
		return;
	}
	else{
		switch(this->orientation){
			case NORTH:
				if(now->w != nullptr){
					this->steps++;
					this->orientation = WEST;
					findPath(now->w, finish);
					return;
				}
				else if(now->n != nullptr){
					this->steps++;
					findPath(now->n, finish);
					return;
				}
				else if(now->e != nullptr){
					this->steps++;
					this->orientation = EAST;
					findPath(now->e, finish);
					return;
				}
				else{
					this->steps++;
					this->orientation = SOUTH;
					findPath(now->s, finish);
					return;
				}
			case EAST:
				if(now->n != nullptr){
					this->steps++;
					this->orientation = NORTH;
					findPath(now->n, finish);
					return;
				}
				else if(now->e != nullptr){
					this->steps++;
					findPath(now->e, finish);
					return;
				}
				else if(now->s != nullptr){
					this->steps++;
					this->orientation = SOUTH;
					findPath(now->s, finish);
					return;
				}
				else{
					this->steps++;
					this->orientation = WEST;
					findPath(now->w, finish);
					return;
				}
			case SOUTH:
				if(now->e != nullptr){
					this->steps++;
					this->orientation = EAST;
					findPath(now->e, finish);
					return;
				}
				else if(now->s != nullptr){
					this->steps++;
					findPath(now->s, finish);
					return;
				}
				else if(now->w != nullptr){
					this->steps++;
					this->orientation = WEST;
					findPath(now->w, finish);
					return;
				}
				else{
					this->steps++;
					this->orientation = NORTH;
					findPath(now->n, finish);
					return;
				}
			case WEST:
				if(now->s != nullptr){
					this->steps++;
					this->orientation = SOUTH;
					findPath(now->s, finish);
					return;
				}
				else if(now->w != nullptr){
					this->steps++;
					findPath(now->w, finish);
					return;
				}
				else if(now->n != nullptr){
					this->steps++;
					this->orientation = NORTH;
					findPath(now->n, finish);
					return;
				}
				else{
					this->steps++;
					this->orientation = EAST;
					findPath(now->e, finish);
					return;
				}
			default:
				return;
		}
	}
}


hubot::hubot(){}
hubot::~hubot(){}

void hubot::findPath(node *now, node *finish) {
	this->path.push_back(now);

	if (now == finish) {
		cout << "found" << endl;
		return;
	}

	if (this->orientation == NORTH && now->n == nullptr && now->e == nullptr && now->w == nullptr) {
		return;
	}

	else if (this->orientation == EAST && now->n == nullptr && now->e == nullptr && now->s == nullptr) {
		return;
	}

	else if (this->orientation == SOUTH && now->w == nullptr && now->e == nullptr && now->s == nullptr) {
		return;
	}

	else if (this->orientation == WEST && now->w == nullptr && now->n == nullptr && now->s == nullptr) {
		return;
	}

	if (now->n == finish) {
		this->orientation = NORTH;
		findPath(now->n, finish);
	}
	else if (now->e == finish) {
		this->orientation = EAST;
		findPath(now->e, finish);
	}
	else if (now->s == finish) {
		this->orientation = SOUTH;
		findPath(now->s, finish);
	}
	else if (now->w == finish) {
		this->orientation = WEST;
		findPath(now->w, finish);
	}

	if (now->n != nullptr) {
		this->orientation = NORTH;
		findPath(now->n, finish);
	}

	if (now->e != nullptr) {
		this->orientation = EAST;
		findPath(now->e, finish);
	}

	if (now->s != nullptr) {
		this->orientation = SOUTH;
		findPath(now->s, finish);
	}

	if (now->w != nullptr) {
		this->orientation = WEST;
		findPath(now->w, finish);
	}

}

joshbot::joshbot(){}
joshbot::~joshbot(){}
