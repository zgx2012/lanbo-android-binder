#include "ListenerManager.h"

extern p_listener* events = 0;
extern p_event_listener listenerHead = 0;
extern p_event_listener listenerTail = 0;

static int hash(void* key) {
    return (int)key;
}

static bool equals(void* keyA, void* keyB) {
    return keyA == keyB;
}

ANDROID_SINGLETON_STATIC_INSTANCE(ListenerManager);

ListenerManager::ListenerManager():Singleton<ListenerManager>() {
    initListenerManager();
}

ListenerManager::~ListenerManager() {
}

void ListenerManager::initListenerManager() {
    mEvents.setCapacity(MAX_EVENT_NUM);
    mListenerMap = hashmapCreate(64, hash, equals);

    listeners = new _event_listener[MAX_LISTENER];
}

void ListenerManager::removeListener(const sp<IEventListener>& l) {
    p_event_listener value = hashmapRemove(mListenerMap, l.get());
    if (value == 0) return;

    value->listener;
    value->name;
    value->events;

    removeEvents(l, value->events);

    delete value;
}

void ListenerManager::addListener(const sp<IEventListener>& l, const String16& n, const std::vector<int>& events) {
    BigBitSet eventSet, moreSet, mergedSet;
    for(int i=0;i<events.size();i++) {
        index = ((~EVENT_MASK) & events[i]); // event unmark
        eventSet.markBit(index);
    }
    moreSet = eventSet;
    mergedSet = eventSet;

    // 创建listener
    p_event_listener value = hashmapGet(mListenerMap, l.get());
    const std::vector<int> increased;
    if (value == 0) {
        p_event_listener value = new _event_listener;
    } else {
        // find diff events
        moreSet = ((~(value->events)) & eventSet); // moreSet = new event set - old event set
        mergedSet |= value->events; // mregedSet = new event set + old event set

        std::set<int> oldSet(value->events.begin(), value->events.end());
    }
    value->listener = l;
    value->name = n;
    value->events = mergedSet;

    // 将listener存到map中
    hashmapPut(mListenerMap, l.get(), value);

    // 所有对应的event中，加入指向该listener的节点
    addEvents(value, moreSet);
}

void ListenerManager::addEvents(p_event_listener value, const BigBitSet& events) {
    // 所有对应的event中，加入指向该listener的节点
    if (events.isEmpty()) return;
    int first = events.firstMarkedBit;
    int last = events.lastMarkedBit();

    for(int i = first; i < last; i++) {
        mEvents[i].push_back(value);
    }
}

void ListenerManager::removeEvents(const sp<IEventListener>& l, const BigBitSet& events) {
    if (events.isEmpty()) return;
    int first = events.firstMarkedBit;
    int last = events.lastMarkedBit();

    for(int i = first; i < last; i++) {
        // 循环mEvents[index]列表，删除 l
        for(List<p_event_listener>::iterator it = mEvents[i].begin(); it < mEvents[i].end(); it++) {
            if (it->listener == l) {
                mEvents[i].erase(it);
                break;
            }
        }
    }
}

void ListenerManager::dispatch(int event, Parcelable* p) {
    int index = ((~EVENT_MASK) & events[i]);
    const List<p_event_listener>& list = mEvents[index];
    for(List<p_event_listener>::iterator it = list.begin(); it < list.end(); it++) {
        it->listener->onEvent(event, p);
    }
}

