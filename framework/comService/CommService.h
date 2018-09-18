#ifndef FRAMEWORKS_COMMSERVICE_H
#define FRAMEWORKS_COMMSERVICE_H

#include <binder/Parcel.h>
#include <binder/BinderService.h>
#include <commService/ICommService.h>
#include "IEventListener.h"
#include "CommonService.h"

namespace android {

class BnCommService : public BnInterface<ICommService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnCommService


class CommService :
    public BinderService<CommService>,
    public BnCommService
{
    friend class BinderService<CommService>;

public:

    static char const* getServiceName() { return COMM_SERVICE_NAME; }

    CommService() : BnCommService(){}
    ~CommService(){};

    // ICommService
    int sendEvent(const char* from, const char* to, int event);
    int sendEventI(const char* from, const char* to, int event, int p1);
    int sendEventII(const char* from, const char* to, int event, int p1, int p2);
    int sendEventIB(const char* from, const char* to, int event, int p1, bool p2);
    int sendEventIS(const char* from, const char* to, int event, int p1, String16& p2);
    int sendEventB(const char* from, const char* to, int event, bool p1);
    int sendEventBB(const char* from, const char* to, int event, bool p1, bool p2);
    int sendEventBS(const char* from, const char* to, int event, bool p1, String16& p2);
    int sendEventS(const char* from, const char* to, int event, String16& p2);
    int addEventListener(const char* name, const sp<IEventListener>& listener, const std::vector<int>& eventVector);

private:

    int mValue;
    //virtual void onFirstRef();
    Mutex mServiceLock;
}; // end class CommService

}; // end namespace android

#endif //FRAMEWORKS_COMMSERVICE_H
