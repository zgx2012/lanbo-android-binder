#define LOG_TAG "ArithmeticService"
#define LOG_NDEBUG 0

#include <utils/Log.h>
//#include <binder/IServiceManager.h>
//#include <binder/MemoryBase.h>
//#include <binder/MemoryHeapBase.h>
#include "ArithmeticService.h"

namespace android {
ArithmeticService::ArithmeticService()
    : BnArithmeticService()
{
    ALOGI("%s", __FUNCTION__);
}

void ArithmeticService::onFirstRef()
{
    ALOGI("%s", __FUNCTION__);
}

ArithmeticService::~ArithmeticService()
{
    ALOGI("%s", __FUNCTION__);
}

int ArithmeticService::add(int a, int b)
{
    AutoMutex lock(mServiceLock);
    return a + b;
}

int ArithmeticService::sub(int a, int b)
{
    AutoMutex lock(mServiceLock);
    return a - b;
}

int ArithmeticService::mul(int a, int b)
{
    AutoMutex lock(mServiceLock);
    return a * b;
}

int ArithmeticService::div(int a, int b)
{
    AutoMutex lock(mServiceLock);
    if (b == 0) return -1;
    return a / b;
}
// ----------------------------------------------------------------------


status_t BnArithmeticService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case ADD: {
            CHECK_INTERFACE(IArithmeticService, data, reply);
            int a = data.readInt32();
            int b = data.readInt32();
            int result = add(a, b);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        case SUB: {
            CHECK_INTERFACE(IArithmeticService, data, reply);
            int a = data.readInt32();
            int b = data.readInt32();
            int result = sub(a, b);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        case MUL: {
            CHECK_INTERFACE(IArithmeticService, data, reply);
            int a = data.readInt32();
            int b = data.readInt32();
            int result = mul(a, b);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        case DIV: {
            CHECK_INTERFACE(IArithmeticService, data, reply);
            int a = data.readInt32();
            int b = data.readInt32();
            int result = div(a, b);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;


        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}


}; // end namespace android