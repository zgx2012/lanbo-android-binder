#include <utils/String16.h>
#include <utils/Singleton.h>
#include "Communication.h"

namespace android
{
void bpReturnMethodImpl(int method, Parcel& data, va_list ap)
{
    switch (method) {
        case METHOD_RETURN_ADD: {
            int result = va_arg(ap, int);
            data.writeInt32(result);
        } break;
    }
}

void bnReturnMethodImpl(int method, const Parcel& data)
{
    switch (method) {
        case METHOD_RETURN_ADD: {
            int result = data.readInt32();
        } break;
    }
}

/*
void bpSendEventImpl(int event, Parcel& data, va_list ap)
{

}

void bnSendEventImpl(int event, const Parcel& data)
{

}
*/

void bpEventImpl(int event, Parcel& data, va_list ap)
{
    switch (event) {
        case EVENT_HELLO: {

        } break;
    }
}

void bnEventImpl(int event, const Parcel& data)
{
    switch (event) {
        case EVENT_HELLO: {

        } break;
    }
}

}; // end namespace android
