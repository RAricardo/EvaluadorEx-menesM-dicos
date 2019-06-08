#include <stdio.h>
#include <unistd.h>
#include "iostream"
#include <string.h>
#include <string>
#include <stdlib.h>
#include <cstring>

#include <getopt.h>


using namespace std;

void init_parameters (int opt,int i,int ie,int oe,string n,int b,int d,int s,int q);
void stop_parameters(char c,string n);
void rep_parameters(char c, string n, int i, int m);
void ctrl_parameters(char c, string n);
void reg_parameters(char c, string n);

// ./a.out reg -n memoria prueba.txt prueba2.txt

// ./a.out reg -n memoria - (cosita interactiva)

// ./a.out rep -n memoria (( -i # ó -m # ))

struct Init_struct {
    int i,b,d,s,q,ie,oe;
    string n;
};

struct Stop_struct {
    string n;
};

struct Rep_struct {
    string n;
    int i,m;
};

struct Ctrl_struct {
    string n;
};

struct Reg_struct {
    string n;
};

Init_struct init_s;
Stop_struct stop_s;
Rep_struct rep_s;
Ctrl_struct ctrl_s;
Reg_struct reg_s;

/*  Files  */
char *infile = NULL;
FILE *file = stdin;
FILE *text = stdout;
char ch[200];

int opt = 0;

static struct option long_options[] = {
        {"i",   required_argument, 0,  'i' },
        {"ie",  required_argument, 0,  'r' },
        {"oe",  required_argument, 0,  't' },
        {"n",   required_argument, 0,  'n' },
        {"b",   required_argument, 0,  'b' },
        {"d",   required_argument, 0,  'd' },
        {"s",   required_argument, 0,  's' },
        {"q",   required_argument, 0,  'q' },
        {0,           0,                 0,  0   }
};

int long_index =0;

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

    // para init falta [-ie <integer>] [-oe <integer>]

    if (init_command == 0) {

        printf("Has escogido el comando (%s)", argv[1]);
        cout << endl;

        init_s.i=5;
        init_s.ie=6;
        init_s.oe=10;
        init_s.b=100;
        init_s.d=100;
        init_s.s=100;
        init_s.q=6;
        init_s.n="evaluator";

        while ((opt = getopt_long_only(argc, argv,"", long_options, &long_index )) != -1) {
            init_parameters(opt,init_s.i,init_s.ie,init_s.oe,init_s.n,init_s.b,init_s.d,init_s.s,init_s.q);
        }

        cout << "valores finales: " << endl;
        cout << "-i: " << init_s.i << endl;
        cout << "-ie: " << init_s.ie << endl;
        cout << "-oe: " << init_s.oe << endl;
        cout << "-n: " << init_s.n << endl;
        cout << "-b: " << init_s.b << endl;
        cout << "-d: " << init_s.d << endl;
        cout << "-s: " << init_s.s << endl;
        cout << "-q: " << init_s.q << endl;

    } else if (reg_command == 0) {

        printf("Has escogido el comando (%s)", argv[1]);
        cout << endl;

        reg_s.n="evaluator";

        while(( c = getopt( argc, argv, "n:" )) != -1 ) {
            reg_parameters(c,reg_s.n);
        }

        cout << "valores finales: " << endl;
        cout << "-n: " << reg_s.n << endl;

        if (infile) {
            file = fopen(infile, "r");
                if (file == NULL) {
                    cout << "cannot open input file" << endl;
                    exit(1);
                }
        }

        while (fgets(ch, 200, file) != NULL) {
            fputs(ch, text);
        }

        fclose(file);
        fclose(text);

    } else if (ctrl_command == 0) {

        printf("Has escogido el comando (%s)", argv[1]);
        cout << endl;

        ctrl_s.n="evaluator";

        while(( c = getopt( argc, argv, "n:" )) != -1 ) {
            ctrl_parameters(c,ctrl_s.n);
        }

        cout << "valores finales: " << endl;
        cout << "-n: " << ctrl_s.n << endl;

    } else if (rep_command == 0) {

        printf("Has escogido el comando (%s)", argv[1]);
        cout << endl;

        rep_s.n = "evaluator";
        rep_s.i = 1;
        rep_s.m = 1;

        while(( c = getopt( argc, argv, "n:i:m:" )) != -1 ) {
            rep_parameters(c,rep_s.n, rep_s.i, rep_s.m);
        }

        cout << "valores finales: " << endl;
        cout << "-n: " << rep_s.n << endl;
        cout << "-i: " << rep_s.i << endl;
        cout << "-m: " << rep_s.m << endl;

    } else if (stop_command == 0) {

        printf("Has escogido el comando (%s)", argv[1]);
        cout << endl;

        stop_s.n="evaluator";

        while(( c = getopt( argc, argv, "n:" )) != -1 ) {
            stop_parameters(c,stop_s.n);
        }

        cout << "valores finales: " << endl;
        cout << "-n: " << stop_s.n << endl;

    } else {

        printf("Has seleccionado un comando invalido.\n");
        cout << endl;

    }
  
    return 0;
}

void init_parameters (int opt, int i, int ie, int oe, string n, int b, int d, int s, int q)
{
    switch (opt)
    {
        case 'i':
            i=atoi(optarg);
            init_s.i=i;
            break;
        //{"ie", optional_argument, 0,  'r' }
        case 'r':
            ie=atoi(optarg);
            init_s.ie=ie;
            break;
        //{"oe",    optional_argument, 0,  't' },
        case 't':
            oe=atoi(optarg);
            init_s.oe=oe;
            break;
        case 'n':
            n=(string)optarg;
            init_s.n=n;
            break;
        case 'b':
            b=atoi(optarg);
            init_s.b=b;
            break;
        case 'd':
            d=atoi(optarg);
            init_s.d=d;
            break;
        case 's':
            s=atoi(optarg);
            init_s.s=s;
            break;
        case 'q':
            q=atoi(optarg);
            init_s.q=q;
            break;

        case '?':
            cout<<"Unrecognized option!\n"<<endl;
            break;
    }
}

void stop_parameters(char c,string n)
{
    switch ( c )
    {
        case 'n':
            n=(string)optarg;
            stop_s.n=n;
            break;
        case '?':
            cout<<"Unrecognized option!\n"<<endl;
            break;
    }
}

void rep_parameters(char c, string n, int i, int m)
{
    switch ( c )
    {
        case 'n':
            n=(string)optarg;
            rep_s.n=n;
            break;
        case 'i':
            i=atoi(optarg);
            rep_s.i=i;
            break;
        case 'm':
            m=atoi(optarg);
            rep_s.m=m;
            break;
        case '?':
            cout<<"Unrecognized option!\n"<<endl;
            break;
    }
}

void ctrl_parameters(char c, string n)
{
    switch ( c )
    {
        case 'n':
            n=(string)optarg;
            ctrl_s.n=n;
            break;
        case '?':
            cout<<"Unrecognized option!\n"<<endl;
            break;
    }
}

void reg_parameters(char c, string n)
{
    switch ( c )
    {
        case 'n':
            n=(string)optarg;
            reg_s.n=n;
            infile = optarg;
            break;
        case '?':
            cout<<"Unrecognized option!\n"<<endl;
            break;
    }
}