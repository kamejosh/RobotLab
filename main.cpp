#include "lab.h"
#include <getopt.h>
#include <assert.h>

using namespace std;

int main(int argc, char* argv[]){
    int cmd;
	int error = 0;
    int cmdOptt[3] = {0,0,0};
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

    startMazerun(mazefile, cmdOptt);

    return 0;
}
