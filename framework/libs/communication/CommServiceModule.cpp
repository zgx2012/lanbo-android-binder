#include <stdarg.h>
#include <utils/String16.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <binder/IInterface.h>

#include "CommServiceModule.h"
#include "commService/ICommService.h"
#include "CommonService.h"

DECLARE_GET_SERVICE(CommService)
IMPLEMENT_GET_SERVICE(CommService)

namespace android
{

int CommServiceModule::sendEvent(const char* from, const char* to, const int event)
{
    int result = RESULT_NO_ERROR;
    // 远程调用
    sp<ICommService> pService = getCommService(COMM_SERVICE_NAME);
    if (pService == 0) {
        printf("[CommServiceModule::dispatchEvent] not such service: [%s]\n", COMM_SERVICE_NAME);
        result = RESULT_NO_SUCH_SERVICE;
    } else {
        int result = pService->sendEvent(from, to, event);
    }

    return result;
}

int CommServiceModule::sendEvent(const char* from, const char* to, const int event, const Parcelable* parcelable)
{
    int result = RESULT_NO_ERROR;
    // 远程调用
    sp<ICommService> pService = getCommService(COMM_SERVICE_NAME);
    if (pService == 0) {
        printf("[CommServiceModule::dispatchEvent] not such service: [%s]\n", COMM_SERVICE_NAME);
        result = RESULT_NO_SUCH_SERVICE;
    } else {
        int result = pService->sendEvent(from, to, event, parcelable);
    }

    return result;
}

int CommServiceModule::addEventListener(const char* name, const sp<IEventListener>& listener, const std::vector<int>& eventVector)
{
    int result = RESULT_NO_ERROR;

    // 远程调用
    sp<ICommService> pService = getCommService(COMM_SERVICE_NAME);
    if (pService == 0) {
        printf("[CommServiceModule::addEventListener] not such service: [%s]\n", COMM_SERVICE_NAME);
        result = RESULT_NO_SUCH_SERVICE;
    } else {
        int result = pService->addEventListener(name, listener, eventVector);
    }

    return result;
}

}; // end namespace android

