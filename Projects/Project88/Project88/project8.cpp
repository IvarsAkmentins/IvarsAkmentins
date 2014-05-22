//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Proj8.cpp                           ASSIGNMENT #:  8                        *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Ivars Akmentins                                               *
//*                                                                                                   *
//*   COURSE #:  CSC 36000                                 DUE DATE:  May 15, 2013                    *
//*   SECTION: 11                                                                                     *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS:  Read the Items ID iformation and saves in a threaded tree. Deletes ID and udates the  *
//*				information. Prints full list in separate page and prints information about each      *
//*				function and all the errors.														  *
//*   USER DEFINED                                                                                    *
//*    MODULES     : Insert- reads items and saves in threaded tree                                   *
//*					 Delete- deletes item from threaded tree                                          *
//*                  Print- prints the information                                                    *
//*                  Sold- Updates the On Hand information                                            *
//*                  Ordered- Updates the On Order information                                        *
//*                  Recieved- Updates the On Order and On Hand information                           *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
struct NodePtr {
		 string ID;
		 string name;
		 int OnHand;
		 int OnOrder;
         NodePtr *Lptr;
         NodePtr *Rptr;
		 int  Thread;
       };

class TreeClass {
   public:
	   TreeClass(){Root = NULL;}
       void Insert(ifstream &, NodePtr *,ofstream &, int &);
	   void Delete( NodePtr*, NodePtr *,ofstream &, int &);
	   void Print(NodePtr *, ofstream &, int &);
	   void PrintN(ofstream &, ifstream &, int &);
	   void Sold(ifstream &,ofstream &, int &);
	   void Ordered(ifstream &,ofstream &, int &);
	   void Recieved(ifstream &,ofstream &, int &);
	   void TraverseInOrder(NodePtr *);
	   NodePtr * GetRoot();
   private:
       NodePtr *Root;
};

void Header (ofstream &);
void Footer (ofstream &);

//***********************    main function   **********************************************************
int main()
  {
    char Op;
    TreeClass Tree;
	NodePtr *temp;
	temp = new NodePtr;
	int pagenum=4;

	ifstream in;							// Open the appropriate files for input and output
	ofstream out;
	in.open ("thread_in_2008.txt", ios::in);
	out.open ("result8.txt", ios::out);
	Header(out);

	Op=in.get();						//gets the first operation

     while ( Op!='Q' ) //sentinel is not read 
        {
             switch (Op)
			 {
				case 'I':
					in>>ws;
					in>>temp->ID;
					in>>ws;
					getline(in,temp->name);
					in>>ws;
					in>>temp->OnHand;
					in>>temp->OnOrder;
					Tree.Insert(in, temp,out, pagenum);
				break;
				case 'D':
					in>>ws;
					in>>temp->ID;
					in>>ws;
					getline(in,temp->name);
					Tree.Delete( Tree.GetRoot(),temp,out, pagenum);
				break;
				case 'P':
					in>>ws>>Op;
					if (Op=='E')
					{
						for (int i=pagenum; i<66; i++)
							out<<endl;
						pagenum=0;
						out<<"               JAKE'S HARDWARE INVENTORY REPORT"<<endl;
						out<<" Item"<<setw(14)<<right<<"Item"<<setw(26)<<right<<"Quantity";
						out<<setw(14)<<right<<"Quantity"<<endl;
						out<<"ID Number"<<setw(15)<<right<<"Description"<<setw(20)<<right<<"On Hand";
						out<<setw(15)<<right<<"On Order"<<endl;
						for (int i=0; i<64; i++)
							out<<"-";
						out<<endl;
						pagenum+=4;
						Tree.Print(Tree.GetRoot(), out, pagenum);
						for (int i=pagenum; i<66; i++)
							out<<endl;
						pagenum=0;
					}
					else if (Op=='N')
						Tree.PrintN(out,in, pagenum);
				break;
				case 'S':
					Tree.Sold(in, out, pagenum);
				break;
				case 'O':
					Tree.Ordered(in, out, pagenum);
				break;
				case 'R':
					Tree.Recieved(in, out, pagenum);
				break;
			 }
			 in>>ws;
			 in>>Op;				//gets next operation
         }

	Footer (out);
	in.close();
	out.close();
	return 0;
} 

//*****************************************************************************************************
// CREATION OF AN "IN ORDERED" TREE
void TreeClass::Insert(ifstream & in, NodePtr *temp, ofstream & out, int &pagenum)
{
	NodePtr *update;

                 	// Declare a  flag to indicate the node to be
				// found node is set to false  
   bool found = false ;

				// Set the pointers to start at the root
   update = Root;

				// Search the tree until we find the node to be
				// deleted or until there are no more nodes to 
				// examine
   while ((found == false) && (update != NULL)  && (update->Thread!=1)  )
   {		// Set flag to true if we find the node
      if (temp->ID == update->ID)
	  {
         found = true;
	  }
      else 	// Otherwise keep track of the parent node and move down
			// the appropriate branch of the tree 
	  {
         if (temp->ID < update->ID)
             update = update->Lptr;
         else
             update = update->Rptr;
      }
    }

   if (found == true)
   {
     out << "ERROR- Attempt to insert a duplicate item "<<temp->ID<<" into the database."<< endl;
	 for (int i=0; i<64; i++)
		out<<"-";
	out<<endl;
	pagenum+=2;
	return;
   }


	bool inserted = false;
    NodePtr *newPtr, *CurrPtr;

    newPtr = new NodePtr;
    if (newPtr != NULL) 
	{	
		newPtr->ID=temp->ID;
		newPtr->name=temp->name;
		newPtr->OnHand=temp->OnHand;
		newPtr->OnOrder=temp->OnOrder;
        newPtr->Lptr = NULL;
        newPtr->Rptr = NULL;
        CurrPtr = Root;
        while (inserted == false)
		{ 
		  if (CurrPtr == NULL)
		  { Root = newPtr;
            inserted = true;
		  } 
          else
		  { if (temp->ID < CurrPtr->ID) 
		  {   if (CurrPtr->Lptr != NULL )
			  { CurrPtr = CurrPtr->Lptr;
			  }
              else 
			  { CurrPtr->Lptr = newPtr;
				newPtr->Rptr=CurrPtr;
				newPtr->Thread=1;
                inserted = true;
			  } 
			}
            else
			{
			if ((CurrPtr->Rptr != NULL) && (CurrPtr->Thread!=1))
			  { CurrPtr = CurrPtr->Rptr;
			  }
              else 
			  { 
				 newPtr->Rptr=CurrPtr->Rptr;
				 CurrPtr->Rptr = newPtr;
				 CurrPtr->Thread=0;
				 newPtr->Thread=1;
                 inserted = true;
			  }
			} 
		  }
		}   /* end while */
	}   /* end if */ 
	out<<"Item ID Number "<<temp->ID<<" successfully entered into database."<<endl;
	for (int i=0; i<64; i++)
		out<<"-";
	out<<endl;
	pagenum+=2;
	return;
}    /* end insert */


//*****************************************************************************************************
// CODE FOR DELETING A NODE FROM A TREE

void TreeClass::Delete(NodePtr *sPtr,NodePtr *temp, ofstream & out, int &pagenum)
{
				// Declare required local pointers 
   NodePtr  *delnode, *parnode, *node1,  *node2,  *node3;


                 	// Declare a  flag to indicate the node to be
				// found node is set to false  
   bool found = false ;

				// Set the pointers to start at the root
     delnode = sPtr;
     parnode = NULL; 
	 // Find the node to be deleted


				// Search the tree until we find the node to be
				// deleted or until there are no more nodes to 
				// examine
   while ((found == false) && (delnode != NULL) )
   {		// Set flag to true if we find the node
      if (temp->ID == delnode->ID && temp->name == delnode->name)
	  {
         found = true;
		 break;
	  }
      else 	// Otherwise keep track of the parent node and move down
			// the appropriate branch of the tree 
	  {
         parnode = delnode;
         if (temp->ID < delnode->ID)
             delnode = delnode->Lptr;
         else
             delnode = delnode->Rptr;
      }
    }

   // Delete the node from the tree considering all 5 cases
				// CASE 1 - If the node is not in the list, print
				//          the appropriate feedback message
   if (found == false)
   {
     out << "ERROR- Attempt to delete an item "<<temp->ID<<" not into the database list." << endl;
	 for (int i=0; i<64; i++)
		out<<"-";
	out<<endl;
	pagenum+=2;
	return;
   }
   else
   {
    if (delnode->Lptr == NULL)   
	{
      if(delnode->Rptr == NULL || delnode->Thread ==1)  	// CASE 2 - Node has NO children
	  {
		if (parnode==NULL)
			sPtr=NULL;
		else if (parnode ->Lptr == delnode)
                    parnode->Lptr = NULL;
              else
				  {
					  parnode->Rptr= delnode->Rptr;
					  parnode->Thread = 1;
				  }
			out<<"Item ID Number "<<temp->ID<<" successfully deleted from database."<<endl;
			for (int i=0; i<64; i++)
				out<<"-";
			out<<endl;
			pagenum+=2;
          return;
	  }
      else 					        // CASE 3 - Node has ONE right child 
          if (( delnode->Lptr == NULL ) &&
         (((delnode->Rptr != NULL) || (delnode ->Thread == 0))))
		 {             
			  if (parnode == NULL)  
				   sPtr = delnode->Rptr;
			  else
			    if ( parnode->Lptr == delnode)          // Delete node is a LEFT CHILD
                   parnode  -> Lptr = delnode->Rptr;
				 else  			    // Delete node is a RIGHT CHILD
					  parnode -> Rptr = delnode -> Rptr;
			  out<<"Item ID Number "<<temp->ID<<" successfully deleted from database."<<endl;
			for (int i=0; i<64; i++)
				out<<"-";
			out<<endl;
			pagenum+=2;
			 return;
		 } 
	}
    else 
	{
      if(( delnode->Lptr != NULL )  &&
         (  ( delnode->Rptr == NULL)  ||  (delnode ->Thread == 1)  )  )
  									// CASE 4 - Node has ONE left child    
		{
			if (parnode == NULL) 
			  sPtr = delnode ->Lptr;
			else
			   if (parnode->Lptr == delnode)	// Delete node is a LEFT CHILD
			           parnode->Lptr = delnode -> Lptr;
			    else   	              		// Delete node is a RIGHT CHILD
                     parnode->Rptr = delnode -> Lptr;
             
			 node1 = delnode->Lptr;
			  while ( (node1 -> Rptr != NULL) && (node1 -> Thread !=1))
				    node1 = node1 -> Rptr;
			  node1 -> Rptr  =  delnode-> Rptr;
			  	out<<"Item ID Number "<<temp->ID<<" successfully deleted from database."<<endl;
				for (int i=0; i<64; i++)
					out<<"-";
				out<<endl;
				pagenum+=2;
			  return;
		}

      else 
	  // CASE 5 --- NODE WITH  2 CHILDREN
   if  (    ( delnode->Lptr != NULL ) &&
             ( delnode->Rptr != NULL ) &&  (delnode ->Thread == 0)  )  
		{              			// Find the rightmost child in the left sub-tree off the Delete node
         node1 = delnode;
         node2 = delnode->Lptr;
         node3 = delnode ->Lptr;
         while ((node3 != NULL)  && (node3 ->Thread != 1))
			{ 
       	     node2 = node3;
              node3 = node3->Rptr;
			}
		 //===========================================
		//  Five cases:  	1.  Delete node is a  LEFT CHILD	
		//2.  Delete node is a RIGHT CHILD
		//3.  Left child of delnode has a RIGHT subtree  but no LEFT subtree
		//4.  Left child of delnode has a LEFT subtree  but no RIGHT subtree
		//5.  Left child of delnode has BOTH a LEFT subtree  and a RIGHT subtree
		 if ( parnode == NULL ) 
               sPtr = node2;
         else
              if (parnode->Lptr == delnode)         //  Delete node is a  LEFT CHILD
                  parnode->Lptr = node3;
              else                                                       // Delete node is a RIGHT CHILD
                 parnode->Rptr = node3;
          
          if ( ( node3->Lptr != NULL) && (node2 != node3) )  
		  {
             node2 -> Rptr = node3 -> Lptr; // Left child of delnode has a RIGHT subtree  but no LEFT
             node3 -> Lptr = delnode->Lptr;													//subtree
             node3 -> Rptr = delnode->Rptr;
             node3 -> Thread = 0;
          }

  else if  (node2 == node3)             // Left child of delnode has a LEFT subtree  but no RIGHT subtree  
		{    
             node3 -> Rptr = delnode -> Rptr;
             node3 -> Thread = 0;
		} 
   else if ( node2->Rptr != NULL)   
		{
             node2 -> Rptr = node3 ;         // Left child of delnode has BOTH a LEFT subtree  and
             node2 -> Thread = 1;                        // a RIGHT subtree
             node3 -> Lptr = delnode->Lptr;
             node3 -> Rptr = delnode->Rptr;
             node3->Thread = 0;
		}
	  }
	}
	
	out<<"Item ID Number "<<temp->ID<<" successfully deleted from database."<<endl;
	for (int i=0; i<64; i++)
		out<<"-";
	out<<endl;
	pagenum+=2;
   } /* end else */
   return;
}


//*****************************************************************************************************
void TreeClass::Sold(ifstream & in, ofstream & out, int &pagenum)
{
	string value;
	int num;

                 	// Declare a  flag to indicate the node to be
				// found node is set to false  
   bool found = false ;

	in>>ws;
	in>>value;
	in>>ws;
	in>>num;
				// Search the tree until we find the node to be
				// deleted or until there are no more nodes to 
				// examine
	int  RightThread;
     NodePtr  *CurrPtr;

      CurrPtr = Root;

       while ( CurrPtr ->Lptr != NULL)
               CurrPtr  = CurrPtr->Lptr;

         while (CurrPtr != NULL)
         {
          if (value == CurrPtr->ID)
			 {
			  found = true;
			  break;
			 }
          RightThread = CurrPtr -> Thread;
          CurrPtr = CurrPtr -> Rptr;
          if ( ( CurrPtr != NULL )  && ( RightThread == 0) )
               while ( CurrPtr ->Lptr != NULL)
          CurrPtr = CurrPtr -> Lptr;
		 }

   if (found == false)
   {
     out << "Item "<<value<<" not in database. Data not updated." << endl;
	 for (int i=0; i<64; i++)
		out<<"-";
	 out<<endl;
	 pagenum+=2;
   }
   else
   {
		CurrPtr->OnHand-=num;
		out<<"Quantity on Hand for item "<<value<<" succesfully updated."<<endl;
		for (int i=0; i<64; i++)
			out<<"-";
		out<<endl;
		pagenum+=2;
   }
	return;
}


//*****************************************************************************************************
void TreeClass::Ordered(ifstream &in, ofstream & out, int &pagenum)
{
	string value;
	int num;

                 	// Declare a  flag to indicate the node to be
				// found node is set to false  
   bool found = false ;


   in>>ws;
   in>>value;
   in>>ws;
   in>>num;
				// Search the tree until we find the node to be
				// deleted or until there are no more nodes to 
				// examine
	int  RightThread;
     NodePtr  *CurrPtr;

      CurrPtr = Root;

       while ( CurrPtr ->Lptr != NULL)
               CurrPtr  = CurrPtr->Lptr;

         while (CurrPtr != NULL)
         {
          if (value == CurrPtr->ID)
			{
			  found = true;
			  break;
			}
          RightThread = CurrPtr -> Thread;
          CurrPtr = CurrPtr -> Rptr;
          if ( ( CurrPtr != NULL )  && ( RightThread == 0) )
               while ( CurrPtr ->Lptr != NULL)
          CurrPtr = CurrPtr -> Lptr;
		 }

   if (found == false)
   {
      out << "Item "<<value<<" not in database. Data not updated." << endl;
	 for (int i=0; i<64; i++)
		out<<"-";
	 out<<endl;
	 pagenum+=2;
   }
   else
   {
		CurrPtr->OnOrder+=num;
		out<<"Quantity on Order for item "<<value<<" succesfully updated."<<endl;
		for (int i=0; i<64; i++)
			out<<"-";
		out<<endl;
		pagenum+=2;
   }
	return;
}

//*****************************************************************************************************
void TreeClass::Recieved(ifstream &in, ofstream & out, int &pagenum)
{
	string value;
	int num;
				// Declare required local pointers 

                 	// Declare a  flag to indicate the node to be
				// found node is set to false  
   bool found = false ;

   in>>ws;
   in>>value;
   in>>ws;
   in>>num;
				// Search the tree until we find the node to be
				// deleted or until there are no more nodes to 
				// examine

	int  RightThread;
     NodePtr  *CurrPtr;

      CurrPtr = Root;

       while ( CurrPtr ->Lptr != NULL)
               CurrPtr  = CurrPtr->Lptr;

         while (CurrPtr != NULL)
         {
          if (value == CurrPtr->ID)
			{
			  found = true;
			  break;
			}
          RightThread = CurrPtr -> Thread;
          CurrPtr = CurrPtr -> Rptr;
          if ( ( CurrPtr != NULL )  && ( RightThread == 0) )
               while ( CurrPtr ->Lptr != NULL)
          CurrPtr = CurrPtr -> Lptr;
		 }
   if (found == false)
   {
     out << "Item "<<value<<" not in database. Data not updated." << endl;
	 for (int i=0; i<64; i++)
		out<<"-";
	 out<<endl;
	 pagenum+=2;
   }
   else
   {
		CurrPtr->OnOrder-=num;
		CurrPtr->OnHand+=num;
		out<<"Quantity on Hand and Order for item "<<value<<" succesfully updated."<<endl;
		for (int i=0; i<64; i++)
			out<<"-";
		out<<endl;
		pagenum+=2;
   }
	return;
}


//*****************************************************************************************************
NodePtr * TreeClass::GetRoot()
{
  return Root;
}


//*****************************************************************************************************
void TreeClass::Print(NodePtr *Root, ofstream &out, int &pagenum)
{ 
	int  RightThread;
     NodePtr  *CurrPtr;

      CurrPtr = Root;

       while ( CurrPtr ->Lptr != NULL)
               CurrPtr  = CurrPtr->Lptr;

         while (CurrPtr != NULL)
         {
          out <<CurrPtr->ID<<setw(28)<<CurrPtr->name;
		  out<<setw(10)<<right<<CurrPtr->OnHand<<setw(13)<<right<<CurrPtr->OnOrder<<endl;
		  pagenum++;
          RightThread = CurrPtr -> Thread;
          CurrPtr = CurrPtr -> Rptr;
          if ( ( CurrPtr != NULL )  && ( RightThread == 0) )
               while ( CurrPtr ->Lptr != NULL)
          CurrPtr = CurrPtr -> Lptr;
		 }
  return;
}

//*****************************************************************************************************
void TreeClass::PrintN(ofstream &out, ifstream &in, int &pagenum)
{ 
	string value;
				// Declare required local pointers 

   in>>ws;
   in>>value;
                 	// Declare a  flag to indicate the node to be
				// found node is set to false  
   bool found = false ;

	int  RightThread;
     NodePtr  *CurrPtr;

      CurrPtr = Root;

       while ( CurrPtr ->Lptr != NULL)
               CurrPtr  = CurrPtr->Lptr;

         while (CurrPtr != NULL)
         {
          if (value == CurrPtr->ID)
		  {
			  found = true;
			  break;
		  }
          RightThread = CurrPtr -> Thread;
          CurrPtr = CurrPtr -> Rptr;
          if ( ( CurrPtr != NULL )  && ( RightThread == 0) )
               while ( CurrPtr ->Lptr != NULL)
          CurrPtr = CurrPtr -> Lptr;
		 }

   if (found == false)
   {
     out << "Item "<<value<<" not in database. Print failed" << endl;
	 for (int i=0; i<64; i++)
			out<<"-";
	 out<<endl;
	 pagenum+=2;

   }
   else
   {
	   out<<" Item"<<setw(14)<<right<<"Item"<<setw(26)<<right<<"Quantity"<<setw(14)<<right;
	   out<<"Quantity"<<endl;
	   out<<"ID Number"<<setw(15)<<right<<"Description"<<setw(20)<<right<<"On Hand";
	   out<<setw(15)<<right<<"On Order"<<endl;
	   for (int i=0; i<64; i++)
			out<<"-";
	   out<<endl;
        out <<CurrPtr->ID<<setw(28)<<CurrPtr->name;
		out<<setw(10)<<right<<CurrPtr->OnHand<<setw(13)<<right<<CurrPtr->OnOrder<<endl;
		pagenum+=4;
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
   Outfile << setw(20) << "Assignment #8" << endl;
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