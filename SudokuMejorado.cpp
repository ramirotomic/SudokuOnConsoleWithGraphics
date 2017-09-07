# ifdef _MSC_VER
# define _CRT_SECURE_NO_WARNINGS
# endif

# include <iostream>
# include <fstream>
# include <windows.h>
# include <conio.h>
# include <ctime>
using namespace std;

int wherex();

int wherey();

void welcomeScreen();

void gotoxy(int column, int line);

void copier(int box[][9], int dupliBox[][9]);						 // Keep the difference of numbers at startup and the user entered

void getTime(int & hour, int & min, int & sec);

bool isLegal(int box[][9], int dupliBox[][9], int colorBox[][9]);

void printBox(int box[][9], int duplibox[][9], int colorBox[][9]); // Print the spaces wala box NOT the colour wala

void editBox(char val, int row, int col, int box[][9], int dupliBox[][9]);

void colorPrint(int colorBox[][9], int dupliBox[][9], int presentRow, int presentCol, int toColorRow, int toColorCol);



int main() {

	 int  colorBox[9][9] = { 0 }, box[9][9]  = {

		  { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
		  { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
		  { 0, 9, 8, 0, 0, 0, 0, 6, 0 },

		  { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
		  { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
		  { 7, 0, 0, 0, 2, 0, 0, 0, 6 },

		  { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
		  { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
		  { 0, 0, 0, 0, 8, 0, 0, 7, 9 }
	 },

	 dupliBox[9][9] = {
		  { 1, 1, 0, 0, 1, 0, 0, 0, 0 },
		  { 1, 0, 0, 1, 1, 1, 0, 0, 0 },  //already Presents are 1
		  { 0, 1, 1, 0, 0, 0, 0, 1, 0 },  // entered by user are 0

		  { 1, 0, 0, 0, 1, 0, 0, 0, 1 },
		  { 1, 0, 0, 1, 0, 1, 0, 0, 1 },
		  { 1, 0, 0, 0, 1, 0, 0, 0, 1 },

		  { 0, 1, 0, 0, 0, 0, 1, 1, 0 },
		  { 0, 0, 0, 1, 1, 1, 0, 0, 1 },
		  { 0, 0, 0, 0, 1, 0, 0, 1, 1 }
		  },
		  hour, min, sec;

		  bool yesLegal = true;
		  char ch = 0;
		  char another = 0;
		  int opt = 0;
		  int row = 4;
		  int col = 15;

		  welcomeScreen();

		  getTime(hour, min, sec);
		  cout << "\n\n\t\t\t  Your Starting Time:   " << hour - 13 << ":" << min << ":" << sec;

//		  copier(box, dupliBox
			   cout << "\n\n\n\n\n";
		  yesLegal = isLegal( box, dupliBox,colorBox);

		  printBox(box, dupliBox, colorBox);
		  gotoxy(col, row);



		  while (opt != 27)
		  {
			   opt = _getch();

			   switch (opt)
			   {
			   case 72:
				    /* Code for up arrow handling */
				    if (row > 4)
				    {
						row -= 2;
				    }
				    gotoxy(col, row);
				    break;
			   case 80:
				    /* Code for down arrow handling */
				    if (row <= 18)
				    {
						row += 2;
				    }
				    gotoxy(col, row);
				    break;
			   case 77:
				    /* Code for right arrow handling */
				    if (col <= 57)
				    {
						col += 6;
				    }
				    gotoxy(col, row);
				    break;
			   case 75:
				    /* Code for left arrow handling */
				    if (col > 15)
				    {
						col -= 6;
				    }
				    gotoxy(col, row);
				    break;
			   case 13:
				    another = _getch();;
				    if (isdigit(another))
				    {
						editBox(another, (row / 2) - 2, (col / 6) - 2, box, dupliBox);
						printBox(box, dupliBox, colorBox);
						gotoxy(col, row);
				    }
				    break;
			   case 'C':
				    /* Code for Check*/
				    yesLegal = isLegal(box, dupliBox, colorBox);
				    printBox(box, dupliBox, colorBox);
				    gotoxy(col, row);
				    break;
			   case 'c':
				    /* Code for Check*/
				    yesLegal = isLegal(box, dupliBox, colorBox);
				    printBox(box, dupliBox, colorBox);
				    gotoxy(col, row);
				    break;
			   default:
				    break;
			   }
		  }
		  system("cls");
		  cout << "\n\n\t\t\t    Suck My Dick \n\n";
		  _getch();
}

bool isLegal(int box[][9], int dupliBox[][9], int colorBox[][9])
{
	 /*******************************************(Checking through Rows)*******************************************/


	 int flag = 1, prevI, prevJ;
	 int numOccurance = 0;
	 bool notLegal = true;
	 bool notLegalCopy = true;




	 for (int i = 0; i < 9; i++) // controls row iteration
	 {
		  for (int j = 0; j < 9; j++) // controls times iteration
		  {
			   for (int k = 0; k < 9; k++) // control each cell iteration
			   {
				    if (box[i][k] == flag)
				    {
						numOccurance++;
						if (numOccurance == 1)
						{
							 prevI = i;
							 prevJ = k;
						}
				    }
				    if (numOccurance >= 2 && box[i][k] == flag)
				    {
						notLegal = false;
						notLegalCopy = false;
						colorPrint(colorBox, dupliBox, i, k, prevI, prevJ);
						prevI = i;
						prevJ = k;
				    }
			   }
			   if (numOccurance == 1)
			   {
				    colorBox[prevI][prevJ] = 0;
			   }
			   flag++;
			   numOccurance = 0;
			   notLegalCopy = true;
		  }
		  flag = 1;

	 }

	 /********************************************************************************************************/


	 /*******************************************(For Coloumn Checking)****************************************/

	 flag = 1;

	 for (int i = 0; i < 9; i++) // controls coloumn iteration i = col
	 {
		  for (int j = 0; j < 9; j++) // controls row iteration     j = row
		  {
			   for (int k = 0; k < 9; k++) // control iteration
			   {
				    if (box[k][i] == flag)
				    {
						numOccurance++;
						if (numOccurance == 1)
						{
							 prevI = k;
							 prevJ = i;
						}
				    }
				    if (numOccurance >= 2 && box[k][i] == flag)
				    {
						notLegal = false;
						colorPrint(colorBox, dupliBox, k, i, prevI, prevJ);
						prevI = k;
						prevJ = i;
				    }
			   }
			   flag++;
			   numOccurance = 0;
		  }
		  flag = 1;
	 }



	 /**********************************(Square testing)***********************************/

	 flag = 1;
	 int kOut,
		  limit;
	 for (int times = 0; times < 3; times++) {
		  if (times == 0) {
			   kOut = 0,
				    limit = 3;
		  }
		  if (times == 1) {
			   kOut = 3,
				    limit = 6;
		  }
		  if (times == 2) {
			   kOut = 6,
				    limit = 9;
		  }

		  for (int i = 0; i < 9; i++) // controls row iteration
		  {
			   for (int j = 0; j < 3; j++) // controls times iteration
			   {
				    for (int k = kOut; k < limit; k++) // control each cell iteration
				    {
						if (box[j][k] == flag)
						{
							 numOccurance++;
							 if (numOccurance == 1)
							 {
								  prevI = j;
								  prevJ = k;
							 }
						}
						if (numOccurance >= 2 && box[j][k] == flag)
						{
							 notLegal = false;
							 colorPrint(colorBox, dupliBox, j, k, prevI, prevJ);
							 prevI = j;
							 prevJ = k;
						}
				    }
			   }
			   flag++;
			   numOccurance = 0;
		  }
		  flag = 1;
	 }

	 /***************************************(2nd Rows & Cols)***********************************************/
	 flag = 1;
	 for (int times = 0; times < 3; times++) {
		  if (times == 0) {
			   kOut = 0,
				    limit = 3;
		  }
		  if (times == 1) {
			   kOut = 3,
				    limit = 6;
		  }
		  if (times == 2) {
			   kOut = 6,
				    limit = 9;
		  }

		  for (int i = 0; i < 9; i++) // controls row iteration
		  {
			   for (int j = 3; j < 6; j++) // controls times iteration
			   {
				    for (int k = kOut; k < limit; k++) // control each cell iteration
				    {
						if (box[j][k] == flag) {
							 numOccurance++;
							 if (numOccurance == 1)
							 {
								  prevI = j;
								  prevJ = k;
							 }
						}
						if (numOccurance >= 2 && box[j][k] == flag)
						{
							 notLegal = false;
							 colorPrint(colorBox, dupliBox, j, k, prevI, prevJ);
							 prevI = j;
							 prevJ = k;
						}
				    }
			   }
			   flag++;
			   numOccurance = 0;
		  }
		  flag = 1;
	 }
	 /***************************************(3rd Rows & Cols)***********************************************/
	 flag = 1;
	 for (int times = 0; times < 3; times++) {
		  if (times == 0) {
			   kOut = 0,
				    limit = 3;
		  }
		  if (times == 1) {
			   kOut = 3,
				    limit = 6;
		  }
		  if (times == 2) {
			   kOut = 6,
				    limit = 9;
		  }

		  for (int i = 0; i < 9; i++) // controls row iteration
		  {
			   for (int j = 6; j < 9; j++) // controls times iteration
			   {
				    for (int k = kOut; k < limit; k++) // control each cell iteration
				    {
						if (box[j][k] == flag) {
							 numOccurance++;
							 if (numOccurance == 1)
							 {
								  prevI = j;
								  prevJ = k;
							 }
						}
						if (numOccurance >= 2 && box[j][k] == flag)
						{
							 notLegal = false;
							 colorPrint(colorBox, dupliBox, j, k, prevI, prevJ);
							 prevI = j;
							 prevJ = k;
						}
				    }
			   }
			   flag++;
			   numOccurance = 0;
		  }
		  flag = 1;
	 }
	 /******************************************************************************************/
	 return notLegal;
}

void printBox(int box[][9], int dupliBox[][9], int colorBox[][9]) {
	 system("CLS");

	 HANDLE ConsoleHandle;
	 ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	 cout << "\n\t    (C) Ta' Piola?\t\t\t\t(Esc) No' Re Vimo'\n\n";
	 cout << "\t    +-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	 cout << "\t    |";

	 for (int i = 0; i < 9; i++) {
		  for (int j = 0; j < 9; j++)
		  {
			   if (box[i][j] == 0)
			   {
				    cout << "     |";
			   }
			   else if (dupliBox[i][j] != 0)
			   {
				    cout << "  ";
				    cout << box[i][j];
				    cout << "  |";
			   }
			   else if (colorBox[i][j] != -1)
			   {
				    cout << "  ";
				    SetConsoleTextAttribute(ConsoleHandle, 43);
				    cout << box[i][j];
				    SetConsoleTextAttribute(ConsoleHandle, 46);
				    cout << "  |";

			   }
			   else if (colorBox[i][j] == -1)
			   {
				    cout << "  ";
				    SetConsoleTextAttribute(ConsoleHandle, 44);
				    cout << box[i][j];
				    SetConsoleTextAttribute(ConsoleHandle, 46);
				    cout << "  |";
			   }
		  }
		  cout << "\n" << "\t    +-----";

		  for (int j = 0; j < 8; j++) {
			   cout << "+-----";
		  }
		  cout << "+\n\t    |";
	 }
	 cout << "\b \b";
}

void copier(int box[][9], int dupliBox[][9]) {
	 for (int i = 0; i < 9; i++) {
		  for (int j = 0; j < 9; j++) {
			   if (box[i][j] != 0)
				    dupliBox[i][j] = 1;
			   else
				    dupliBox[i][j] = 0;
		  }
	 }
}

void colorPrint(int colorBox[][9], int dupliBox[][9], int presentRow, int presentCol, int toColorRow, int toColorCol) {
	 if (colorBox[presentRow][presentCol] != -1 && dupliBox[presentRow][presentCol] != 1)
	 {
		  colorBox[presentRow][presentCol] = -1;
	 }
	 if (colorBox[toColorRow][toColorCol] != -1 && dupliBox[toColorRow][toColorCol] != 1)
	 {
		  colorBox[toColorRow][toColorCol] = -1;
	 }
}

void welcomeScreen() {
	 system("color 2C");

	 HANDLE myConsoleHandle;
	 myConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	 SetConsoleTextAttribute(myConsoleHandle, 46);

	 char ch;

	 ifstream fin("Design.txt");

	 if (fin.is_open()) {
		  while (fin.get(ch)) {
			   if (ch == '.')
				    cout << "{";
			   else
				    cout << ch;

			   //	Sleep(10);
		  }
	 }

	 cout << "\n\n\t\t\t  Ehhhh Apreta ENTER para jugar pa' ";

	 ch = 0;
	 while (ch != '\r') {
		  ch = _getch();
	 }

	 system("CLS");

	 ch = 58;
	 cout << "\n\n\t\t\t  DALE QUE EMPIEZA GIL ";
	 while (ch != 48) {
		  cout << --ch;
		  //	Sleep(1000);
		  cout << "\b \b";
	 }



}

void getTime(int & hour, int & min, int & sec) {
	 // current date/time based on current system
	 time_t now = time(0);

	 tm * ltm = localtime(&now);

	 hour = 1 + ltm->tm_hour;
	 min = 1 + ltm->tm_min;
	 sec = 1 + ltm->tm_sec;
}

void editBox(char val, int row, int col, int box[][9], int dupliBox[][9])
{
	 if (dupliBox[row][col] != 1)
	 {
		  box[row][col] = val - 48;
	 }
}

void gotoxy(int column, int line)
{
	 COORD coord;
	 coord.X = column;
	 coord.Y = line;
	 SetConsoleCursorPosition(
		  GetStdHandle(STD_OUTPUT_HANDLE),
		  coord
		  );
}

int wherex()
{
	 CONSOLE_SCREEN_BUFFER_INFO csbi;
	 COORD result;
	 result.X = 0;
	 if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		  return -1;
	 return result.X;
}

int wherey()
{
	 CONSOLE_SCREEN_BUFFER_INFO csbi;
	 COORD result;
	 result.Y = 0;
	 if (!GetConsoleScreenBufferInfo(
		  GetStdHandle(STD_OUTPUT_HANDLE),
		  &csbi
		  ))
		  return -1;
	 return result.Y;
}
