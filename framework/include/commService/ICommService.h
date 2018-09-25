#ifndef FRAMEWORKS_ICOMMSERVICE_H
#define FRAMEWORKS_ICOMMSERVICE_H

#include "comm.h"

#define COMM_SERVICE_NAME "native.commService"
#define COMM_SERVICE_DESC "native.ICommService"

namespace android {

extern void (*bpSendEvent)(int event, Parcel& data, va_list ap);
extern void (*bnSendEvent)(int event, const Parcel& data);

class ICommService : public IInterface
{
public:
    enum {
        SEND_EVENT = IBinder::FIRST_CALL_TRANSACTION,
        ADD_EVENT_LISTENER,
        REMOVE_EVENT_LISTENER,
        DUMP_LISTENER,
    };
public:
    DECLARE_META_INTERFACE(CommService);
    // 定义纯虚函数, 定义接口
    virtual int sendEvent(const char* from, const char* to, int event, const Parcelable* parcelable) = 0;
    //virtual int sendEventIZ(int event, int param1, bool param2) = 0;
    //virtual int sendEventII(int event, int param1, int param2) = 0;
    //virtual int sendEventIS(int event, int param1, const char* param2) = 0;
    virtual int addEventListener(const char* name, const sp<IEventListener>& listener, const std::vector<int>& eventVector) = 0;
    virtual int removeEventListener(const sp<IEventListener>& listener) = 0;

    // for debug
    virtual int dumpListener() = 0;
}; // end ICommService

}; // end namespace android

#endif //FRAMEWORKS_ICOMMSERVICE_H
