#define LOG_TAG "MatrixService"
#define LOG_NDEBUG 0

#include <utils/Log.h>
#include <binder/IMemory.h>
//#include <binder/IServiceManager.h>
//#include <binder/MemoryBase.h>
//#include <binder/MemoryHeapBase.h>
#include "MatrixService.h"
#include "CommonService.h"

namespace android {
MatrixService::MatrixService()
    : BnMatrixService()
{
    ALOGI("%s", __FUNCTION__);
}

void MatrixService::onFirstRef()
{
    ALOGI("%s", __FUNCTION__);
}

MatrixService::~MatrixService()
{
    ALOGI("%s", __FUNCTION__);
}

void MatrixService::reverse(const sp<IMemory>& mem)
{
    AutoMutex lock(mServiceLock);
    if (mem != 0) {
        int* p = static_cast<int*>(mem->pointer());
        size_t size = mem->size();
        if (size >= MATRIX_SIZE) {
            for (int i=0;i<BASE_SIZE;i++) {
                for (int j = 0; j < BASE_SIZE; j++) {
                    p[i * BASE_SIZE + j] = MATRIX_SIZE-BASE_SIZE * i - j - 1;
                }
            }
        }
    }
}

// ----------------------------------------------------------------------


status_t BnMatrixService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case REVERSE: {
            CHECK_INTERFACE(IMatrixService, data, reply);
            sp<IMemory> mem = interface_cast<IMemory>(data.readStrongBinder());
            reverse(mem);
            return NO_ERROR;
        } break;


        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}


}; // end namespace android