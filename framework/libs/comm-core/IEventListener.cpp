#include "IEventListener.h"
//#include "CommonService.h"

namespace android {

extern void (*bpEvent)(int event, Parcel& data, va_list ap) = 0;
extern void (*bnEvent)(int event, const Parcel& data) = 0;

class BpEventListener: public BpInterface<IEventListener>
{
public:
    BpEventListener(const sp<IBinder>& impl)
        : BpInterface<IEventListener>(impl)
    {
    }

    virtual void onEvent(int event, ...)
    {
        printf("%s, event %d\n", __FUNCTION__, event);
        Parcel data, reply;
        data.writeInterfaceToken(IEventListener::getInterfaceDescriptor());
        data.writeInt32(event);

        va_list ap;
        va_start(ap, event);

        if (bpEvent != 0) {
            bpEvent(event, data, ap);
        }

        va_end(ap);

        status_t status = remote()->transact(IEventListener::ON_EVENT, data, &reply);
        if (status != NO_ERROR) {
            return;
        }
        return;
    }
}; // end BpEventListener

IMPLEMENT_META_INTERFACE(EventListener, EVENT_LISTENER_DESC);

// ----------------------------------------------------------------------

status_t BnEventListener::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case ON_EVENT: {
            CHECK_INTERFACE(IEventListener, data, reply);
            int event = data.readInt32();
            if (bnEvent != 0) {
                bnEvent(event, data);
            }
            return NO_ERROR;
        } break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

}; // end namespace android
