#ifndef NOTIFIER_H
#define NOTIFIER_H
#include <sys/inotify.h>
#include <map>
#include <queue>
#include <memory>
#include <string>
#include "poller.h"

class Notifier
{
public:
    Notifier();
    ~Notifier();
    int add_watch(const std::string& path,u_int32_t mask);
    int rm_watch(const std::string& path);
    void start();
    void stop();
private:
    int rm_watch(int wd);
    void loop();
private:
    std::map<std::string,int > file_to_wd;
    std::map<int,std::string> wd_to_file;
    std::queue<struct inotify_event *> eventQueue_;
    std::unique_ptr<Poller> poller_;
    int inotifier_fd;
    int pipe_fd;
    bool quit_;
};

#endif // NOTIFIER_H
