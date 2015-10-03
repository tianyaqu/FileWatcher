#ifndef FILEWATCHER_H
#define FILEWATCHER_H
#include <sys/inotify.h>
#include <string>
#include <map>
#include <functional>
#include <thread>

class FileWatcher
{
public:
    FileWatcher();
    ~FileWatcher();
    typedef std::function<void(struct inotify_event*)> CallBack;
    void registerCallBack(CallBack& cb);
    int watch(const std::string& path,u_int32_t mask = IN_ALL_EVENTS);
    int unwatch(const std::string& path);
        void onRead();
private:
    int unwatch(int wd);

    void handle_event(struct inotify_event * event);
private:
    std::map<std::string,int > file_to_wd;
    std::map<int,std::string> wd_to_file;
    int inotifier_fd;
    CallBack cb_;
    std::thread thread_;
};

#endif // FILEWATCHER_H
