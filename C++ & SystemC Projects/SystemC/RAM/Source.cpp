#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
using namespace std;

void filetest()
{
	char data[100]; // buffer to store a line read from file
	char b[10];
	string x="6C";
	int a;
	ifstream ifile; // declaring an object of class ifstream
	ifile.open("C:\\Kannan\\T1.txt"); // open "file.txt" for reading
	cout << "Reading data from a file :-" << endl << endl;
	while (!ifile.eof()) { // while the end of file [ eof() ] is not reached 
		ifile.getline(data, 100); // read a line from file
		ifile >> a;
		ifile >> b;
		int c = *((int*)b);
		//int y = isstring(x);
		//int x = (int)(*a);
		
		cout <<"A : "<< a << "\t B : " <<c  <<endl; // print the file to console
	}
	ifile.close(); // close the file
}