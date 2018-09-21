#ifndef FRAMEWORKS_EVENTMANAGER_H
#define FRAMEWORKS_EVENTMANAGER_H

#include <List.h>
#include <Mutex.h>
#include <Singleton.h>

namespace android
{

class EventQueue
{
public:
    class Event {
    public:
        inline Event(int e, const Parcelable* p) : event(e), parcelable(p)  {}
        inline ~Event() {}

        int event;
        Parcelable *parcelable;
    };

public:
    EventQueue(){}
    ~EventQueue(){}

public:
    void enqueue(const Event& e);
    Event& dequeue() const;

private:
    Condition mCondition;
    Mutex mLock;
    List<Event> mEventList;

}; // end class EventQueue

class EventManager : public Singleton<EventManager>
{
public:
    EventManager();
    ~EventManager();

public:
    Event& EventManager::getEvent() const;
    void putEvent(const Event& event);

private:
    EventQueue mQueue;

}; // end class EventManager

}; // end namespace android

#endif //FRAMEWORKS_EVENTMANAGER_H
