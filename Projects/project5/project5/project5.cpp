//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  proj5.cpp                           ASSIGNMENT #:  5                        *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Ivars Akmentins                                               *
//*                                                                                                   *
//*   COURSE #:  CSC 36000                                 DUE DATE:  April 10, 2013                  *
//*   SECTION: 11                                                                                     *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS:  Takes a mathematical expression in INFIX notation converts it to POSTFIX notation,    *
//*				and then evaluate the POSTFIX notation from the expression. The program uses stacks   *
//*				witht the EMPTY, PUSH, POP operations.												  *
//*   USER DEFINED                                                                                    *
//*    MODULES     : Push- Saves structure in stack                                                   *
//*                  POP- Gets the structure from stack                                               *
//*                  Print- prints the information                                                    *
//*                  Operation- does the conversion                                                   *
//*					 evaluate- evaluates two numbers												  *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct NodeType
{
   int data;
   char operation;
   int number;
   NodeType * next;
};

class StackClass 
{  
	public:
	  StackClass(){TopPtr = NULL;}      
	  void Push( NodeType );
	  void Pop (NodeType & );
	  bool IsEmpty()  {return (TopPtr == NULL);}
 	  bool IsFull();
	  void Print(ofstream &);
  	private:
  	  NodeType *TopPtr;
};

void Header (ofstream &);
void Footer (ofstream &);
void Operation(ofstream & ,StackClass &, int, char [30], int &);
int evaluate(char, char);

//***********************    main function   **********************************************************
int main()
{
	NodeType  Item;
	StackClass  Stack, ReverseStack;	
	char i={NULL};				//to sace character
	char function [30]={NULL};	//to save the original function
	int n=0;					//how many elements in array
	int pageline=4;				//pageline counter

	ifstream in;							// Open the appropriate files for input and output
	ofstream out;
	in.open ("stack_in_2010.txt", ios::in);
	out.open ("result5.txt", ios::out);
	Header(out);

	i=in.get();						//reads character
	while (i!='X')					//checks for sentinel
	{
		if (isspace(i))			//if theres new line, do the operation of stack
		{
			for (int i=0; i<n; i++)			//reverses stack to propper way
			{
				ReverseStack.Pop(Item);		//pops reversestack
				Stack.Push(Item);			//saves Item on stack
			}
			Operation (out ,Stack, n, function, pageline);		//calls operation
			out<<endl<<endl;
			i=in.get();			//reads next character
			n=0;				//sets array counter to 0
			pageline=0;			//sets pageline to 0
		}
		else
		{
			if(isdigit(i))		//if character is a digit
			{	
				function[n]=i;	//saves to array
				in.putback (i);	//puts back character on data
				in>>Item.number;	//reads it as an integer
				Item.data=0;		//indicator that it is operand
				ReverseStack.Push(Item);	//puts Item on reverse stack
			}
			else if(!isdigit(i))	//if it is an operation
			{
				function[n]=i;		//saves to array
				Item.operation=i;	//saves it as an char on Item
				Item.data=1;		//indicator that it is operation
				ReverseStack.Push(Item);	//puts Item on reverse stack
			}
			i=in.get();		//reads next character
			n++;		//adds one to array counter
		}
	}
	Footer(out);
	return 0;
}

//********************          Operation             *************************************************
void Operation(ofstream &out, StackClass &charact, int n, char function[30], int &pageline)
{
	//Recieves: output file, stack, array counter, original function and pageline
	//Task:	calls operations to process the data
	//Returns:	updates stacks and prints them
	StackClass  Stack, Stack2, PostFix;	//stacks for operations
	NodeType Item, Item2, Item3;	//Items for operations

	out<<setw(50)<<right<<"CONVERSION DISPLAY"<<endl;
	out<<"Infix Expression"<<setw(33)<<"POSTFIX Expression"<<setw(30)<<"Stack Contents"<<endl;
	out<<setw(80)<<"(Top to Bottom)"<<endl;
	pageline+=4;	//adds number to page line counter

	charact.Print(out);	//prints the first line of stacks
	PostFix.Print(out);
	Stack.Print(out);
	out<<endl;
	pageline++;

	while(!charact.IsEmpty())
	{
		charact.Pop(Item);	//pops the first Item
		if (Item.data==0)		//checks if it is an operand
			PostFix.Push(Item);	//pushes on postfix
		else if(Item.operation=='(')	//if it is (
			Stack.Push(Item);			//pushes on stock
		else if (Item.operation==')')	//if it is )
		{
			Stack.Pop(Item);			//pops item from stack
			while(Item.operation!='(')	//if it is (
			{
				PostFix.Push(Item);			//pushes item on postfix
				Stack.Pop(Item);			//pops item from stack
			}
		}
		else if(Item.operation=='+' || Item.operation=='-'
			|| Item.operation=='*' || Item.operation=='/')		//if item is operation
		{
			if(Stack.IsEmpty())		//if stack is empty
				Stack.Push(Item);		//pushes item on stack
			else 
			{
				while(1)
				{
					Stack.Pop(Item2);	//pops item2 from stack2
					if(evaluate(Item.operation, Item2.operation)==1)
					{						//evaluation
						Stack.Push(Item2);	//pushes item2 and item on stack
						Stack.Push(Item);
						break;		//breaks the infinite loop
					}
					else if(Stack.IsEmpty())	//if empty pushes item2 on postfix
					{
						PostFix.Push(Item2);		//pushes item on stack
						Stack.Push(Item);
						break;					//breaks the infinite loop
					}
					else if(evaluate(Item.operation, Item2.operation)==2)
					{				//pushes item 2 on postfix
						PostFix.Push(Item2);
					}
				}
			}
		}
		if(charact.IsEmpty())	//if infix stack is empty
		{
			while(1)	//pops items from stack and pushes on postfix
			{
				Stack.Pop(Item);
				PostFix.Push(Item);
				if(Stack.IsEmpty())
					break;	//breaks the infinite loop when done
			}
		}

		while(!PostFix.IsEmpty())	//reverses postfix to print it properly
		{
			PostFix.Pop(Item);
			Stack2.Push(Item);
		}
		charact.Print(out);	//prints stacks
		Stack2.Print(out);
		Stack.Print(out);
		while(!Stack2.IsEmpty())	//puts back in corect order
		{
			Stack2.Pop(Item);
			PostFix.Push(Item);
		}
		out<<endl;
		pageline++;
	}

	out<<endl;
	out<<setw(50)<<right<<"EVALUATION DISPLAY"<<endl;
	out<<"POSTFIX Expression"<<setw(60)<<"Stack Contents"<<endl;
	out<<setw(79)<<"(Top to Bottom)"<<endl;
	pageline+=4;

	do		//reverses postfix
	{
		PostFix.Pop(Item);
		Stack.Push(Item);
	}while(!PostFix.IsEmpty());

	
	Stack.Print(out);	//prints stacks
	PostFix.Print(out);
	out<<endl;
	pageline++;

	do
	{
		Stack.Pop(Item);	//pops item from stack
		if(Item.data==0)	//if it is an operand, push on stack2
			Stack2.Push(Item);
		else //if it is an operation
		{
			Stack2.Pop(Item2);	//pops item2 from stack2
			Stack2.Pop(Item3);	//pops item3 from stack2
			if(Item.operation=='*')	//checks what kind of operation it is and executes it
				Item2.number=Item3.number*Item2.number;	//saves result it as Item2
			else if(Item.operation=='/')
				(int) Item2.number=Item3.number/Item2.number;
			else if(Item.operation=='+')
				(int) Item2.number=Item3.number+Item2.number;
			else if(Item.operation=='-')
				Item2.number=Item3.number-Item2.number;
			Stack2.Push(Item2);
		}
		
		Stack.Print(out);	//prints stacks
		
		Stack2.Print(out);
		
		out<<endl;
		pageline++;
	}while(!Stack.IsEmpty());
	Stack2.Pop(Item);	//pops the last item from stack
	
		Stack.Print(out);	//prints stacks
		
		Stack2.Print(out);
		
		out<<endl<<endl;;
		pageline+=2;


	out<<"ORIGINAL EXPRESSION AND THE ANSWER:"<<endl<<endl;;
	for (int i=0; i<n; i++)
		out<<function[i];
	out<<"="<<Item.number;
	out<<endl;
	pageline+=3;

	for (int i=pageline; i<65; i++)
		out<<endl;


return;
}


//********************    Evaluation function         *************************************************
int evaluate(char a, char b)
{
	//Recieves: two characters
	//Task:	evaluates two operations
	//Returns:	integer value
	
	int c,d;
	if (a=='*')
		c=4;
	else if (a=='/')
		c=3;
	else if (a=='+')
		c=2;
	else if (a=='-')
		c=1;

	if (b=='*')
		d=4;
	else if (b=='/')
		d=3;
	else if (b=='+')
		d=2;
	else if (b=='-')
		d=1;
	else if (b=='(')
		d=0;

	if (d<c)
		return 1;
	else return 2;
}


//********************    The Print stack function    *************************************************
void StackClass::Print(ofstream &out)
{
	int line=0;
	if (IsEmpty() )
	{
		out <<setw(25)<<left<< "EMPTY";
		out<<setw(9)<<" ";
		return;
	}
  NodeType *current;

  current = TopPtr;

  while (current != NULL)
  {
	  if(current->data==0)
	  {
		  out<<current->number<<" ";
		  if (current->number<10)
			line+=2;
		  else
			line+=1;
	  }
	  else
	  {
		  out<<current->operation;
		  line++;
	  }
   current = current->next;
  }
  line=34-line;
  for (int i=0; i<line; i++)
	  out<<" ";
  return;
}

//********************    Test if stack is full      **************************************************
bool StackClass::IsFull() 
{
   NodeType  *p;
   p = new NodeType;
   if (p == NULL)
   {
     delete p;
     cout << "Out of Memory. " 
          << endl;
     return true;
   }
   return false;
}


// *******************    The PUSH Function           *************************************************
void StackClass::Push( NodeType  DataIn)
{
   if (IsFull () )
   {
     cout << " Add operation failed! " << endl;
     return;
   }

   NodeType *p ;          // create node for
   p = new NodeType;     // new element

   p -> data = DataIn.data; 
   p ->number= DataIn.number;
   p->operation= DataIn.operation;
   p -> next = TopPtr;
   TopPtr = p;
              
   return;
}


// *******************   The POP Function            **************************************************
void StackClass::Pop( NodeType &DataOut)
{
    NodeType *p ;
    if (IsEmpty() )
	{
      cout << " Stack is empty. " << endl;
      cout << " Delete Operation Failed. " << endl;
      delete p;
      return;
    }		
 	             // Save element in the first node
    DataOut.data = TopPtr->data; 
	DataOut.number= TopPtr->number;
	DataOut.operation= TopPtr->operation;
                // Adjust Stack Top
    p = TopPtr;	  
    TopPtr = TopPtr -> next;

    delete p;
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
   Outfile << setw(20) << "Assignment #5" << endl;
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
