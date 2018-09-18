#define LOG_TAG "moduleBserver"
#define LOG_NDEBUG 0

//#include <fcntl.h>
//#include <sys/prctl.h>
//#include <sys/wait.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <pthread.h>

// from LOCAL_C_INCLUDES
#include "ModuleBService.h"
#include "communication/Communication.h"
#include "BaseModuleFactory.h"
#include "communication/ModuleFactory.h"
#include "ReturnCallback.h"

using namespace android;


void *thread(void *arg)
{
    sleep(1);

    //MethodAddCallback* p = new MethodAddCallback();
    sp<MethodAddCallback> p = new MethodAddCallback();
    methodCallReturn(MODULE_NAME_B, MODULE_NAME_A, METHOD_RETURN_ADD, p, 30, 40);

    //sleep(1);
    //methodCallReturn(MODULE_NAME_B, MODULE_NAME_A, METHOD_RETURN_ADD, p, 30, 40);

    //sleep(1);
    //methodCallReturn(MODULE_NAME_B, MODULE_NAME_A, METHOD_RETURN_ADD, p, 30, 40);

    //sendEvent(MODULE_NAME_B, MODULE_NAME_A, EVENT_HELLO);
    //methodCall(MODULE_NAME_B, MODULE_NAME_A, METHOD_SET_VALUE, 100);

    //sendToModuleA(MODULE_NAME_B, EVENT_ADD, 3, 4);
    //sendToModuleB(MODULE_NAME_B, EVENT_ADD, 5, 6);
    //sendToModuleC(MODULE_NAME_B, EVENT_ADD, 7, 8);

    sleep(1);
    pthread_exit(NULL);
}

int main(int argc, char* const argv[])
{
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    ALOGI("ServiceManager: %p", sm.get());
    ModuleBService::instantiate();

    bpReturnMethod = bpReturnMethodImpl;
    bnReturnMethod = bnReturnMethodImpl;

    gModuleFactory = &(ModuleFactory::getInstance());
    sp<MethodAddCallback> p = new MethodAddCallback();
    methodCallReturn(MODULE_NAME_B, MODULE_NAME_A, METHOD_RETURN_ADD, p, 10, 20);

    pthread_t tid;
    int err = pthread_create(&tid, NULL, thread, NULL);

    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
