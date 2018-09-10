#define LOG_TAG "MonitorService"
#define LOG_NDEBUG 0

#include <utils/Log.h>
//#include <binder/IServiceManager.h>
//#include <binder/MemoryBase.h>
//#include <binder/MemoryHeapBase.h>
#include "MonitorService.h"

namespace android {
MonitorService::MonitorService()
    : BnMonitorService(), mValue(0), mCallback(0)
{
    ALOGI("%s", __FUNCTION__);
    printf("%s\n", __FUNCTION__);
}

void MonitorService::onFirstRef()
{
    ALOGI("%s", __FUNCTION__);
    printf("%s\n", __FUNCTION__);
}

MonitorService::~MonitorService()
{
    ALOGI("%s", __FUNCTION__);
    printf("%s\n", __FUNCTION__);
}

void MonitorService::setValue(int value)
{
    printf("%s\n", __FUNCTION__);
    AutoMutex lock(mServiceLock);
    mValue = value;
    if (mCallback != NULL) {
        mCallback->onValueChanged(mValue);
    }
}

void MonitorService::setCallback(const sp<IMonitorCallback>& callback)
{
    printf("%s\n", __FUNCTION__);
    AutoMutex lock(mServiceLock);
    mCallback = callback;
}

// ----------------------------------------------------------------------


status_t BnMonitorService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case SET_VALUE: {
            CHECK_INTERFACE(IMonitorService, data, reply);
            int value = data.readInt32();
            setValue(value);
            return NO_ERROR;
        } break;

        case SET_CALLBACK: {
            CHECK_INTERFACE(IMonitorService, data, reply);
            sp<IMonitorCallback> callback = interface_cast<IMonitorCallback>(data.readStrongBinder());
            setCallback(callback);
            return NO_ERROR;
        } break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}


}; // end namespace android