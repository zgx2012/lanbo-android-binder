#ifndef FRAMEWORKS_IARITHMETICSERVICE_H
#define FRAMEWORKS_IARITHMETICSERVICE_H

//#include <utils/RefBase.h>
#include <binder/IInterface.h>
//#include <binder/Parcel.h>

namespace android {

class IArithmeticService : public IInterface
{
public:
    enum {
        ADD = IBinder::FIRST_CALL_TRANSACTION,
        SUB,
        MUL,
        DIV,
    };
public:
    DECLARE_META_INTERFACE(ArithmeticService);
    // 定义纯虚函数, 定义接口
    virtual int add(int a, int b) = 0;
    virtual int sub(int a, int b) = 0;
    virtual int div(int a, int b) = 0;
    virtual int mul(int a, int b) = 0;

}; // end IArithmeticService

/*
class BnArithmeticService : public BnInterface<IArithmeticService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnArithmeticService
*/

}; // end namespace android

#endif //FRAMEWORKS_IARITHMETICSERVICE_H
