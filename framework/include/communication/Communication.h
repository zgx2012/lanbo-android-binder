#ifndef FRAMEWORKS_COMMUNICATION_H
#define FRAMEWORKS_COMMUNICATION_H
#include "comm.h"
//#include "IReturnCallback.h"
//#include "BaseModuleFactory.h"

namespace android {

#define MODULE_NAME_A "module_a"
#define MODULE_NAME_B "module_b"
#define MODULE_NAME_C "module_c"
#define MODULE_COMM_SERVICE COMM_SERVICE_NAME

//-----------------------------------------------------------------
#define METHOD_SET_VALUE            (METHOD_MASK | 0x01)
#define METHOD_ADD_EVENT_LISTENER   (METHOD_MASK | 0x02)
#define METHOD_SEND_EVENT           (METHOD_MASK | 0x03)
//-----------------------------------------------------------------
#define METHOD_RETURN_ADD       (METHOD_RETURN_MASK | 0x01)
//-----------------------------------------------------------------
#define EVENT_HELLO             (EVENT_MASK | 0x01)
//-----------------------------------------------------------------

void bpReturnMethodImpl(int method, Parcel& data, va_list ap);
void bnReturnMethodImpl(int method, const Parcel& data);

void bpEventImpl(int event, Parcel& data, va_list ap);
void bnEventImpl(int event, const Parcel& data);
//bpReturnMethod = bpReturnMethodImpl;
//bnReturnMethod = bnReturnMethodImpl;

}; // end namespace android

#endif //FRAMEWORKS_COMMUNICATION_H