#include "lab.h"
#include <thread>
#include <cstring>

#define NUMROBOTS 3;

using namespace std;

lab::lab(string name){
    ifstream filename(name);
    string tempvalue;
	int once = 0;
	int line = 0;

    while(getline(filename, tempvalue)){
		if(once == 0){
			this->labyrinth.resize(tempvalue.length()-1);

			for(unsigned int i = 0; i < tempvalue.length(); i++){
				this->labyrinth[i].resize(tempvalue.length()-1);
			}

			once = 1;
			this->width = (int)tempvalue.length()-1;
            //cout << this->width << endl;
			this->height = (int)tempvalue.length()-1;
            //cout << this->height << endl;
		}

        for(unsigned int i = 0; i < tempvalue.length()-1; i++){
            //cout << line << endl;
            if(tempvalue[i] == '#'){
				this->labyrinth[line][i] = nullptr;
            }
			else{
				this->labyrinth[line][i] = new node(line, i);
			}
        }

		line++;
    }
}

lab::~lab(){}

void lab::connectNodes(){
	for(int i = 0; i < this->height; i++){
        //cout << "iiiiiiii:" << i << endl;
		for(int j = 0; j < this->width; j++){
            //cout << "j:" << j << endl;
			if(this->labyrinth[i][j] != nullptr){
				if(i == 0){
					this->labyrinth[i][j]->n = nullptr;
				}
				else{
					this->labyrinth[i][j]->n = this->labyrinth[i-1][j];
				}
				if(j == 0){
					this->labyrinth[i][j]->w = nullptr;
				}
				else{
					this->labyrinth[i][j]->w = this->labyrinth[i][j-1];
				}
				if(i == this->width-1){
					this->labyrinth[i][j]->e = nullptr;
				}
				else{
					this->labyrinth[i][j]->e = this->labyrinth[i][j+1];
				}
				if(i == this->height-1){
					this->labyrinth[i][j]->s = nullptr;
				}
				else{
					this->labyrinth[i][j]->s = this->labyrinth[i+1][j];
				}
			}
		}
	}
}

void lab::findStartAndEnd(){
	//searching for the entrypoint of the labyrinth
	for(int i = 0; i < this->width; i++){
		if(this->labyrinth[0][i] != nullptr){
			this->start = this->labyrinth[0][i];
			break;
		}
	}
	if(this->start == nullptr){
		for(int i = 0; i < this->height; i++){
			if(this->labyrinth[this->width-1][i] != nullptr){
				this->start = this->labyrinth[width-1][i];
				break;
			}
		}
		if(this->start == nullptr){
			for(int i = this->width -1; i >= 0; i--){
				if(this->labyrinth[height-1][i] != nullptr){
					this->start = this->labyrinth[height-1][i];
					break;
				}
			}
			if(this->start == nullptr){
				for(int i = this->height -1; i >= 0; i--){
					if(this->labyrinth[i][0] != nullptr){
						this->start = this->labyrinth[i][0];
						break;
					}
				}
			}
		}
	}
	//searching for the exitpoint of the labyrinth
	for(int i = 0; i < this->width; i++){
		if(this->labyrinth[0][i] != nullptr && this->labyrinth[0][i] != this->start){
			this->end = this->labyrinth[0][i];
			break;
		}
	}
	if(this->end == nullptr){
		for(int i = 0; i < this->height; i++){
			if(this->labyrinth[this->width-1][i] != nullptr && this->labyrinth[this->width-1][i] != this->start){
				this->end = this->labyrinth[width-1][i];
				break;
			}
		}
		if(this->end == nullptr){
			for(int i = this->width -1; i >= 0; i--){
				if(this->labyrinth[height-1][i] != nullptr && this->labyrinth[height-1][i] != this->start){
					this->end = this->labyrinth[height-1][i];
					break;
				}
			}
			if(this->end == nullptr){
				for(int i = this->height -1; i >= 0; i--){
					if(this->labyrinth[i][0] != nullptr && this->labyrinth[i][0] != this->start){
						this->end = this->labyrinth[i][0];
						break;
					}
				}
			}
		}
	}
}

void lab::printLab(vector<node*> path){
	int stepOn = 0;

	for(int i = 0; i < this->height; i++){
		for(int j = 0; j < this->width; j++){
			if(this->labyrinth[i][j] == nullptr){
				cout << "#";
			}
			else{
				for(unsigned int k = 0; k < path.size(); k++){
					if(this->labyrinth[i][j] == path[k]){
                        if(stepOn == 0){
    						cout << "r";
    						stepOn = 1;
                        }
					}
				}
				if(!stepOn){
					cout << " ";
				}
				stepOn = 0;
			}
		}
		cout << endl;
	}
}

void lab::startRunning(int robo[3]){
    /*if(robo[0] == 1){
		//cout << "hier" << endl;
		thread th1(this->startRobots, this, 1);
		th1.join();
	}
	if(robo[1] == 1){
		//cout << "da" << endl;
		thread th2(this->startRobots, this, 2);
		th2.join();
	}
	if(robo[2] == 1){
		//cout << "dort" << endl;
		thread th3(this->startRobots, this, 3);
		th3.join();
	}*/
}
/*
void lab::startRobots(int type, void* args){

	//erzeugt ein this-> für static function
	lab *das = static_cast<lab*>(args);

	das->robots.resize(3);

	int i;

	//r.lock();

	for(i = 0; i < 3; i++){
		if(das->robots[i] == nullptr){
			switch(type){
				case 1:
					das->robots[i] = new robot_left;
					break;
				case 2:
					das->robots[i] = new hubot;
					break;
				case 3:
					das->robots[i] = new joshbot;
					break;
				default:
					break;
			}
			break;
		}
	}

	//r.unlock();

	das->robots[i]->findPath(das->start, das->end);

	das->printLab(das->robots[i]->path);

	cout << "robo!" << endl;
}*/

void lab::startRobots(int type){

	//erzeugt ein this-> für static function
	//lab *das = static_cast<lab*>(args);

	this->robots.resize(3);

	int i;

	//r.lock();

	for(i = 0; i < 3; i++){
		if(this->robots[i] == nullptr){
			switch(type){
				case 1:
					this->robots[i] = new robot_left;
					break;
				case 2:
					this->robots[i] = new hubot;
					break;
				case 3:
					this->robots[i] = new joshbot;
					break;
				default:
					break;
			}
			break;
		}
	}

	//r.unlock();

	this->robots[i]->findPath(this->start, this->end);

	this->printLab(this->robots[i]->path);

	cout << "robo!" << endl;
}

void startMazerun(string mazefile, int robo[3]){
	//cout << "hier" << endl;
    lab *labyrinth = new lab(mazefile);
	//cout << "da" << endl;
	labyrinth->connectNodes();
	//cout << "oder" << endl;
    labyrinth->findStartAndEnd();
	//cout << "drüben" << endl;
/*
    for(int i = 0; i < 3; i++){
        cout << robo[i] << endl;
    }
*/
/*
	if(robo[0] == 1){
		thread th1(labyrinth->startRobots, 1);
		th1.join();
	}
	if(robo[1] == 1){
		thread th2(labyrinth->startRobots, 2);
		th2.join();
	}
	if(robo[2] == 1){
		thread th3(labyrinth->startRobots, 3);
		th3.join();
	}
*/
	labyrinth->startRobots(2);
	//labyrinth->startRunning(robo);
    delete labyrinth;
}

string CharAToString(char* arr){
	string temp;
	for(unsigned int i = 0; i < strlen(arr); i++){
		temp += arr[i];
		//debugging
		//cout << temp << endl;
	}

	return temp;
}

void print_usage(char *name){
	fprintf(stderr,"Usage: %s DATEINAME [-t1] [-t2] [-t3] ... [-tN] [-h]\n", name);
	exit(EXIT_FAILURE);
}
