#define LOG_TAG "ModuleCService"
#define LOG_NDEBUG 0

#include <utils/Log.h>
//#include <binder/IServiceManager.h>
//#include <binder/MemoryBase.h>
//#include <binder/MemoryHeapBase.h>
#include "ModuleCService.h"

namespace android {
ModuleCService::ModuleCService()
    : BnModuleCService()
{
    ALOGI("%s", __FUNCTION__);
}

void ModuleCService::onFirstRef()
{
    ALOGI("%s", __FUNCTION__);
}

ModuleCService::~ModuleCService()
{
    ALOGI("%s", __FUNCTION__);
}

int ModuleCService::add(int a, int b)
{
    AutoMutex lock(mServiceLock);
    return a + b;
}

// ----------------------------------------------------------------------


status_t BnModuleCService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case ADD: {
            CHECK_INTERFACE(IModuleCService, data, reply);
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