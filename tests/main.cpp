#include <iostream>
#include "filewatcher.h"
#include <functional>
//using namespace std;

int main()
{
    FileWatcher fs;
    fs.watch("aa");
   typedef std::function<void(std::shared_ptr<struct inotify_event>)> CallBackh;
    CallBackh c  = std::bind(&FileWatcher::print_log,&fs,std::placeholders::_1);
    fs.registerCallBack(c);
    fs.loop();
    return 0;
}

