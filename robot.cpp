#include "robot.h"

using namespace std;

robot::robot(){}
robot::~robot(){}

void robot::findPath(node* now, node* finish){
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

//Pledge Algorithmus
void joshbot::findPath(node* now, node* finish){
	//calculating in wich direction from the startpoint the finish lies
	this->setDirection(now, finish);
	if(this->steps == 0){
		this->orientation = this->direction;
	}
	this->path.push_back(now);
	if(now == finish){
		return;
	}
	
	else{
		if(this->direction == this->orientation && this->turns == 0){
			switch(this->orientation){
				case NORTH:
					if(now->n != nullptr){
						this->steps++;
						this->findPath(now->n, finish);
					}
					else if(now->w != nullptr){
						this->turnleft();
						this->steps++;
						this->findPath(now->w, finish);
					}
					else if(now->s != nullptr){
						this->turnleft();
						this->turnleft();
						this->steps++;
						this->findPath(now->s, finish);
					}
					break;
				case EAST:
					if(now->e != nullptr){
						this->steps++;
						this->findPath(now->e, finish);
					}
					else if(now->n != nullptr){
						this->turnleft();
						this->steps++;
						this->findPath(now->n, finish);
					}
					else if(now->w != nullptr){
						this->turnleft();
						this->turnleft();
						this->steps++;
						this->findPath(now->w, finish);
					}
					break;
				case SOUTH:
					if(now->s != nullptr){
						this->steps++;
						this->findPath(now->s, finish);
					}
					else if(now->e != nullptr){
						this->turnleft();
						this->steps++;
						this->findPath(now->e, finish);
					}
					else if(now->n != nullptr){
						this->turnleft();
						this->turnleft();
						this->steps++;
						this->findPath(now->n, finish);
					}
					break;
				case WEST:
					if(now->w != nullptr){
						this->steps++;
						this->findPath(now->w, finish);
					}
					else if(now->s != nullptr){
						this->turnleft();
						this->steps++;
						this->findPath(now->s, finish);
					}
					else if(now->e != nullptr){
						this->turnleft();
						this->turnleft();
						this->steps++;
						this->findPath(now->e, finish);
					}
					break;
			}
		}
		else{
			if(this->turns < 0){
				switch(this->orientation){
					case NORTH:
						if(now->e != nullptr){
							turnright();
							this->steps++;
							this->findPath(now->e, finish);
						}
						else if(now->n != nullptr){
							this->steps++;
							this->findPath(now->n, finish);
						}
						else if(now->w != nullptr){
							this->turnleft();
							this->steps++;
							this->findPath(now->w, finish);
						}
						break;
					case EAST:
						if(now->s != nullptr){
							turnright();
							this->steps++;
							this->findPath(now->s, finish);
						}
						else if(now->e != nullptr){
							this->steps++;
							this->findPath(now->e, finish);
						}
						else if(now->n != nullptr){
							this->turnleft();
							this->steps++;
							this->findPath(now->n, finish);
						}
						break;
					case SOUTH:
						if(now->w != nullptr){
							turnright();
							this->steps++;
							this->findPath(now->w, finish);
						}
						else if(now->s != nullptr){
							this->steps++;
							this->findPath(now->s, finish);
						}
						else if(now->e != nullptr){
							this->turnleft();
							this->steps++;
							this->findPath(now->e, finish);
						}
						break;
					case WEST:
						if(now->n != nullptr){
							turnright();
							this->steps++;
							this->findPath(now->n, finish);
						}
						else if(now->w != nullptr){
							this->steps++;
							this->findPath(now->w, finish);
						}
						else if(now->s != nullptr){
							this->turnleft();
							this->steps++;
							this->findPath(now->s, finish);
						}
						break;
				}
			}
			else{
				cout << "this should never happen!" << endl;
				return;
			}
		}
	}
}

void joshbot::setDirection(node *now, node *finish){
	int tempY = now->x - finish->x;
	int tempX = now->y - finish->y;
	if(tempX > 0 && tempY > 0){
		if(tempX > tempY){
			this->direction = WEST;
		}
		else{
			this->direction = NORTH;
		}
	}
	else if(tempX < 0 && tempY > 0){
		if(abs(tempX) > tempY){
			this->direction = EAST;
		}
		else{
			this->direction = NORTH;
		}
	}
	else if(tempX > 0 && tempY < 0){
		if(tempX > abs(tempY)){
			this->direction = WEST;
		}
		else{
			this->direction = SOUTH;
		}
	}
	else if(tempX < 0 && tempY < 0){
		if(abs(tempX) > abs(tempY)){
			this->direction = EAST;
		}
		else{
			this->direction = SOUTH;
		}
	}
	else if(tempX == 0 || tempY == 0){
		if(tempX > 0){
			this->direction = WEST;
		}
		else if(tempX < 0){
			this->direction = EAST;
		}
		else if(tempY > 0){
			this->direction = NORTH;
		}
		else if(tempY < 0){
			this->direction = SOUTH;
		}
	}
	if(tempX == tempY){
		
	}
}

void joshbot::turnleft(){
	this->orientation = (this->orientation -1)%4;
	this->turns--;
}

void joshbot::turnright(){
	this->orientation = (this->orientation +1)%4;
	this->turns++;
}