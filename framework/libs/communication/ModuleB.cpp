#include <stdarg.h>
#include <utils/String16.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <binder/IInterface.h>

#include "ModuleB.h"
#include "moduleB/IModuleBService.h"
#include "CommonService.h"

DECLARE_GET_SERVICE(ModuleBService)
IMPLEMENT_GET_SERVICE(ModuleBService)

namespace android
{

int ModuleB::methodCall(const char* from, const int method, va_list ap)
{
    int result = RESULT_NO_ERROR;
    switch(method) {
        default: { result = RESULT_NO_SUCH_METHOD; } break;
    }
    return result;
}

int ModuleB::methodCallReturn(const char* from, const int method, const sp<IReturnCallback>& callback, va_list ap)
{
    int result = RESULT_NO_ERROR;
    switch(method) {
        default: { result = RESULT_NO_SUCH_METHOD; } break;
    }
    return result;
}

}; // end namespace android


