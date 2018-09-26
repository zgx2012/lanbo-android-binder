#ifndef FRAMEWORKS_SOMEARGS_H
#define FRAMEWORKS_SOMEARGS_H

#include "comm.h"

namespace android
{

class SomeArgs : public Parcelable
{
public:
    SomeArgs();
    ~SomeArgs();

    status_t writeToParcel(Parcel* parcel) const;
    status_t readFromParcel(const Parcel* parcel);
    void copyFrom(const SomeArgs& a);
    void copyFrom(const SomeArgs* a);

public:
    char* arg1;
    char* arg2;
    char* arg3;
    char* arg4;
    char* arg5;
    char* arg6;
    int argi1;
    int argi2;
    int argi3;
    int argi4;
    int argi5;
    int argi6;
};

};

#endif //FRAMEWORKS_SOMEARGS_H
