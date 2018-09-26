#define LOG_TAG "EventListener"
#define LOG_NDEBUG 0

#include <utils/Log.h>
#include "EventListener.h"
#include "SomeArgs.h"

namespace android {
EventListener::EventListener()
    : BnEventListener()
{
    ALOGI("%s", __FUNCTION__);
}

EventListener::~EventListener()
{
    ALOGI("%s", __FUNCTION__);
}

void EventListener::onEvent(int event, const Parcelable* parcelable)
{
    printf("%s, event = %d\n", __FUNCTION__, event);

    SomeArgs* args = (SomeArgs*) parcelable;

    switch(event) {
        case EVENT_HELLO: {
            printf("hello: %s\n", args->arg1);
        } break;
    }

}

}; // end namespace android