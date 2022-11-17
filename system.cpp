#include "system.h"
    Sys::Sys(char* path):ManageFile(path){
        
    }

    void Sys::start(){  
        init();
        //run each subfolder
        for (int i=0;i<size;i++) {
            s[i].init(subfilename[i].c_str());
            s[i].start();
		}
    }

    void Sys::init(){
        //init the output folder and csv file first
        system("mkdir output");
        FILE* fp=fopen("output/equal.csv","w");
        fputs("file1,file2\n",fp);
        fclose(fp);
        fp=fopen("output/inequal.csv","w");
        fputs("file1,file2\n",fp);
        fclose(fp);

        //acquire all the subfile needed
        getFileName(SYSTEM);
        //according subfile num
	    s.resize(size);
    }

