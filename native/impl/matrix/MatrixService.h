#ifndef FRAMEWORKS_MATRIXSERVICE_H
#define FRAMEWORKS_MATRIXSERVICE_H

//#include <utils/RefBase.h>
//#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IMemory.h>
#include <binder/BinderService.h>
//#include <binder/IAppOpsCallback.h>
#include <matrix/IMatrixService.h>
#include "CommonService.h"
//#include <matrix/IMatrix.h>
//#include <matrix/IMatrixClient.h>

namespace android {


class BnMatrixService : public BnInterface<IMatrixService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnMatrixService


class MatrixService :
    public BinderService<MatrixService>,
    public BnMatrixService
{
    friend class BinderService<MatrixService>;

public:

    static char const* getServiceName() { return MATRIX_SERVICE_NAME; }

            MatrixService();
    virtual ~MatrixService();

    // IMatrixService
    virtual void reverse(const sp<IMemory>& mem);

private:

    virtual void onFirstRef();
    Mutex mServiceLock;
}; // end class MatrixService

}; // end namespace android

#endif //FRAMEWORKS_MATRIXSERVICE_H
