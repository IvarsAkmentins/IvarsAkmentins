//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  itsiac.cpp                          ASSIGNMENT #:  1                        *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Ivars Akmentins                                               *
//*                                                                                                   *
//*   COURSE #:  CSC 460                                 DUE DATE:  April 8, 2013                     *
//*                                                                                                   *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program simulates itsiac machine, by reading binary code, decoding it and making  *
//*			   its own program. Reads the data and executed with the read program. It consists from   *
//*			   Machine Language Instructions which consists from many microinstructions.			  *
//*                                                                                                   *
//*****************************************************************************************************


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "functions.h"

using namespace std;

void Header (ofstream &);
void Footer (ofstream &);

//*********************  Main Function  ***************************************************************
int main()
{
	functionsClass Pro;

	ifstream in;							// Open the appropriate files for input and output
	ofstream out;
	in.open ("Data__its.txt", ios::in);
	out.open ("result.txt", ios::out);
	Header(out);

	Pro.readData(in);			//reads the data and saves it to primary memory

	Pro.dump(out);				//prints the first dump file

	Pro.FetchAInc(out);				//executes first machine language instruction

	for (int i=0; i<Pro.GetMLC(); i++)		//executes machine language instructions from primary memory
		Pro.ControlStor(Pro.GetPrimaryMemory(i), out);

	Pro.dump(out);		//prints second dump file
	for (int n=Pro.GetX(); n<256; n++)		//fills up the 8x32 table
	{
		out<<"FFFF ";
		if(n%8==0)
			out<<endl;
	}
	out<<Pro.GetMLC()<<Pro.Getmicro();		//prints out the counters

	Footer(out);
	in.close();
	out.close();
	return 0;
}

//*************************************  FUNCTION HEADER  *********************************************
void Header(ofstream &Outfile) 
{
               // Receive – the output file
               // Task - Print the output preamble
               // Return - Nothing
   Outfile << setw(30) << "Ivars Akmentins ";
   Outfile << setw(17) << "CSC 460";
   Outfile << setw(15) << "Section 11" << endl;
   Outfile << setw(30) << "Spring 2013";
   Outfile << setw(20) << "Assignment #1" << endl;
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
