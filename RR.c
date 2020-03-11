#include <stdio.h>
#define MAXPROCESSES 20
//These are the function declarations
void displaySplash();
void findAvgTime(char selection, int n, int bt[], int quantum, int p[]);
void findRRWaitingTime(int n, int bt[], int wt[], int quantum);
void findSortedWaitingTime(int n, int bt[], int unsortedBT[], int wt[], int quantum, int pi[]);
void findPriorityRRWaitingTime(int n, int bt[], int unsortedBT[], int wt[], int quantum, int p[], int pi[], int counter);
void findMeanTSJFWaitingTime(int n, int bt[], int wt[], int quantum, int p[]);
void findTurnAroundTime(int n, int bt[], int wt[], int tat[], int p[]);
void normalRR(char selection, int quantum);
void sortedRR(char selection);
void priorityRR(char selection, int quantum);
void meanTSJFRR(char selection, int quantum);
void findAvgTime(char selection, int n, int bt[], int quantum, int p[]);
//The main function to run the application
void main() {
	displaySplash();
	char selection;
	int i, n, quantum;
	float wt = 0, att = 0;
	//Information for users to know that the burst times will be hardcoded to the fixed values below
	printf("Take note that the burst time for all processes will be fixed to: 20, 17, 28, 24, 19, 30 for a fair comparison.\n");
	do {
		//Prompts user to enter a time quantum
		do {
			printf("Enter a time quantum for slicing for Choices 1, 3 and 4 only: ");
			scanf("%d", &quantum);
			//If users enter an invalid time quantum (less than or equal to 0), prompt error message to allow users to select a new time quantum
			if (quantum <= 0) {
				printf("Sorry, you have entered an invalid time quantum, please try again!\n");
			}
		} while (quantum <= 0);
		//After entering a valid time quantum, users will be prompted a list of selections for the different Round-Robin Algorithms (Original Round Robin + 3 Proposed Round Robin Algorithms).
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
			//If users select 1, they will execute the Normal Round Robin Algorithm
			normalRR(selection, quantum);
			break;
		case '2':
			//If users select 2, they will execute the Sorted Round Robin Algorithm
			sortedRR(selection);
			break;
		case '3':
			//If users select 3 , they will execute the Modified Round Robin Scheduling Algorithm Based on Priorities Algorithm
			priorityRR(selection, quantum);
			break;
		case '4':
			//If users select 3 , they will execute the Mean Threshold Shortest Job Round Robin CPU Scheduling Algorithm
			meanTSJFRR(selection, quantum);
			break;
		case 'Q':
		case 'q':
			//Quits the application
			printf("You have terminated the application!");
			break;
		default:
			//If users enter a choice other than 1-4 and Q, users prompted to enter again
			printf("Invalid selection, please try again!\n");
			break;
		}
	} while (selection != 'Q' && selection != 'q');
}
void displaySplash() {
	//This is to display the splash/introduction screen once users run the application
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
	//Display our team members information
	printf("\n                                                  CPU Scheduling Algorithms");
	printf("\n                                                     Group 26 members:");
	printf("\n                                           Ni Jun Jie Shawn              1902112");
	printf("\n                                           Zulfadli bin Johari           1902147");
	printf("\n                                           Jerone Poh Yong Cheng         1902606");
	printf("\n                                           Yeo Khee Theong Joel          1902645");
	printf("\n");
	printf("\n\n                                               Press any key to continue");
	getch();
	//Once user presses any key, users will be prompted to the main screen
	system("cls");
}
void findAvgTime(char selection, int n, int bt[], int quantum, int p[]) {
	//This is the function to find the average waiting and turnaround times for all 4 round robin algorithms
	int wt[20], tat[20], unsortedBT[20], unsortedPriority[20], total_wt = 0, total_tat = 0, counter = 0;
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
		for (int i = 0; i < n; i++) {
			unsortedBT[i] = bt[i];
		}
		//TODO Add functionalities for Sorted Round Robin
		findSortedWaitingTime(n, bt, unsortedBT, wt, quantum, p);
		// Function to find turn around time for all processes 
		findTurnAroundTime(n, unsortedBT, wt, tat, p);
		printf("Processes\tBurst Time\tWaiting Time\tTurn Around Time\n");
		// Calculate total waiting time and total turn around time 
		for (int i = 0; i < n; i++) {
			total_wt = total_wt + wt[i];
			total_tat = total_tat + tat[i];
			printf("%d\t\t%2d\t\t%2d\t\t%2d\n", (i + 1), unsortedBT[i], wt[i], tat[i]);
		}
	}
	//If users select Priority Round Robin
	else if (selection == '3') {
		//Make a copy of the unsorted burst times and priorities that are to be displayed in table later
		for (int i = 0; i < n; i++) {
			unsortedBT[i] = bt[i];
			unsortedPriority[i] = p[i];
		}
		int pi[MAXPROCESSES] = { 1, 2, 3, 4, 5, 6 };
		// Function to find waiting time of all processes 
		counter = n;
		findPriorityRRWaitingTime(n, bt, unsortedBT, wt, quantum, p, pi, counter);
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
		//This is the unsorted process index
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
//This is to find the waiting time for the Normal Round Robin
void findRRWaitingTime(int n, int bt[], int wt[], int quantum) {
	int t = 0;
	int rem_bt[20];
	for (int i = 0; i < n; i++) {
		rem_bt[i] = bt[i];
	}
	printf(" Round Robin (RR) for %d process(es)\n", n);
	printf("------------------------------------\n");
	printf("Time Quantum: %d\n", quantum);
	while (1) {
		int done = 1;
		//loops through all process starting from the first index of RR process
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
					// Waiting time is current time minus time used by this process 
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
//This is to find the waiting time for the Sorted Round Robin
void findSortedWaitingTime(int n, int bt[], int unsortedBT[], int wt[], int quantum, int pi[]) {
	int count, j, t = 0, tempIndex, tempBt, remain, flag = 0;
	remain = n;
	printf(" Sorted Round Robin for %d process(es)\n", n);
	printf("--------------------------------------\n");
	printf("Time Quantum: %d\n", quantum);
	for (j = 0; j < n; j++) {
		for (int k = j + 1; k < n; k++) {
			//Comparison between 2 burst times from array
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
	//As long as there are still processes remaining to execute, run the round robin algorithm below
	for (t = 0, count = 0; remain != 0;)
	{
		//If the burst time is less than or equal to quantum
		if (bt[count] <= quantum && bt[count] > 0)
		{
			//Increase the value of t i.e. shows how much time a process has been processed 
			t += bt[count];
			bt[count] = 0;
			flag = 1;
		}
		//If the burst time is more than the quantum
		else if (bt[count] > 0)
		{
			// Increase the value of t i.e. shows how much time a process has been processed 
			bt[count] -= quantum;
			t += quantum;
		}
		//If a process has completed its execution
		if (bt[count] == 0 && flag == 1)
		{
			remain--;
			// Waiting time is current time minus time used by this process 
			wt[pi[count] - 1] = t - unsortedBT[pi[count] - 1];
			flag = 0;
		}
		//Resets the counter if the last process has been executed
		if (count == n - 1) {
			count = 0;
		}
		//Increments the counter for the next process to execute
		else if (t >= 0) {
			count++;
		}
		else {
			count = 0;
		}
	}
}
//This is to find the waiting time for the Priority Round Robin
void findPriorityRRWaitingTime(int n, int bt[], int unsortedBT[], int wt[], int quantum, int p[], int pi[], int counter) {
	int prioritySorted = 0, temp1, temp2, temp3, i, j, k, index = 0, noOfExecutions = 0, cpyIndex = 0, t = 0;
	int rem_bt[MAXPROCESSES];
	int new_rem_bt[MAXPROCESSES];
	int new_pi[MAXPROCESSES];
	printf(" Round Robin with Priority for %2d process(es)\n", n);
	printf("-----------------------------------------------\n");
	printf("Original Time Quantum: %d\n", quantum);
	while(1) {
		if (!prioritySorted) {
			//Sort priority first only for initial step
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
			prioritySorted = 1;
			//Make a copy of the sorted burst times
			for (int k = 0; k < n; k++) {
				rem_bt[k] = bt[k];
			}
		}
		//If there are still burst times left for the process, execute round robin for the processes
		if (rem_bt[index] != 0) {
			if (rem_bt[index] > quantum) {
				// Increase the value of t i.e. shows how much time a process has been processed 
				t += quantum;
				//reduce burst by quantum
				rem_bt[index] -= quantum;
			}
			//IF a process finishes its execution
			else {
				//Find waiting time of a process which is the current time - original burst of the process
				t += rem_bt[index];
				wt[pi[index] - 1] = t - unsortedBT[pi[index] - 1];
				rem_bt[index] = 0;
				counter--;
			}
		}
		//Increment the index to execute every single process
		index++;
		if (index == n) {
			//If all processes completes its execution, exit the while loop
			if (counter == 0) {
				break;
			}
			else {
				//Resets index if last process
				index = 0;
				//Do sorting again, but this time will sort based on remaining burst times only
				for (i = 0; i < n; i++) {
					if (rem_bt[i] != 0) {
						//Put inside a new copy of remaining burst times in order to determine the new time quantum of remaining processes
						new_rem_bt[cpyIndex] = rem_bt[i];
						cpyIndex++;
					}
				}
				//Reset the index count
				cpyIndex = 0;
				for (i = 0; i < counter; i++) {
					for (j = i + 1; j < counter; j++) {
						//Swaps the remaining burst time here (lowest burst time = highest priority)
						//It checks the remaining burst time here
						if (rem_bt[i] > 0) {
							if (rem_bt[i] > rem_bt[j]) {
								//Holds the lowest priority burst time
								temp1 = rem_bt[i];
								//Changes the burst[i] to burst[j]
								rem_bt[i] = rem_bt[j];
								//new burst of j is to i
								rem_bt[j] = temp1;
								//Stores process indexes into temp
								temp2 = pi[i];
								//swaps process index
								pi[i] = pi[j];
								//new process index
								pi[j] = temp2;
							}
						}
					}
				}
				//Find the new time quantum based on the median of the remaining burst times
				if (counter % 2 != 0) {
					//If the number of processes left is odd
					quantum = new_rem_bt[(counter) / 2];
				}
				else {
					//If the number of processes left is even
					quantum = (new_rem_bt[(counter - 1) / 2] + new_rem_bt[counter / 2]) / 2;
				}
				//This is to track down how many number of executions it takes for the process amnd display the updated time quantum
				noOfExecutions++;
				printf("New Time Quantum after %d execution(s): %d\n", noOfExecutions, quantum);
			}
		}
	}
}
//This is to find the waiting time for the Mean Threshold Shortest Job First
void findMeanTSJFWaitingTime(int n, int bt[], int wt[], int quantum, int p[]) {
	float threshold = 0, awt = 0, att = 0;
	int totalBurst = 0, noOfSJFProcesses = 0, noOfRRProcesses = 0, tempIndex = 0, tempBt = 0, max = 0, t = 0;
	int pi[MAXPROCESSES] = { 1, 2, 3, 4, 5, 6 }, rem_bt[20];
	//Find sum of the burst times of all processes
	for (int i = 0; i < n; i++) {
		totalBurst += bt[i];
	}
	printf("Time Quantum: %d\n", quantum);
	printf("Total Burst Time is: %d\n", totalBurst);
	//Find the threshold time for the processes in the form of Total Burst Time / Number of Processes
	threshold = (float)totalBurst / n;
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
					//Comparison between 2 burst times from array
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
		//Displays the sorted process and its burst times based on SJF and RR
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
// Function to calculate turn around time which is universal for all round robin algorithms
void findTurnAroundTime(int n, int bt[], int wt[], int tat[], int p[]) {
	// calculating turnaround time by adding 
	// bt[i] + wt[i] 
	for (int i = 0; i < n; i++) {
		tat[i] = bt[i] + wt[i];
	}
}
//Function to call the round robin algorithm
void normalRR(char selection, int quantum) {
	int burst_time[] = { 20, 17, 28, 24, 19, 30 };
	int n = sizeof burst_time / sizeof burst_time[0];
	//Priority
	int pi[] = { 1, 2, 3, 4, 5, 6 };
	findAvgTime(selection, n, burst_time, quantum, pi);
}
//Function to call the sorted round robin functionalities
void sortedRR(char selection) {
	int totalBurst = 0;
	int burst_time[] = { 20, 17, 28, 24, 19, 30 };
	int n = sizeof burst_time / sizeof burst_time[0];
	for (int i = 0; i < n; i++) {
		totalBurst += burst_time[i];
	}
	int quantum = totalBurst / n;
	int pi[] = { 1, 2, 3, 4, 5, 6 };
	findAvgTime(selection, n, burst_time, quantum, pi);
}
//Function to call the priority round robin functionalities
void priorityRR(char selection, int quantum) {
	int burst_time[] = { 20, 17, 28, 24, 19, 30 };
	int n = sizeof burst_time / sizeof burst_time[0];
	//Priority
	int p[] = { 4, 2, 1, 3, 5, 6 };
	findAvgTime(selection, n, burst_time, quantum, p);
}
//Function to call the mean threshold round robin functionalities
void meanTSJFRR(char selection, int quantum) {
	int burst_time[] = { 20, 17, 28, 24, 19, 30 };
	//Process Indexes
	int pi[] = { 1, 2, 3, 4, 5, 6 };
	int n = sizeof burst_time / sizeof burst_time[0];
	printf(" Mean Threshold Shortest Job First Round Robin\n");
	printf("-----------------------------------------------\n");
	findAvgTime(selection, n, burst_time, quantum, pi);
}