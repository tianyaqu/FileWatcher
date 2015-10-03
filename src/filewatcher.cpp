#include <assert.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "filewatcher.h"
#include <iostream>
#include <poll.h>
#define EVENT_SIZE (sizeof (struct inotify_event))
#define EVENT_BUF_LEN (4096 * (EVENT_SIZE + 16))

FileWatcher::FileWatcher()
{
    inotifier_fd = inotify_init();
    assert(inotifier_fd != -1);
    //thread_ = std::thread(&FileWatcher::onRead, this);
}

FileWatcher::~FileWatcher()
{
    ::close(inotifier_fd);
    //thread_.join();
}

int FileWatcher::watch(const std::string &path,u_int32_t mask)
{
    if(file_to_wd.count(path)  > 0)
    {
        return -1;
    }

    int wd = inotify_add_watch(inotifier_fd,path.c_str(),mask);
    if(wd > 0)
    {
        file_to_wd[path] = wd;
        wd_to_file[wd] = path;
    }

    return wd;
}

int FileWatcher::unwatch(int wd)
{
    int ret = inotify_rm_watch(inotifier_fd,wd);
    if(ret >=0 )
    {
        auto x = wd_to_file.find(wd);
        std::string path = "";
        if(x != wd_to_file.end())
        {
            path = x->second;
            wd_to_file.erase(x);
            file_to_wd.erase(path);
        }
    }

    return ret;
}

int FileWatcher::unwatch(const std::string &path)
{
    auto x = file_to_wd.find(path);
    if(x != file_to_wd.end())
    {
        int ret = unwatch(x->second);
        return ret;
    }
    else
    {
        return -1;
    }
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

 std::string maskToString(uint32_t mask) {
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

void FileWatcher::onRead()
{
    std::cout<<"hello\n";
    while(1)
    {
        //sleep(1);
        std::cout<<"ff\n";
        char buffer[EVENT_BUF_LEN];
        char * offset = NULL;
        struct inotify_event* event;
        int len;
        struct pollfd pfd = { inotifier_fd, POLLIN, 0 };
        int ret = poll(&pfd, 1, 1000);  // timeout of 50ms
        if (ret < 0) {
            //fprintf(stderr, "poll failed: %s\n", strerror(errno));
            std::cout<<"err\n";
        } else if (ret == 0) {
            // Timeout with no events, move on.
        } else {
            struct inotify_event event;
            int nbytes = read(inotifier_fd, &event, sizeof(event));
            std::cout<<maskToString(event.mask);
#if 0
        while ((len = ::read(inotifier_fd, buffer, EVENT_BUF_LEN)) > 0)
        {
            std::cout<<"one\n";
            offset = buffer;
            event = (struct inotify_event *) buffer;
            while (((char *) event - buffer) < len)
            {
                int tmp_len = sizeof(struct inotify_event) + event->len;
                event = (struct inotify_event *) (offset + tmp_len);
                offset += tmp_len;
                //if(event->mask & )
                std::cout<<maskToString(event->mask);
            }
        }
#endif
        }
    }
}
