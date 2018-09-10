#define LOG_TAG "BpMonitorService"
//
#define LOG_NDEBUG 0

//#include <utils/Log.h>
#include <utils/Errors.h>

//#include <stdint.h>
//#include <sys/types.h>
//#include <binder/IMemory.h>
#include <binder/Parcel.h>
//#include <binder/IPCThreadState.h>
//#include <binder/IServiceManager.h>

#include <monitor/IMonitorService.h>
#include <monitor/IMonitorCallback.h>
#include <CommonService.h>

namespace android {

class BpMonitorService: public BpInterface<IMonitorService>
{
public:
    BpMonitorService(const sp<IBinder>& impl)
        : BpInterface<IMonitorService>(impl)
    {
    }

    virtual void setValue(int value)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IMonitorService::getInterfaceDescriptor());
        data.writeInt32(value);
        status_t status = remote()->transact(IMonitorService::SET_VALUE, data, &reply);
        if (status != NO_ERROR) {
            return;
        }
        return;
    }

    virtual void setCallback(const sp<IMonitorCallback>& callback)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IMonitorService::getInterfaceDescriptor());
        data.writeStrongBinder(IInterface::asBinder(callback));
        status_t status = remote()->transact(IMonitorService::SET_CALLBACK, data, &reply);
        if (status != NO_ERROR) {
            return;
        }
        return;
    }

}; // end BpMonitorService

IMPLEMENT_META_INTERFACE(MonitorService, MONITOR_SERVICE_DESC);

// ----------------------------------------------------------------------

}; // end namespace android
