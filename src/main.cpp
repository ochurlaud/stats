#include <fstream>

#include "keyboardlog.h"

class KeyboardLog;

int main()
{   
    std::string statsfilePath("./stats.txt");
    std::ofstream statsfile;
    KeyboardLog kblog;
    MouseLog mouselog;
    kblog.start();
    //mouselog.start();
    //mouselog.join()
    kblog.join();
           
    return 0;
}
