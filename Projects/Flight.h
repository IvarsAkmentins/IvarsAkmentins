#include <fstream>
using namespace std;

class FlightClass
{
	public:
			void GBoardNum(ifstream &in);
			void GFlightNum(ifstream &in);
			void GSection(ifstream &in);
			void GRow(ifstream &in);
			void GColumn(ifstream &in);
			void Print (ofstream &out);
			void Loop(int [][9][2],int, int, int, int, int, int, int);
			int GetBoardNum();
			int GetFlightNum();
			char GetSection();
			int GetRow();
			char GetColumn();
	private:
			int BoardNum;
			int FlightNum;
			char Section;
			int Row;
			char Column;
};

