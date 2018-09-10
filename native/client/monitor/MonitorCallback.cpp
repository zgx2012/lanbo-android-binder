#define LOG_TAG "MonitorCallback"
#define LOG_NDEBUG 0

#include <utils/Log.h>
//#include <binder/IServiceManager.h>
//#include <binder/MemoryBase.h>
//#include <binder/MemoryHeapBase.h>
#include "MonitorCallback.h"

namespace android {
MonitorCallback::MonitorCallback()
    : BnMonitorCallback()
{
    ALOGI("%s", __FUNCTION__);
}

void MonitorCallback::onFirstRef()
{
    ALOGI("%s", __FUNCTION__);
}

MonitorCallback::~MonitorCallback()
{
    ALOGI("%s", __FUNCTION__);
}

void MonitorCallback::onValueChanged(int value)
{
    printf("%s, value = %d\n", __FUNCTION__, value);
    AutoMutex lock(mServiceLock);
    ALOGI("%s, value = %d", __FUNCTION__, value);
}

}; // end namespace android