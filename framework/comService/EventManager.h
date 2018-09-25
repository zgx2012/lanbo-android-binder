#ifndef FRAMEWORKS_EVENTMANAGER_H
#define FRAMEWORKS_EVENTMANAGER_H

#include <utils/Singleton.h>
#include <utils/Mutex.h>
#include <utils/List.h>
#include <binder/Parcelable.h>

namespace android
{

class EventManager : public Singleton<EventManager>
{

public:
    class Event {
    public:
        inline Event(int e, const Parcelable* p) : event(e), parcelable(p)  {}
        inline ~Event() {}

        int event;
        const Parcelable *parcelable;
    }; // end class Event

    class EventQueue
    {
    public:
        EventQueue(){
            mLock = new Mutex;
            mCondition = new Condition;
        }
        ~EventQueue(){
            delete mCondition;
            delete mLock;
        }

        void enqueue(const Event& e);
        Event& dequeue() const;

    private:
        Condition *mCondition;
        Mutex *mLock;
        List<Event> *mEventList;

    }; // end class EventQueue

public:
    EventManager();
    ~EventManager();

    Event& getEvent() const;
    void putEvent(const Event& event);

private:
    EventQueue mQueue;

}; // end class EventManager

}; // end namespace android

#endif //FRAMEWORKS_EVENTMANAGER_H
