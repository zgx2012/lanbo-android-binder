#define LOG_TAG "moduleAserver"
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
#include "ModuleAService.h"
#include "communication/Communication.h"
#include "BaseModuleFactory.h"
#include "communication/ModuleFactory.h"
#include "EventListener.h"

using namespace android;

void *thread(void *arg)
{
    sleep(1);

    //sendToModuleA(MODULE_NAME_A, EVENT_ADD, 3, 4);
    //sendToModuleB(MODULE_NAME_A, EVENT_ADD, 5, 6);
    //sendToModuleC(MODULE_NAME_A, EVENT_ADD, 7, 8);
    sp<EventListener> listener = new EventListener();
    std::vector<int> events;
    events.push_back(EVENT_HELLO);
    addEventListener(MODULE_NAME_A, listener, events);

    sleep(1);
    pthread_exit(NULL);
}

int main(int argc, char* const argv[])
{
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    ALOGI("ServiceManager: %p", sm.get());
    ModuleAService::instantiate();

    gModuleFactory = &(ModuleFactory::getInstance());

    pthread_t tid;
    int err = pthread_create(&tid, NULL, thread, NULL);

    //ProcessState::self()->setThreadPoolMaxThreadCount(10);
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
