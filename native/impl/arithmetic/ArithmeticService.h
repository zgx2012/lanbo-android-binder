#ifndef FRAMEWORKS_ARITHMETICSERVICE_H
#define FRAMEWORKS_ARITHMETICSERVICE_H

//#include <utils/RefBase.h>
//#include <binder/IInterface.h>
#include <binder/Parcel.h>
//#include <binder/MemoryDealer.h>
#include <binder/BinderService.h>
//#include <binder/IAppOpsCallback.h>
#include <arithmetic/IArithmeticService.h>
#include "CommonService.h"
//#include <arithmetic/IArithmetic.h>
//#include <arithmetic/IArithmeticClient.h>

namespace android {


class BnArithmeticService : public BnInterface<IArithmeticService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnArithmeticService


class ArithmeticService :
    public BinderService<ArithmeticService>,
    public BnArithmeticService
{
    friend class BinderService<ArithmeticService>;

public:

    static char const* getServiceName() { return ARITHMETIC_SERVICE_NAME; }

            ArithmeticService();
    virtual ~ArithmeticService();

    // IArithmeticService
    virtual int add(int a, int b);
    virtual int sub(int a, int b);
    virtual int div(int a, int b);
    virtual int mul(int a, int b);

private:

    virtual void onFirstRef();
    Mutex mServiceLock;
}; // end class ArithmeticService

}; // end namespace android

#endif //FRAMEWORKS_ARITHMETICSERVICE_H
