#include "SomeArgs.h"

namespace android
{

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
    argi1 = parcel->readInt32();
    argi2 = parcel->readInt32();
    argi3 = parcel->readInt32();
    argi4 = parcel->readInt32();
    argi5 = parcel->readInt32();
    argi6 = parcel->readInt32();
    arg1 = parcel->readString16();
    arg2 = parcel->readString16();
    arg3 = parcel->readString16();
    arg4 = parcel->readString16();
    arg5 = parcel->readString16();
    arg6 = parcel->readString16();
    return NO_ERROR;
}

};
