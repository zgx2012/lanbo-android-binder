#ifndef FRAMEWORKS_COMMONSERVICE_H
#define FRAMEWORKS_COMMONSERVICE_H

namespace android {


#define ARITHMETIC_SERVICE_NAME "native.arithmetic"
#define ARITHMETIC_SERVICE_DESC "native.IArithmeticService"

#define MATRIX_SERVICE_NAME "native.matrix"
#define MATRIX_SERVICE_DESC "native.IMatrixService"
#define BASE_SIZE 10
#define MATRIX_SIZE (BASE_SIZE*BASE_SIZE)

#define MONITOR_SERVICE_NAME "native.monitor"
#define MONITOR_SERVICE_DESC "native.IMonitorService"
#define MONITOR_CALLBACK_DESC "native.IMonitorCallback"

#define DECLARE_GET_SERVICE(SERVICE)                                                \
    static android::Mutex s##SERVICE##Lock;                                         \
    static android::sp<android::I##SERVICE> get##SERVICE(const char* serviceName, int count=1); \

#define IMPLEMENT_GET_SERVICE(SERVICE)                                              \
    android::sp<android::I##SERVICE> get##SERVICE(const char* serviceName, int count) {         \
        android::Mutex::Autolock _l(s##SERVICE##Lock);                              \
        android::sp<android::I##SERVICE> pService;                                  \
        android::sp<android::IServiceManager> sm = android::defaultServiceManager();\
        android::sp<android::IBinder> binder;                                       \
        do {                                                                        \
            binder = sm->getService(android::String16(serviceName));                \
            count--;                                                                \
            if (binder != 0 || count <= 0) break;                                   \
            usleep(500000);                                                         \
        } while(true);                                                              \
        if (binder != 0) {                                                          \
            pService = android::interface_cast<android::I##SERVICE>(binder);        \
        } else {                                                                    \
            pService = 0;                                                           \
        }                                                                           \
        return pService;                                                            \
    }                                                                               \

}; // end namespace android

#endif //FRAMEWORKS_COMMONSERVICE_H
