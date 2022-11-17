#include "Judge.h"

//the folder user provide
class Sys:public ManageFile{
    vector<Judge> s;

public:
    Sys(char* path);
    void start();
    void init();

};
