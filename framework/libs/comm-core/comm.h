#ifndef FRAMEWORKS_COMM_H
#define FRAMEWORKS_COMM_H
#include <stdarg.h>
#include <utils/Errors.h>
#include <utils/String16.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android {

class IReturnCallback;
class IEventListener;
class CommunicationModule;
class BaseModuleFactory;

#define RESULT_NO_ERROR         (0)
#define RESULT_ERROR            (-1)
#define RESULT_NO_SUCH_SERVICE  (-10)
#define RESULT_NO_SUCH_METHOD   (-20)
#define RESULT_UNKNOWN_EVENT    (-30)

#define COMM_SERVICE_NAME "comm_service_server"
#define RETURN_CALLBACK_DESC "native.IReturnCallback"
#define EVENT_LISTENER_DESC "native.IEventListener"

#define METHOD_MASK             10000

#define METHOD_RETURN_MASK      20000

#define EVENT_MASK              30000

// 同步方法调用
int methodCall(const char* from, const char* to, const int method, ...);
// 同步方法调用，将会同步进行回调
int methodCallReturn(const char* from, const char* to, const int method, const sp<IReturnCallback>& callback, ...);
// 同步发送消息
int sendEventSync(const char* from, const char* to, const int event);

// 异步发送消息
int sendEvent(const char* from, const char* to, const int event);

// 添加消息监听, 用于接收其他程序发送的消息
int addEventListener(const char* from, const sp<IEventListener>& listener, const std::vector<int>& eventVector);

extern void (*bpReturnMethod)(int method, Parcel& data, va_list ap);
extern void (*bnReturnMethod)(int method, const Parcel& data);

extern void (*bpEvent)(int event, Parcel& data, va_list ap);
extern void (*bnEvent)(int event, const Parcel& data);
/*
int sendToModuleA(const char* from, const int event, ...);
int sendToModuleB(const char* from, const int event, ...);
int sendToModuleC(const char* from, const int event, ...);
*/

}; // end namespace android

#endif //FRAMEWORKS_COMM_H
