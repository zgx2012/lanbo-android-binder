#ifndef FRAMEWORKS_SOMEARGS_H
#define FRAMEWORKS_SOMEARGS_H

#include "comm.h"

class SomeArgs : public Parcelable
{
    SomeArgs(){}
    ~SomeArgs(){}

    status_t writeToParcel(Parcel* parcel) const;
    status_t readFromParcel(const Parcel* parcel);

    String16 arg1;
    String16 arg2;
    String16 arg3;
    String16 arg4;
    String16 arg5;
    String16 arg6;
    int argi1;
    int argi2;
    int argi3;
    int argi4;
    int argi5;
    int argi6;
};

#endif //FRAMEWORKS_SOMEARGS_H
