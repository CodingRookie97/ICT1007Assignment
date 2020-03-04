#include <stdio.h>
#define MAXPROCESSES 6
void displaySplash();
void normalRR(int iBurstTime[], float ct[], int t);
void sortedRR(int iBurstTime[], float ct[], int t);
void priorityRR(int iBurstTime[], float ct[], int t);
void meanTSJFRR(int iBurstTime[], float ct[], int t);
void rrComparison();
void main() {
	displaySplash();
	char selection;
	int i, n, t;
	do {
		int iBurstTime[] = { 5, 6, 7, 9, 2, 3 }, ct[MAXPROCESSES];
		float wt = 0, att = 0;
		for (i = 0; i < MAXPROCESSES; i++) {
			//ct is used to store actual burst time for each processes
			ct[i] = iBurstTime[i];
		}
		printf("\nEnter a choice of selections to execute these Round-Robin algorithms:\n");
		printf("1: Normal Round Robin Algorithm\n");
		printf("2: Sorted Round Robin Algorithm\n");
		printf("3: Modified Round Robin Scheduling Algorithm Based on Priorities\n");
		printf("4: Mean Threshold Shortest Job Round Robin CPU Scheduling Algorithm\n");
		printf("5: Round Robin Algorithms Comparison\n");
		printf("Q: Terminate application\n");
		printf("Your choice: ");
		scanf(" %c", &selection);
		printf("Enter a time slicing: ");
		scanf("%d", &t);
		printf("\n");
		switch (selection) {
		case '1':
			normalRR(iBurstTime, ct, t);
			break;
		case '2':
			sortedRR(iBurstTime, ct, t);
			break;
		case '3':
			priorityRR(iBurstTime, ct, t);
			break;
		case '4':
			meanTSJFRR(iBurstTime, ct, t);
			break;
		case '5':
			rrComparison();
			break;
		case 'Q':
		case 'q':
			printf("You have terminated the application!");
			break;
		default:
			printf("Invalid selection, please try again!\n");
		}
	} while (selection != 'Q' && selection != 'q');
}
void displaySplash() {
	char splash[14][63] = {
	{"            _____ _____ _______   __  ___   ___ ______ "},
	{"           |_   _/ ____|__   __| /_ |/ _ \\ / _ \\____  |"},
	{"             | || |       | |     | | | | | | | |  / /"},
	{"             | || |       | |     | | | | | | | | / /"},
	{"            _| || |____   | |     | | |_| | |_| |/ /"},
	{"           |_____\\_____|  |_|     |_|\\___/ \\___//_/"},
	{"                  _                                  _     __ "},
	{"    /\\           (_)                                | |   /_ |"},
	{"   /  \\   ___ ___ _  __ _ _ __  _ __ ___   ___ _ __ | |_   | |"},
	{"  / /\\ \\ / __/ __| |/ _` | '_ \\| '_ ` _ \\ / _ \\ '_ \\| __|  | |"},
	{" / ____ \\\\__ \\__ \\ | (_| | | | | | | | | |  __/ | | | |_   | |"},
	{"/_/    \\_\\___/___/_|\\__, |_| |_|_| |_| |_|\\___|_| |_|\\__|  |_|"},
	{"                     __/ |                                    "},
	{"                    |___/                                     "},
	};
	printf("\n\n\n");
	for (int i = 0; i < 14; ++i) {
		printf("                               %s\n", splash[i]);
	}
	printf("\n                                                  CPU Scheduling Algorithms");
	printf("\n                                                     Group 26 members:");
	printf("\n                                           Ni Jun Jie Shawn              1902112");
	printf("\n                                           Zulfadli bin Johari           1902147");
	printf("\n                                           Jerone Poh Yong Cheng         1902606");
	printf("\n                                           Yeo Khee Theong Joel          1902645");
	printf("\n");
	printf("\n\n                                               Press any key to continue");
	getch();
	system("cls");
}
void normalRR(int iBurstTime[], int ct[], int t) {
	int i, j, k, l;
	int wa[10], tat[10], max, twt = 0, ttt = 0, temp = 0;
	float awt = 0, att = 0;
	printf(" Normal Round robin\n");
	printf("--------------------\n");
	max = iBurstTime[0];
	//Need to compare and check what process has the longest burst time
	for (i = 1; i < MAXPROCESSES; i++) {
		if (max <= iBurstTime[i]) {
			max = iBurstTime[i];
		}
	}
	//Use maximum burst (max) time to guarentee all process to be able to fully time-slice and execute
	while (max != 0) {
		for (i = 0; i < MAXPROCESSES; i++) {
			if (iBurstTime[i] != 0) {
				if (iBurstTime[i] <= t) {
					//calculation of turnaround time takes place here: turnaround time = current time (temp) + burst time
					tat[i] = temp + iBurstTime[i];
					temp = temp + iBurstTime[i];
					iBurstTime[i] = 0;
				}
				else {
					//calculate the remaining burst time of a process after finishing an execution on a time quantum basis
					iBurstTime[i] = iBurstTime[i] - t;
					//track out the current time after each process execution
					temp = temp + t;
				}
			}
		}
		max--;
	}
	printf("Processes   Burst time   Waiting time   Turnaround time\n");
	//waiting time (wa) is equivalent to turnaround time - burst time
	for (k = 0; k < MAXPROCESSES; k++) {
		wa[k] = tat[k] - ct[k];
	}
	//loop the arrays to find out total waiting time and total turnaround time
	for (l = 0; l < MAXPROCESSES; l++) {
		twt += wa[l];
		ttt += tat[l];
		printf("   %d ", (l + 1));
		printf("          %3d ", ct[l]);
		printf("          %3d ", wa[l]);
		printf("           %3d\n", tat[l]);
	}
	//Finding out the average waiting time
	awt = (float) twt / MAXPROCESSES;
	printf("\nAverage waiting time for %d processes is %.3f.\n", MAXPROCESSES, awt);
	//Finding out the average turnaround time
	att = (float) ttt / MAXPROCESSES;
	printf("Average turnaround time for %d processes is %.3f.\n", MAXPROCESSES, att);
}
void sortedRR(int iBurstTime[], int ct[], int t) {
	//TODO: Sorted Round Robin Algorithm
	printf(" Sorted Round Robin\n");
	printf("--------------------\n");
}
void priorityRR(int iBurstTime[], int ct[], int t) {
	//TODO: Modified Round Robin based on priorities
	printf(" Priority Round Robin\n");
	printf("----------------------\n");
}
void meanTSJFRR(int iBurstTime[], int ct[], int t) {
	//TODO: Mean Threshold Shortest Job First Round Robin Algorithm
	float threshold = 0, awt = 0, att = 0;
	int n = MAXPROCESSES, totalBurst = 0, noOfSJFProcesses = 0, noOfRRProcesses = 0, tempIndex = 0, tempBt = 0, max = 0, currentTime = 0, wa[10], tat[10], twt = 0, ttt = 0;
	int pi[MAXPROCESSES] = { 1, 2, 3, 4, 5, 6 };
	printf(" Mean Threshold Shortest Job First Round Robin\n");
	printf("-----------------------------------------------\n");
	for (int i = 0; i < n; i++) {
		totalBurst += iBurstTime[i];
	}
	printf("Total Burst Time is: %d\n", totalBurst);
	threshold = (float) totalBurst / n;
	//Find the threshold time for the processes in the form of (Total Burst Time) / Number of Processes
	printf("Threshold Time is: %.3f\n", threshold);
	if (n > 0) {
		for (int i = 0; i < n; i++) {
			//If there are burst times which are lesser or equal than the threshold, increment the number of SJF processes
			if (iBurstTime[i] <= threshold) {
				noOfSJFProcesses++;
			}
			//If there are burst times which are more than the threshold, increment the number of RR processes
			else {
				noOfRRProcesses++;
			}
		}
		printf("Total processes involved in SJF: %d\n", noOfSJFProcesses);
		printf("Total processes involved in RR: %d\n", noOfRRProcesses);
		for (int j = 0; j < n; j++) {
			printf("\nUnsorted Processes to execute: %d\n", j + 1);
			printf("Unsorted Burst Times to execute: %d\n", ct[j]);
		}
		//Sort based on SJF if there are processes that will be involved in SJF
		if (noOfSJFProcesses > 0) {
			for (int j = 0; j < n; j++) {
				for (int k = j + 1; k < n; k++) {
					//Comparison between 2 arrival times from array
					if (iBurstTime[j] > iBurstTime[k]) {
						//Sort out which process index will come first based on earliest arrival time
						tempIndex = pi[j];
						pi[j] = pi[k];
						pi[k] = tempIndex;
						//Sort out which amount of burst time will execute first based on earliest arrival time
						tempBt = iBurstTime[j];
						iBurstTime[j] = iBurstTime[k];
						iBurstTime[k] = tempBt;
					}
				}
			}
			for (int i = 0; i < n; i++) {
				printf("\nSorted Processes to execute for SJF: %d\n", pi[i]);
				printf("Sorted Burst Times to execute for SJF: %d\n", iBurstTime[i]);
			}
		}
		//Sort based on Process ID if there are processes that will be involved in RR
		if (noOfRRProcesses > 0) {
			for (int l = noOfSJFProcesses; l < n; l++) {
				for (int m = l + 1; m < n; m++) {
					//Comparison between 2 arrival times from array
					if (pi[l] > pi[m]) {
						//Sort out which process index will come first based on earliest arrival time
						tempIndex = pi[l];
						pi[l] = pi[m];
						pi[m] = tempIndex;
						//Sort out which amount of burst time will execute first based on earliest arrival time
						tempBt = iBurstTime[l];
						iBurstTime[l] = iBurstTime[m];
						iBurstTime[m] = tempBt;
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			printf("\nSorted Processes to execute based on both SJF and RR: %d\n", pi[i]);
			printf("Sorted Burst Times to execute based on both SJF and RR: %d\n", iBurstTime[i]);
		}
		//1st step: If there are processes (below or equal to threshold) that requires FCFS after sorted based on shortest job, perform SJF
		if (noOfSJFProcesses > 0) {
			printf("\n Shortest Job First (SJF) for %d process(es)\n", noOfSJFProcesses);
			printf("--------------------------------------------\n");
			//Assume the current time is now after the first process has been executed
			currentTime += iBurstTime[0];
			//Store the turnaround of the first process as the current time into the array
			tat[pi[0] - 1] = currentTime;
			//Store the turnaround for the remaining SJF processes
			for (int i = 1; i < noOfSJFProcesses; i++) {
				//TODO: FCFS Algorithm Here
				currentTime += iBurstTime[i];
				tat[pi[i] - 1] = currentTime;
			}
			//waiting time (wa) is equivalent to turnaround time - burst time
			for (int l = 0; l < noOfSJFProcesses; l++) {
				wa[pi[l] - 1] = tat[pi[l] - 1] - iBurstTime[l];
			}
		}
		//2nd Step: If there are processes that requires RR (above threshold) after sorted based on shortest job, perform RR
		if (noOfRRProcesses > 0) {
			printf("\n Round Robin (RR) for %d process(es)\n", noOfRRProcesses);
			printf("------------------------------------\n");
			max = iBurstTime[noOfSJFProcesses];
			for (int i = noOfSJFProcesses + 1; i < n; i++) {
				if (max <= iBurstTime[i]) {
					max = iBurstTime[i];
				}
			}
			//Use maximum burst (max) time to guarentee all process to be able to fully time-slice and execute
			while (max != 0) {
				//Start at the Process Index after the SJF Processes
				for (int j = noOfSJFProcesses; j < n; j++) {
					if (iBurstTime[j] != 0) {
						if (iBurstTime[j] <= t) {
							//calculation of turnaround time takes place here: turnaround time = current time (temp) + burst time
							tat[pi[j] - 1] = currentTime + iBurstTime[j];
							currentTime = currentTime + iBurstTime[j];
							iBurstTime[j] = 0;
						}
						else {
							//calculate the remaining burst time of a process after finishing an execution on a time quantum basis
							iBurstTime[j] = iBurstTime[j] - t;
							//track out the current time after each process execution
							currentTime = currentTime + t;
						}
					}
				}
				max--;
			}
			//waiting time (wa) is equivalent to turnaround time - burst time
			for (int k = noOfSJFProcesses; k < n; k++) {
				wa[pi[k] - 1] = tat[pi[k] - 1] - ct[pi[k] - 1];
			}
		}
		printf("Number of Processes: %d\n", n);
		printf("Time Slice = %d\n", t);
		printf("Process   Burst time   Waiting time   Turnaround time\n");
		//loop the arrays to find out total waiting time and total turnaround time
		for (int k = 0; k < n; k++) {
			twt += wa[k];
			ttt += tat[k];
			printf("   %d ", k + 1);
			printf("        %3d ", ct[k]);
			printf("         %3d ", wa[k]);
			printf("            %3d\n", tat[k]);
		}
		//Finding out the average waiting time
		awt = (float)twt / n;
		printf("\nAverage waiting time for %d processes is %.3f.\n", n, awt);
		//Finding out the average turnaround time
		att = (float)ttt / n;
		printf("Average turnaround time for %d processes is %.3f.\n", n, att);
	}
	else {
		printf("No processes are in the ready queue!\n");
	}
}
void rrComparison() {
	//Function to compare overall Round-Robin performances between the different RR algorithms to see which algorithms have best performance
	printf(" Comparing Round Robin Algorithm Performances\n");
	printf("----------------------------------------------\n");
}