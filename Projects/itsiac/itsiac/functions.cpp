#include <iostream>
#include <iomanip>
#include <string>
#include "functions.h"


//*****************************************************************************************************
int functionsClass::convert (int part, int code[16])
{
	//Recieves: part and code
	//Task:	converts to decimal system 
	//Returns:	decimal value
	int number=0;
	switch (part)
	{
		case 0:
			number=128*code[0]+64*code[1]+32*code[2]+16*code[3]+8*code[4]+4*code[5]+2*code[6]+1*code[7];
			return number;	
		break;
		case 1:
			number=128*code[8]+64*code[9]+32*code[10]+16*code[11]+8*code[12]+4*code[13]+2*code[14]+1*
				code[15];
		break;
		case 3:
			{
				if (code[0]==0)
				{
					number=8192*code[2]+4096*code[3]+2048*code[4]+1024*code[5]+512*code[6]+256*code[7]+
						128*code[8]+64*code[9]+32*code[10]+16*code[11]+8*code[12]+4*code[13]+2*
						code[14]+1*code[15];
				break;
				}
				else
				{
					number=8192*(code[2]-1)+4096*(code[3]-1)+2048*(code[4]-1)+1024*(code[5]-1)+512*
						(code[6]-1)+256*(code[7]-1)+128*(code[8]-1)+64*(code[9]-1)+32*(code[10]-1)+
						16*(code[11]-1)+8*(code[12]-1)+4*(code[13]-1)+2*(code[14]-1)+1*(code[15]-1)-1;
				break;
				}
			}
	}
	return number;
}


//*****************************************************************************************************
void functionsClass::FetchAInc(ofstream &out)
{
	//Recieves: output file
	//Task:	executes from control storage
	//Returns:	nothing
	ControlStor(8, out);
	ControlStor(25, out);
	ControlStor(21, out);
	ControlStor(23, out);
	ControlStor(20, out);
	ControlStor(18, out);
	ControlStor(28, out);
	mli++;		//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::add(ofstream &out)
{
	//Recieves: output file
	//Task:	executes from control storage
	//Returns:	nothing
	ControlStor(6, out);
	ControlStor(9, out);
	ControlStor(25, out);
	ControlStor(6, out);
	ControlStor(12, out);
	ControlStor(29, out);
	mli++;		//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::sub(ofstream &out)
{
	//Recieves: output file
	//Task:	executes from control storage
	//Returns:	nothing
	ControlStor(6, out);
	ControlStor(9, out);
	ControlStor(25, out);
	ControlStor(6, out);
	ControlStor(15, out);
	ControlStor(29, out);
	mli++;	//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::load(ofstream &out)
{
	//Recieves: output file
	//Task:	executes from control storage
	//Returns:	nothing
	ControlStor(6, out);
	ControlStor(9, out);
	ControlStor(25, out);
	ControlStor(6, out);
	ControlStor(18, out);
	ControlStor(29, out);
	mli++;		//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::store(ofstream &out)
{
	//Recieves: output file
	//Task:	executes from control storage
	//Returns:	nothing
	ControlStor(6, out);
	ControlStor(9, out);
	ControlStor(1, out);
	ControlStor(26, out);
	ControlStor(29, out);
	mli++;		//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::branch(ofstream &out)
{
	//Recieves: output file
	//Task:	executes from control storage
	//Returns:	nothing
	ControlStor(5, out);
	ControlStor(29, out);
	mli++;		//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::branchOnO(ofstream &out)
{
	//Recieves: output file
	//Task:	executes from control storage
	//Returns:	nothing
	ControlStor(30, out);
	ControlStor(29, out);
	ControlStor(5, out);
	ControlStor(29, out);
	mli++;		//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::dump(ofstream &out)
{
	//Recieves: output file
	//Task:	prints from primary memory and registers
	//Returns:	updates the result file
	for(int i=0; i<101; i++)
	{
		convertH(i);			//runs convert funtion
		for (int i=0; i<4;i++)
			out<<hex[i];		//prints the converted number
		out<<" ";
		if (x%8==0)			//if it is eight in line, takes it to next row
			out<<endl;
		x++;		//adds one to printed values
	}

	convertR(acc1,1);		//converts each part separetly
	convertR(acc2,2);	// 0,1,2 shows which cnvertion to execute
	out<<hex<<" ";
	if (x%8==0)
		out<<endl;
	x++;
	convertR(psiar,0);
	out<<hex<<" ";
	if (x%8==0)
		out<<endl;
	x++;
	convertR(sar,0);
	out<<hex<<" ";
	if (x%8==0)
		out<<endl;
	x++;
	convertR(sdr1,1);
	convertR(sdr2,2);
	out<<hex<<" ";
	if (x%8==0)
		out<<endl;
	x++;
	convertR(tmpr1,1);
	convertR(tmpr2,2);
	out<<hex<<" ";
	if (x%8==0)
		out<<endl;
	x++;
	convertR(csiar,0);
	out<<hex<<" ";
	if (x%8==0)
		out<<endl;
	x++;
	convertR(mir,0);
	out<<hex<<" ";
	if (x%8==0)
		out<<endl;
	x++;				
	mli++;		//adds one to mli
	return;
}


//*****************************************************************************************************
void functionsClass::halt()
{
	//Recieves: nothing
	//Task:	halt
	//Returns:	nothing
	mli++;		//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::branchHL(ofstream &out)
{
	//Recieves: output file
	//Task:	executes from control storage
	//Returns:	nothing
	ControlStor(30, out);
	ControlStor(29, out);
	ControlStor(5, out);
	ControlStor(29, out);
	mli++;				//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::MLO(int op, ofstream &out)
{
	//Recieves: operation code, output file
	//Task:	executes requested function
	//Returns:	nothing
	switch(op)
	{
	case 1:
		add(out);
	break;
	case 2:
		sub(out);
	break;
	case 3:
		load(out);
	break;
	case 4:
		store(out);
	break;
	case 5:
		branch(out);
	break;
	case 6:
		branchOnO(out);
	break;
	case 7:
		dump(out);
	break;
	case 8:
		halt();
	break;
	}
	return;
}


//*****************************************************************************************************
void functionsClass::read()
{
	//Recieves: nothing
	//Task:	executes from control storage
	//Returns:	nothing
	mir=csiar;
	csiar++;
	sdr1=primaryMemory[sar][0];
	sdr2=primaryMemory[sar][1];
	micro++;		//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::write()
{
	//Recieves: nothing
	//Task:	executes from control storage
	//Returns:	nothing
	mir=csiar;
	csiar++;
	primaryMemory[sar][0]=sdr1;
	primaryMemory[sar][1]=sdr2;
	micro++;		//adds one to mli counter
	return;
}


//*****************************************************************************************************
void functionsClass::ControlStor(int OpCode, ofstream &out)
{
	//Recieves: requested operation code ,output file
	//Task:	executes from control storage
	//Returns:	nothing
	switch(OpCode)
	{
	case 0:
		halt();
		micro++;		//adds one to micro counter
	break;
	case 1:
		mir=csiar;
		csiar++;
		sdr1=acc1;
		sdr2=acc2;
		micro++;
	break;
	case 2:
		mir=csiar;
		csiar++;
		sdr1=psiar;
		micro++;
	break;
	case 3:
		mir=csiar;
		csiar++;
		sdr1=tmpr1;
		sdr2=tmpr2;
		micro++;
	break;
	case 4:
		mir=csiar;
		csiar++;
		acc1=sdr1;
		acc2=sdr2;
		micro++;
	break;
	case 5:
		mir=csiar;
		csiar++;
		psiar=sdr2;
		micro++;
	break;
	case 6:
		mir=csiar;
		csiar++;
		tmpr1=sdr1;
		tmpr2=sdr2;
		micro++;
	break;
	case 7:
		mir=csiar;
		csiar++;
		sar=acc1;
		micro++;
	break;
	case 8:
		mir=csiar;
		csiar++;
		sar=psiar;
		micro++;
	break;
	case 9:
		mir=csiar;
		csiar++;
		sar=tmpr2;
		micro++;
	break;
	case 10:
		mir=csiar;
		csiar++;
		acc1+=acc1;
		acc2+=acc2;
		micro++;
	break;
	case 11:
		mir=csiar;
		csiar++;
		acc2+=psiar;
		micro++;
	break;
	case 12:
		mir=csiar;
		csiar++;
		acc2+=tmpr2;
		micro++;
	break;
	case 13:
		mir=csiar;
		csiar++;
		acc1-=acc1;
		acc2-=acc2;
		micro++;
	break;
	case 14:
		mir=csiar;
		csiar++;
		acc2-=psiar;
		micro++;
	break;
	case 15:
		mir=csiar;
		csiar++;
		acc1-=tmpr1;
		acc2-=tmpr2;
		micro++;
	break;
	case 16:
		mir=csiar;
		csiar++;
		acc1=acc1;
		acc2=acc2;
		micro++;
	break;
	case 17:
		mir=csiar;
		csiar++;
		acc2=psiar;
		micro++;
	break;
	case 18:
		mir=csiar;
		csiar;
		acc1=tmpr1;
		acc2=tmpr2;
		micro++;
	break;
	case 19:
		mir=csiar;
		csiar++;
		acc1=acc1;
		acc2=acc2;
		micro++;
	break;
	case 20:
		mir=csiar;
		csiar++;
		psiar=acc2;
		micro++;
	break;
	case 21:
		mir=csiar;
		csiar++;
		tmpr1=acc1;
		tmpr2=acc2;
		micro++;
	break;
	case 22:
		mir=csiar;
		csiar++;
		acc2++;
		micro++;
	break;
	case 23:
		mir=csiar;
		csiar++;
		acc2=psiar+1;
		micro++;
	break;
	case 24:
		acc1=tmpr1+1;
		acc2=tmpr2+1;
		micro++;
	break;
	case 25:
		read();
		micro++;
	break;
	case 26:
		write();
		micro++;
	break;
	case 27:
		mir=csiar;
		csiar++;
		micro++;
	break;
	case 28:
		mir=csiar;		
		if(sdr1=1)		//converts to requested operation
			csiar=10;
		else if (sdr1=2)
			csiar=20;
		else if (sdr1=3)
			csiar=30;
		else if (sdr1=4)
			csiar=40;
		else if (sdr1=5)
			csiar=50;
		else if (sdr1=6)
			csiar=60;
		else if (sdr1=7)
			csiar=70;
		else if (sdr1=8)
			csiar=80;
		micro++;
	break;
	case 29:
		mir=csiar;
		csiar=0;
		micro++;
	break;
	case 30:
		mir=csiar;
		if(acc1==0)
			csiar++;
		micro++;
	break;
	case 31:
		dump(out);
		micro++;
	break;
	case 32:
		mir=csiar;
		micro++;
	break;
	}
	return;
}


//*****************************************************************************************************
void functionsClass::convertH(int num)
{
	//Recieves: decimal number to convert
	//Task:	converts from decimal to hex
	//Returns:	updates hex 
	int reminder;
	if (num<50)		//if it is the first part of data file
	{
		int number=primaryMemory[num][0];	//reads the first part of 8 bits
		if (number==1000 || number==255)	//these are NULL numbers
		{
			hex[0]='F';
			hex[1]='F';
		}
		else
		{
		hex[0]='0';
		if (number==0)
			hex[1]='0';
		else if (number==1)
				hex[1]='1';
		else if (number==2)
				hex[1]='2';
		else if (number==3)
				hex[1]='3';
		else if (number==4)
				hex[1]='4';
		else if (number==5)
				hex[1]='5';
		else if (number==6)
				hex[1]='6';
		else if (number==7)
				hex[1]='7';
		else if (number==8)
				hex[1]='8';
		}

		number=primaryMemory[num][1];		//reads the second part of 8 bits
		if (number==1000|| number==255)
		{
			hex[2]='F';
			hex[3]='F';
		}
		else for (int i=3; i>1; i--)
		{
			int mult=number/16;			
				reminder=number-(mult*16);
				if (reminder==1)
					hex[i]='1';
				else if (reminder==2)
					hex[i]='2';
				else if (reminder==3)
					hex[i]='3';
				else if (reminder==4)
					hex[i]='4';
				else if (reminder==5)
					hex[i]='5';
				else if (reminder==6)
					hex[i]='6';
				else if (reminder==7)
					hex[i]='7';
				else if (reminder==8)
					hex[i]='8';
				else if (reminder==9)
					hex[i]='9';
				else if (reminder==10)
					hex[i]='A';
				else if (reminder==11)
					hex[i]='B';
				else if (reminder==12)
					hex[i]='C';
				else if (reminder==13)
					hex[i]='D';
				else if (reminder==14)
					hex[i]='E';
				else if (reminder==15)
					hex[i]='F';
				else if (reminder==0)
					hex[i]='0';
				number=mult;
		}
	}
	else if (num>=50)		//if it is second part of data file
	{
		int number=primaryMemory[num][1];	//reads the number
		if (number>=0)		//if it is positive
		{
			for (int i=3; i>=0; i--)
			{
				int mult=number/16;
				reminder=number-(mult*16);
					if (reminder==1)
						hex[i]='1';
					else if (reminder==2)
						hex[i]='2';
					else if (reminder==3)
						hex[i]='3';
					else if (reminder==4)
						hex[i]='4';
					else if (reminder==5)
						hex[i]='5';
					else if (reminder==6)
						hex[i]='6';
					else if (reminder==7)
						hex[i]='7';
					else if (reminder==8)
						hex[i]='8';
					else if (reminder==9)
						hex[i]='9';
					else if (reminder==10)
						hex[i]='A';
					else if (reminder==11)
						hex[i]='B';
					else if (reminder==12)
						hex[i]='C';
					else if (reminder==13)
						hex[i]='D';
					else if (reminder==14)
						hex[i]='E';
					else if (reminder==15)
						hex[i]='F';
					else if (reminder==0)
						hex[i]='0';
					number=mult;
			}
		}
		else
		{
				//if it is negative
		}
		{ number=number*(-1);		//make it positive
			for (int i=3; i>=0; i--)
			{
				int mult=number/16;
				reminder=number-(mult*16);
					if (i==3)
						reminder--;
					if (reminder==15)		//reversed numbers
						hex[i]='0';
					else if (reminder==14)
						hex[i]='1';
					else if (reminder==13)
						hex[i]='2';
					else if (reminder==12)
						hex[i]='3';
					else if (reminder==11)
						hex[i]='4';
					else if (reminder==10)
						hex[i]='5';
					else if (reminder==9)
						hex[i]='6';
					else if (reminder==8)
						hex[i]='7';
					else if (reminder==7)
						hex[i]='8';
					else if (reminder==6)
						hex[i]='9';
					else if (reminder==5)
						hex[i]='A';
					else if (reminder==4)
						hex[i]='B';
					else if (reminder==3)
						hex[i]='C';
					else if (reminder==2)
						hex[i]='D';
					else if (reminder==1)
						hex[i]='E';
					else if (reminder==0)
						hex[i]='F';
				number=mult;
			}
		}
	}
	return;
}


//*****************************************************************************************************
void functionsClass::convertR(int num, int part)
{
	//Recieves: number, and what instruction
	//Task:	convert from decimal to hex for counters
	//Returns:	updated hex
	int m, n;
	int reminder;
	if (part==0)	//if it has only one part
	{
		n=3;
		m=0;
	}
	else if (part==1)	//if it  is first part
	{
		n=1;
		m=0;
	}
	else if (part==2)	//if it is second part
	{
		n=3;
		m=2;
	}
	if (num>=0)		//if it is positive
		{
			for (int i=n; i>=m; i--)
			{
				int mult=num/16;
				reminder=num-(mult*16);
					if (reminder==1)
						hex[i]='1';
					else if (reminder==2)
						hex[i]='2';
					else if (reminder==3)
						hex[i]='3';
					else if (reminder==4)
						hex[i]='4';
					else if (reminder==5)
						hex[i]='5';
					else if (reminder==6)
						hex[i]='6';
					else if (reminder==7)
						hex[i]='7';
					else if (reminder==8)
						hex[i]='8';
					else if (reminder==9)
						hex[i]='9';
					else if (reminder==10)
						hex[i]='A';
					else if (reminder==11)
						hex[i]='B';
					else if (reminder==12)
						hex[i]='C';
					else if (reminder==13)
						hex[i]='D';
					else if (reminder==14)
						hex[i]='E';
					else if (reminder==15)
						hex[i]='F';
					else if (reminder==0)
						hex[i]='0';
					num=mult;
			}
		}
		else		//if it is negative
		{ num=num*(-1);	//make it positive
			for (int i=3; i>=0; i--)
			{
				int mult=num/16;
				reminder=num-(mult*16);
					if (i==3)
						reminder--;
					if (reminder==15)		//reverse numbers
						hex[i]='0';
					else if (reminder==14)
						hex[i]='1';
					else if (reminder==13)
						hex[i]='2';
					else if (reminder==12)
						hex[i]='3';
					else if (reminder==11)
						hex[i]='4';
					else if (reminder==10)
						hex[i]='5';
					else if (reminder==9)
						hex[i]='6';
					else if (reminder==8)
						hex[i]='7';
					else if (reminder==7)
						hex[i]='8';
					else if (reminder==6)
						hex[i]='9';
					else if (reminder==5)
						hex[i]='A';
					else if (reminder==4)
						hex[i]='B';
					else if (reminder==3)
						hex[i]='C';
					else if (reminder==2)
						hex[i]='D';
					else if (reminder==1)
						hex[i]='E';
					else if (reminder==0)
						hex[i]='F';
				num=mult;
			}
		}
	return;
}


//*****************************************************************************************************
void functionsClass::readData(ifstream &in)
{
	//Recieves: data file
	//Task:	reads all data in primary memory
	//Returns:	updates primary memory
	char binarycode;	//reads by one character
	int binC[16]={0};	//saves as a bit

	for(int i=0; i<16;i++)	//reads the first line
	{
		in>>ws;					
		in.get(binarycode);	//reads the charecter

		if (binarycode=='0')	//checks if it is 0 or 1
			binC[i]=0;
		else if (binarycode=='1')
			binC[i]=1;
		else
			binC[i]=9;	//if it isnt any of them, like sentinel X
	}

	while (binC[0]!=9)	//checks for the sentinel
	{
		primaryMemory[MLC][0]=convert(0, binC);	//converts first part
		primaryMemory[MLC][1]=convert(1, binC);	//converts second part
		MLC++;
		for(int i=0; i<16;i++)
		{
			in>>ws;
			in.get(binarycode);

			if (binarycode=='0')
				binC[i]=0;
			else if (binarycode=='1')
				binC[i]=1;
			else
				binC[i]=9;
		}
	}

	while(m!=50)		//reads the second part of the file
	{
		for(int i=0; i<16;i++)
		{
			in>>ws;
			in.get(binarycode);

			if (binarycode=='0')
				binC[i]=0;
			else if (binarycode=='1')
				binC[i]=1;
			else
				binC[i]=9;
		}
		primaryMemory[m+50][1]=convert(3,binC);	//converts number
		m++;
	}
	return;
}


//*****************************************************************************************************
int functionsClass::GetPrimaryMemory(int n)
{
	return primaryMemory[n][0];
}


//*****************************************************************************************************
int functionsClass::Getmli()
{
	return mli;
}


//*****************************************************************************************************
int functionsClass::Getmicro()
{
	return micro;
}


//*****************************************************************************************************
int functionsClass::GetX()
{
	return x;
}