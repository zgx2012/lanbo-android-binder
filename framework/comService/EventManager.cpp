#include "EventManager.h"

namespace android
{

void EventQueue::enqueue(const Event& e)
{
    mEventList.push_back(e);
    mCondition.signal();
}

Event& EventQueue::dequeue() const
{
    if (mEventList.empty()) {
        mCondition.wait(mLock);
    }
    List<Event>::iterator it = mEventList.begin();
    const Event& event = *it;
    mEventList.erase(it);
    return event;
}; // end class EventQueue


ANDROID_SINGLETON_STATIC_INSTANCE(EventManager);

EventManager::EventManager():Singleton<EventManager>()
{
}

EventManager::~EventManager()
{
}

Event& EventManager::getEvent() const
{
    return mQueue.dequeue();
}

void EventManager::putEvent(const Event& event)
{
    mQueue.enqueue(event);
}

}; // end namespace android



