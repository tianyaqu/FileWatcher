#ifndef POLLER_H
#define POLLER_H
#include <queue>
#include <poll.h>
#include <string>

class Poller
{
public:
    Poller(struct pollfd* fd,int size,int timeout);
    ~Poller();
    int poll(std::queue<struct inotify_event *>& events);
private:
    void onRead(struct pollfd);
    std::string maskToString(uint32_t mask);
private:
    typedef std::vector<struct pollfd> PollFdList;
    PollFdList fdSet_;
    int timeout_;
};

#endif // POLLER_H
