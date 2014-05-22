//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Proj6.cpp                           ASSIGNMENT #:  6                        *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Ivars Akmentins                                               *
//*                                                                                                   *
//*   COURSE #:  CSC 36000                                 DUE DATE:  April 17, 2013                  *
//*   SECTION: 11                                                                                     *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS:  Program reads different items and their information. It uses different sort methods   *
//*             and prints the table.                                                                 *
//*   USER DEFINED                                                                                    *
//*    MODULES     : read- reads items and saves in array                                             *
//*                  Print- prints the information                                                    *
//*                  BubbleSort- sorts value with bubble sort method                                  *
//*                  ShellSort- sorts value with shell sort method                                    *
//*                  QuickSort- sorts value with quick sort method                                    *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
struct Item
{
   int number;
   char desc[25];
   int quantity;
   int Rnumber;
   float cost;
   float price;
};

void Header (ofstream &);
void Footer (ofstream &);
int read (Item [50], ifstream &);
void print(ofstream &, Item [50], int, int &);
void BubbleSort(Item [], int);
void ShellSort (Item [], int );
void QuickSort (Item [], int , int  );


//***********************    main function   **********************************************************
int main()
{
	Item item[50];
	int itemNum=0;
	int pagenum=4;

	ifstream in;							// Open the appropriate files for input and output
	ofstream out;
	in.open ("data6_2008..txt", ios::in);
	out.open ("result6.txt", ios::out);
	Header(out);

	out<<"The Original Inventory Array:"<<endl;
	pagenum++;
	itemNum=read(item, in);
	print(out, item, itemNum, pagenum);
	out<<"The Inventory Array sorted in descending order according to the quantity on hand ";
	out<<"using the"<<endl<<"Exchange Sort:"<<endl;
	pagenum=2;
	BubbleSort(item, itemNum);
	print(out, item, itemNum, pagenum);
	out<<"The Inventory Array sorted in descending order according to the selling price ";
	out<<"using the"<<endl<<"Exchange Sort:"<<endl;
	pagenum=2;
	ShellSort(item, itemNum);
	print(out, item, itemNum, pagenum);
	out<<"The Inventory Array sorted in ascending order according to the inventory number ";
	out<<"using the"<<endl<<"Exchange Sort:"<<endl;
	pagenum=2;
	QuickSort(item, 0, itemNum-1);
	print(out, item, itemNum, pagenum);

	Footer(out);
	return 0;
}

//***********************    Bubble Sort   ************************************************************
void BubbleSort(Item list[], int ElementsUsed)
{
  int IndexA, IndexB;
  Item temp;

				// IndexA controls how many times we pass thru 
				// the array the array
  for ( IndexA = 0 ; IndexA < ElementsUsed-1; IndexA++)    
  {
	            // IndexB controls at which end of the array we begin and
	            // which elements are compared and swapped if needed.
     for ( IndexB = ElementsUsed-1; IndexB > IndexA ; IndexB--)    
		 if (list[IndexB].quantity > list[IndexB-1].quantity )                
		{
          temp = list[IndexB];
          list[IndexB] = list[IndexB-1];
          list[IndexB-1] = temp;
		}
  }  

 return;
}

//***********************    Shell Sort   *************************************************************
void ShellSort ( Item array[], int ElementsUsed) 
{
	 int count = 0;
     int NumOfStages = 3;
     int KValues[3] = {7, 3, 1};         
     int i, j, k, Stage;
	 Item Temp;
     bool  Found;

     for ( Stage = 0; Stage < NumOfStages;  Stage++) 
	 {
       k = KValues[Stage];
       for (i=k; i<ElementsUsed; i++)  
	   {
         Temp = array[i];
         j = i-k;
         Found = false;
         while (( j >= 0) && ( !Found) ) 
		 {
			 if (Temp.price > array[j].price) 
		   {
             array[j+k] = array[j];
             j -= k;
		   }
           else
		     Found = true;
		 }   // end while
         array[j+k] = Temp;
	   }
	 }
}

//***********************    Quick Sort   *************************************************************
void QuickSort (Item Array[], int First, int Last )
{
    int I, J, MID;
	Item Temp; 
	I = First;
	J = Last;     
           
    MID = (First+Last)/2;    // Find the middle indexed 

    while (I <= J)
	{
		while (Array[I].number < Array[MID].number)
		  ++I;
      while (Array[J].number > Array[MID].number)
          --J;  

 	  if(I <= J)  
	  {
 	    Temp = Array[I];      //  switch  Num[I] and Num[J]
		Array[I] = Array[J];
		Array[J] = Temp; 
        ++I;
 		--J;
	  }
	}

	if( J > First )
      QuickSort(Array, First, J);        //  Partition left subarray

	if( I < Last  )
      QuickSort(Array, I, Last);         //  Partition right subarray 

}

//***********************    read function   **********************************************************
int read(Item item[50], ifstream & in)
{
	int n=0;
	in>>item[n].number;
	while(item[n].number>=0)
	{
		in>>ws;
		in.getline(item[n].desc, 26);
		in>>item[n].quantity;
		in>>item[n].Rnumber;
		in>>item[n].cost;
		in>>item[n].price;
		n++;
		in>>item[n].number;
	}

	return n;
}

//***********************    print function   *********************************************************
void print (ofstream &out, Item item[50], int n, int &pageline)
{
	out<<"Inventory  "<<setw(23)<<left<<"Item"<<"Quantity  "<<"Recorder  "<<"Cost of  "<<"Selling";
	out<<endl;
	out<<" Number    "<<setw(23)<<left<<"Description"<<"on hand   "<<"Number    "<<"Item     ";
	out<<"Price"<<endl;
	out<<"--------   ---------------------  --------  --------  -------  -------"<<endl;
	pageline+=3;
	for(int i=0; i<n; i++)
	{
		out<<"  "<<setw(10)<<item[i].number<<setw(18)<<item[i].desc<<setw(9)<<item[i].quantity;
		out<<setw(9)<<item[i].Rnumber<<setw(9)<<item[i].cost<<item[i].price<<endl;
		pageline++;
	}
	for (int i=pageline; i<66; i++)
		out<<endl;
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
   Outfile << setw(20) << "Assignment #6" << endl;
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
