#include "EventManager.h"

namespace android
{

void EventManager::EventQueue::enqueue(const EventManager::Event& e)
{
    if (mEventList == NULL) mEventList = new List<EventManager::Event>;
    mEventList->push_back(e);
    mCondition->signal();
}

EventManager::Event& EventManager::EventQueue::dequeue() const
{
    if (mEventList == NULL || mEventList->empty()) {
        mCondition->wait(*mLock);
    }
    List<EventManager::Event>::iterator it = mEventList->begin();
    Event& event = *it;
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

EventManager::Event& EventManager::getEvent() const
{
    return mQueue.dequeue();
}

void EventManager::putEvent(const EventManager::Event& event)
{
    mQueue.enqueue(event);
}

void EventManager::dump()
{
    // start dump event queue
}

}; // end namespace android



