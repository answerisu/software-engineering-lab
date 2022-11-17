#include "Judge.h"


void Judge::init(const char* file) {
	this->filename=file;
	filepath="input/"+this->filename;
	setpath(filepath);
		
	getFileName(JUDGE);
	parentJudge.resize(size);
	for(int i=0;i<size;i++){
		parentJudge[i]=i;
	}

	FILE*fp = fopen((filepath+"/input.txt").c_str(), "w");
	fclose(fp);
	fp=fopen("output1.txt","w");
	fclose(fp);
	fp=fopen("output2.txt","w");
	fclose(fp);
}

void Judge::start() {
	findInput();
	judge();
	output();

}


void Judge::findInput() {
	ifstream readfile;
	readfile.open(filepath+"/stdin_format.txt", ios::in);
	string temp;
	int i = 0;
	istringstream is(temp);
	while (getline(readfile,temp)) {
		int pos = temp.find(" ");
		while (pos!=-1) {
			inputFormat.push_back(temp.substr(0,pos));
			temp.erase(0, pos+1);
			pos = temp.find(" ");
		}
		inputFormat.push_back(temp.substr(0, temp.size()));
	}
	readfile.close();
}


void Judge::judge(){
	compile();

	int flag=1;
	for(int i=0;i<size;i++){
		for(int j=i+1;j<size;j++){
			if(find(i)==find(j)){
				continue;
			}
			for(int k=0;k<TEST_NUM;k++){
				createInput();
				system((runfile(i,1)).c_str());
				system((runfile(j,2)).c_str());
				if(!same()){
					flag=0;
					break;
				}
			}
			if(flag==1){
				join(i,j);
			}
			else{
				flag=1;
			}
		}
	}
}

void Judge::compile(){
	for(int i=0;i<size;i++){
		string command="g++ ";
		command+=filepath;
		command+="/";
		command+=subfilename[i];
		command+=".cpp -o ";
		command+=filepath;
		command+="/";
		command+=subfilename[i];
		//cout<<"run the command: "<<command<<endl;
		system(command.c_str());
	}
}


int Judge::find(int num){
	if(parentJudge[num]!=num){
		return find(parentJudge[num]);
	}
	else{
		return num;
	}
}


void Judge::join(int a, int b){
	parentJudge[find(a)]=find(b);

}

bool Judge::same(){
	bool flag=1;
	ifstream readfile1;
	readfile1.open("output1.txt", ios::in);
	string temp1;
	ifstream readfile2;
	readfile2.open("output2.txt", ios::in);
	string temp2;
	while (getline(readfile1, temp1)) {		
		if(!getline(readfile2,temp2)){
			flag=0;
		}
		if(temp1!=temp2){
			flag=0;
		}
	}
	if(getline(readfile2,temp2)){
		flag=0;
	}
	readfile1.close();
	readfile2.close();
	return flag;
}

void Judge::output(){
	FILE*fp1=fopen("output/equal.csv","a");
	FILE*fp2=fopen("output/inequal.csv","a");
	for(int i=0;i<size;i++){
		for(int j=i+1;j<size;j++){
			if(find(i)==find(j)){
				fputs((filepath+"/"+subfilename[i]).c_str(),fp1);
				fputc(',',fp1);
				fputs((filepath+"/"+subfilename[j]).c_str(),fp1);
				fputc('\n',fp1);
			}
			else{
				fputs((filepath+"/"+subfilename[i]).c_str(),fp2);
				fputc(',',fp2);
				fputs((filepath+"/"+subfilename[j]).c_str(),fp2);
				fputc('\n',fp2);
			}
		}
	}
	fclose(fp1);
	fclose(fp2);
	

}


void Judge::createInput(){
	FILE*fp = fopen((filepath+"/input.txt").c_str(), "w");
	if(fp==NULL){
		cout<<"file "<< filename<<" not exist";
		cout<<"file path:"<<filepath+"/input.txt"<<endl;
	}
	fclose(fp);

	for (int i = 0; i < inputFormat.size(); i++) {
		random(inputFormat[i].c_str());
		FILE*fp = fopen((filepath+"/input.txt").c_str(), "a");
		fputs(" ", fp);
		fclose(fp);
	}
}

void Judge::random(const char* format) {
	string f = format;
	int posint = f.find("int");
	int poschar = f.find("char");
	int posstr = f.find("string");
	int posend = f.find(",");
	int a, b;
	if (posstr != -1) {
		a = stoi(f.substr(posstr + 7, posend - posstr - 7));
		b = stoi(f.substr(posend + 1, f.size() - posend - 1));
		int x=rand();
		x = (x % (b - a + 1) + a);
		randomstr(x);
	}
	else if (posint != -1) {
		a = stoi(f.substr(posint + 4, posend - posint - 4));
		b = stoi(f.substr(posend+1, f.size()-posend-1));
		randomint(x);
	}
	else if(poschar != -1) {
		randomchar();
	}
	else {
		cout << "unknown type";
	}
}


void Judge::randomstr(int x) {
	while (x > 0) {
		randomchar();
		x--;
	}
}


void Judge::randomchar() {
	FILE*fp = fopen((filepath+"/input.txt").c_str(), "a");
	if(fp==NULL){
		cout<<"file "<< filename<<" not exist";
		cout<<"file path:"<<filepath+"/input.txt"<<endl;
	}

	int x = rand();
	x %= 52;
	if (x > 25) {
		x += 6;
	}

	char temp = x + 'A';
	fputc(temp, fp);
	fclose(fp);
}


void Judge::randomint(int x) {
	FILE*fp = fopen((filepath+"/input.txt").c_str(), "a");
	if(fp==NULL){
		cout<<"file "<< filename<<" not exist";
		cout<<"file path:"<<filepath+"/input.txt"<<endl;
	}
	fputs(to_string(x).c_str(), fp);
	fclose(fp);
}