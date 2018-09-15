#ifndef FRAMEWORKS_IMODULEASERVICE_H
#define FRAMEWORKS_IMODULEASERVICE_H

#include "comm.h"

#define MODULEA_SERVICE_NAME "native.moduleA"
#define MODULEA_SERVICE_DESC "native.IModuleAService"

namespace android {

class IModuleAService : public IInterface
{
public:
    enum {
        HELLO = IBinder::FIRST_CALL_TRANSACTION,
        SET_VALUE,
        ADD_RETURN,
    };
public:
    DECLARE_META_INTERFACE(ModuleAService);
    // 定义纯虚函数, 定义接口
    virtual int hello(const char* text) = 0;
    virtual int setValue(int value) = 0;
    virtual int addReturn(int method, int a, int b, const sp<IReturnCallback>& callback) = 0;

}; // end IModuleAService

}; // end namespace android

#endif //FRAMEWORKS_IMODULEASERVICE_H
