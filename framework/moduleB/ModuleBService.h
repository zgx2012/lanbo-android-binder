#ifndef FRAMEWORKS_MODULEBSERVICE_H
#define FRAMEWORKS_MODULEBSERVICE_H

//#include <utils/RefBase.h>
//#include <binder/IInterface.h>
#include <binder/Parcel.h>
//#include <binder/MemoryDealer.h>
#include <binder/BinderService.h>
//#include <binder/IAppOpsCallback.h>
#include <moduleB/IModuleBService.h>
#include "CommonService.h"
//#include <moduleB/IModuleB.h>
//#include <moduleB/IModuleBClient.h>

namespace android {


class BnModuleBService : public BnInterface<IModuleBService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnModuleBService


class ModuleBService :
    public BinderService<ModuleBService>,
    public BnModuleBService
{
    friend class BinderService<ModuleBService>;

public:

    static char const* getServiceName() { return MODULEB_SERVICE_NAME; }

            ModuleBService();
    virtual ~ModuleBService();

    // IModuleBService
    virtual int add(int a, int b);

private:

    virtual void onFirstRef();
    Mutex mServiceLock;
}; // end class ModuleBService

}; // end namespace android

#endif //FRAMEWORKS_MODULEBSERVICE_H
