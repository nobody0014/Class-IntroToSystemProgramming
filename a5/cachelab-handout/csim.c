#include "cachelab.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

typedef struct Set Set;
typedef struct Line Line;
typedef struct Statistic Stat;
void print_usage();
void print_trace_info();
void evaluate_input(int s, int E, int b, char *t, int h, int v);
void manual_string_copy(char **t, char *optarg);
void setup_memory(Set **sets, int s, int E, int b);
void cleanup_memory(Set **sets, int s, int E, int b);

struct Statistic{
	int miss;
	int hit;
	int evict;
};

struct Set{
	int total_lines;
	Line *lines;
};

struct Line{
	int valid;
	long long tag;
	int total_bytes;
	int b;
	clock_t timestamp;
	// char *cache_block;
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
		(*sets)[i].total_lines = E;
		(*sets)[i].lines = (Line *) malloc(sizeof(Line) * E);
		for (int j = 0; j < E; ++j){
			(*sets)[i].lines[j].valid = 0;
			(*sets)[i].lines[j].tag = -1;
			(*sets)[i].lines[j].total_bytes = B;
			(*sets)[i].lines[j].b = b;
			(*sets)[i].lines[j].timestamp = 0;
			// (*sets)[i].lines[j].cache_block = (char*) malloc(sizeof(char) * (B));
		}
	}
}

void cleanup_memory(Set **sets, int s, int E, int b){
	int i, j;
	int S = pow(2,s);
	for(i = 0; i < S; ++i){
		for(j = 0; j < E; ++j){
			(*sets)[i].lines[j].valid = 0;
			(*sets)[i].lines[j].tag = -1;
			(*sets)[i].lines[j].total_bytes = 0;
			(*sets)[i].lines[j].b = 0;
			(*sets)[i].lines[j].timestamp = 0;
			// free((*sets)[i].lines[j].cache_block);
			// (*sets)[i].lines[j].cache_block = 0;
		}
		(*sets)[i].total_lines = 0;
		free((*sets)[i].lines);
		(*sets)[i].lines = NULL;
	}
	free(*sets);
	*sets = NULL;
}

/*
I --> instruction load
L --> data load
S --> data store
M --> data modify
[space] operation address, size
space doesnt exist for I
size is the the number of size accessed by the operation
*/
int get_least_recently_used_line(Set s){
	clock_t least_recent = clock();
	int i;
	int index = 0;
	for (i = 0; i < s.total_lines; ++i){
		clock_t line_timestamp = s.lines[i].timestamp;
		if (line_timestamp != 0 && line_timestamp < least_recent){
			least_recent = line_timestamp;
			index = i;
		}
	}
	return index;
}

int make_mask(int size){
	int mask = 1;
	for (int i = 0; i < size-1; ++i){
		mask = mask << 1;
		mask += 1;
	}
	return mask;
}

void print_v(char *toPrint, int v){
	if(v == 1){
		printf(" %s", toPrint);
	}
}

int check_tag_in_set(Set set, long long tag){
	int i;
	int all_lines_valid;
	all_lines_valid = 0;
	for (i = 0; i < set.total_lines; ++i){
		if(set.lines[i].valid == 1 && set.lines[i].tag == tag){
			return i;
		}else if(set.lines[i].valid == 1){
			all_lines_valid++;
		}
	}
	if (all_lines_valid == set.total_lines){
		return -2;
	}
	return -1;
}

void all_lines_are_not_filled(Stat *stat, Set **sets, long long tag, int byte, int s_mask){
	int i;
	for(i = 0; i < (*sets)[s_mask].total_lines; i++){ //find the line that's not filled yet
		if ((*sets)[s_mask].lines[i].valid == 0){
			break;
		}
	}
	(*sets)[s_mask].lines[i].valid = 1;
	(*sets)[s_mask].lines[i].tag = tag;
	(*sets)[s_mask].lines[i].timestamp = clock();
}

void simulate_instruction(Stat *stat, Set **sets, char instruction, long long addr, int size, int v, int s, int E, int b){
	int byte_mask = make_mask(b);
	int byte = addr & (byte_mask);
	int s_mask = make_mask(s);
	s_mask = s_mask << b;
	s_mask = addr & s_mask;
	s_mask = s_mask >> b;
	// printf(" %x\n",s_mask);
	long long tag = addr >> (s+b);
	int check = check_tag_in_set((*sets)[s_mask],tag);
	if(instruction == 'L' || instruction == 'S'){
		if(check >= 0){
			stat->hit++;
			print_v("hit",v);
			(*sets)[s_mask].lines[check].timestamp = clock();
		}else if(check == -1){ 
			stat->miss++;
			print_v("miss",v);//all lines are not filled
			all_lines_are_not_filled(stat,sets,tag,byte,s_mask);
			
		}else if(check == -2){ //all lines are filled
			stat->miss++;
			stat->evict++;
			print_v("miss",v);
			print_v("eviction",v);
			int index  = get_least_recently_used_line((*sets)[s_mask]);
			(*sets)[s_mask].lines[index].tag = tag;
			(*sets)[s_mask].lines[index].timestamp = clock();
		}
	}else if(instruction == 'M'){
		if (check >= 0){
			stat->hit++;
			stat->hit++;
			print_v("hit",v);
			print_v("hit",v);
			(*sets)[s_mask].lines[check].timestamp = clock();
		}else if(check == -1){
			stat->miss++;
			stat->hit++;
			print_v("miss",v);
			print_v("hit",v);
			all_lines_are_not_filled(stat,sets,tag,byte,s_mask);
		}else if(check == -2){
			stat->miss++;
			stat->evict++;
			stat->hit++;
			print_v("miss",v);
			print_v("eviction",v);
			print_v("hit",v);
			int index  = get_least_recently_used_line((*sets)[s_mask]);

			(*sets)[s_mask].lines[index].tag = tag;
			(*sets)[s_mask].lines[index].timestamp = clock();
		}
	}
	printf("\n");
}




void simulate_memory(Stat *stat,Set *sets,char *fileName, int s, int E, int b, int v){
	FILE* file = fopen(fileName, "r"); 
    char instruction;
    long long addr;
    int size;
    while (fscanf(file, " %c %llx,%d\n", &instruction,&addr,&size) == 3) {  
    	if (instruction != 'I')
    	{
    		if(v == 1){
    			printf("%c %llx,%d", instruction,addr,size);
	    	} 
	    	simulate_instruction(stat,&sets,instruction,addr,size,v,s,E,b);
    	}
    	
    }
    fclose(file);
}




int main(int argc, char **argv){
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

	Set *sets;
	Stat *stat = (Stat *) malloc(sizeof(Stat));
	stat->miss = 0;
	stat->hit = 0;
	stat->evict = 0;
	setup_memory(&sets,s,E,b);
	simulate_memory(stat,sets,t,s,E,b,v);
    printSummary(stat->hit, stat->miss, stat->evict);
    cleanup_memory(&sets,s,E,b);
    free(stat);
    free(t);
    return 0;
}
