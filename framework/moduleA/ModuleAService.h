#ifndef FRAMEWORKS_MODULEASERVICE_H
#define FRAMEWORKS_MODULEASERVICE_H

//#include <utils/RefBase.h>
//#include <binder/IInterface.h>
#include <binder/Parcel.h>
//#include <binder/MemoryDealer.h>
#include <binder/BinderService.h>
//#include <binder/IAppOpsCallback.h>
#include <moduleA/IModuleAService.h>
#include "IReturnCallback.h"
#include "CommonService.h"
//#include <moduleA/IModuleA.h>
//#include <moduleA/IModuleAClient.h>

namespace android {


class BnModuleAService : public BnInterface<IModuleAService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnModuleAService


class ModuleAService :
    public BinderService<ModuleAService>,
    public BnModuleAService
{
    friend class BinderService<ModuleAService>;

public:

    static char const* getServiceName() { return MODULEA_SERVICE_NAME; }

            ModuleAService();
    virtual ~ModuleAService();

    // IModuleAService
    virtual int hello(const char* text);
    virtual int setValue(int value);
    virtual int addReturn(int method, int a, int b, const sp<IReturnCallback>& callback);

private:

    int mValue;
    virtual void onFirstRef();
    Mutex mServiceLock;
    sp<IReturnCallback> mCallback;
}; // end class ModuleAService

}; // end namespace android

#endif //FRAMEWORKS_MODULEASERVICE_H
