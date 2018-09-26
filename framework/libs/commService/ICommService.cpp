#include "commService/ICommService.h"
#include "IEventListener.h"

namespace android {

class BpCommService: public BpInterface<ICommService>
{
public:
    BpCommService(const sp<IBinder>& impl)
        : BpInterface<ICommService>(impl)
    {
    }

    virtual int sendEvent(const char* from, const char* to, int event, const Parcelable* parcelable)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ICommService::getInterfaceDescriptor());
        data.writeCString(from);
        data.writeCString(to);
        data.writeInt32(event);
        data.writeParcelable(*parcelable);
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

    virtual int removeEventListener(const sp<IEventListener>& listener)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ICommService::getInterfaceDescriptor());
        data.writeStrongBinder(IInterface::asBinder(listener));
        status_t status = remote()->transact(ICommService::REMOVE_EVENT_LISTENER, data, &reply);
        if (status != NO_ERROR) {
            return RESULT_ERROR;
        }
        return reply.readInt32();
    }

    virtual int dumpListener()
    {
        Parcel data, reply;
        data.writeInterfaceToken(ICommService::getInterfaceDescriptor());
        status_t status = remote()->transact(ICommService::DUMP_LISTENER, data, &reply);
        if (status != NO_ERROR) {
            return RESULT_ERROR;
        }
        return reply.readInt32();
    }

}; // end BpCommService

IMPLEMENT_META_INTERFACE(CommService, COMM_SERVICE_DESC);

}; // end namespace android
