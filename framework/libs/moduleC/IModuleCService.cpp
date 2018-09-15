#include "moduleC/IModuleCService.h"
//#include "IReturnCallback.h"

namespace android {

class BpModuleCService: public BpInterface<IModuleCService>
{
public:
    BpModuleCService(const sp<IBinder>& impl)
        : BpInterface<IModuleCService>(impl)
    {
    }

    virtual int add(int a, int b)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IModuleCService::getInterfaceDescriptor());
        data.writeInt32(a);
        data.writeInt32(b);
        status_t status = remote()->transact(IModuleCService::ADD, data, &reply);
        if (status != NO_ERROR) {
            return 0;
        }
        return reply.readInt32();
    }

}; // end BpModuleCService

IMPLEMENT_META_INTERFACE(ModuleCService, MODULEC_SERVICE_DESC);

}; // end namespace android
