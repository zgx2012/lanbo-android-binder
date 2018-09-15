#ifndef FRAMEWORKS_COMMUNICATIONMODULE_H
#define FRAMEWORKS_COMMUNICATIONMODULE_H

#include <stdarg.h>
#include <utils/String16.h>
#include "comm.h"

namespace android
{

class CommunicationModule
{
public:
    CommunicationModule(const char* name);
    CommunicationModule(const String16& name);
    virtual ~CommunicationModule();
    virtual int sendEvent(const char* name, const char* to, const int event);
    virtual int sendEventSync(const char* name, const char* to, const int event);
    virtual int addEventListener(const char* name, const sp<IEventListener>& listener, const std::vector<int>& eventVector);
    virtual int methodCall(const char* name, const int method, va_list ap);
    virtual int methodCallReturn(const char* name, const int method, const sp<IReturnCallback>& callback, va_list ap);
    inline String16 getName() const {
        return mName;
    }

    inline bool localTarget(const char* from) const
    {
        return (String16(from) == mName);
    }

private:
    String16 mName;

}; // end class CommunicationModule

}; // end namespace android

#endif //FRAMEWORKS_COMMUNICATIONMODULE_H
