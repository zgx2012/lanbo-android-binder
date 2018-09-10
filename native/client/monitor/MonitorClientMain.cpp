#define LOG_TAG "monitorclient"
#define LOG_NDEBUG 0

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>

#include "monitor/IMonitorService.h"
#include "CommonService.h"

using namespace android;
DECLARE_GET_SERVICE(MonitorService)
IMPLEMENT_GET_SERVICE(MonitorService)

int main(int argc, char* const argv[])
{
    //sp<ProcessState> proc(ProcessState::self());
    sp<IMonitorService> pService = getMonitorService(MONITOR_SERVICE_NAME);
    pService->setValue(10);

    //ProcessState::self()->startThreadPool();
    //IPCThreadState::self()->joinThreadPool();
    return 0;
}
