#define LOG_TAG "BpMatrixService"
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

#include <matrix/IMatrixService.h>
#include <CommonService.h>
//#include "../include/matrix/IMatrixService.h"
//#include <matrix/IMatrix.h>
//#include <matrix/IMatrixClient.h>

namespace android {

class BpMatrixService: public BpInterface<IMatrixService>
{
public:
    BpMatrixService(const sp<IBinder>& impl)
        : BpInterface<IMatrixService>(impl)
    {
    }

    virtual void reverse(const sp<IMemory>& mem)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IMatrixService::getInterfaceDescriptor());
        data.writeStrongBinder(IInterface::asBinder(mem));
        status_t status = remote()->transact(IMatrixService::REVERSE, data, &reply);
        if (status != NO_ERROR) {
            return;
        }
        return;
    }

}; // end BpMatrixService

IMPLEMENT_META_INTERFACE(MatrixService, MATRIX_SERVICE_DESC);

// ----------------------------------------------------------------------

}; // end namespace android
