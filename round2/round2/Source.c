#include <stdio.h>
int findavgTime( int n, int bt[],
	int quantum,int p[])
{
	int wt[20], tat[20], total_wt = 0, total_tat = 0, counter = 0, remaining = 0;
	// Function to find waiting time of all processes 
	findWaitingTime( n, bt, wt, quantum,p,counter,remaining);

	// Function to find turn around time for all processes 
	findTurnAroundTime( n, bt, wt, tat,p);
	// Display processes along with all details
	totalProcess(n);
	printf("Processes\tBurst Time\tWaiting Time\tTurn Around Time\tPriority\n");

	// Calculate total waiting time and total turn 
	// around time 
	for (int i = 0; i < n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		printf("%d\t\t%2d\t\t%2d\t\t%2d\t\t\t%2d\n", (i + 1), bt[i], wt[i], tat[i],p[i]);

	}
	//average of wt and tat
	printf("Average Waiting Time = %.2f\n", (float)total_wt / (float)n);
	printf("Average Turn Around Time = %.2f\n", (float)total_tat / (float)n);
	return 0;
}
int totalProcess(int n) {
	printf("Round Robin with Priority for %2d process(es)\n", n);
	printf("-----------------------------------------------------\n");
	printf("Number of Processes: %2d\n", n);
}
int main()
{
	// process id's 


	// Burst time of all processes 
	int burst_time[] = { 23,19,10,11,5};
	int n = sizeof burst_time / sizeof burst_time[0];
	//Priority
	int p[] = { 4,2,1,3,5 };

	// Time quantum 
	int quantum = 5;

	findavgTime(n, burst_time, quantum,p);
	return 0;
}


int findWaitingTime(int n,
	int bt[], int wt[], int quantum,int p[],int counter,int remaining)
{
	int temp1, temp2, i, j;
	for (i = 0;i < n;i++)
		for (j = i + 1;j < n;j++)
			//Swaps the priority here 
			//It checks the priority here
			if (p[i] > p[j])
			{
				//Holds the lowest priority burst time
				temp1 = bt[i];
				//Changes the burst[i] to burst[j]
				bt[i] = bt[j];
				//new burst of j is to i
				bt[j] = temp1;
				//it stores priorityinto temp
				temp2 = p[i];
				//swaps priority
				p[i] = p[j];
				//new priority
				p[j] = temp2;
			}
	//sotres bt into compt, waiting time = 0
	// Make a copy of burst times bt[] to store remaining 
	// burst times. 
	int rem_bt[20];
	for (int i = 0; i < n; i++)
		rem_bt[i] = bt[i];

	int t = 0; // Current time 

	// until done, it loops through
	while (1)
	{
		int done = 1;

		//loops through all process
		for (int i = 0; i < n; i++)
		{
			
			//checks for burst greater than 0
			if (rem_bt[i] > 0)
			{
				done = 0; // There is a pending process 
				if (rem_bt[i] > quantum)
				{
					// Increase the value of t i.e. shows 
					// how much time a process has been processed 
					t += quantum;

					//reduce burst by quantum
					rem_bt[i] -= quantum;
				}

				//means burst smaller than quantum
				else
				{
					// Increase the value of t i.e. shows how much time a process has been processed 
					t = t + rem_bt[i];

					// Waiting time is current time minus time  used by this process 
					wt[i] = t - bt[i];

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
		if (done == 1)
			break;
	}
	return 0;
}

// Function to calculate turn around time 
int findTurnAroundTime(int n,
	int bt[], int wt[], int tat[],int p[])
{
	// calculating turnaround time by adding 
	// bt[i] + wt[i] 
	for (int i = 0; i < n; i++)
		tat[i] = bt[i] + wt[i];
	return 0;
}