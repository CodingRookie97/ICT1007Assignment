#include <stdio.h>
#define MAXPROCESSES 3
void displaySplash();
void normalRR(float iBurstTime[], float ct[], int t);
void sortedRR(float iBurstTime[], float ct[], int t);
void priorityRR(float iBurstTime[], float ct[], int t);
void sjfRR(float iBurstTime[], float ct[], int t);
void main() {
	displaySplash();
	char selection;
	int i, n, t;
	do {
		float iBurstTime[MAXPROCESSES] = { 24, 3, 3 }, wa[10], tat[10], ct[10], max, twt = 0, awt = 0, ttt = 0, att = 0, temp = 0;
		//Entering size of time quantum (t)
		printf("\nEnter the size of time slice : ");
		scanf("%d", &t);
		for (i = 0; i < MAXPROCESSES; i++) {
			//ct is used to store actual burst time for each processes
			ct[i] = iBurstTime[i];
		}
		printf("\nEnter a choice of selections to execute these Round-Robin algorithms:\n");
		printf("1: Normal Round Robin Algorithm\n");
		printf("2: Sorted Round Robin Algorithm\n");
		printf("3: Modified Round Robin Scheduling Algorithm Based on Priorities\n");
		printf("4: Mean Threshold Shortest Job Round Robin CPU Scheduling Algorithm\n");
		printf("Q: Terminate application\n");
		printf("Your choice: ");
		scanf(" %c", &selection);
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
			sjfRR(iBurstTime, ct, t);
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
void normalRR(float iBurstTime[], float ct[], int t) {
	int i, j, k, l;
	float wa[10], tat[10], max, twt = 0, awt = 0, ttt = 0, att = 0, temp = 0;
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
	//waiting time (wa) is equivalent to turnaround time - burst time
	for (k = 0; k < MAXPROCESSES; k++) {
		wa[k] = tat[k] - ct[k];
	}
	//loop the arrays to find out total waiting time and total turnaround time
	for (l = 0; l < MAXPROCESSES; l++) {
		twt += wa[l];
		ttt += tat[l];
		printf("Waiting time for process #%d: %.3f\n", (l + 1), wa[l]);
		printf("Turnaround time for process #%d: %.3f\n", (l + 1), tat[l]);
	}
	//Finding out the average waiting time
	awt = twt / MAXPROCESSES;
	printf("\nAverage waiting time for %d processes is %.3f.\n", MAXPROCESSES, awt);
	//Finding out the average turnaround time
	att = ttt / MAXPROCESSES;
	printf("Average turnaround time for %d processes is %.3f.\n", MAXPROCESSES, att);
}
void sortedRR(float iBurstTime[], float ct[], int t) {
	//TODO: Sorted Round Robin Algorithm
	printf(" Sorted Round Robin\n");
	printf("--------------------\n");
}
void priorityRR(float iBurstTime[], float ct[], int t) {
	//TODO: Modified Round Robin based on priorities
	printf(" Priority Round Robin\n");
	printf("----------------------\n");
}
void sjfRR(float iBurstTime[], float ct[], int t) {
	//TODO: Mean Threshold Shortest Job First Round Robin Algorithm
	printf(" Shortest Job First Round Robin\n");
	printf("--------------------------------\n");
}