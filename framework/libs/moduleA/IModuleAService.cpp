#include "moduleA/IModuleAService.h"
#include "IReturnCallback.h"

namespace android {

class BpModuleAService: public BpInterface<IModuleAService>
{
public:
    BpModuleAService(const sp<IBinder>& impl)
        : BpInterface<IModuleAService>(impl)
    {
    }

    virtual int hello(const char* text)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IModuleAService::getInterfaceDescriptor());
        data.writeCString(text);
        status_t status = remote()->transact(IModuleAService::HELLO, data, &reply);
        if (status != NO_ERROR) {
            return RESULT_ERROR;
        }
        return reply.readInt32();
    }

    virtual int setValue(int value)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IModuleAService::getInterfaceDescriptor());
        data.writeInt32(value);
        status_t status = remote()->transact(IModuleAService::SET_VALUE, data, &reply);
        if (status != NO_ERROR) {
            return RESULT_ERROR;
        }
        return reply.readInt32();
    }

    virtual int addReturn(int method, int a, int b, const sp<IReturnCallback>& callback)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IModuleAService::getInterfaceDescriptor());
        data.writeInt32(method);
        data.writeInt32(a);
        data.writeInt32(b);
        data.writeStrongBinder(IInterface::asBinder(callback));
        status_t status = remote()->transact(IModuleAService::ADD_RETURN, data, &reply);
        if (status != NO_ERROR) {
            return RESULT_ERROR;
        }
        return reply.readInt32();
    }

}; // end BpModuleAService

IMPLEMENT_META_INTERFACE(ModuleAService, MODULEA_SERVICE_DESC);

}; // end namespace android
