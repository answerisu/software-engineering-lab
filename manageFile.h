#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>
#include <string>
#include <cstring>        
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
using namespace std;

#define SYSTEM 0
#define JUDGE 1
#define TEST_NUM 10



class ManageFile{
protected:
	vector<string> subfilename;       //name for all subfile needed
	string filepath;                  //path for this folder
	int size;                         //num of subfile

public:
	ManageFile(char* path);           
	ManageFile();

	int getsize();                    //return how many subfile
	void setpath(string path);        //set member filepath
	void getFileName(int con);        //read all the subfile name needed according to the member filepath
	string runfile(int i,int con);    //return the command for file[i] to compile

};


