#ifndef FRAMEWORKS_IMONITORSERVICE_H
#define FRAMEWORKS_IMONITORSERVICE_H

#include <binder/IInterface.h>
#include "IMonitorCallback.h"

namespace android {

class IMonitorService : public IInterface
{
public:
    enum {
        SET_VALUE = IBinder::FIRST_CALL_TRANSACTION,
        SET_CALLBACK,
    };
public:
    DECLARE_META_INTERFACE(MonitorService);
    // 定义纯虚函数, 定义接口
    virtual void setValue(int value) = 0;
    virtual void setCallback(const sp<IMonitorCallback>& callback) = 0;

}; // end IMonitorService

}; // end namespace android

#endif //FRAMEWORKS_IMONITORSERVICE_H
