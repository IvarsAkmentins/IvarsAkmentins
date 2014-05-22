#include <fstream>

using namespace std;

class functionsClass
{
	public:
		functionsClass()		// constructor
		{
			acc1=NULL;
			acc2=NULL;
			psiar=0;
			sar=NULL;
			sdr1=NULL;
			sdr2=NULL;
			tmpr1=NULL;
			tmpr2=NULL;
			csiar=0;
			mir=NULL;
			mli=0;
			micro=0;
			MLC=0;
			x=1;
			m=0;
			for (int i=0; i<101; i++)
			{
				primaryMemory[i][0]=1000;
				primaryMemory[i][1]=1000;
			}
		}
		int convert(int, int [16]);	//converts from binary to decimal
		void convertH(int);				//converts from decimal to hex for values
		void convertR(int, int);		//converts from decimal to hex for registers
		void FetchAInc(ofstream &);
		void add(ofstream &);
		void sub(ofstream &);
		void load(ofstream &);
		void store(ofstream &);
		void branch(ofstream &);
		void branchOnO(ofstream &);
		void dump(ofstream &);
		void halt();
		void branchHL(ofstream &);
		void ControlStor(int, ofstream &);	//control storage table
		void read();		//read instruction
		void write();		//write instruction
		void MLO(int, ofstream &); //machine language operation table
		void readData(ifstream &);	//reads data from data file
		int GetMLC() {return MLC;}	//returns counter value for instructions
		int GetPrimaryMemory(int );	//returns primarymemory value
		int Getmli();	//returns machine language instruction counters
		int Getmicro();	//returns micro counter
		int GetX();		//returns printing counter

	private:
		int acc1;
		int acc2;
		int psiar;
		int sar;	//address of the location in PM
		int sdr1;
		int sdr2;
		int tmpr1;
		int tmpr2;
		int csiar;	//next microinstruction
		int mir;	//current microinstruction
		int mli;  //machine language instruction counter
		int micro;	//microcode counter
		char hex[4];	//printing hex number
		int primaryMemory[101][2];	//primary memory
		int MLC;	//used as an counter while reading everything in primary storage
		int x;	//printing counter
		int m;		//counter for data
};

