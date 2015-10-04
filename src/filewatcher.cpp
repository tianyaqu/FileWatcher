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

void FileWatcher::loop()
{
    notifier_->start();
}

 void FileWatcher::registerCallBack(CallBack& cb)
 {
    notifier_->registerCallBack(cb);
 }

 void FileWatcher::print_log(std::shared_ptr<inotify_event> event_ptr)
 {
     std::cout<<maskToString(event_ptr->mask);
 }

 std::string FileWatcher::maskToString(uint32_t mask) {
    std::string maskString = "";

  if(IN_ACCESS & mask)
    maskString.append("IN_ACCESS ");
  if(IN_ATTRIB & mask)
    maskString.append("IN_ATTRIB ");
  if(IN_CLOSE_WRITE & mask)
    maskString.append("IN_CLOSE_WRITE ");
  if(IN_CLOSE_NOWRITE & mask)
    maskString.append("IN_CLOSE_NOWRITE ");
  if(IN_CREATE & mask)
    maskString.append("IN_CREATE ");
  if(IN_DELETE & mask)
    maskString.append("IN_DELETE ");
  if(IN_DELETE_SELF & mask)
    maskString.append("IN_DELETE_SELF ");
  if(IN_MODIFY & mask)
    maskString.append("IN_MODIFY ");
  if(IN_MOVE_SELF & mask)
    maskString.append("IN_MOVE_SELF ");
  if(IN_MOVED_FROM & mask)
    maskString.append("IN_MOVED_FROM ");
  if(IN_MOVED_TO & mask)
    maskString.append("IN_MOVED_TO ");
  if(IN_OPEN & mask)
    maskString.append("IN_OPEN ");
  if(IN_ISDIR & mask)
    maskString.append("IN_ISDIR ");
  if(IN_UNMOUNT & mask)
    maskString.append("IN_UNMOUNT ");
  if(IN_Q_OVERFLOW & mask)
    maskString.append("IN_Q_OVERFLOW ");
  if(IN_CLOSE & mask)
    maskString.append("IN_CLOSE ");
  if(IN_IGNORED & mask)
    maskString.append("IN_IGNORED ");
  if(IN_ONESHOT & mask)
    maskString.append("IN_ONESHOT ");

  return maskString+"\n";
 }
