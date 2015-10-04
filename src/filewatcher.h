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
    int watch(const std::string& path,u_int32_t mask = IN_ALL_EVENTS);
    int unwatch(const std::string& path);

    typedef std::function<void(std::shared_ptr<struct inotify_event>)> CallBack;
    void registerCallBack(CallBack& cb);

    std::string maskToString(uint32_t mask);
    void print_log(std::shared_ptr<struct inotify_event>);
    void loop();
private:
    std::unique_ptr<Notifier> notifier_;
};

#endif // FILEWATCHER_H
