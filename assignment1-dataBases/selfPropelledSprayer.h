#pragma once
#include <iostream>
#include<fstream>
#include <chrono>//for timing executions
#include<sstream>
#include<stdio.h>
#include <cstdlib>
#include <iomanip>
#include <string>

#define NUMOFCHOICES 5
#define MAXIFUEL 350
#define MAXIPRODUCT 1200
#define MAXFIELDID 255
#define NUMOFSPSID 5
#define NUMOFPRODUCTID 3
#define NUMOFCHOICES 5


using namespace std::chrono;
using namespace std;

class Sps 
	// self propelled sprayer sold by the company 
{
	string SPSID;
	int FieldID;
	int IFuel;
	int Iproduct;
	string productID;

public:
	
	Sps();
	Sps(string SPSID, int fieldID, int IFuel, int Iproduct, string productID);
	friend ofstream& operator <<(ofstream& fout, Sps& newsps);
	friend ifstream& operator >>(ifstream& foin, Sps& newsps);
};
int displayMenu();

void removesps(string,string);

Sps insertsps(string SPSID, int fieldID, int IFuel, int Iproduct, string productID);

void InsertionExecutionTime(string,Sps);

string* GetSPSIDValues();

string* getProductIDValues();

void findsps(string, string);

void randomSps(string ,int);