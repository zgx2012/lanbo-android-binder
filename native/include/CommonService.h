#ifndef FRAMEWORKS_COMMONSERVICE_H
#define FRAMEWORKS_COMMONSERVICE_H

namespace android {

#define ARITHMETIC_SERVICE_NAME "native.arithmetic"
#define ARITHMETIC_SERVICE_DESC "native.IArithmeticService"

#define MONITOR_SERVICE_NAME "native.monitor"
#define MONITOR_SERVICE_DESC "native.IMonitorService"
#define MONITOR_CALLBACK_DESC "native.IMonitorCallback"

#define DECLARE_GET_SERVICE(SERVICE)                                                \
    static android::Mutex s##SERVICE##Lock;                                         \
    static android::sp<android::I##SERVICE> get##SERVICE(const char* serviceName);  \

#define IMPLEMENT_GET_SERVICE(SERVICE)                                              \
    android::sp<android::I##SERVICE> get##SERVICE(const char* serviceName) {        \
        android::Mutex::Autolock _l(s##SERVICE##Lock);                              \
        android::sp<android::I##SERVICE> pService;                                  \
        android::sp<android::IServiceManager> sm = android::defaultServiceManager();\
        android::sp<android::IBinder> binder;                                       \
        do {                                                                        \
            binder = sm->getService(android::String16(serviceName));                \
            if (binder != 0) break;                                                 \
            usleep(500000);                                                         \
        } while(true);                                                              \
        pService = android::interface_cast<android::I##SERVICE>(binder);            \
        return pService;                                                            \
    }                                                                               \

}; // end namespace android

#endif //FRAMEWORKS_COMMONSERVICE_H
