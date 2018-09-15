#define LOG_TAG "MonitorCallback"
#define LOG_NDEBUG 0

#include <utils/Log.h>
//#include <binder/IServiceManager.h>
//#include <binder/MemoryBase.h>
//#include <binder/MemoryHeapBase.h>
#include "ReturnCallback.h"

namespace android {
ReturnCallback::ReturnCallback()
    : BnReturnCallback()
{
    ALOGI("%s", __FUNCTION__);
}

void ReturnCallback::onFirstRef()
{
    ALOGI("%s", __FUNCTION__);
}

ReturnCallback::~ReturnCallback()
{
    ALOGI("%s", __FUNCTION__);
}

void ReturnCallback::onReturn(int method, ...)
{
    printf("%s, method = %d\n", __FUNCTION__, method);

    va_list ap;
    va_start(ap, method);

    onMethod(ap);

    va_end(ap);
}

void MethodAddCallback::onMethod(va_list ap)
{
    int result = va_arg(ap, int);
    printf("%s, result = %d\n", __FUNCTION__, result);
}

}; // end namespace android