#ifndef FRAMEWORKS_IRETURNCALLBACK_H
#define FRAMEWORKS_IRETURNCALLBACK_H

#include "comm.h"

namespace android {

//extern void (*bpReturnMethod)(int method, Parcel& data, va_list ap);
//extern void (*bnReturnMethod)(int method, const Parcel& data);

class IReturnCallback : public IInterface
{
public:
    enum {
        ON_RETURN = IBinder::FIRST_CALL_TRANSACTION,
    };
public:
    DECLARE_META_INTERFACE(ReturnCallback);
    // 定义纯虚函数, 定义接口
    virtual void onReturn(int method, int result) = 0;
}; // end IReturnCallback

class BnReturnCallback : public BnInterface<IReturnCallback>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnReturnCallback

}; // end namespace android

#endif //FRAMEWORKS_IRETURNCALLBACK_H
