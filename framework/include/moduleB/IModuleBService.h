#ifndef FRAMEWORKS_IMODULEBSERVICE_H
#define FRAMEWORKS_IMODULEBSERVICE_H

#include "comm.h"

#define MODULEB_SERVICE_NAME "native.moduleB"
#define MODULEB_SERVICE_DESC "native.IModuleBService"

namespace android {

class IModuleBService : public IInterface
{
public:
    enum {
        ADD = IBinder::FIRST_CALL_TRANSACTION,
    };
public:
    DECLARE_META_INTERFACE(ModuleBService);
    // 定义纯虚函数, 定义接口
    virtual int add(int a, int b) = 0;

}; // end IModuleBService

}; // end namespace android

#endif //FRAMEWORKS_IMODULEBSERVICE_H
