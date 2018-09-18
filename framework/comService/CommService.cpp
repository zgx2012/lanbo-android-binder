#define LOG_TAG "CommService"
#define LOG_NDEBUG 0

#include <utils/Log.h>
#include <time.h>
#include <cutils/threads.h>
//#include <binder/IServiceManager.h>
//#include <binder/MemoryBase.h>
//#include <binder/MemoryHeapBase.h>
#include "IReturnCallback.h"
#include "communication/Communication.h"
#include "CommService.h"

namespace android {

int CommService::sendEvent(const char* from, const char* to, int event)
{
    printf("%s: %d\n", __FUNCTION__, event);
    AutoMutex lock(mServiceLock);
    //
    return RESULT_NO_ERROR;
}

int CommService::sendEvent(const char* from, const char* to, int event, const Parcelable* parcelable)
{
    printf("%s: %d\n", __FUNCTION__, event);
    AutoMutex lock(mServiceLock);
    //
    return RESULT_NO_ERROR;
}

int CommService::addEventListener(const char* name, const sp<IEventListener>& listener, const std::vector<int>& eventVector)
{
    AutoMutex lock(mServiceLock);

    // TODO 将listener, name 保存起来

    return RESULT_NO_ERROR;
}

// ----------------------------------------------------------------------

status_t BnCommService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case SEND_EVENT: {
            CHECK_INTERFACE(ICommService, data, reply);
            const char* name = data.readCString();
            const char* to = data.readCString();
            int event = data.readInt32();
            int result = sendEvent(name, to, event);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        case ADD_EVENT_LISTENER: {
            CHECK_INTERFACE(ICommService, data, reply);
            const char* name = data.readCString();
            sp<IEventListener> listener = interface_cast<IEventListener>(data.readStrongBinder());
            std::vector<int> eventVector;
            data.readInt32Vector(&eventVector);
            int result = addEventListener(name, listener, eventVector);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}


}; // end namespace android