#define LOG_TAG "ModuleAService"
#define LOG_NDEBUG 0

#include <utils/Log.h>
#include <time.h>
#include <cutils/threads.h>

#include <private/binder/Static.h>

#include <binder/BufferedTextOutput.h>
#include <binder/BpBinder.h>
#include <utils/Log.h>

//#include <binder/IServiceManager.h>
//#include <binder/MemoryBase.h>
//#include <binder/MemoryHeapBase.h>
#include "IReturnCallback.h"
#include "communication/Communication.h"
#include "ModuleAService.h"

namespace android {

Vector<int32_t> gTextBuffers;

class LogTextOutput : public BufferedTextOutput
{
public:
    LogTextOutput() : BufferedTextOutput(MULTITHREADED) { }
    virtual ~LogTextOutput() { };

protected:
    virtual status_t writeLines(const struct iovec& vec, size_t N)
    {
        //android_writevLog(&vec, N);       <-- this is now a no-op
        if (N != 1) ALOGI("WARNING: writeLines N=%zu\n", N);
        ALOGI("%.*s", (int)vec.iov_len, (const char*) vec.iov_base);
        return NO_ERROR;
    }
};

class FdTextOutput : public BufferedTextOutput
{
public:
    FdTextOutput(int fd) : BufferedTextOutput(MULTITHREADED), mFD(fd) { }
    virtual ~FdTextOutput() { };

protected:
    virtual status_t writeLines(const struct iovec& vec, size_t N)
    {
        writev(mFD, &vec, N);
        return NO_ERROR;
    }

private:
    int mFD;
};

static LogTextOutput gLogTextOutput;
static FdTextOutput gStdoutTextOutput(STDOUT_FILENO);
static FdTextOutput gStderrTextOutput(STDERR_FILENO);

TextOutput& alog(gLogTextOutput);
TextOutput& aout(gStdoutTextOutput);
TextOutput& aerr(gStderrTextOutput);

ModuleAService::ModuleAService()
    : BnModuleAService(), mValue(0)
{
    ALOGI("%s", __FUNCTION__);
}

void ModuleAService::onFirstRef()
{
    ALOGI("%s", __FUNCTION__);
}

ModuleAService::~ModuleAService()
{
    ALOGI("%s", __FUNCTION__);
}

int ModuleAService::hello(const char* text)
{
    printf("%s: %s\n", __FUNCTION__, text);
    return RESULT_NO_ERROR;
}

int ModuleAService::setValue(int value)
{
    printf("%s: %d\n", __FUNCTION__, value);
    AutoMutex lock(mServiceLock);
    mValue = value;
    return RESULT_NO_ERROR;
}

int ModuleAService::addReturn(int method, int a, int b, const sp<IReturnCallback>& callback)
{
    struct timespec ts;
    int ret = clock_gettime(CLOCK_REALTIME, &ts);
    if (ret == 0)
    printf("[%ld:%ld]: %s: %d, %d, uid:%d, pid:%d, tid:%d\n", ts.tv_sec, ts.tv_nsec, __FUNCTION__, a, b, getuid(), getpid(), gettid());
    else printf("%s: %d, %d, uid:%d, pid:%d, tid:%d\n", __FUNCTION__, a, b, getuid(), getpid(), gettid());

    mCallback = callback;
    printf("%p\n", (IInterface::asBinder(callback)).get());
    AutoMutex lock(mServiceLock);
    int result = a + b;
    if (callback != 0) {
        printf("do method[%d] callback, result=%d\n", method, result);
        callback->onReturn(method, result);
        printf("callback done\n");
    } else {
        printf("no callback\n");
    }
    return RESULT_NO_ERROR;
}

// ----------------------------------------------------------------------

status_t BnModuleAService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case HELLO: {
            CHECK_INTERFACE(IModuleAService, data, reply);
            const char* text = data.readCString();
            int result = hello(text);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        case SET_VALUE: {
            CHECK_INTERFACE(IModuleAService, data, reply);
            int value = data.readInt32();
            int result = setValue(value);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        case ADD_RETURN: {
            CHECK_INTERFACE(IModuleAService, data, reply);
            //data.print(aout, 0);
            int method = data.readInt32();
            int a = data.readInt32();
            int b = data.readInt32();
            //sp<IBinder> binder = data.readStrongBinder();
            //printf("binder = %p\n", binder->remoteBinder());
            //sp<BpBinder> bpBinder = (BpBinder*)(binder.get());
            //printf("bpBinder = %d\n", bpBinder->handle());
            const sp<IReturnCallback>& callback = interface_cast<IReturnCallback>(data.readStrongBinder());
            int result = addReturn(method, a, b, callback);
            reply->writeInt32(result);
            return NO_ERROR;
        } break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}


}; // end namespace android