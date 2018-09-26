#include "EventManager.h"
#include "SomeArgs.h"

namespace android
{

void EventManager::EventQueue::enqueue(EventManager::Event* e)
{
    SomeArgs* args = e->args;
    printf("%s %d, %s\n", __FUNCTION__, e->event, args == NULL ? "NULL" : args->arg1);
    if (mEventList == NULL) mEventList = new List<EventManager::Event*>;
    mEventList->push_back(e);
    mCondition->signal();
}

EventManager::Event* EventManager::EventQueue::dequeue() const
{
    if (mEventList == NULL || mEventList->empty()) {
        mCondition->wait(*mLock);
    }
    List<EventManager::Event*>::iterator it = mEventList->begin();
    Event* event = *it;

    SomeArgs* args = event->args;
    printf("%s %d, %s\n", __FUNCTION__, event->event, args == NULL ? "NULL" : args->arg1);

    mEventList->erase(it);
    return event;
}; // end class EventQueue


ANDROID_SINGLETON_STATIC_INSTANCE(EventManager);
EventManager::EventManager():Singleton<EventManager>()
{
}

EventManager::~EventManager()
{
}

EventManager::Event* EventManager::getEvent() const
{
    return mQueue.dequeue();
}

void EventManager::putEvent(EventManager::Event* event)
{
    SomeArgs* args = event->args;
    if (args != NULL) {
        printf("%s %d, %s\n", __FUNCTION__, event->event, args->arg1);
    } else {
        printf("%s %d, NULL\n", __FUNCTION__, event->event, args);
    }
    mQueue.enqueue(event);
}

void EventManager::dump()
{
    // start dump event queue
}

}; // end namespace android



