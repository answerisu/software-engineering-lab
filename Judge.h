#include "manageFile.h"



class Judge:public ManageFile{
	vector<string> inputFormat;   //save the information from stdin_format
	string filename;              //filename
	vector <int> parentJudge;     //for Disjoint set 

public:
	//Judge(char* );
	void init(const char* );      //set file name for reading
	void start();                 //start to run
	void findInput();             //find input according to input format
	void judge();                 //loop to compare program pairs
	void output();                //print to csv according to disjoint set

	void compile();               //compile all the cpp file
	void createInput();           //create a group of input according to inputFormat
	void random(const char* format);//generate a random input
	bool same();                  //judge two output file
	
	void randomstr(int x);        //generate a random string (len is x)
	void randomchar();            //generate a random char()
	void randomint(int x);        //write x to input file
	int find(int num);            //find root index
	void join(int a, int b);      //join to disjoint set
	
};