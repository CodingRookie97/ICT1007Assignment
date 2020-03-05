#include <stdio.h>
#define MAXPROCESSES 6
void displaySplash();
void findAvgTime(char selection, int n, int bt[], int quantum, int p[]);
void findRRWaitingTime(int n, int bt[], int wt[], int quantum);
void findPriorityRRWaitingTime(int n, int bt[], int wt[], int quantum, int p[], int pi[], int counter, int remaining);
void findMeanTSJFWaitingTime(int n, int bt[], int wt[], int quantum, int p[]);
void findTurnAroundTime(int n, int bt[], int wt[], int tat[], int p[]);
void normalRR(char selection, int quantum);
void sortedRR(char selection, int quantum);
void priorityRR(char selection, int quantum);
void meanTSJFRR(char selection, int quantum);
void findAvgTime(char selection, int n, int bt[], int quantum, int p[]);
void rrComparison();
void main() {
	displaySplash();
	char selection;
	int i, n, quantum;
	do {
		printf("Enter a time quantum for slicing: ");
		scanf("%d", &quantum);
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
		printf("\n");
		switch (selection) {
		case '1':
			normalRR(selection, quantum);
			break;
		case '2':
			sortedRR(selection, quantum);
			break;
		case '3':
			priorityRR(selection, quantum);
			break;
		case '4':
			meanTSJFRR(selection, quantum);
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
void findAvgTime(char selection, int n, int bt[], int quantum, int p[]) {
	int wt[20], tat[20], unsortedBT[20], unsortedPriority[20], total_wt = 0, total_tat = 0, counter = 0, remaining = 0;
	//If users select Round Robin
	if (selection == '1') {
		findRRWaitingTime(n, bt, wt, quantum, p);
		// Function to find turn around time for all processes 
		findTurnAroundTime(n, bt, wt, tat, p);
		// Display processes along with all details
		printf("Processes\tBurst Time\tWaiting Time\tTurn Around Time\n");
		// Calculate total waiting time and total turn around time 
		for (int i = 0; i < n; i++) {
			total_wt = total_wt + wt[i];
			total_tat = total_tat + tat[i];
			printf("%d\t\t%2d\t\t%2d\t\t%2d\n", (i + 1), bt[i], wt[i], tat[i]);
		}
	}
	//If users select Sorted Round Robin
	else if (selection == '2') {
		//TODO Add functionalities for Sorted Round Robin
	}
	//If users select Priority Round Robin
	else if (selection == '3') {
		//Make a copy of the unsorted burst times and priorities that are to be displayed in table later
		for (int i = 0; i < n; i++) {
			unsortedBT[i] = bt[i];
			unsortedPriority[i] = p[i];
		}
		int pi[MAXPROCESSES] = { 1, 2, 3, 4, 5 };
		// Function to find waiting time of all processes 
		findPriorityRRWaitingTime(n, bt, wt, quantum, p, pi, counter, remaining);
		// Function to find turn around time for all processes 
		findTurnAroundTime(n, unsortedBT, wt, tat, p);
		// Display processes along with all details
		printf("Processes\tBurst Time\tWaiting Time\tTurn Around Time\tPriority\n");
		// Calculate total waiting time and total turn around time 
		for (int i = 0; i < n; i++) {
			total_wt = total_wt + wt[i];
			total_tat = total_tat + tat[i];
			printf("%d\t\t%2d\t\t%2d\t\t%2d\t\t\t%2d\n", (i + 1), unsortedBT[i], wt[i], tat[i], unsortedPriority[i]);
		}
	}
	//If users select Mean Threshold Shortest Job First Round Robin
	else if (selection == '4') {
		//Make a copy of the unsorted burst times that is to be displayed in table later
		for (int i = 0; i < n; i++) {
			unsortedBT[i] = bt[i];
		}
		int pi[MAXPROCESSES] = { 1, 2, 3, 4, 5, 6 };
		// Function to find waiting time of all processes 
		findMeanTSJFWaitingTime(n, bt, wt, quantum, p);
		// Function to find turn around time for all processes 
		findTurnAroundTime(n, unsortedBT, wt, tat, p);
		// Display processes along with all details
		printf("Processes\tBurst Time\tWaiting Time\tTurn Around Time\n");
		// Calculate total waiting time and total turn around time 
		for (int i = 0; i < n; i++) {
			total_wt = total_wt + wt[i];
			total_tat = total_tat + tat[i];
			printf("%d\t\t%2d\t\t%2d\t\t%2d\n", (i + 1), unsortedBT[i], wt[i], tat[i]);
		}
	}
	//average of wt and tat
	printf("Average Waiting Time = %.3f\n", (float)total_wt / (float)n);
	printf("Average Turn Around Time = %.3f\n", (float)total_tat / (float)n);
	printf("\n");
}
void findRRWaitingTime(int n, int bt[], int wt[], int quantum) {
	int t = 0;
	int rem_bt[20];
	for (int i = 0; i < n; i++) {
		rem_bt[i] = bt[i];
	}
	printf(" Round Robin (RR) for %d process(es)\n", n);
	printf("------------------------------------\n");
	while (1) {
		int done = 1;
		//loops through all process starting from the first indx of RR process
		for (int i = 0; i < n; i++) {
			//checks for burst greater than 0
			if (rem_bt[i] > 0) {
				done = 0; // There is a pending process 
				if (rem_bt[i] > quantum) {
					// Increase the value of t i.e. shows 
					// how much time a process has been processed 
					t += quantum;
					//reduce burst by quantum
					rem_bt[i] -= quantum;
				}
				//means burst smaller than quantum
				else {
					// Increase the value of t i.e. shows how much time a process has been processed 
					t = t + rem_bt[i];
					// Waiting time is current time minus time  used by this process 
					wt[i] = t - bt[i];
					// As the process gets fully executed ,make its remaining burst time = 0 
					rem_bt[i] = 0;
				}
			}
		}
		// If all processes are done 
		if (done == 1) {
			break;
		}
	}
}
void findPriorityRRWaitingTime(int n, int bt[], int wt[], int quantum, int p[], int pi[], int counter, int remaining) {
	int temp1, temp2, temp3, i, j, t = 0;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			//Swaps the priority here 
			//It checks the priority here
			if (p[i] > p[j]) {
				//Holds the lowest priority burst time
				temp1 = bt[i];
				//Changes the burst[i] to burst[j]
				bt[i] = bt[j];
				//new burst of j is to i
				bt[j] = temp1;
				//it stores priority into temp
				temp2 = p[i];
				//swaps priority
				p[i] = p[j];
				//new priority
				p[j] = temp2;
				//Stores process indexes into temp
				temp3 = pi[i];
				//swaps process index
				pi[i] = pi[j];
				//new process index
				pi[j] = temp3;
			}
		}
	}
	//stores bt into compt, waiting time = 0
	// Make a copy of burst times bt[] to store remaining 
	// burst times. 
	int rem_bt[20];
	for (int i = 0; i < n; i++) {
		rem_bt[i] = bt[i];
	}
	printf(" Round Robin with Priority for %2d process(es)\n", n);
	printf("-----------------------------------------------\n");
	// until done, it loops through
	while (1) {
		int done = 1;
		//loops through all process
		for (int i = 0; i < n; i++) {
			//checks for burst greater than 0
			if (rem_bt[i] > 0) {
				done = 0; // There is a pending process 
				if (rem_bt[i] > quantum) {
					// Increase the value of t i.e. shows 
					// how much time a process has been processed 
					t += quantum;
					//reduce burst by quantum
					rem_bt[i] -= quantum;
				}
				//means burst smaller than quantum
				else {
					// Increase the value of t i.e. shows how much time a process has been processed 
					t = t + rem_bt[i];
					// Waiting time is current time minus time  used by this process 
					wt[pi[i] - 1] = t - bt[i];
					// As the process gets fully executed ,make its remaining burst time = 0 
					rem_bt[i] = 0;
				}
			}
			//Checks for remaining burst, if its not 0, adds a counter(to show that its there and remaining of burst)
			if (rem_bt[i] != 0) {
				counter += 1;
				remaining += rem_bt[i];
			}
			//Checks if burst is 0 and i ==4 ( means loop through every process)
			else if (rem_bt[i] == 0 && i == 4) {
				if (remaining == 0) {
					break;
				}
				//new quantum  and resets counter and remaining to 0
				else {
					quantum = remaining / (counter);
					counter = 0;
					remaining = 0;
				}
			}
		}
		// If all processes are done 
		if (done == 1) {
			break;
		}
	}
}
void findMeanTSJFWaitingTime(int n, int bt[], int wt[], int quantum, int p[]) {
	float threshold = 0, awt = 0, att = 0;
	int totalBurst = 0, noOfSJFProcesses = 0, noOfRRProcesses = 0, tempIndex = 0, tempBt = 0, max = 0, t = 0;
	int pi[MAXPROCESSES] = { 1, 2, 3, 4, 5, 6 }, rem_bt[20];
	//Find sum of the burst times of all processes
	for (int i = 0; i < n; i++) {
		totalBurst += bt[i];
	}
	printf("Total Burst Time is: %d\n", totalBurst);
	threshold = (float)totalBurst / n;
	//Find the threshold time for the processes in the form of (Total Burst Time) / Number of Processes
	printf("Threshold Time is: %.3f\n", threshold);
	if (n > 0) {
		for (int i = 0; i < n; i++) {
			//If there are burst times which are lesser or equal than the threshold, increment the number of SJF processes
			if (bt[i] <= threshold) {
				noOfSJFProcesses++;
			}
			//If there are burst times which are more than the threshold, increment the number of RR processes
			else {
				noOfRRProcesses++;
			}
		}
		//Sort based on SJF if there are processes that will be involved in SJF
		if (noOfSJFProcesses > 0) {
			for (int j = 0; j < n; j++) {
				for (int k = j + 1; k < n; k++) {
					//Comparison between 2 arrival times from array
					if (bt[j] > bt[k]) {
						//Sort out which process index will come first based on earliest arrival time
						tempIndex = pi[j];
						pi[j] = pi[k];
						pi[k] = tempIndex;
						//Sort out which amount of burst time will execute first based on earliest arrival time
						tempBt = bt[j];
						bt[j] = bt[k];
						bt[k] = tempBt;
					}
				}
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
						tempBt = bt[l];
						bt[l] = bt[m];
						bt[m] = tempBt;
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			printf("\nSorted Processes to execute based on both SJF and RR: %d\n", pi[i]);
			printf("Sorted Burst Times to execute based on both SJF and RR: %d\n", bt[i]);
		}
		for (int i = 0; i < n; i++) {
			rem_bt[i] = bt[i];
		}
		//1st step: If there are processes (below or equal to threshold) that requires FCFS after sorted based on shortest job, perform SJF
		if (noOfSJFProcesses > 0) {
			printf("\n Shortest Job First (SJF) for %d process(es)\n", noOfSJFProcesses);
			printf("--------------------------------------------\n");
			//Assume the current time is now after the first process has been executed
			t += bt[0];
			//Store the waiting time of the first process by subtracting current time - burst time of 1st process
			wt[pi[0] - 1] = t - bt[0];
			//Store the waiting times for the remaining SJF processes
			for (int i = 1; i < noOfSJFProcesses; i++) {
				t += bt[i];
				//Store the waiting time of the first process by subtracting current time - burst time of 1st process
				wt[pi[i] - 1] = t - bt[i];
			}
		}
		//2nd Step: If there are processes that requires RR (above threshold) after sorted based on shortest job, perform RR
		if (noOfRRProcesses > 0) {
			printf("\n Round Robin (RR) for %d process(es)\n", noOfRRProcesses);
			printf("------------------------------------\n");
			// until done, it loops through
			while (1) {
				int done = 1;
				//loops through all process starting from the first indx of RR process
				for (int i = noOfSJFProcesses; i < n; i++) {
					//checks for burst greater than 0
					if (rem_bt[i] > 0) {
						done = 0; // There is a pending process 
						if (rem_bt[i] > quantum) {
							// Increase the value of t i.e. shows 
							// how much time a process has been processed 
							t += quantum;
							//reduce burst by quantum
							rem_bt[i] -= quantum;
						}
						//means burst smaller than quantum
						else {
							// Increase the value of t i.e. shows how much time a process has been processed 
							t = t + rem_bt[i];
							// Waiting time is current time minus time  used by this process 
							wt[pi[i] - 1] = t - bt[i];
							// As the process gets fully executed ,make its remaining burst time = 0 
							rem_bt[i] = 0;
						}
					}
				}
				// If all processes are done 
				if (done == 1) {
					break;
				}
			}
		}
	}
	else {
		printf("No processes are in the ready queue!\n");
	}
}
// Function to calculate turn around time 
void findTurnAroundTime(int n, int bt[], int wt[], int tat[], int p[]) {
	// calculating turnaround time by adding 
	// bt[i] + wt[i] 
	for (int i = 0; i < n; i++) {
		tat[i] = bt[i] + wt[i];
	}
}
void normalRR(char selection, int quantum) {
	int burst_time[] = { 24, 3, 3 };
	int n = sizeof burst_time / sizeof burst_time[0];
	//Priority
	int pi[] = { 1, 2, 3 };
	findAvgTime(selection, n, burst_time, quantum, pi);
}
void sortedRR(char selection, int quantum) {
	//TODO: Sorted Round Robin Algorithm
	printf(" Sorted Round Robin\n");
	printf("--------------------\n");
}
void priorityRR(char selection, int quantum) {
	//TODO: Modified Round Robin based on priorities
	int burst_time[] = { 23, 19, 10, 11, 5 };
	int n = sizeof burst_time / sizeof burst_time[0];
	//Priority
	int p[] = { 4, 2, 1, 3, 5 };
	findAvgTime(selection, n, burst_time, quantum, p);
}
void meanTSJFRR(char selection, int quantum) {
	int burst_time[] = { 5, 6, 7, 9, 2, 3 };
	//Process Indexes
	int pi[] = { 1, 2, 3, 4, 5, 6 };
	int n = sizeof burst_time / sizeof burst_time[0];
	printf(" Mean Threshold Shortest Job First Round Robin\n");
	printf("-----------------------------------------------\n");
	findAvgTime(selection, n, burst_time, quantum, pi);
}
void rrComparison() {
	//Function to compare overall Round-Robin performances between the different RR algorithms to see which algorithms have best performance
	printf(" Comparing Round Robin Algorithm Performances\n");
	printf("----------------------------------------------\n");
}