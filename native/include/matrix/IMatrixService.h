#ifndef FRAMEWORKS_IMATRIXSERVICE_H
#define FRAMEWORKS_IMATRIXSERVICE_H

//#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/IMemory.h>
//#include <binder/Parcel.h>

namespace android {

class IMatrixService : public IInterface
{
public:
    enum {
        REVERSE = IBinder::FIRST_CALL_TRANSACTION,
    };
public:
    DECLARE_META_INTERFACE(MatrixService);
    // 定义纯虚函数, 定义接口
    virtual void reverse(const sp<IMemory>& mem) = 0;

}; // end IMatrixService

}; // end namespace android

#endif //FRAMEWORKS_IMATRIXSERVICE_H
