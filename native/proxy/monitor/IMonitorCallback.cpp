#define LOG_TAG "BpMonitorCallback"
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

#include <monitor/IMonitorCallback.h>
#include <CommonService.h>

namespace android {

class BpMonitorCallback: public BpInterface<IMonitorCallback>
{
public:
    BpMonitorCallback(const sp<IBinder>& impl)
        : BpInterface<IMonitorCallback>(impl)
    {
    }

    virtual void onValueChanged(int newValue)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IMonitorCallback::getInterfaceDescriptor());
        data.writeInt32(newValue);
        status_t status = remote()->transact(IMonitorCallback::ON_VALUE_CHANGED, data, &reply);
        if (status != NO_ERROR) {
            return;
        }
        return;
    }

}; // end BpMonitorCallback

IMPLEMENT_META_INTERFACE(MonitorCallback, MONITOR_CALLBACK_DESC);

// ----------------------------------------------------------------------

status_t BnMonitorCallback::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case ON_VALUE_CHANGED: {
            CHECK_INTERFACE(IMonitorCallback, data, reply);
            int value = data.readInt32();
            onValueChanged(value);
            return NO_ERROR;
        } break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

}; // end namespace android
