#define LOG_TAG "arithmeticserver"
#define LOG_NDEBUG 0

//#include <fcntl.h>
//#include <sys/prctl.h>
//#include <sys/wait.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>

// from LOCAL_C_INCLUDES
#include "ArithmeticService.h"

using namespace android;

int main(int argc, char* const argv[])
{
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    ALOGI("ServiceManager: %p", sm.get());
    ArithmeticService::instantiate();
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
