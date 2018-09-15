#include "moduleB/IModuleBService.h"
//#include "IReturnCallback.h"

namespace android {

class BpModuleBService: public BpInterface<IModuleBService>
{
public:
    BpModuleBService(const sp<IBinder>& impl)
        : BpInterface<IModuleBService>(impl)
    {
    }

    virtual int add(int a, int b)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IModuleBService::getInterfaceDescriptor());
        data.writeInt32(a);
        data.writeInt32(b);
        status_t status = remote()->transact(IModuleBService::ADD, data, &reply);
        if (status != NO_ERROR) {
            return 0;
        }
        return reply.readInt32();
    }

}; // end BpModuleBService

IMPLEMENT_META_INTERFACE(ModuleBService, MODULEB_SERVICE_DESC);

}; // end namespace android
