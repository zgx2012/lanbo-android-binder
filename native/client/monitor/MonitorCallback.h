#ifndef FRAMEWORKS_MONITORSERVICE_H
#define FRAMEWORKS_MONITORSERVICE_H

//#include <utils/RefBase.h>
//#include <binder/IInterface.h>
#include <binder/Parcel.h>
//#include <binder/MemoryDealer.h>
#include <binder/BinderService.h>
//#include <binder/IAppOpsCallback.h>
#include <monitor/IMonitorCallback.h>
#include "CommonService.h"

namespace android {

class MonitorCallback :
    public BnMonitorCallback
{
public:
            MonitorCallback();
    virtual ~MonitorCallback();

    // IMonitorCallback
    virtual void onValueChanged(int value);

private:

    virtual void onFirstRef();
    Mutex mServiceLock;
}; // end class MonitorCallback

}; // end namespace android

#endif //FRAMEWORKS_MONITORSERVICE_H
