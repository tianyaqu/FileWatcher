#include <iostream>
#include "filewatcher.h"

using namespace std;

int main()
{
    FileWatcher fs;
    fs.watch("aa");

    fs.loop();
    return 0;
}

