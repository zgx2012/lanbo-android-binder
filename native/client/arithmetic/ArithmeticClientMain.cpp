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
#include "arithmetic/IArithmeticService.h"
#include "CommonService.h"

using namespace android;
DECLARE_GET_SERVICE(ArithmeticService)
IMPLEMENT_GET_SERVICE(ArithmeticService)

/*
Mutex mArithmeticLock;
sp<IArithmeticService> getArithmeticService(const char* serviceName) {
    Mutex::Autolock _l(mArithmeticLock);
    sp<IArithmeticService> pService;
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder;

    do {
        binder = sm->getService(String16(serviceName));
        if (binder != 0) break;
        ALOGW("%s not published, waiting...", serviceName);
        usleep(500000); // 0.5 s
    } while(true);
    pService = interface_cast<IArithmeticService>(binder);
    ALOGE_IF(pService == 0, "no ArithmeticService!?");
    return pService;
}
*/

int main(int argc, char* const argv[])
{
    //sp<ProcessState> proc(ProcessState::self());
    sp<IArithmeticService> pService = getArithmeticService(ARITHMETIC_SERVICE_NAME);
    printf("[client] call Add result = %d \n",pService->add(10, 20));

    //ProcessState::self()->startThreadPool();
    //IPCThreadState::self()->joinThreadPool();
    return 0;
}
