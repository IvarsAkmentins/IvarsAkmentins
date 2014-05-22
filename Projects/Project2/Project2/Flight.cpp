#include <iostream>
#include <iomanip>
#include "Flight.h"

void FlightClass::GBoardNum(ifstream& in)
{in>>BoardNum;}

void FlightClass::GFlightNum(ifstream & in)
{in>>FlightNum;}

void FlightClass::GSection(ifstream & in)
{in>>Section;}

void FlightClass::GRow(ifstream & in)
{in>>Row;}

void FlightClass::GColumn(ifstream &in)
{in>>Column;}

void FlightClass::Loop(int arrays [][9][2], int waiting, int boarding ,int flight ,int row, int col, int begining, int ending)
{
	if (arrays [flight][row][col]==-999)
	{
		arrays [flight][row][col]=boarding;
		return;
	}
	else
	{
		for (int i=0; i<3; i++)							//i is column
		{
			if (arrays [flight][row][i]==-999)
				arrays [flight][row][i]=boarding;
				return;									//Rule 1
		}
	}

	for (int j=begining; j<ending; j++)					//j is row
	{
		if (arrays [flight][j][col]==-999)
				arrays [flight][j][col]=boarding;
		return;											//Rule 2
	}

	for (int j=begining; j<ending; j++)	
		for (int i=0; i<3; i++)
		{
			if (arrays [flight][j][i]==-999)
			{
				arrays [flight][j][i]=boarding;
				return;
			}											//Rule 3
		}
	waiting=1;
}

int FlightClass::GetBoardNum()
{return BoardNum;}

int FlightClass::GetFlightNum()
{return FlightNum;}

char FlightClass::GetSection()
{return Section;}

int FlightClass::GetRow()
{return Row;}

char FlightClass::GetColumn()
{return Column;}

void FlightClass::Print(ofstream &out)
{out<<setw(10)<<BoardNum;}