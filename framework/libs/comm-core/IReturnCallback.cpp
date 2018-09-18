#include "IReturnCallback.h"
//#include "CommonService.h"

namespace android {

extern void (*bpReturnMethod)(int method, Parcel& data, va_list ap) = 0;
extern void (*bnReturnMethod)(int method, const Parcel& data) = 0;

class BpReturnCallback: public BpInterface<IReturnCallback>
{
public:
    BpReturnCallback(const sp<IBinder>& impl)
        : BpInterface<IReturnCallback>(impl)
    {
    }

    virtual void onReturn(int method, int result)
    {
        printf("%s, method %d\n", __FUNCTION__, method);
        Parcel data, reply;
        data.writeInterfaceToken(IReturnCallback::getInterfaceDescriptor());
        data.writeInt32(method);

        //va_list ap;
        //va_start(ap, method);

        if (bpReturnMethod != 0) {
            //bpReturnMethod(method, data, ap);
        }
        data.writeInt32(result);

        //va_end(ap);

        status_t status = remote()->transact(IReturnCallback::ON_RETURN, data, &reply);
        if (status != NO_ERROR) {
            printf("ERROR: %d\n", status);
            return;
        }
        return;
    }
}; // end BpReturnCallback

IMPLEMENT_META_INTERFACE(ReturnCallback, RETURN_CALLBACK_DESC);

// ----------------------------------------------------------------------

status_t BnReturnCallback::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case ON_RETURN: {
            CHECK_INTERFACE(IReturnCallback, data, reply);
            int method = data.readInt32();
            int result = data.readInt32();
            //if (bnReturnMethod != 0) {
            //    bnReturnMethod(method, data);
            //}
            onReturn(method, result);
            return NO_ERROR;
        } break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

}; // end namespace android
