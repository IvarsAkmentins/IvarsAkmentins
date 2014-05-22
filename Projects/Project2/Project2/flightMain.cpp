//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  assignment6.cpp                     ASSIGNMENT #:  1                        *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Ivars Akmentins                                               *
//*                                                                                                   *
//*   COURSE #:  CSC 24400 11                              DUE DATE:  April 27, 2013                  *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS:                                                                                        *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : 
//*                                                                                                   *
//*****************************************************************************************************

#include <fstream>
#include <iomanip>
#include <string>
#include "Flight.h"

using namespace std;

int main () 
{
	int BoardN, FlightN, SeatC, waiting=0, waitingList[7][50], i=0, begining, ending;
	int SeatR;
	int Array [7][9][2]={-999};        //flight number, row, column
	FlightClass Flights;

	ifstream in;				// Open the appropriate files for input and output
	ofstream out;
	in.open ("data1", ios::in);
	out.open ("result1.txt", ios::out);
	
	Flights.GBoardNum(in);
	BoardN=Flights.GetBoardNum;
	while (BoardN!=-999)
	{
		Flights.GFlightNum(in);
		Flights.GSection(in);
		Flights.GRow(in);
		Flights.GColumn(in);

		BoardN=Flights.GetBoardNum;
		FlightN=Flights.GetFlightNum;
		SeatR=Flights.GetRow;

		if(strcmp(Flights.GetColumn, "L")==0)
			SeatC=0;
		else if (strcmp(Flights.GetColumn, "M")==0)
					SeatC=1;
		else SeatC=2;

		if(strcmp(Flights.GetRow, "F")==0)
			{
				begining=0;
				ending=3;
			}
		else if (strcmp(Flights.GetRow, "C")==0)
			{
				begining=4;
				ending=9;
			}

		switch (Flights.GetFlightNum)
		{
			case 1010:
				Flights.Loop(Array, waiting, BoardN, FlightN, SeatR, SeatC, begining, ending);
				//if (waiting	==1)
					//{
						//waitingList[0][i]=Flights.GetBoardNum;
						//i+=1;
					//}
				break;
			case 1015:
				if (waiting	==1)
					{
						//waitingList[1][i]=Flights.GetBoardNum;
						//i+=1;
					}
				break;
			case 1020:
				if (waiting	==1)
					{
						//waitingList[2][i]=Flights.GetBoardNum;
						//i+=1;
					}
				break;
			case 1025:
				if (waiting	==1)
					{
						//waitingList[3][i]=Flights.GetBoardNum;
						//i+=1;
					}
				break;
			case 1030:
				if (waiting	==1)
					{
						//waitingList[4][i]=Flights.GetBoardNum;
						//i+=1;
					}
				break;
			case 1035:
				if (waiting	==1)
					{
						//waitingList[5][i]=Flights.GetBoardNum;
						//i+=1;
					}
				break;
			case 1040:
				if (waiting	==1)
					{
						//waitingList[6][i]=Flights.GetBoardNum;
						//i+=1;
					}
				break;
			case 1045:
				if (waiting	==1)
					{
						//waitingList[7][i]=Flights.GetBoardNum;
						//i+=1;
					}
				break;
			Flights.GBoardNum(in);
			BoardN=Flights.GetBoardNum;
		}
		}
	in.close();
	out.close();
	return 0;
	
}