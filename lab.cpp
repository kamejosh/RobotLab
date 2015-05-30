#include "lab.h"
#include <getopt.h>
#include <assert.h>

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

void lab::printLab(){
	for(int i = 0; i < this->height; i++){
		for(int j = 0; j < this->width; j++){
			if(this->labyrinth[i][j] == nullptr){
				cout << "#";
			}
			else{
				cout << " ";
			}
		}
		cout << endl;
	}
}

void startMazerun(int argc, char* argv[]){
    int cmd;
	int error = 0;
    int cmdOptt[3];
    string temp;
    int tempNum;

	/*
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

    //wi want the name of the file saved to the string variable mazefile
    string mazefile(argv[optind]);
	*/
	
	string mazefile = "maze5_cavern.txt";
	
    lab *labyrinth = new lab(mazefile);
	
	labyrinth->connectNodes();

    labyrinth->findStartAndEnd();

	labyrinth->printLab();
	
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
