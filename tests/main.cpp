#include <iostream>
#include "filewatcher.h"
#include <functional>
//using namespace std;

int main()
{
    FileWatcher fs;
    fs.watch(".");
   typedef std::function<void(std::shared_ptr<WEvent>)> CallBackh;
    CallBackh c  = std::bind(&FileWatcher::print_log,&fs,std::placeholders::_1);
    fs.registerCreateCallBack(c);
    fs.loop();
    return 0;
}

