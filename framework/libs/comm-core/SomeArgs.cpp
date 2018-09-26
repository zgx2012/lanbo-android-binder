#include <stdlib.h>
#include <string.h>
#include "SomeArgs.h"

namespace android
{

SomeArgs::SomeArgs() : arg1(0), arg2(0), arg3(0), arg4(0), arg5(0), arg6(0),
    argi1(0), argi2(0), argi3(0), argi4(0), argi5(0), argi6(0) {
}

SomeArgs::~SomeArgs() {
    if (arg1 != NULL) {
        free(arg1);
        arg1 = NULL;
    }

    if (arg2 != NULL) {
        free(arg2);
        arg2 = NULL;
    }

    if (arg3 != NULL) {
        free(arg3);
        arg3 = NULL;
    }

    if (arg4 != NULL) {
        free(arg4);
        arg4 = NULL;
    }

    if (arg5 != NULL) {
        free(arg5);
        arg5 = NULL;
    }

    if (arg6 != NULL) {
        free(arg6);
        arg6 = NULL;
    }
}

static void writeCString(Parcel* parcel, char* str) {
    int len = str == NULL ? 0 : strlen(str);
    parcel->writeInt32(len);
    if (len > 0) parcel->writeCString(str);
}

status_t SomeArgs::writeToParcel(Parcel* parcel) const {
    parcel->writeInt32(argi1);
    parcel->writeInt32(argi2);
    parcel->writeInt32(argi3);
    parcel->writeInt32(argi4);
    parcel->writeInt32(argi5);
    parcel->writeInt32(argi6);

    writeCString(parcel, arg1);
    writeCString(parcel, arg2);
    writeCString(parcel, arg3);
    writeCString(parcel, arg4);
    writeCString(parcel, arg5);
    writeCString(parcel, arg6);
    return NO_ERROR;
}

static char* readCString(const Parcel* parcel) {
    int len = parcel->readInt32();
    char* result = NULL;
    if (len > 0) {
        const char* str = parcel->readCString();
        result = (char*) malloc(len + 1);
        memcpy(result, str, len);
        result[len] = 0;
    }
    return result;
}

status_t SomeArgs::readFromParcel(const Parcel* parcel) {
    argi1 = parcel->readInt32();
    argi2 = parcel->readInt32();
    argi3 = parcel->readInt32();
    argi4 = parcel->readInt32();
    argi5 = parcel->readInt32();
    argi6 = parcel->readInt32();

    arg1 = readCString(parcel);
    arg2 = readCString(parcel);
    arg3 = readCString(parcel);
    arg4 = readCString(parcel);
    arg5 = readCString(parcel);
    arg6 = readCString(parcel);

    return NO_ERROR;
}

static char* copy(char* str) {
    char* result = NULL;
    if (str != NULL) {
        int len = strlen(str);
        result = (char*) malloc(len + 1);
        memcpy(result, str, len);
        result[len] = 0;
    }
    return result;
}

void SomeArgs::copyFrom(const SomeArgs& a) {
    argi1 = a.argi1;
    argi2 = a.argi2;
    argi3 = a.argi3;
    argi4 = a.argi4;
    argi5 = a.argi5;
    argi6 = a.argi6;

    arg1 = copy(a.arg1);
    arg2 = copy(a.arg2);
    arg3 = copy(a.arg3);
    arg4 = copy(a.arg4);
    arg5 = copy(a.arg5);
    arg6 = copy(a.arg6);
}

void SomeArgs::copyFrom(const SomeArgs* a) {
    argi1 = a->argi1;
    argi2 = a->argi2;
    argi3 = a->argi3;
    argi4 = a->argi4;
    argi5 = a->argi5;
    argi6 = a->argi6;

    arg1 = copy(a->arg1);
    arg2 = copy(a->arg2);
    arg3 = copy(a->arg3);
    arg4 = copy(a->arg4);
    arg5 = copy(a->arg5);
    arg6 = copy(a->arg6);
}
};
