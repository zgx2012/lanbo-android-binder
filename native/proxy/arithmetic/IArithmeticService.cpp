#define LOG_TAG "BpArithmeticService"
//
#define LOG_NDEBUG 0

//#include <utils/Log.h>
#include <utils/Errors.h>

//#include <stdint.h>
//#include <sys/types.h>
//#include <binder/IMemory.h>
#include <binder/Parcel.h>
//#include <binder/IPCThreadState.h>
//#include <binder/IServiceManager.h>

#include <arithmetic/IArithmeticService.h>
#include <CommonService.h>
//#include "../include/arithmetic/IArithmeticService.h"
//#include <arithmetic/IArithmetic.h>
//#include <arithmetic/IArithmeticClient.h>

namespace android {

class BpArithmeticService: public BpInterface<IArithmeticService>
{
public:
    BpArithmeticService(const sp<IBinder>& impl)
        : BpInterface<IArithmeticService>(impl)
    {
    }

    virtual int add(int a, int b)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IArithmeticService::getInterfaceDescriptor());
        data.writeInt32(a);
        data.writeInt32(b);
        status_t status = remote()->transact(IArithmeticService::ADD, data, &reply);
        if (status != NO_ERROR) {
            return 0;
        }
        return reply.readInt32();
    }

    virtual int sub(int a, int b)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IArithmeticService::getInterfaceDescriptor());
        data.writeInt32(a);
        data.writeInt32(b);
        status_t status = remote()->transact(IArithmeticService::SUB, data, &reply);
        if (status != NO_ERROR) {
            return 0;
        }
        return reply.readInt32();
    }

    virtual int mul(int a, int b)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IArithmeticService::getInterfaceDescriptor());
        data.writeInt32(a);
        data.writeInt32(b);
        status_t status = remote()->transact(IArithmeticService::MUL, data, &reply);
        if (status != NO_ERROR) {
            return 0;
        }
        return reply.readInt32();
    }

    virtual int div(int a, int b)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IArithmeticService::getInterfaceDescriptor());
        data.writeInt32(a);
        data.writeInt32(b);
        status_t status = remote()->transact(IArithmeticService::DIV, data, &reply);
        if (status != NO_ERROR) {
            return 0;
        }
        return reply.readInt32();
    }

}; // end BpArithmeticService

IMPLEMENT_META_INTERFACE(ArithmeticService, ARITHMETIC_SERVICE_DESC);

// ----------------------------------------------------------------------

/*
status_t BnArithmeticService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case ADD: {
            CHECK_INTERFACE(IArithmeticService, data, reply);
            int a = data.readInt32();
            int b = data.readInt32();
            int result = add(a, b);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        case SUB: {
            CHECK_INTERFACE(IArithmeticService, data, reply);
            int a = data.readInt32();
            int b = data.readInt32();
            int result = sub(a, b);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        case MUL: {
            CHECK_INTERFACE(IArithmeticService, data, reply);
            int a = data.readInt32();
            int b = data.readInt32();
            int result = mul(a, b);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        case DIV: {
            CHECK_INTERFACE(IArithmeticService, data, reply);
            int a = data.readInt32();
            int b = data.readInt32();
            int result = div(a, b);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;


        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}
*/

}; // end namespace android
