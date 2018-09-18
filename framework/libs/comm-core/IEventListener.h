#ifndef FRAMEWORKS_IEVENTLISTENER_H
#define FRAMEWORKS_IEVENTLISTENER_H

#include "comm.h"

namespace android {

//extern void (*bpEvent)(int event, Parcel& data, va_list ap);
//extern void (*bnEvent)(int event, const Parcel& data);

class IEventListener : public IInterface
{
public:
    enum {
        ON_EVENT = IBinder::FIRST_CALL_TRANSACTION,
    };
public:
    DECLARE_META_INTERFACE(EventListener);
    // 定义纯虚函数, 定义接口
    virtual void onEvent(int event, const Parcelable* parcelable) = 0;
}; // end IEventListener

class BnEventListener : public BnInterface<IEventListener>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnEventListener

}; // end namespace android

#endif //FRAMEWORKS_IEVENTLISTENER_H
