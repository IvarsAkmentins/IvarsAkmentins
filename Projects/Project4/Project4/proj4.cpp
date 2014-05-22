//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  proj4.cpp                           ASSIGNMENT #:  4                        *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Ivars Akmentins                                               *
//*                                                                                                   *
//*   COURSE #:  CSC 36000                                 DUE DATE:  March 18, 2013                  *
//*   SECTION: 11                                                                                     *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program makes a queue of customers. Each customer comes in their own time and has *
//*			   their own processing time. Calculates which customer will be done first and lets him go*
//*            from the queue. Prints out the original list and ordered list.                         *
//*   USER DEFINED                                                                                    *
//*    MODULES     : Add- adds customer to the queue                                                  *
//*                  Delete- deletes the customer                                                     *
//*                  Print- prints the information                                                    *
//*                  Process- processes customer list                                                 *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#define MaxSize 100

using namespace std;

struct NODETYPE  
{
	string name;
	int ProcTime;
};

class QueueClass 
{
	public:
		QueueClass();
		bool IsEmpty(){return(cout==0);}
		bool IsFull() {return(count == MaxSize);}
       	int QueueCount(){return count;}
     	bool Add(NODETYPE datain);
     	bool Delete( NODETYPE &dataout);
		void Process();
        void Print(ofstream &);

   private:
     	int front;
     	int rear;
     	int size;
       	int count;
		int OrigNum;
		int OrderNum;
        NODETYPE ArrayOfNodes[MaxSize];	   
		string Original[MaxSize];
		string Order[MaxSize];
};
void Header (ofstream &);
void Footer (ofstream &);

//*****************************************************************************************************
int main()
{   int arrival;
	int time=1;							//start time
	string name;						//customers name
	NODETYPE Node;
    QueueClass Queue;

	ifstream in;							// Open the appropriate files for input and output
	ofstream out;
	in.open ("queue_in_2010.txt", ios::in);
	out.open ("result4.txt", ios::out);
	Header(out);

	in>>arrival;				//gets the customers arrival time
     while (arrival!=(-99))		//checks for the sentinel
	 {
		 if(time==arrival)			//if it is customers arrival time, proceed
		 {
			in>>ws;	
			getline(in,Node.name);		//gets customers name
			in>>ws;
			in>>Node.ProcTime;			//and processing time
			Queue.Add(Node);			//adds customer to the queue
			Queue.Process();			//processes customers
			in>>arrival;				//gets next customers arrival time
			time++;						//adds time
		 }
		 else
		 {
			Queue.Process();			//processes customers 
			time++;						//adds time
		 }
	 }

	 for(int n=0;n<50; n++)				//finishes all processes with customers
	 {
		Queue.Process();
	 }

    Queue.Print(out);		//prints the list
	Footer (out);
	in.close();
	out.close();
  return 0;
}

//*****************************************************************************************************
QueueClass::QueueClass ( )
{
   size = MaxSize;
   front = rear = -1;
   count = 0;
   OrigNum=0;
   OrderNum=0;
}

//*****************************************************************************************************
void QueueClass::Print(ofstream &out) 
{
	//Recieves: output file
	//Task:	prints customer list
	//Returns:	nothing

	out<<"The order of customer arrival is:    |     The order of customer departure is:"<<endl;
  for (int i=0; i< OrigNum; i++)   
	  out <<setw(5)<<" "<<setw(25)<<Original[i]<<setw(8)<<"|"<<setw(10)<<" "<<setw(25)<<Order[i]<<endl;
}


//*****************************************************************************************************
bool QueueClass::Delete(NODETYPE &dataOut) 
{
	//Recieves: Node to be changed
	//Task:	Deletes node from the queue
	//Returns:	updated Node

   if ( IsEmpty() ) 
      return false;
 	  
   dataOut = ArrayOfNodes[front+1];		//changes node information to the front node

   front++;		//adds 1 to front value

   if (front == MaxSize)
     front = 0;

   if (count == 1)
     rear = front = -1;

   count--;			//decreases count

   return true;
}

//*****************************************************************************************************
bool QueueClass::Add(NODETYPE dataIn) 
{
	//Recieves: Node
	//Task:Add Node to the queue
	//Returns:	updated queue

   if ( IsFull() ) 
     return false;

   rear++;					//adds rear value
   if (rear == MaxSize)
     rear = 0;

   ArrayOfNodes[rear] = dataIn;		//saves node to the queue
   Original[OrigNum]=dataIn.name;	//saves name to the original list

   if ( IsEmpty() )
      front = 0;

   count++;		//adds count
   OrigNum++;	//adds original number count

   return true;
}

//*****************************************************************************************************
void QueueClass::Process() 
{
	//Recieves:nothing
	//Task:processes the queue
	//Returns:updated queue

	for(int i=front+1; i<rear+1; i++)		//decreases every nodes process time
			ArrayOfNodes[i].ProcTime--;

	for(int i=front+1; i<rear+1; i++)		//checks if nodes process time is done
	{
		if(ArrayOfNodes[i].ProcTime==0)			//if it is done, delete node
			{
				Order[OrderNum]=ArrayOfNodes[i].name;		//saves name to the ordered list
				OrderNum++;							//adds ordered number value by 1
				Delete(ArrayOfNodes[i]);
			}
	}
	return;
}

//*************************************  FUNCTION HEADER  *********************************************
void Header(ofstream &Outfile) 
{
               // Receive – the output file
               // Task - Print the output preamble
               // Return - Nothing

   Outfile << setw(30) << "Ivars Akmentins ";
   Outfile << setw(17) << "CSC 36000";
   Outfile << setw(15) << "Section 11" << endl;
   Outfile << setw(30) << "Spring 2013";
   Outfile << setw(20) << "Assignment #4" << endl;
   Outfile << setw(35) << "-----------------------------------";
   Outfile << setw(35) << "-----------------------------------\n\n";
   return;
}
//************************************* END OF FUNCTION HEADER  ***************************************



//*************************************  FUNCTION FOOTER  *********************************************
void Footer (ofstream &Outfile) 
{
               // Receive – the output file
               // Task - Print the output salutation
               // Return - Nothing

   Outfile << endl;
   Outfile << setw(35) << " --------------------------------- " << endl;
   Outfile << setw(35) << "|      END OF PROGRAM OUTPUT      |" << endl;
   Outfile << setw(35) << " --------------------------------- " << endl;

   return;
  }
//************************************* END OF FUNCTION FOOTER  ***************************************
