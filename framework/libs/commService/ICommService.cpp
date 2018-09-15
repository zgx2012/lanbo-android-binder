#include "commService/ICommService.h"
#include "IEventListener.h"

namespace android {

extern void (*bpSendEvent)(int event, Parcel& data, va_list ap) = 0;
extern void (*bnSendEvent)(int event, const Parcel& data) = 0;

class BpCommService: public BpInterface<ICommService>
{
public:
    BpCommService(const sp<IBinder>& impl)
        : BpInterface<ICommService>(impl)
    {
    }

    virtual int sendEvent(const char* from, const char* to, int event)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ICommService::getInterfaceDescriptor());
        data.writeCString(from);
        data.writeCString(to);
        data.writeInt32(event);
        status_t status = remote()->transact(ICommService::SEND_EVENT, data, &reply);
        if (status != NO_ERROR) {
            return RESULT_ERROR;
        }
        return reply.readInt32();
    }

    virtual int addEventListener(const char* name, const sp<IEventListener>& listener, const std::vector<int>& eventVector)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ICommService::getInterfaceDescriptor());
        data.writeCString(name);
        data.writeStrongBinder(IInterface::asBinder(listener));
        data.writeInt32Vector(eventVector);
        status_t status = remote()->transact(ICommService::ADD_EVENT_LISTENER, data, &reply);
        if (status != NO_ERROR) {
            return RESULT_ERROR;
        }
        return reply.readInt32();
    }

}; // end BpCommService

IMPLEMENT_META_INTERFACE(CommService, COMM_SERVICE_DESC);

}; // end namespace android
