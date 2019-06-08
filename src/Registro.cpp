#include <stdio.h>
#include <unistd.h>
#include "iostream"
#include <string.h>

using namespace std;

int main( int argc, char  *argv[] )
{
    char c;
    char init[] = "init";
    char reg[] = "reg";
    char ctrl[] = "ctrl";
    char rep[] = "rep";
    char stop[] = "stop";

    int init_command = strcmp(argv[1], init);
    int reg_command = strcmp(argv[1], reg);
    int ctrl_command = strcmp(argv[1], ctrl);
    int rep_command = strcmp(argv[1], rep);
    int stop_command = strcmp(argv[1], stop);

    if (init_command == 0) {
        printf("Has escogido el comando init (%s)", argv[1]);
    } else if (reg_command == 0) {
        printf("Has escogido el comando reg (%s)", argv[1]);
    } else if (ctrl_command == 0) {
        printf("Has escogido el comando ctrl (%s)", argv[1]);
    } else if (rep_command == 0) {
        printf("Has escogido el comando rep (%s)", argv[1]);
    } else if (stop_command == 0) {
        printf("Has escogido el comando stop (%s)", argv[1]);
    } else {
        printf("Has seleccionado un comando invalido.\n");
    }
  
    while(( c = getopt( argc, argv, "i:p:" )) != -1 )
        switch ( c )
        {
            case 'i':
                cout << optarg << endl;
                break;
            case 'p':
                cout << optarg << endl;
                break;
            case '?':
                cout<<"Unrecognized option!\n"<<endl;
                break;
        }

    return 0;
}