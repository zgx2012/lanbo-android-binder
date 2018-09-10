#ifndef FRAMEWORKS_MONITORSERVICE_H
#define FRAMEWORKS_MONITORSERVICE_H

//#include <utils/RefBase.h>
//#include <binder/IInterface.h>
#include <binder/Parcel.h>
//#include <binder/MemoryDealer.h>
#include <binder/BinderService.h>
//#include <binder/IAppOpsCallback.h>
#include <monitor/IMonitorService.h>
#include "CommonService.h"

namespace android {


class BnMonitorService : public BnInterface<IMonitorService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnMonitorService


class MonitorService :
    public BinderService<MonitorService>,
    public BnMonitorService
{
    friend class BinderService<MonitorService>;

public:

    static char const* getServiceName() { return MONITOR_SERVICE_NAME; }

            MonitorService();
    virtual ~MonitorService();

    // IMonitorService
    virtual void setValue(int value);
    virtual void setCallback(const sp<IMonitorCallback>& callback);

private:

    int mValue;
    sp<IMonitorCallback> mCallback;
    virtual void onFirstRef();
    Mutex mServiceLock;
}; // end class MonitorService

}; // end namespace android

#endif //FRAMEWORKS_MONITORSERVICE_H
