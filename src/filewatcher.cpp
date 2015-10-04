#include <assert.h>

#include "filewatcher.h"
#include <iostream>


FileWatcher::FileWatcher():notifier_(new Notifier)
{
}

FileWatcher::~FileWatcher()
{
}

int FileWatcher::watch(const std::string &path,u_int32_t mask)
{
    return notifier_->add_watch(path,mask);
}

int FileWatcher::unwatch(const std::string &path)
{
    return notifier_->rm_watch(path);
}

void FileWatcher::registerCallBack(CallBack &cb)
{
    cb_ = cb;
}

void FileWatcher::handle_event(inotify_event *event)
{
    if(cb_)
    {
        cb_(event);
    }
}

void FileWatcher::loop()
{
    notifier_->start();
}
