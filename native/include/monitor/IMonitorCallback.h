#ifndef FRAMEWORKS_IMONITORCALLBACK_H
#define FRAMEWORKS_IMONITORCALLBACK_H

#include <binder/IInterface.h>

namespace android {

class IMonitorCallback : public IInterface
{
public:
    enum {
        ON_VALUE_CHANGED = IBinder::FIRST_CALL_TRANSACTION,
    };
public:
    DECLARE_META_INTERFACE(MonitorCallback);
    // 定义纯虚函数, 定义接口
    virtual void onValueChanged(int newValue) = 0;

}; // end IMonitorCallback

class BnMonitorCallback : public BnInterface<IMonitorCallback>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
}; // end BnMonitorCallback

}; // end namespace android

#endif //FRAMEWORKS_IMONITORCALLBACK_H
