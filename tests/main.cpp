#include <iostream>
#include "filewatcher.h"
using namespace std;

int main()
{
    FileWatcher fs;
    fs.watch("aa");
    fs.onRead();
    return 0;
}

