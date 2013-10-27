// Matei Razvan Madalin
// 313CA

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Stack.h"
#include"Queue.h"
#include"Structures.h"

int main(int argc, char* argv[]) {
	FILE *f;
	int i;
	int N;
	int WINDOW_ID, N_PEOPLE, toProcess;
	int *WEIGHT_MIN, *WEIGHT_MAX, *Q, *K, *working;
	char *command = new char[40];
	char *p;
	struct Person pers;
	struct Person *persToProcess;
	Queue<struct Person>* queues;
	Stack<int>* stacks;
	
	f = fopen(argv[1], "r");
	
	// Reading the number of wickets
	fscanf(f, "%d", &N);
	// Reading the newline caracter
	fgets(command, 20, f);
	
	queues = new Queue<struct Person>[N];
	stacks = new Stack<int>[N];
	WEIGHT_MIN = new int[N];
	WEIGHT_MAX = new int[N];
	Q = new int[N];
	K = new int[N];
	working = new int[N];
	for(i=0; i<N; i++) {
		working[i] = 0;
	}
	
	// Reading and executing the commands
	while(fgets(command, 40, f) != NULL) {
		if(strcmp(command, "\n")==0) {
			continue;
		}

		p = strtok(command, " \n");
		
		if(strcmp(p, "OPEN_WINDOW") == 0) {
			// Get WINDOW_ID
			p = strtok(NULL, " \n");
			WINDOW_ID = atoi(p);
			// Mark the wicket as working
			working[WINDOW_ID] = 1;
			// Get WEIGHT_MIN
			p = strtok(NULL, " \n");
			WEIGHT_MIN[WINDOW_ID] = atoi(p);
			// Get WEIGHT_MAX
			p = strtok(NULL, " \n");
			WEIGHT_MAX[WINDOW_ID] = atoi(p);
			// Get the maximum number of packages
			p = strtok(NULL, " \n");
			Q[WINDOW_ID] = atoi(p);
			// Alocate just enough memory per stack
			stacks[WINDOW_ID].initialize(Q[WINDOW_ID]);
			// Get the maximum weight per stack
			p = strtok(NULL, " \n");
			K[WINDOW_ID] = atoi(p);
		}
		
		if(strcmp(p, "ADD_PERSON") == 0) {
			// Get PERSONAL_ID
			p = strtok(NULL, " \n");
			pers.PERSONAL_ID = atoi(p);
			// Get PACKAGE_WEIGHT
			p = strtok(NULL, " \n");
			pers.PACKAGE_WEIGHT = atoi(p);
			// Get WINDOW_ID for person to be added
			p = strtok(NULL, " \n");
			WINDOW_ID = atoi(p);
			// Add person to queue
			queues[WINDOW_ID].enqueue(pers);
		}
		
		if(strcmp(p, "PROCESS") == 0) {
			// Get WINDOW_ID
			p = strtok(NULL, " \n");
			WINDOW_ID = atoi(p);
			// Get number of persons to process
			p = strtok(NULL, " \n");
			N_PEOPLE = atoi(p);
			
			// Get the first N_PEOPLE persons for processing
			persToProcess = new struct Person[N_PEOPLE];
			queues[WINDOW_ID].getFirstInRow(N_PEOPLE, persToProcess);
			
			for(i=0; i<N_PEOPLE; i++) {
				if( (persToProcess[i].PACKAGE_WEIGHT >= WEIGHT_MIN[WINDOW_ID]) && 
					 (persToProcess[i].PACKAGE_WEIGHT <= WEIGHT_MAX[WINDOW_ID]) ) {
					if(stacks[WINDOW_ID].topLevel == Q[WINDOW_ID]-1) {
						stacks[WINDOW_ID].Clear();
						stacks[WINDOW_ID].push(persToProcess[i].PACKAGE_WEIGHT);
						continue;
					}
					if(stacks[WINDOW_ID].topLevel < Q[WINDOW_ID]-1) {
						if(stacks[WINDOW_ID].Sum() + persToProcess[i].PACKAGE_WEIGHT > K[WINDOW_ID]) {
							stacks[WINDOW_ID].Clear();
							stacks[WINDOW_ID].push(persToProcess[i].PACKAGE_WEIGHT);
							continue;
						}
						if(stacks[WINDOW_ID].Sum() + persToProcess[i].PACKAGE_WEIGHT <= K[WINDOW_ID]) {
							stacks[WINDOW_ID].push(persToProcess[i].PACKAGE_WEIGHT);
						continue;
						}
					}
				}
				else { //Not in weight limits
					// Move person to the next wicket
					queues[getNextWorking(working, N, WINDOW_ID)].enqueue(persToProcess[i]);
				}	
			}
		}
		
		if(strcmp(p, "PROCESS_ALL") == 0) {
			// Get WINDOW_ID
			p = strtok(NULL, " \n");
			WINDOW_ID = atoi(p);
			
			// Get size of the queue
			toProcess = queues[WINDOW_ID].getSize();
			
			// Get all the people from the queue
			persToProcess = new struct Person[toProcess];
			queues[WINDOW_ID].getFirstInRow(toProcess, persToProcess);
			
			for(i=0; i<toProcess; i++) {
				if( (persToProcess[i].PACKAGE_WEIGHT >= WEIGHT_MIN[WINDOW_ID]) && 
					 (persToProcess[i].PACKAGE_WEIGHT <= WEIGHT_MAX[WINDOW_ID]) ) {
					if(stacks[WINDOW_ID].topLevel == Q[WINDOW_ID]-1) {
						stacks[WINDOW_ID].Clear();
						stacks[WINDOW_ID].push(persToProcess[i].PACKAGE_WEIGHT);
						continue;
					}
					if(stacks[WINDOW_ID].topLevel < Q[WINDOW_ID]-1) {
						if(stacks[WINDOW_ID].Sum() + persToProcess[i].PACKAGE_WEIGHT > K[WINDOW_ID]) {
							stacks[WINDOW_ID].Clear();
							stacks[WINDOW_ID].push(persToProcess[i].PACKAGE_WEIGHT);
							continue;
						}
						if(stacks[WINDOW_ID].Sum() + persToProcess[i].PACKAGE_WEIGHT <= K[WINDOW_ID]) {
							stacks[WINDOW_ID].push(persToProcess[i].PACKAGE_WEIGHT);
							continue;
						}
					}
				}
				else { //Not in weight limits
					// Move person to the next wicket
					queues[getNextWorking(working, N, WINDOW_ID)].enqueue(persToProcess[i]);
				}	
			}
		}
		
		if(strcmp(p, "PRINT_STACKS") == 0) {
			printf("STACKS:\n");
			
			for(i=0; i<N; i++) {
				if(working[i] == 1) {
					printf("%d: ", i);
					stacks[i].dump();
				}
			}
		}
		
		if(strcmp(p, "FLUSH_STACKS") == 0) {
			printf("FLUSHING:\n");
			
			for(i=0; i<N; i++) {
				if(working[i] == 1) {
					printf("%d: ", i);
					stacks[i].dump();
					stacks[i].Clear();
				}
				
			}
		}
		
		if(strcmp(p, "PRINT_QUEUES") == 0) {
			printf("QUEUES:\n");
			
			for(i=0; i<N; i++) {
				if(working[i] == 1) {
					printf("%d: ", i);
					queues[i].dump();
				}
			}
		}			
	}
	
	// Cleaning
	fclose(f);
	delete[] queues;
	delete[] stacks;
	delete[] WEIGHT_MIN;
	delete[] WEIGHT_MAX;
	delete[] Q;
	delete[] K;
	delete[] working;
	delete[] command;
	
	return 0;
}

