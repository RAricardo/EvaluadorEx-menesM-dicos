#include <stdio.h>
#include <unistd.h>
#include "iostream"
#include <string.h>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <getopt.h>
#include <fstream>
#include <iostream>
#include "Memoria.h"
#include "ColaEntrada.h"
#include "ColaSalida.h"
#include "Evaluador.h"
#include <bits/stdc++.h> 
#include <sstream>
#include "MemoryManager.h"

using namespace std;

void init_parameters (int opt,int i,int ie,int oe,char* n,int b,int d,int s,int q);
void stop_parameters(char c,char* n);
void rep_parameters(char c, char* n, int i, int m);
void ctrl_parameters(char c, char* n);
void reg_parameters(char c, char* n);

struct Init_struct {
    int i,b,d,s,q,ie,oe;
    char* n;
};

struct Reg_struct {
    char* n;
};

struct Stop_struct {
    char* n;
};

struct Rep_struct {
    char* n;
    int i,m;
};

struct Ctrl_struct {
    char* n;
};


Init_struct init_s;
Stop_struct stop_s;
Rep_struct rep_s;
Ctrl_struct ctrl_s;
Reg_struct reg_s;

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

    string dm = "evaluator";
    int n = dm.size()+1;
    char* default_memory = new char[n];
    strcpy(default_memory, dm.c_str());

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

        init_s.i=5;
        init_s.ie=6;
        init_s.oe=10;
        init_s.b=100;
        init_s.d=100;
        init_s.s=100;
        init_s.q=6;
        init_s.n=default_memory;

        while ((opt = getopt_long_only(argc, argv,"", long_options, &long_index )) != -1) {
            init_parameters(opt,init_s.i,init_s.ie,init_s.oe,init_s.n,init_s.b,init_s.d,init_s.s,init_s.q);
        }

        Evaluador::init(init_s.n, init_s.i, init_s.ie, init_s.oe, init_s.b, init_s.d, init_s.s, init_s.q);
        
        for(;;){}

    } else if (reg_command == 0) {

        reg_s.n=default_memory;

        while(( c = getopt( argc, argv, "n:" )) != -1 ) {
            reg_parameters(c,reg_s.n);
        }
        int arg_count = 0; 
        while(argv[++arg_count] != NULL);

        int is_interactive=-1;
        int is_not_file=-1;

        if(arg_count==3){
            is_interactive = strcmp(argv[2], "-");
        }else if(arg_count==5) {
            is_not_file = strcmp(argv[4], "-");
            if(is_not_file==0){
                is_interactive = 0;
            }
        }
        if(arg_count==2){
            exit(1);
        }

        if(is_interactive == 0){

            string x="";
            string bandeja_entrada="";
            string muestra="";
            string cantidad_muestra="";
            int entrada=0;
            int cantidad=0;
            char tipo_muestra;

            int j=0;
            while(cin >> bandeja_entrada >> muestra >> cantidad_muestra) {

                entrada = atoi(bandeja_entrada.c_str());
                tipo_muestra = muestra[0];
                cantidad = atoi(cantidad_muestra.c_str());

                cout << j << endl;
                j++;
            }  

        } else {

            string bandeja_entrada="";
            string muestra="";
            string cantidad_muestra="";
            int entrada=0;
            int cantidad=0;
            char tipo_muestra;

            int i=0;
            if(arg_count==3 && is_interactive!=0){
                i=2;
            }else if((arg_count>=5 && is_not_file!=0)){
                i=2;
            }else if(arg_count==4){
                i=2;
            }

            for(i; i <= argc; i++) {
                
                ifstream infile(argv[i]); //open the file

                if (infile.is_open() && infile.good()) {

                    string out_file = argv[i];
                    size_t lastindex = out_file.find_last_of("."); 
                    string rawname = out_file.substr(0, lastindex);

                    string out_name = rawname + ".spl";

                    const char *out_file_name = out_name.c_str();
                    ofstream outfile (out_file_name);

                    /*
                        Si las muestras provienen de un fichero
                        se retorna un fichero con el mismo nombre pero con extensioon spl (Samples)
                        donde se muestra los identicadores pendientes y las muestras provienen de la
                        entrada estandar despues de un examen se retorna el numero de la muestra.
                     */
                    if (outfile.is_open()){
                        outfile << "Pending identifiers.\n"; //writing into the .spl file
                        outfile.close();
                    }

                    string line = "";
                    while (getline(infile, line)){

                        string arr[3];
                        int i = 0;
                        stringstream ssin(line);
                        while (ssin.good() && i < 3){
                            ssin >> arr[i];
                            ++i;
                        }

                        entrada = atoi(arr[0].c_str());
                        tipo_muestra = (arr[1].c_str())[0];
                        cantidad = atoi(arr[2].c_str());

                    }
                    infile.close();
                }
            }
        }

    } else if (ctrl_command == 0) {

        ctrl_s.n=default_memory;

        while(( c = getopt( argc, argv, "n:" )) != -1 ) {
            ctrl_parameters(c,ctrl_s.n);
        }

        char processing[] ="list processing";
        char waiting[]="list waiting";
        char reported[]="list reported"; 
        char reactive[]="list reactive"; 
        char all[]="list all";
        char update[]="update";
        string updated="update";

        int processing_command;
        int waiting_command;
        int reported_command;
        int reactive_command;
        int all_command;
        int update_command;

        string sub_command;

            while(getline(cin, sub_command))  {
            
            int carga=0;
            char tipo_muestra;
            string type_command;

            if (sub_command.find(updated) != string::npos) {

                string arr[3];
                int i = 0;
                stringstream ssin(sub_command);
                while (ssin.good() && i < 3){
                    ssin >> arr[i];
                    ++i;
                }

                type_command = arr[0];
                tipo_muestra = (arr[1].c_str())[0];
                carga = atoi(arr[2].c_str());

            } 

            int n = sub_command.size()+1;
            char* char_sub_command = new char[n];

            //char char_sub_command[sub_command.size()+1];
            strcpy(char_sub_command, sub_command.c_str());

            int m = type_command.size()+1;
            char* char_type_command = new char[m];

            //char char_type_command[type_command.size()+1];
            strcpy(char_type_command, type_command.c_str());

            processing_command = strcmp(processing, char_sub_command);
            waiting_command = strcmp(waiting, char_sub_command);
            reported_command = strcmp(reported, char_sub_command);
            reactive_command = strcmp(reactive, char_sub_command);
            all_command = strcmp(all, char_sub_command);
            update_command = strcmp(update, char_type_command);

            if(processing_command==0){
                cout << "Processing: " << endl;

            }else if(waiting_command==0){
                cout << "Waiting: " << endl;

            }else if(reported_command==0){
                cout << "Reported: " << endl;

            }else if(reactive_command==0){
                cout << "Reactive: " << endl;

            }else if(all_command==0){
                cout << "All: " << endl;

            }else if(update_command==0){
                
                //code for update (tipo_muestra, carga)

            }
        } 

    } else if (rep_command == 0) {

        rep_s.n = default_memory;
        rep_s.i = 1;
        rep_s.m = 1;

        while(( c = getopt( argc, argv, "n:i:m:" )) != -1 ) {
            rep_parameters(c,rep_s.n, rep_s.i, rep_s.m);
        }


    } else if (stop_command == 0) {

        stop_s.n=default_memory;

        while(( c = getopt( argc, argv, "n:" )) != -1 ) {
            stop_parameters(c,stop_s.n);
        }

        MemoryManager::unlink(stop_s.n);
        
    } else {

        exit(1);

    }
  
    return 0;
}

void init_parameters (int opt, int i, int ie, int oe, char* n, int b, int d, int s, int q)
{
    switch (opt)
    {
        case 'i':
            i=atoi(optarg);
            init_s.i=i;
            break;
        //r is equal to ie
        case 'r':
            ie=atoi(optarg);
            init_s.ie=ie;
            break;
        //t is equal to oe
        case 't':
            oe=atoi(optarg);
            init_s.oe=oe;
            break;
        case 'n':
            n=optarg;
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

void stop_parameters(char c,char* n)
{
    switch ( c )
    {
        case 'n':
            n=optarg;
            stop_s.n=n;
            break;
        case '?':
            cout<<"Unrecognized option!\n"<<endl;
            break;
    }
}

void rep_parameters(char c, char* n, int i, int m)
{
    switch ( c )
    {
        case 'n':
            n=optarg;
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

void ctrl_parameters(char c, char* n)
{
    switch ( c )
    {
        case 'n':
            n=optarg;
            ctrl_s.n=n;
            break;
        case '?':
            cout<<"Unrecognized option!\n"<<endl;
            break;
    }
}

void reg_parameters(char c, char* n)
{
    switch ( c )
    {
        case 'n':
            n=optarg;
            reg_s.n=n;
            break;
        case '?':
            cout<<"Unrecognized option!\n"<<endl;
            break;
    }
}