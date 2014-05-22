#include <iostream>

#include "funct.h"

QueueClass::QueueClass (int Size )
{
   size = Size;
   front = NULL;
   rear = NULL;
   count = 0;
   OrigNum=0;
   OrderNum=0;
}

bool QueueClass::Delete() //change to LL
{
	//Recieves: Node to be changed
	//Task:	Deletes node from the queue
	//Returns:	updated Node
	NODETYPE *temp;

   if ( IsEmpty() ) 
      return false;
 
   count--;			//decreases count

                   // Delete the node
   temp = front;
   front = front->next;
   delete temp;

   return true;
}

bool QueueClass::Add(NODETYPE dataIn)
{
	//Recieves: Node
	//Task:Add Node to the queue
	//Returns:	updated queue

	NODETYPE *NewPtr;
	NewPtr = new (NODETYPE); 
	NewPtr->ID=dataIn.ID;
	NewPtr->length=dataIn.length;
	NewPtr->arrivalTime=dataIn.arrivalTime;
	NewPtr->arrive=dataIn.arrive;
	NewPtr->IO=dataIn.IO;
	for(int i=0; i<10;i++)
	{
		NewPtr->CPU[i]=dataIn.CPU[i];
		NewPtr->CPUBursts[i]=dataIn.CPUBursts[i];
	}
	NewPtr->NumberOfBurst=dataIn.NumberOfBurst;
	NewPtr->count=dataIn.count;
	NewPtr->test=false;
	NewPtr->CPUWait=dataIn.CPUWait;
	NewPtr->next=0;

   if ( IsFull() ) 
     return false;

   if (front == NULL)
   {
     front = NewPtr;
   }
   else
      rear-> next = NewPtr;   // queue is not empty
   rear = NewPtr;
   count++;		//adds count
   OrigNum++;	//adds original number count

   return true;
}

bool QueueClass::Process()		//YOU MAY MAKEDIFFERENT PROCESSES TO DECREMENT STQ, LTQ, IOQ, CPU WAIT COUNTERS YOU MADE
								//JUST COPY AND CHANGE COUNT-- TO WHATEVER YOU NEED TO
{
	//Recieves:nothing
	//Task:processes the queue
	//Returns:updated queue
	NODETYPE *current;

	current  = front;

	if (current == NULL)
		return false;
	else
		while (current  != NULL)
		{
			current ->count--;
			current  = current ->next;
		}

	return true;
}

NODETYPE *QueueClass::First() 
{
  if ( IsEmpty() )
  {
     cout << "Queue is Empty. " << endl;
     return NULL;
  }
  return front;
}
//**********************************************
NODETYPE * QueueClass::Last() 
{
   if ( IsEmpty() )
   {
      cout << "Queue is Empty. " << endl;
      return NULL;
   }
   return rear;
}

bool QueueClass::IsFull() 
{
   NODETYPE  *p;
   p = new (NODETYPE);

   if (p == NULL)
   {
      delete p;
      cout << "Out of Memory. " << endl;
      return true;
   }
   return false;
}