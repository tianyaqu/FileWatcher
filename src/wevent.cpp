#include "wevent.h"

WEvent::WEvent(int wd,u_int32_t mask):wd_(wd),mask_(mask)
{

}

WEvent::~WEvent()
{

}
uint32_t WEvent::getMask() const
{
    return mask_;
}

void WEvent::setMask(const uint32_t &value)
{
    mask_ = value;
}
int WEvent::wd() const
{
    return wd_;
}

void WEvent::setWd(int wd)
{
    wd_ = wd;
}



