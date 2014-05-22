//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  proj3.cpp                           ASSIGNMENT #:  3                        *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Ivars Akmentins                                               *
//*                                                                                                   *
//*   COURSE #:  CSC 36000                                 DUE DATE:  March 4, 2013                   *
//*   SECTION: 11                                                                                     *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program makes a list of customers in alphabetical order. It checkes if customer   *
//*            already exists. Also changes customer specific information and deletes customer from   *
//*			   the list, first searching for it, if there is no customer, it prints the error message.*
//*   USER DEFINED                                                                                    *
//*    MODULES     : InsertNoce- adds customer to the list                                            *
//*                  DeleteNode- deletes the customer                                                 *
//*                  PrintNode- prints the information                                                *
//*                  Change- prints the appropriate error                                             *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


struct NodeType												//customers information
{
	string FName, LName, StreetA, City, State, ZipCode;
	NodeType *next;
};


void InsertNode (NodeType *&, ifstream &, ofstream &);
void Change (NodeType *&, ifstream &, ofstream &, int);
void PrintNode (NodeType *&, ofstream &, int);
void DeleteNode (NodeType *&, ifstream &, ofstream &, int);
void Header (ofstream &);
void Footer (ofstream &);

//*********************  Main Function  ***************************************************************
int main()
{
	char Operation;
	NodeType *StartPtr=NULL;
	int lines=5;
	
	ifstream in;							// Open the appropriate files for input and output
	ofstream out;
	in.open ("data3 2008.txt", ios::in);
	out.open ("result3.txt", ios::out);
	
	Header(out);
	in>>Operation;						//gets the first operation
	while(Operation !='Q')				//checks for sentinel
	{
		switch(Operation)				//performs specific operation
		{
			case 'A':
				InsertNode(StartPtr, in, out);		//adds customer
			break;
			case 'D':
				DeleteNode(StartPtr, in, out, lines);	//deletes
			break;
			case 'P':
				PrintNode(StartPtr, out, lines);		//prints list
			break;
			case 'C':
				Change(StartPtr, in, out, lines);		//changes information
			break;
		}
		in>>ws>>Operation;				//gets next operation
	}
	Footer (out);
	in.close();
	out.close();
	return 0;
}


//*****************************************************************************************************
void InsertNode(NodeType *&SPtr,ifstream &in, ofstream &out)
{
	//Receives: Node, input, outputstream
	//Task: adds new record
	//Returns: nothing
	NodeType *newPtr, *PreviousPtr, *CurrentPtr;
	newPtr= new (NodeType);		//creates new node
	string FName, LName;

	if(newPtr==NULL)		//if there is no free memory
	{
		out<<"No memory available."<<endl;
	}

	else		//else place data 
	{
		in>>ws;
		getline(in,newPtr->FName);		//reads the new data
		in>>ws;
		getline(in,newPtr->LName);
		in>>ws;
		getline(in,newPtr->StreetA);
		in>>ws;
		getline(in,newPtr->City);
		in>>ws;
		getline(in,newPtr->State);
		in>>ws;
		getline(in,newPtr->ZipCode);
		in>>ws;

		newPtr->next=NULL;		//adds new node to the begining
		PreviousPtr=NULL;
		CurrentPtr=SPtr;

		while ((CurrentPtr !=NULL) && (newPtr->LName>CurrentPtr->LName))
		{
			if(newPtr->LName==CurrentPtr->LName)
			{
				if(newPtr->FName==CurrentPtr->FName)
				{
					out<<newPtr->FName<<newPtr->LName<<" is already in the list.";
					out<<" Attempt to add duplicate record failed!"<<endl;
					return;		//if the last names and first names are equal
				}
			while ((CurrentPtr !=NULL) && (newPtr->LName==CurrentPtr->LName) && 
												(newPtr->FName>CurrentPtr->FName))
			{
				PreviousPtr=CurrentPtr;		//puts in alphabetical order by the first name, since last 
																					//names are equal
				CurrentPtr=CurrentPtr->next;

				if ((CurrentPtr !=NULL) && (newPtr->LName==CurrentPtr->LName) && 
											(newPtr->FName==CurrentPtr->FName))
				{
					out<<newPtr->FName<<newPtr->LName<<" is already in the list.";
					out<<" Attempt to add duplicate record failed!"<<endl;
					return;	// if the last names and firs names are equal
				}
			}

			if (PreviousPtr==NULL)		//if it is to be places first, places in fron of every node
			{
				newPtr->next=CurrentPtr;
				return;
			}

			else		//puts it in apropriate place
				{
					PreviousPtr->next=newPtr;
					newPtr->next= CurrentPtr;
					return;
				}
			}		//ends operations with the same last name

		PreviousPtr=CurrentPtr;
		CurrentPtr=CurrentPtr->next;
		}

		if (PreviousPtr==NULL)		//if the entry is to be laced first
		{
			newPtr->next=SPtr;
			SPtr=newPtr;
		}

		else		//places it in apropriate position
		{
			PreviousPtr->next=newPtr;
			newPtr->next=CurrentPtr;
		}
	}
	return;
}


//*****************************************************************************************************
void DeleteNode(NodeType *&SPtr, ifstream &in, ofstream &out, int lines)
{
	//Receives: Node, input, outputstream
	//Task: remove a new record
	//Returns: nothing
	NodeType *tempPtr, *PreviousPtr, *CurrentPtr; 
	NodeType Node;
	string FName, LName;

	Node.FName=' ';
	Node.LName=' ';
	Node.StreetA=' ';
	Node.City=' ';
	Node.State=' ';
	Node.ZipCode=' ';
	Node.next=NULL;

	in>>ws;
	getline(in,FName);		//gets customers first and last name to search for
	in>>ws;
	getline(in,LName);
	in>>ws;

	if ((LName==SPtr->LName) && (LName==SPtr->LName))	//if the first node entry is the searched customer
	{
		Node.FName=FName;
		Node.LName=LName;

		tempPtr= SPtr;					//saves the customers location
		SPtr= SPtr->next;				//points to the next entry
		free (tempPtr);					//deletes customer
		return;
	}
	else
	{
		PreviousPtr= SPtr;							//sets to check next customer
		CurrentPtr= SPtr->next;
		while ((CurrentPtr!=NULL) && (CurrentPtr->LName !=LName) && (CurrentPtr->FName !=FName))
		{
			PreviousPtr=CurrentPtr;					//sets next customer if they arent the same
			CurrentPtr=CurrentPtr ->next;
		}
		if(CurrentPtr !=NULL)			//when it finds the customer, it deletes it
		{
			Node.FName=FName;
			Node.LName=LName;

			tempPtr= CurrentPtr;			//saves customers location
			PreviousPtr->next=CurrentPtr->next;		//sets previous customer to point to the next
			free(tempPtr);					//deletes the customer
			return;
		}
	}
	out<<"Record of "<<FName<<LName<<"not found. Attempt to delete record failed!"<<endl<<endl;
	lines+=2;
	for (int i=lines; i<70; i++)		//prints spaces to the new page
			out<<endl;
	lines=5;
	return;
}


//*****************************************************************************************************
void Change (NodeType *&SPtr, ifstream &in, ofstream &out, int lines)
{
	//Receives: Node, input, outputstream
	//Task: changes customers information
	//Returns: nothing
	NodeType *CurrentPtr;
	string change;
	string FName, LName;
	CurrentPtr=SPtr;
	int numb;

	in>>ws;
	getline(in,FName);		//gets customers first and last name
	in>>ws;
	getline(in,LName);
	in>>ws;

	while ( (CurrentPtr->next != NULL) )	//loop till it points to nothing
	{
		if ((CurrentPtr->LName ==LName) && (CurrentPtr->FName ==FName))	//checks for specific customer
		{
			in>>numb;
			switch (numb)		//changes the specific information
			{
				case 1:
					in>>ws;
					getline(in,CurrentPtr->FName);
					in>>ws;
					return;
				break;
				case 2:
					in>>ws;
					getline(in,CurrentPtr->LName);
					in>>ws;
					return;
				break;
				case 3:
					in>>ws;
					getline(in,CurrentPtr->StreetA);
					in>>ws;
					return;
				break;
				case 4:
					in>>ws;
					getline(in,CurrentPtr->City);
					in>>ws;
					return;
				break;
				case 5:
					in>>ws;
					getline(in,CurrentPtr->State);
					in>>ws;
					return;
				break;
				case 6:
					in>>ws;
					getline(in,CurrentPtr->ZipCode);
					in>>ws;
					return;
				break;
			}
		}
		CurrentPtr = CurrentPtr -> next;		//gets to the next customer
	}
	out<<"Record of "<<FName<<LName<<" not found. Attempt to change record failed!"<<endl<<endl;
	lines+=2;
	for (int i=lines; i<70; i++)		//prints spaces to the new page
			out<<endl;
	lines=5;
	return;
}


//*****************************************************************************************************
void PrintNode (NodeType *&SPtr, ofstream &out, int lines)
{
    // Given: A list of values 
	// Task: Print the values in the list 
	// Returns: The an indicator of success

   NodeType  *CurrentPtr;
    
   CurrentPtr = SPtr;

   if ( CurrentPtr == NULL)		//if the list is empty
   {
	   out << "List is Empty" << endl;
	   return;
   }

   out<<setw(35)<<right<<"MAILING LIST"<<endl;
   out<<setw(12)<<left<<"Last Name"<<setw(12)<<left<<"First Name";
   out<<setw(22)<<left<<"Address"<<setw(14)<<left<<"City";
   out<<setw(7)<<left<<"State"<<"Zip Code"<<endl;
   out<<"==========================================================================="<<endl;

   lines+=3;
   while ( (CurrentPtr->next != NULL) )		//prints every customers information
	{
		out<<setw(12)<<CurrentPtr->LName<<setw(12)<<CurrentPtr->FName<<setw(22)<<CurrentPtr->StreetA;
		out<<setw(14)<<CurrentPtr->City<<setw(7)<<CurrentPtr->State<< CurrentPtr->ZipCode<<endl;
		lines++;
		CurrentPtr = CurrentPtr -> next;
	}
    out<<setw(12)<<CurrentPtr->LName<<setw(12)<<CurrentPtr->FName<<setw(22)<<CurrentPtr->StreetA;
	out<<setw(14)<<CurrentPtr->City<<setw(7)<<CurrentPtr->State<< CurrentPtr->ZipCode<<endl<<endl;
	lines+=2;

	for (int i=lines; i<72; i++)		//prints spaces to the new page
			out<<endl;
	lines=8;
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
   Outfile << setw(20) << "Assignment #3" << endl;
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
