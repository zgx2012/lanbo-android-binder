#define LOG_TAG "ModuleBService"
#define LOG_NDEBUG 0

#include <utils/Log.h>
//#include <binder/IServiceManager.h>
//#include <binder/MemoryBase.h>
//#include <binder/MemoryHeapBase.h>
#include "ModuleBService.h"

namespace android {
ModuleBService::ModuleBService()
    : BnModuleBService()
{
    ALOGI("%s", __FUNCTION__);
}

void ModuleBService::onFirstRef()
{
    ALOGI("%s", __FUNCTION__);
}

ModuleBService::~ModuleBService()
{
    ALOGI("%s", __FUNCTION__);
}

int ModuleBService::add(int a, int b)
{
    AutoMutex lock(mServiceLock);
    return a + b;
}

// ----------------------------------------------------------------------


status_t BnModuleBService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case ADD: {
            CHECK_INTERFACE(IModuleBService, data, reply);
            int a = data.readInt32();
            int b = data.readInt32();
            int result = add(a, b);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;


        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}


}; // end namespace android