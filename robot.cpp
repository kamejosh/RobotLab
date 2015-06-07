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

	for (unsigned int i = 0; i < this->path.size(); i++) {
		if (now == this->path[i]) {
			return;
		}
	}

	this->path.push_back(now);


	if (now == finish || this->found == true) {
		this->found = true;
		return;
	}

	else {

		if (this->steps != 0) {

			if (now->n == nullptr && now->e == nullptr && now->w == nullptr) {
				return;
			}

			else if (now->n == nullptr && now->e == nullptr && now->s == nullptr) {
				return;
			}

			else if (now->w == nullptr && now->e == nullptr && now->s == nullptr) {
				return;
			}

			else if (now->w == nullptr && now->n == nullptr && now->s == nullptr) {
				return;
			}

		}

		if (now->n == finish || now->e == finish || now->s == finish || now->w == finish) {

			if (now->n == finish) {
				this->steps++;
				findPath(now->n, finish);
			}
			else if (now->e == finish) {
				this->steps++;
				findPath(now->e, finish);
			}
			else if (now->s == finish) {
				this->steps++;
				findPath(now->s, finish);
			}
			else if (now->w == finish) {
				this->steps++;
				findPath(now->w, finish);
			}

		}

		else {

			if (now->n != nullptr) {
				this->steps++;
				findPath(now->n, finish);
			}

			if (now->e != nullptr) {
				this->steps++;
				findPath(now->e, finish);
			}

			if (now->s != nullptr) {
				this->steps++;
				findPath(now->s, finish);
			}

			if (now->w != nullptr) {
				this->steps++;
				findPath(now->w, finish);
			}

		}

	}

}

joshbot::joshbot(){}
joshbot::~joshbot(){}
