#include "cachelab.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


void print_usage();
void print_trace_info();
void evaluate_input(int s, int E, int b, char *t, int h, int v);
void manual_string_copy(char **t, char *optarg);
// typedef struct Sets Sets;
typedef struct Set Set;
typedef struct Line Line;

//S = 2^s sets
//E = 2^e lines
//B = 2^b bytes per cache block

// struct Sets{
// 	int total_sets;
// 	Set *sets;
// };

struct Set{
	int total_lines;
	Line *lines;
};

struct Line{
	int valid;
	int tag;
	int total_bytes;
	int b;
	char *cache_block;
};




void print_usage(){
	printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n");
	printf("Options:\n");
	printf("  %-12s %s\n", "-h", "Print this help message.");
	printf("  %-12s %s\n", "-v", "Optional verbose flag.");
	printf("  %-12s %s\n", "-s <num>", "Number of set index bits.");
	printf("  %-12s %s\n", "-E <num>", "Number of lines per set.");
	printf("  %-12s %s\n", "-b <num>", "Number of block offset bits.");
	printf("  %-12s %s\n", "-t <file>", "Trace file.");

	printf("\n");

	printf("Examples:\n");
	printf("  %s\n", "linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace");
	printf("  %s\n", "linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace");
}

void print_trace_info(char * fileName){
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        printf("%s", line); 
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);

}

void evaluate_input(int s, int E, int b, char *t, int h, int v){
	if (h == 1){
		print_usage();
	}
	
	if (s == -1 || E == -1 || b == -1 || t == NULL){

		//check which command was not input
		int ns, nE, nb, nt, total;
		ns = 0;
		nE = 0;
		nb = 0;
		nt = 0;
		total = 0;
		if (s == -1){
			ns = 1;
			total++;
		}
		if(E == -1){
			nE = 1;
			total++;
		}
		if(b == -1){
			nb = 1;
			total++;
		}
		if (t != NULL){
			free(t);
		}else{
			nt = 1;
			total++;
		}


		if (total > 1){
			printf("Missing required command line argument\n");
		}else if(total == 1){
			printf("%s\n", t);
			printf("Options require an argument -- ");
			if(ns == 1){
				printf("\'%c\'", 's');
			}else if(nE == 1){
				printf("\'%c\'", 'E');
			}else if(nb == 1){
				printf("\'%c\'", 'b');
			}else if(nt == 1){
				printf("\'%c\'", 't');
			}
		}

		if(h != 1){
			print_usage();
		}
        exit(EXIT_FAILURE);
	}
}

void manual_string_copy(char **t, char *optarg){
	*t = malloc(sizeof(char) * strlen(optarg) + 1); //last byte for the trailing '\0'
	strcpy(*t,optarg);
}

void setup_memory(Set **sets, int s, int E, int b){
	int S = pow(2,s);
	int B = pow(2,b);
	*sets = (Set *) malloc(sizeof(Set) * S);
	for (int i = 0; i < S; ++i){
		(*sets[i]).total_lines = E;
		(*sets[i]).lines = (Line *) malloc(sizeof(Line) * E);
		for (int j = 0; j < E; ++j){
			(*sets[i]).lines[j].valid = 0;
			(*sets[i]).lines[j].tag = 0;
			(*sets[i]).lines[j].total_bytes = B;
			(*sets[i]).lines[j].b = b;
			(*sets[i]).lines[j].cache_block = (char*) malloc(sizeof(char) * (B));
		}
	}
}

void cleanup_memory(Set **sets, int s, int E, int b){
	int i, j;
	int S = pow(2,s);
	for(i = 0; i < S; ++i){
		for(j = 0; j < E; ++j){
			(*sets[i]).lines[j].valid = 0;
			(*sets[i]).lines[j].tag = 0;
			(*sets[i]).lines[j].total_bytes = 0;
			(*sets[i]).lines[j].b = 0;
			free((*sets[i]).lines[j].cache_block);
			(*sets[i]).lines[j].cache_block = 0;
		}
		(*sets[i]).total_lines = 0;
		free((*sets[i]).lines);
		(*sets[i]).lines = NULL;
	}
	free(*sets);
	*sets = NULL;
}

int main(int argc, char **argv)
{
	int option,s, E, b, h, v;
	char *t;
	option = 0;
	s = -1;
	E = -1;
	b = -1;
	t = NULL;
	h = -1;
	v = -1;

	//use getopt to get the input and parse from the command line
	while ((option = getopt(argc, argv,"hvs:E:b:t:")) != -1) {
        switch (option) {
            case 's' : s = atoi(optarg);
                break;
			case 'E' : E = atoi(optarg);
				break;
			case 'b' : b = atoi(optarg); 
				break;
			case 't' : manual_string_copy(&t,optarg);
				break;
			case 'h' : h = 1;
				break;
			case 'v' : v = 1;
				break;
             default: print_usage(); 
                 exit(EXIT_FAILURE);
        }
    }
    //evulate the inputs, exit right away if fail
    evaluate_input(s,E,b,t,h,v);

    //exit if file does not exist
    if( access( t, F_OK ) == -1 ) {
    	printf("%s: No such file or directory\n", t);
    	exit(EXIT_FAILURE);
	} 

	if (v == 1){
		print_trace_info(t);
	}

	Set *sets;
	setup_memory(&sets,s,E,b);



    printSummary(0, 0, 0);
    cleanup_memory(&sets,s,E,b);
    free(t);
    return 0;
}
