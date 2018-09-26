#define LOG_TAG "moduleCserver"
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
#include "ModuleCService.h"
#include "communication/Communication.h"
#include "BaseModuleFactory.h"
#include "communication/ModuleFactory.h"

using namespace android;

void *thread(void *arg)
{
    sleep(1);

    //sendToModuleA(MODULE_NAME_C, EVENT_ADD, 3, 4);
    //sendToModuleB(MODULE_NAME_C, EVENT_ADD, 5, 6);
    //sendToModuleC(MODULE_NAME_C, EVENT_ADD, 7, 8);

    sleep(1);
    pthread_exit(NULL);
}

int main(int argc, char* const argv[])
{
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    ALOGI("ServiceManager: %p", sm.get());
    ModuleCService::instantiate();

    gModuleFactory = &(ModuleFactory::getInstance());

    pthread_t tid;
    int err = pthread_create(&tid, NULL, thread, NULL);

    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
