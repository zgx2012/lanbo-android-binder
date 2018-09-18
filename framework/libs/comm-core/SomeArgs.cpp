#include "SomeArgs.h"

status_t SomeArgs::writeToParcel(Parcel* parcel) const {
    parcel->writeInt32(argi1);
    parcel->writeInt32(argi2);
    parcel->writeInt32(argi3);
    parcel->writeInt32(argi4);
    parcel->writeInt32(argi5);
    parcel->writeInt32(argi6);
    parcel->writeString16(arg1);
    parcel->writeString16(arg2);
    parcel->writeString16(arg3);
    parcel->writeString16(arg4);
    parcel->writeString16(arg5);
    parcel->writeString16(arg6);
    return NO_ERROR;
}

status_t SomeArgs::readFromParcel(const Parcel* parcel) {
    parcel->writeInt32(argi1);
    parcel->writeInt32(argi2);
    parcel->writeInt32(argi3);
    parcel->writeInt32(argi4);
    parcel->writeInt32(argi5);
    parcel->writeInt32(argi6);
    parcel->writeString16(arg1);
    parcel->writeString16(arg2);
    parcel->writeString16(arg3);
    parcel->writeString16(arg4);
    parcel->writeString16(arg5);
    parcel->writeString16(arg6);
    return NO_ERROR;
}

