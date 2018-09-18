#define LOG_TAG "matrixserver"
#define LOG_NDEBUG 0

//#include <fcntl.h>
//#include <sys/prctl.h>
//#include <sys/wait.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/IMemory.h>
#include <binder/MemoryDealer.h>
#include <utils/Log.h>

// from LOCAL_C_INCLUDES
#include "matrix/IMatrixService.h"
#include "CommonService.h"

using namespace android;
DECLARE_GET_SERVICE(MatrixService)
IMPLEMENT_GET_SERVICE(MatrixService)

/*
实现将二维数组逆过来
*/
int main(int argc, char* const argv[])
{
    //sp<ProcessState> proc(ProcessState::self());
    sp<IMatrixService> pService = getMatrixService(MATRIX_SERVICE_NAME);

    sp<MemoryDealer> heap;
    sp<IMemory> iMem;
    int* p;

    // 数组初始化
    int buffer[BASE_SIZE][BASE_SIZE];
    for (int i = 0; i < BASE_SIZE; i++) {
        for (int j = 0; j < BASE_SIZE; j++) {
            buffer[i][j] = j + i * BASE_SIZE;
        }
    }

    // 创建一块1MB大小的共享堆内存
    heap = new MemoryDealer(1024*1024, "AudioTrack Heap Base");

    // 在上述共享堆内存上，分配一块buffer内存.
    // 内存分配时会做32个字节对齐，即申请11个字节,实际会分配32个字节
    iMem = heap->allocate(MATRIX_SIZE*sizeof(int));

    // 获取当前使用buffer的地址
    p = static_cast<int*>(iMem->pointer());
    // 将数组内容拷贝到共享内存中
    for (int i = 0; i < BASE_SIZE; i++) {
        memcpy(p+i*BASE_SIZE, buffer[i], BASE_SIZE*sizeof(int));
    }
    //memcpy(p, buffer, MATRIX_SIZE*sizeof(int));

    // 打印数组信息
    for (int i=0;i<BASE_SIZE;i++) {
        for (int j=0;j<BASE_SIZE;j++) {
            printf("%d ", buffer[i][j]);
        }
        printf("\n");
    }

    // 实现数组逆过来
    if (pService != 0) {
        pService->reverse(iMem);
    } else {
        printf("[client] no service found\n");
    }

    // 将内容从共享内存中拷贝出来
    for (int i = 0; i < BASE_SIZE; i++) {
        memcpy(buffer[i], p + i * BASE_SIZE, BASE_SIZE * sizeof(int));
    }

    // 打印数组信息
    printf("================================\n");
    for (int i = 0; i < BASE_SIZE; i++) {
        for (int j = 0; j < BASE_SIZE; j++) {
            printf("%d ", buffer[i][j]);
        }
        printf("\n");
    }

    // 清理共享内存
    iMem.clear();
    heap.clear();

    //ProcessState::self()->startThreadPool();
    //IPCThreadState::self()->joinThreadPool();
    return 0;
}
