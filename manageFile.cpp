#include "manageFile.h"
ManageFile::ManageFile(char* path){
    filepath=path;
    size=0;
}
ManageFile::ManageFile(){
    size=0;
}

int ManageFile::getsize(){
    return size;
}

void ManageFile::setpath(string path){
    filepath=path;
}
void ManageFile::getFileName(int con) {
    DIR *pDir;   
    struct dirent *ptr;  
    if (!(pDir = opendir(filepath.c_str()))){
        return;
    }
    while ((ptr = readdir(pDir)) != 0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) {
            if(con==SYSTEM&&ptr->d_type==DT_DIR){//find folder
                subfilename.push_back(ptr->d_name);
                size++;
            }
            else if(con==JUDGE&&strstr(ptr->d_name,".cpp")!=NULL){//find .cpp file
                string name=ptr->d_name;
                int pos=name.find(".cpp");
                if(pos==-1){
                    cout<<"file type error\nplease check function getFileName"<<endl;
                    exit(-1);
                }
                name.erase(pos,4);
                subfilename.push_back(name);
                size++;
            }
        }
    }
    closedir(pDir);
    
}


string ManageFile::runfile(int i,int con){
    if(con==1){//running and print output to output1.txt
        return "./"+filepath +"/"+subfilename[i]+" <"+filepath+"/input.txt>output1.txt";
    }
    else if(con==2){//running and print output to output1.txt
        return "./"+filepath +"/"+subfilename[i]+" <"+filepath+"/input.txt>output2.txt";
    }
    else {//for debugging
        return "./"+filepath +"/"+subfilename[i]+" <"+filepath+"/input.txt";
    }
}
