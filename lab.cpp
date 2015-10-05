#include "lab.h"
#include <thread>
#include <cstring>
#include <mutex>

#define NUMROBOTS 3;

using namespace std;

mutex mtx;

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

lab::~lab(){
    for (unsigned int i = 0; i < this->labyrinth.capacity(); i++) {
        for (unsigned int j = 0; j < this->labyrinth[0].capacity(); j++) {
            delete this->labyrinth[i][j];
        }
    }
}

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
    						cout << "\033[31mr\033[0m";
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


void lab::startRobots(int type){

	//erzeugt ein this-> für static function
	//lab *das = static_cast<lab*>(args);

	this->robots.resize(3);

	int i;



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
					this->robots[i] = new robot_right;
					break;
				default:
					break;
			}
			break;
		}
	}



	this->robots[i]->findPath(this->start, this->end);

    mtx.lock();
	this->printLab(this->robots[i]->path);

    switch(type){
        case 1:
            cout << "robot_left needed: " << this->robots[i]->steps << " steps, to find a way out of the maze" << endl;
            delete this->robots[i];
            break;
        case 2:
            cout << "hubot needed: " << this->robots[i]->steps << " steps, to find a way out of the maze" << endl;
            delete this->robots[i];
            break;
        case 3:
            cout << "robot_right needed: " << this->robots[i]->steps << " steps, to find a way out of the maze" << endl;
            delete this->robots[i];
            break;
        default:
            break;
    }

    mtx.unlock();

}

void startMazerun(string mazefile, int robo[3]){
    int started = 0;
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

    auto fun = [&labyrinth](int n){labyrinth->startRobots(n);};

	if(robo[0] == 1){
        started++;
		thread th1(fun, 1);
		th1.join();
	}
	if(robo[1] == 1){
        started++;
		thread th2(fun, 2);
		th2.join();
	}
	if(robo[2] == 1){
        started++;
		thread th3(fun, 3);
		th3.join();
	}
    if(started == 0){
        thread thx(fun, 1);
        thx.join();
    }

	//labyrinth->startRobots(3);
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
	fprintf(stderr,"Usage: %s DATEINAME [-t1] [-t2] [-t3] [-h]\n", name);
	exit(EXIT_FAILURE);
}
