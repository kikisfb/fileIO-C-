#include "selfPropelledSprayer.h"



int displayMenu()
{
	//place holders for insertion
	string spsid;
	string productid;
	int fieldid;
	int ifuel;
	int iproduct;
	int choice;
	Sps newsps;
	int numofrandominserts;

	string* spsids = GetSPSIDValues();// the values for sps id values given which is read from a text file
	
	string* productids = getProductIDValues();// the values for product id values given which is read from a text file
	
	string fileName = "DataFile.txt";
	
	
	cout <<"Please choose one of these options\n1. Insert a new sprayer\n2. Remove an existing sprayer\n3. Find a sprayer\n4. Random sprayer insert\n5. Quit" << endl;
	cin >> choice;

	switch (choice)
	{
		
	case 1:
		
		cout << "what is the SPS ID" << endl;
		cin >> spsid;
		for (int i=0; i < NUMOFSPSID; i++)
		{
			if (spsid == spsids[i]) {//check if the sps id given is found in the ones in the text file
				
				cout << "SPS ID found in " << i + 1 << "th SPS id value" << endl;
				cout << "what is the product ID" << endl;
				cin >> productid;
				for (int i = 0; i < NUMOFPRODUCTID; i++) {
					
					if (productid == productids[i])//check if the product id given is found in the ones in the text file
					{
						cout << "Product ID found in " << i + 1 << "th product id value" << endl;
						cout << "what is field ID" << endl;
						cin >> fieldid;
						if (fieldid > MAXFIELDID||fieldid<1) {// check to see if the field id is in the range asked for
							cout << "the field ID can not be more than" << MAXFIELDID << "or less than 1"<< endl;
								break;
						}
						else {
							cout << "what is the ifuel" << endl;
							cin >> ifuel;
							if (ifuel > MAXIFUEL||ifuel<1) {// check to see if the ifuel is in the range asked for
								cout << "the ifuel can not be more than"<<MAXIFUEL<< "litres or less than a litre " << endl;
								break;
							}
							else {
								cout << "what is the iproduct" << endl;
								cin >> iproduct;
								if (iproduct > MAXIPRODUCT||iproduct<1) {// check to see if the iproduct is in the range asked for
									cout << "The iproduct can not be more than"<<MAXIPRODUCT<< "litres or less than a litre" << endl;
									break;
								}
								else {
									
									newsps = insertsps(spsid, fieldid, ifuel, iproduct, productid);
									
									InsertionExecutionTime(fileName, newsps);
								}
							}
						}
					}
				}
			}
		}
		
		break;

	case 2:
		cout << "what is the SPS ID" << endl;
		cin >> spsid;
		removesps(fileName,spsid);

		break;

	case 3:
		cout << "what is the SPS ID" << endl;
		cin >> spsid;
		findsps(fileName, spsid);
		break;

	case 4:
		cout << "How many random inserts?" << endl;
		cin >> numofrandominserts;
		
		randomSps(fileName, numofrandominserts);
		
		break;

	case 5:
		cout << "SAD TO SEE YOU GO TT" << endl;
		exit(1);
		break;

	default:
		cout << "Your answer is invalid" << endl;
		exit(1);

	}
	return choice;
};

Sps::Sps() {
	string SPSID = "";
	int fieldID = 0;
	int IFuel = 0;
	int Iproduct = 0;
	string productID = "";
};
Sps::Sps(string SPSID, int fieldID, int IFuel, int Iproduct, string productID) {

	this->SPSID = SPSID;
	this->FieldID = fieldID;
	this->IFuel = IFuel;
	this->Iproduct = Iproduct;
	this->productID = productID;
};
ofstream& operator <<(ofstream& fout, Sps& newsps) {
	fout << newsps.SPSID << endl;
	fout << newsps.FieldID << endl;
	fout << newsps.IFuel << endl;
	fout << newsps.Iproduct << endl;
	fout << newsps.productID << endl;
	return fout;
}
ifstream& operator >>(ifstream& fin, Sps& newsps) {
	fin >> newsps.SPSID;
	fin >> newsps.FieldID;
	fin >> newsps.IFuel;
	fin >> newsps.Iproduct;
	fin >> newsps.Iproduct;
	fin >> newsps.productID;
	return fin;
}

/*
The removesps fucntion removes a sps information from the data file
while timing the execution
It opens a template file to delete the matched sps ids and the four line after it because there are five total information
sections for each sprayer
*/
void removesps(string fileName,string spsId) {
	int foundLineNum=0;
	int lineNum = 0;
	int numofdeletes = 0;
	auto t1 = chrono::system_clock::now();
	ofstream temp;
	ifstream fin;
	fin.open(fileName);
	temp.open("temp.txt");
	if (fin.is_open()) {

		while (!fin.eof()) {
			lineNum++;
			string line;
			getline(fin, line);
			if (lineNum != foundLineNum) {//if the matched sps id is found then do not add the next four lines to the temp file
				if (lineNum != foundLineNum + 1) {
					if (lineNum != foundLineNum + 2) {
						if (lineNum != foundLineNum + 3) {
							if (lineNum != foundLineNum + 4) {

								if (line != spsId) {
									temp << line << endl;

								}
								else {
									foundLineNum = lineNum;
									numofdeletes++;
								}
									


							}
							else
								foundLineNum = 0;
						}
					}
			}
			
		}	
			
	}
		cout << "The record with the sps id " << spsId << " was found "<<numofdeletes<<" times and have been deleted" << endl;
		fin.close();
		temp.close();
		remove("DataFile.txt");
		rename("temp.txt", "DataFile.txt");
		
	}
	else {
		cout << "I can not open this file: " << fileName << endl;

	}
	auto t2 = chrono::system_clock::now();
	auto duration = chrono::duration_cast<milliseconds>(t2 - t1);
	cout << "the remove execution time was " << duration.count() << " ms" << endl;
}
/*
The findsps function goes through every line of the data file text file 
and looks for a spcific sps id and it returns found if it finds the match 
and returns not found if it does not find any match.
It also returns the execution time for this function
*/
void findsps(string filename, string spsId) {
	int found = 0;
	int howManyMatch = 0;
	auto t1 = chrono::system_clock::now();
	ifstream fin;
	fin.open(filename);
	if (fin.is_open()) {

		while (!fin.eof()) {
			string line;
			getline(fin, line);
			if (line == spsId) {
				howManyMatch++;
				found = 1;
			}
		}
		if (found == 1)
		{
			cout << "sprayer found successfully "<< howManyMatch<<" times!" << endl;
		}
		else
			cout << "sprayer is not found!" << endl;
		fin.close();
	}
	else {
		cout << "I can not open this file: " << filename << endl;

	}
	auto t2 = chrono::system_clock::now();
	auto duration = chrono::duration_cast<milliseconds>(t2 - t1);
	cout << "the finding execution time was " << duration.count() << " ms" << endl;
}

/*
This fuction writes the new sps added to a file called data file and 
records the long the execution took 
*/
void InsertionExecutionTime(string filename, Sps newsps) {
	
	auto t1 = chrono::system_clock::now();
	ofstream fout;
	fout.open(filename,ios_base::app);//open in appand mode to add the new sprayer to the end of the file
	
	if (fout.is_open()) {
		fout << newsps;
		
		cout << "Sprayer has succesfully been added to the file"<<endl;
		fout.close();
	}
	else
		cout << "could not insert to file\n please try again" << endl;
	auto t2 = chrono::system_clock::now();


	auto duration = chrono::duration_cast<milliseconds>(t2 - t1);
	cout << "the insert execution time was " << duration.count() << " ms" << endl;
}

Sps insertsps(string SPSID, int fieldID, int IFuel, int Iproduct, string productID) {
	Sps newsps(SPSID, fieldID, IFuel, Iproduct, productID);
	return newsps;
}
/*
this function returns a string array of pointers to the sps ids read from spsid text file

*/
string* GetSPSIDValues() {
	string spsidFile = "SPSID.txt";
	string*  spsId=new string[10];
	int i = 0;
	ifstream fin;
	fin.open(spsidFile);
	if (fin.is_open()) {
		
		while (!fin.eof()) {
			string line;
			getline(fin, line);
			spsId[i] = line;
			i++;
			}
		
		fin.close();
	}
	else {
		cout << "I can not open this file: " << spsidFile << endl;

	}
	return spsId;
}
/*
this function returns a string array of pointers to the product ids read from sproductid text file

*/
string* getProductIDValues() {
	string productidFile = "productID.txt";
	string* productId = new string[10];
	int i = 0;
	ifstream fin;
	fin.open(productidFile);
	if (fin.is_open()) {

		while (!fin.eof()) {
			string line;
			getline(fin, line);
			productId[i] = line;
			i++;
		}

		fin.close();
	}
	else {
		cout << "I can not open this file: " << productidFile << endl;

	}
	return productId;
}
/*
this function uses the rand function to generate a random sprayer and add it to the data file text file
*/
void randomSps(string filename, int numofrepetitions) {
	
	string* spsids = GetSPSIDValues();

	string* productids = getProductIDValues();
	
	auto t1 = chrono::system_clock::now();
	for (int i = 0; i < numofrepetitions; i++) {
		int spsidRand = (rand() % NUMOFSPSID);
		int productidRand = (rand() % NUMOFPRODUCTID);
		int fieldidRand = (rand() % MAXFIELDID) + 1;
		int ifuelRand = (rand() % MAXIFUEL) + 1;
		int iproductRand = (rand() % MAXIPRODUCT) + 1;

		Sps newsps(spsids[spsidRand], fieldidRand, ifuelRand, iproductRand, productids[productidRand]);
		InsertionExecutionTime(filename, newsps);
	}
	auto t2 = chrono::system_clock::now();
	auto duration = chrono::duration_cast<milliseconds>(t2 - t1);
	cout << "the random insert execution time was " << duration.count() << " ms" << endl;
	
}