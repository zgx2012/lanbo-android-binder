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

int CommService::sendEvent(const char* from, const char* to, int event, const Parcelable* parcelable)
{
    printf("%s: %d\n", __FUNCTION__, event);
    AutoMutex lock(mServiceLock);
    QueueEvent::Event e(event, parcelable);
    EventManager.instance().putEvent(e);
    return RESULT_NO_ERROR;
}

int CommService::addEventListener(const char* name, const sp<IEventListener>& listener, const std::vector<int>& eventVector)
{
    AutoMutex lock(mServiceLock);

    // 将listener, name 保存起来
    ListenerManager.instance().addListener(listener, String16(name), eventVector);

    return RESULT_NO_ERROR;
}

int CommService::removeEventListener(const sp<IEventListener>& listener)
{

    AutoMutex lock(mServiceLock);

    ListenerManager.instance().removeListener(listener);

    return RESULT_NO_ERROR;
}

int CommService::dump()
{
    printf("dump\n");
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
            SomeArgs args;
            data.readParcelable(&args);
            int result = sendEvent(name, to, event, &args);
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

        case REMOVE_EVENT_LISTENER: {
            CHECK_INTERFACE(ICommService, data, reply);
            sp<IEventListener> listener = interface_cast<IEventListener>(data.readStrongBinder());
            int result = removeEventListener(listener);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        case DUMP: {
            CHECK_INTERFACE(ICommService, data, reply);
            const char* name = data.readCString();
            int result = dump();
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}


}; // end namespace android