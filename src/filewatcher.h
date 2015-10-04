#ifndef FILEWATCHER_H
#define FILEWATCHER_H
#include "notifier.h"
#include <string>
#include <functional>
#include <memory>

class FileWatcher
{
public:
    FileWatcher();
    ~FileWatcher();
    typedef std::function<void(struct inotify_event*)> CallBack;
    void registerCallBack(CallBack& cb);
    int watch(const std::string& path,u_int32_t mask = IN_ALL_EVENTS);
    int unwatch(const std::string& path);
    void loop();
private:
    void handle_event(struct inotify_event * event);
private:
    CallBack cb_;
    std::unique_ptr<Notifier> notifier_;
};

#endif // FILEWATCHER_H
