#ifndef WEVENT_H
#define WEVENT_H
#include <string>

class WEvent
{
public:
    WEvent(int wd,u_int32_t mask);
    ~WEvent();
    uint32_t getMask() const;
    void setMask(const uint32_t &value);

    int wd() const;
    void setWd(int wd);

private:
    int wd_;		/* Watch descriptor.  */
    uint32_t mask_;	/* Watch mask.  */
    uint32_t cookie_;	/* Cookie to synchronize two events.  */
    std::string path_;
    std::string name_;
};

#endif // WEVENT_H
