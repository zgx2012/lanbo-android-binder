#define LOG_TAG "commserver"
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
#include "CommService.h"
#include "communication/Communication.h"
#include "BaseModuleFactory.h"
#include "communication/ModuleFactory.h"

using namespace android;

void *thread(void *arg)
{
    while(true) {
        // 读取一个Event，如果无Event则会阻塞，直到有Event为止
        const QueueEvent::Event& event = EventManager.instance().getEvent();

        // 向监听者分发Event
        ListenerManager.instance().dispatch(event.event, event.parcelable);
    }
    pthread_exit(NULL);
}

int main(int argc, char* const argv[])
{
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    ALOGI("ServiceManager: %p", sm.get());
    CommService::instantiate();

    //bpReturnMethod = bpReturnMethodImpl;
    //bnReturnMethod = bnReturnMethodImpl;

    gModuleFactory = &(ModuleFactory::getInstance());

    pthread_t tid;
    int err = pthread_create(&tid, NULL, thread, NULL);

    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
