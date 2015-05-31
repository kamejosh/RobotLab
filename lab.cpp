#include "lab.h"
#include <getopt.h>
#include <assert.h>
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
			this->width = tempvalue.length()-1;
			this->height = tempvalue.length()-1;
		}
        for(unsigned int i = 0; i < tempvalue.length(); i++){
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
		for(int j = 0; j < this->width; j++){
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
				if(i == this->height){
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
}

void startMazerun(int argc, char* argv[]){
    int cmd;
	int error = 0;
    int cmdOptt[3];
    string temp;
    int tempNum;


    while((cmd = getopt(argc, argv, "t:h")) != EOF){
        switch(cmd){
            case 't':
                temp = CharAToString(optarg);
                tempNum = stoi(temp);
                if(cmdOptt[tempNum]){
                    error = 1;
                    break;
                }
                cmdOptt[tempNum] = 1;
                break;
            case 'h':
                print_usage(argv[0]);
                break;
            default:
                assert(0);
        }
    }

    if(error){
        print_usage(argv[0]);
    }

    if(argc < optind + 1){
        print_usage(argv[0]);
    }

    //we want the name of the file saved to the string variable mazefile
    string mazefile(argv[optind]);

	//string mazefile = "maze1_small.txt";

    lab *labyrinth = new lab(mazefile);

	labyrinth->connectNodes();

    labyrinth->findStartAndEnd();

	//labyrinth->printLab();


	if(cmdOptt[0] == 1){
		thread th1(labyrinth->startRobots, 1, labyrinth);
		th1.join();
	}
	if(cmdOptt[1] == 1){
		thread th2(labyrinth->startRobots, 2, labyrinth);
		th2.join();
	}
	if(cmdOptt[2] == 1){
		thread th3(labyrinth->startRobots, 3, labyrinth);
		th3.join();
	}


	//labyrinth->startRobots(1, labyrinth);

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
