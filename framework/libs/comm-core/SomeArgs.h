#ifndef FRAMEWORKS_SOMEARGS_H
#define FRAMEWORKS_SOMEARGS_H

#include "comm.h"

namespace android
{

class SomeArgs : public Parcelable
{
public:
    SomeArgs(){}
    virtual ~SomeArgs(){}

    virtual status_t writeToParcel(Parcel* parcel) const;
    virtual status_t readFromParcel(const Parcel* parcel);

public:
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

};

#endif //FRAMEWORKS_SOMEARGS_H
