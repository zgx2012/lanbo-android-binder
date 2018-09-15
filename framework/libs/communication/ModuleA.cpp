#include <stdarg.h>
#include <utils/String16.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <binder/IInterface.h>

#include "ModuleA.h"
#include "moduleA/IModuleAService.h"
#include "CommonService.h"

DECLARE_GET_SERVICE(ModuleAService)
IMPLEMENT_GET_SERVICE(ModuleAService)

namespace android
{

/*
int ModuleA::sendEvent(const char* from, const char* to, const int event, va_list ap)
{
    int result = RESULT_NO_ERROR;
    switch(event) {
        case EVENT_HELLO: {// TODO async
            result = eventHello(from, ap);
        } break;

        default: { result = RESULT_UNKNOWN_EVENT; } break;
    }

    return result;
}

int ModuleA::sendEventSync(const char* from, const char* to, const int event, va_list ap)
{
    int result = RESULT_NO_ERROR;
    switch(event) {
        case EVENT_HELLO: {
            result = eventHello(from, ap);
        } break;

        default: { result = RESULT_UNKNOWN_EVENT; } break;
    }
    return result;
}
*/

int ModuleA::methodCall(const char* from, const int method, va_list ap)
{
    int result = RESULT_NO_ERROR;
    switch(method) {
        case METHOD_SET_VALUE: {
            result = methodSetValue(from, ap);
        } break;

        default: { result = RESULT_NO_SUCH_METHOD; } break;
    }
    return result;
}

int ModuleA::methodCallReturn(const char* from, const int method, const sp<IReturnCallback>& callback, va_list ap)
{
    int result = RESULT_NO_ERROR;
    switch(method) {
        case METHOD_RETURN_ADD: {
            result = methodAddReturn(from, method, callback, ap);
        } break;

        default: { result = RESULT_NO_SUCH_METHOD; } break;
    }
    return result;
}

//----------------------------------------------------------------------
/*
int ModuleA::eventHello(const char* from, va_list ap)
{
    const char* text = va_arg(ap, char*);
    printf("--[ModuleA::eventHello]: %s\n", text);

    int result = RESULT_NO_ERROR;
    // TODO
    if (localTarget(from)) {
        // 本地调用
        printf("[ModuleA::eventHello] local target\n");
    } else {
        // 远程调用
        sp<IModuleAService> pService = getModuleAService(MODULEA_SERVICE_NAME);
        if (pService == 0) {
            printf("[ModuleA::eventHello] not such service: [%s]\n", MODULEA_SERVICE_NAME);
            result = RESULT_NO_SUCH_SERVICE;
        } else {
            result = pService->hello(text);
        }
    }
    return result;
}
*/
int ModuleA::methodSetValue(const char* from, va_list ap)
{
    int value = va_arg(ap, int);
    printf("--[ModuleA::methodSetValue]: %d\n", value);

    int result = RESULT_NO_ERROR;
    if (localTarget(from)) {
        // TODO
        // 本地调用
        printf("[ModuleA::methodSetValue] local target\n");
    } else {
        // 远程调用
        sp<IModuleAService> pService = getModuleAService(MODULEA_SERVICE_NAME);
        if (pService == 0) {
            printf("[ModuleA::methodSetValue] not such service: [%s]\n", MODULEA_SERVICE_NAME);
            result = RESULT_NO_SUCH_SERVICE;
        } else {
            // 记录调用
            result = pService->setValue(value);
        }
    }
    return result;
}

int ModuleA::methodAddReturn(const char* from, int method, const sp<IReturnCallback>& callback, va_list ap)
{
    int a = va_arg(ap, int);
    int b = va_arg(ap, int);
    printf("--[ModuleA::methodAddReturn]: %d, %d\n", a, b);

    int result = RESULT_NO_ERROR;
    // TODO
    if (localTarget(from)) {
        // 本地调用
        printf("[ModuleA::methodAddReturn] local target\n");
    } else {
        // 远程调用
        sp<IModuleAService> pService = getModuleAService(MODULEA_SERVICE_NAME);
        if (pService == 0) {
            printf("[ModuleA::methodAddReturn] not such service: [%s]\n", MODULEA_SERVICE_NAME);
            result = RESULT_NO_SUCH_SERVICE;
        } else {
            int result = pService->addReturn(method, a, b, callback);
        }
    }
    return result;
}

}; // end namespace android

