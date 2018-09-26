#ifndef FRAMEWORKS_EVENTLISTENER_H
#define FRAMEWORKS_EVENTLISTENER_H

#include <binder/Parcel.h>
#include <binder/BinderService.h>
#include <IEventListener.h>
#include "communication/Communication.h"
#include "CommonService.h"

namespace android {

class EventListener :
    public BnEventListener
{
public:
            EventListener();
    virtual ~EventListener();
    virtual void onEvent(int event, const Parcelable* parcelable);
}; // end class EventListener



}; // end namespace android

#endif //FRAMEWORKS_EVENTLISTENER_H
