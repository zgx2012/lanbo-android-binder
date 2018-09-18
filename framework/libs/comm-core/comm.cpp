
#include "comm.h"
#include "BaseModuleFactory.h"
#include "IReturnCallback.h"
#include "CommunicationModule.h"

namespace android {

extern BaseModuleFactory* gModuleFactory = 0;

CommunicationModule* getModule(const char* name)
{
    if (gModuleFactory != 0) {
        return gModuleFactory->getModule(name);
    }
    return 0;
}

int methodCall(const char* from, const char* to, const int method, ...)
{
    va_list ap;
    va_start(ap, method);

    printf("methodCall [%s] -> [%s]:", from, to);
    int result = getModule(to)->methodCall(from, method, ap);

    va_end(ap);
    return result;
}

int methodCallReturn(const char* from, const char* to, const int method,
    const sp<IReturnCallback>& callback, ...)
{
    va_list ap;
    va_start(ap, callback);

    printf("methodCallReturn [%s] -> [%s]:", from, to);
    int result = getModule(to)->methodCallReturn(from, method, callback, ap);

    va_end(ap);
    return result;
}

int addEventListener(const char* from, const sp<IEventListener>& listener, const std::vector<int>& eventVector)
{
    int result = getModule(MODULE_COMM_SERVICE)->addEventListener(from, listener, eventVector);
    return result;
}

int sendEvent(const char* from, const char* to, const int event)
{
    printf("sendEvent [%s] -> [%s]:", from, to);
    //int result = getModule(to)->dispatchEvent(from, event, ap);
    int result = getModule(MODULE_COMM_SERVICE)->sendEvent(from, to, event);
    return result;
}

int sendEventSync(const char* from, const char* to, const int event)
{
    printf("sendEventSync [%s] -> [%s]:", from, to);
    int result = getModule(MODULE_COMM_SERVICE)->sendEventSync(from, to, event);
    return result;
}

}; // end namespace android
