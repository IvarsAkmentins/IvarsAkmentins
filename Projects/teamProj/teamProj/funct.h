#include <iostream>
#define MaxSize 60
using namespace std;

struct NODETYPE  
{
   int ID;
   int length;
   int arrivalTime;
   int arrive;
   int IO;
   int CPU[10];
   int CPUBursts[10];
   int CPUBurstCounter;
   int NumberOfBurst;
   int count;
   bool test;
   int CPUWait;
   NODETYPE * next;
};

class QueueClass 
{
	public:
		QueueClass(int);
		bool IsEmpty(){return ((front==NULL) ? true : false);}
		bool IsFull();
       	int QueueCount(){return count;}
     	bool Add(NODETYPE datain);
		NODETYPE *First(); 
     	NODETYPE *Last();
		//NODETYPE FirstNode();
     	bool Delete();
		bool Process();

   private:
     	int size;
       	int count;
		int OrigNum;
		int OrderNum;
		NODETYPE *front;
        NODETYPE *rear;
        //NODETYPE ArrayOfNodes[MaxSize];	   
};