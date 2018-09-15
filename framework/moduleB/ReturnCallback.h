#ifndef FRAMEWORKS_MONITORSERVICE_H
#define FRAMEWORKS_MONITORSERVICE_H

#include <stdarg.h>
//#include <utils/RefBase.h>
//#include <binder/IInterface.h>
#include <binder/Parcel.h>
//#include <binder/MemoryDealer.h>
#include <binder/BinderService.h>
//#include <binder/IAppOpsCallback.h>
#include <IReturnCallback.h>
#include "CommonService.h"

namespace android {

class ReturnCallback :
    public BnReturnCallback
{
public:
            ReturnCallback();
    virtual ~ReturnCallback();
    virtual void onReturn(int method, ...);
    virtual void onMethod(va_list ap) = 0;

private:

    virtual void onFirstRef();
}; // end class ReturnCallback

//--------------------------------------------

class MethodAddCallback :
    public ReturnCallback
{
public:
    virtual void onMethod(va_list ap);
}; // end class MethodAddCallback


}; // end namespace android

#endif //FRAMEWORKS_MONITORSERVICE_H
