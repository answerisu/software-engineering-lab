#include "system.h"
using namespace std;

int main() {
    //acquire working path
    char path[256];
	getcwd(path,256);
    strcat(path,"/input");    
    
    Sys sys(path);
	sys.start();
    return 0;
}
