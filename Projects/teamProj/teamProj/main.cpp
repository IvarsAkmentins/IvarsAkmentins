#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "funct.h"

using namespace std;

int io_timer=0;				//indicates the current I/O burst
int job_timer=0;			//keeps track of the time between job arivals
int more_jobs=0;			//keeps track of the # of jobs in system
int process_timer=0;		//keeps track of the current CPU burst
int suspend_timer=0;		//keeps track of current interrupt time
bool cpu_ready_flag=true;	//signals that the CPU is available
bool cpu_complete_flag=false;	//signals the completion of a CPU burst
bool finished_flag=false;		//signals that a JOB is finished
bool interrupt_flag=false;		//signals that an interrupt is in progress
bool io_complete_flag=false;	//signals the completion of an I/O burst
bool io_device_flag=true;		//signals that the I/O device is available
bool job_flag=false;			//signals the a job has arrived
bool stop_flag=false;			//signals to stop CPU job processing
bool suspend_flag=false;		//signals context switch to handle interrupt
NODETYPE CPU;				//which job has the CPU
NODETYPE device;		//which job has the device
int count=0;			//number of processes ran
NODETYPE process;			//processs entering the CPU	
NODETYPE ioprocess;		//processs entering the I/O device
NODETYPE temp;				//which process is suspended
int cpuburstlength;		
int ioburstlength;
bool ltq_empty=true;	//Long Term queue is empty
bool ltq_full=false;	//Long term queue is full
bool stq_empty=true;	//short term queue is empty
bool stq_full=false;	//short term queue is full
bool ioq_full=false;	//I/O queue is full
bool ioq_empty=true;	//I/O queue if empty
bool IOcomplete;		
bool IOdevice;
bool finished;
bool last_job=false;

void manageLTQ(QueueClass, NODETYPE );
void manageSTQ(QueueClass , QueueClass , NODETYPE );
void manageIOQueue(QueueClass);
void manageCPU(QueueClass , QueueClass);
void manageIODevice(QueueClass);

int main()
{
	int clock=0;				//the simulator clock to keep track of the total time
							//of the simulation run
	QueueClass ShortTerm(30), LongTerm(60), IO(30);
	NODETYPE JobProcess[151], node;
	int NumBur=0;
	ofstream OutFile;
	int Temporary;
	OutFile.open("OutPut.txt", ios::out);

	// Open up the input file
	ifstream InFile;
	InFile.open("SIM_DATA.txt", ios::in);

	int JobCounter = 0;


	InFile >> Temporary;
	InFile >> ws;
	while (Temporary != -1)
	{
		JobProcess[JobCounter].ID=Temporary;

		InFile >> JobProcess[JobCounter].length;
		JobProcess[JobCounter].count=JobProcess[JobCounter].length;
		InFile >> ws;


		InFile >> JobProcess[JobCounter].arrivalTime;
		InFile >> ws;

		InFile >> JobProcess[JobCounter].IO;
		InFile >> ws;

		InFile >> Temporary;
		InFile >> ws;

		while (Temporary != 0 || Temporary != -1)
		{
			JobProcess[JobCounter].CPU[NumBur] = Temporary;
			JobProcess[JobCounter].CPUBursts[NumBur]=Temporary;
			NumBur++;

			InFile >> Temporary;
			InFile >> ws;
		}

		JobProcess[JobCounter].NumberOfBurst = NumBur;

		NumBur = 0;
		JobCounter++;
	}

	more_jobs=0;
	job_timer++;
	do//do while Last_Job not done
	{
		//start clock
			for (int i=0; i<JobCounter; i++)
			{
				if (JobProcess[i].arrivalTime==job_timer)
				{
					JobProcess[i].arrive=clock;
					node=JobProcess[i];
					job_flag=true;
					more_jobs++;
				}
			}
		manageLTQ(LongTerm, node);
		manageSTQ(ShortTerm, LongTerm, node);
		manageIOQueue(IO);
		manageIODevice(IO);
		manageCPU(ShortTerm, LongTerm);
		//check for finished jobs
		//check for incoming processes
		job++;
		clock++;
	}while(more_jobs==0);

	//Compile the statistical data
	//process the data
	//produce the desired output


	return 0;
}


void manageLTQ(QueueClass LongTerm, NODETYPE DataIn)
{
	if (ltq_empty==false)
		{//increment wait timer for all processes
			LongTerm.Process();
		}
	if (!LongTerm.IsFull() && job_flag==true)
		{
			LongTerm.Add(DataIn);
			job_flag=false;
			ltq_empty=false;
		}
	if (LongTerm.IsFull())
		ltq_full=true;

	if(LongTerm.IsEmpty())
		ltq_empty=true;

	return;
}

void manageSTQ(QueueClass STQ, QueueClass LTQ, NODETYPE DataIn)
{
	NODETYPE *first, tempor;
	if (stq_empty==false)
		//increment wait timer for all processes
			STQ.Process();
	if (IOcomplete==true)
	{
			IOcomplete=false;
			IOdevice=true;
		if (finished_flag==true)
			{
				//remove job from the system and collect the data
				//delete from the system
				more_jobs--;
				//collect the data
			}
		else if (stq_full==false)
			{
				STQ.Add(DataIn);
				device.test=false;		//set device=0
				if (STQ.IsFull())
					stq_full=true;
			}
	}
	if (stq_full==false && ltq_empty==false)
	{
		//move operation from LTQ to STQ
		first=LTQ.First();						//copy node pointer to regular node
		tempor.ID=first->ID;
		tempor.length=first->length;
		tempor.arrivalTime=first->arrivalTime;
		tempor.arrive=first->arrive;
		tempor.IO=first->IO;
		for(int i=0; i<10;i++)
		{
			tempor.CPU[i]=first->CPU[i];
			tempor.CPUBursts[i]=first->CPUBursts[i];
		}
		tempor.NumberOfBurst=first->NumberOfBurst;
		tempor.count=first->count;
		tempor.test=first->test;
		tempor.CPUWait=first->CPUWait;

		LTQ.Delete();
		STQ.Add(tempor);
		stq_empty=false;
		if (LTQ.IsEmpty())
		{
			ltq_empty=true;
			ltq_full=false;
		}
		if (STQ.IsFull())
			stq_full=true;
	}
	return;
}	

void manageIOQueue(QueueClass IO)
{
	if (ioq_empty == false)
	{
		//increment I/O queue wait counter for all processes
		IO.Process();
	}
	if (cpu_complete_flag == true)
	{
		if (ioq_full == false)
		{
						//add the process to the tail of the queue
			IO.Add(CPU);
			CPU.test=false;;
			ioq_empty = false;
			cpu_ready_flag = true;
			if (IO.IsFull())
				ioq_full = true;
			cpu_complete_flag = false;
		}
	}
	return;
}

void manageCPU(QueueClass STQ, QueueClass LTQ)
{
	NODETYPE *tempor;
	if (suspend_flag==true)
	{
		suspend_timer--;
		if (suspend_timer=0)
		{
			interrupt_flag=false;
			suspend_flag=false;
		}
		else if (temp.ID==process.ID)
		{
			stop_flag=true;
			CPU.CPUWait++;
		}
	}
	if(stop_flag==false)
	{
		if(interrupt_flag==true)
		{
			if(suspend_timer==0)
			{
				if(CPU.test==true)
				{
					temp=CPU;
					CPU.test=false;
				}
				suspend_timer=3;
				suspend_flag=true;
			}
			else if (CPU.ID==process.ID)
			{
				process_timer++;
				if (process_timer==CPU.CPUBursts[CPU.CPUBurstCounter])
				{
					cpu_complete_flag=true;
					process_timer=0;
					CPU.CPUBurstCounter++;
				}
			}
			else if (temp.ID==process.ID)
			{
				CPU=process;
				CPU.CPUWait++;	//cpu wait counter
				temp.test=false;
			}
			else if (stq_empty==false && cpu_ready_flag==true)
			{
				tempor=STQ.First();
				process.ID=tempor->ID;
				process.length=tempor->length;
				process.arrivalTime=tempor->arrivalTime;
				process.arrive=tempor->arrive;
				process.IO=tempor->IO;
				for(int i=0; i<10;i++)
				{
					process.CPU[i]=tempor->CPU[i];
					process.CPUBursts[i]=tempor->CPUBursts[i];
				}
				process.NumberOfBurst=tempor->NumberOfBurst;
				process.count=tempor->count;
				process.test=tempor->test;
				process.CPUWait=tempor->CPUWait;

				CPU=process;
						//delete job from the queue
				STQ.Delete();
				stq_full=false;
				if(STQ.IsEmpty())
					stq_empty=true;
				cpu_ready_flag=false;
				process_timer=0;
			}
		}
	}
	stop_flag=false;
	return;
}

void manageIODevice(QueueClass IO)
{
	NODETYPE *tempor;
	if (interrupt_flag==false)
	{
		if (device.ID==ioprocess.ID)
		{
					//increment IO timer
			io_timer++;
			if (io_timer==device.IO)
			{
				io_complete_flag=true;
				device.test=false;
				if (device.CPUBursts[device.CPUBurstCounter]!=0)
				{
					interrupt_flag=true;
				}
				else
					finished_flag=true;
			}
		}
		else if (ioq_empty==false && io_device_flag==true)
		{
			tempor=IO.First();

			ioprocess.ID=tempor->ID;
			ioprocess.length=tempor->length;
			ioprocess.arrivalTime=tempor->arrivalTime;
			ioprocess.arrive=tempor->arrive;
			ioprocess.IO=tempor->IO;
			for(int i=0; i<10;i++)
			{
				ioprocess.CPU[i]=tempor->CPU[i];
				ioprocess.CPUBursts[i]=tempor->CPUBursts[i];
			}
			ioprocess.NumberOfBurst=tempor->NumberOfBurst;
			ioprocess.count=tempor->count;
			ioprocess.test=tempor->test;
			ioprocess.CPUWait=tempor->CPUWait;

			device=ioprocess;
			IO.Delete();
			if (IO.IsEmpty())
				ioq_empty=true;
			io_timer=0;
			io_device_flag=false;
		}
	}
	return;
}