#ifndef FRAMEWORKS_MODULECSERVICE_H
#define FRAMEWORKS_MODULECSERVICE_H

//#include <utils/RefBase.h>
//#include <binder/IInterface.h>
#include <binder/Parcel.h>
//#include <binder/MemoryDealer.h>
#include <binder/BinderService.h>
//#include <binder/IAppOpsCallback.h>
#include <moduleC/IModuleCService.h>
#include "CommonService.h"
//#include <moduleC/IModuleC.h>
//#include <moduleC/IModuleCClient.h>

namespace android {


class BnModuleCService : public BnInterface<IModuleCService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnModuleCService


class ModuleCService :
    public BinderService<ModuleCService>,
    public BnModuleCService
{
    friend class BinderService<ModuleCService>;

public:

    static char const* getServiceName() { return MODULEC_SERVICE_NAME; }

            ModuleCService();
    virtual ~ModuleCService();

    // IModuleCService
    virtual int add(int a, int b);

private:

    virtual void onFirstRef();
    Mutex mServiceLock;
}; // end class ModuleCService

}; // end namespace android

#endif //FRAMEWORKS_MODULECSERVICE_H
