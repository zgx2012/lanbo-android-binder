#ifndef FRAMEWORKS_IMODULECSERVICE_H
#define FRAMEWORKS_IMODULECSERVICE_H

#include "comm.h"

#define MODULEC_SERVICE_NAME "native.moduleC"
#define MODULEC_SERVICE_DESC "native.IModuleCService"

namespace android {

class IModuleCService : public IInterface
{
public:
    enum {
        ADD = IBinder::FIRST_CALL_TRANSACTION,
    };
public:
    DECLARE_META_INTERFACE(ModuleCService);
    // 定义纯虚函数, 定义接口
    virtual int add(int a, int b) = 0;

}; // end IModuleCService

}; // end namespace android

#endif //FRAMEWORKS_IMODULECSERVICE_H
