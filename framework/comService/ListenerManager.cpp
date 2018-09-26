#include <stdlib.h>
#include <string.h>

#include "ListenerManager.h"
#include "IEventListener.h"
#include "SomeArgs.h"

namespace android
{

static int hash(void* key) {
    return *((int*) key);
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
    printf("%s\n", __FUNCTION__);
    //mEvents.setCapacity(MAX_EVENT_NUM);
    mEvents = (List<p_event_listener>**)malloc(MAX_EVENT_NUM * sizeof(List<p_event_listener>*));
    for(int i=0;i<MAX_EVENT_NUM;i++) {
        mEvents[i]=NULL;
    }
    mListenerMap = hashmapCreate(64, hash, equals);
}

void ListenerManager::removeListener(const sp<IEventListener>& l) {
    printf("%s\n", __FUNCTION__);
    p_event_listener value = (p_event_listener)hashmapRemove(mListenerMap, l.get());
    if (value == 0) return;

    //value->listener;
    if (value->name != NULL) {
        free(value->name);
    };
    //value->events;

    removeEvents(l, value->events);

    delete value;
}

void ListenerManager::addListener(const sp<IEventListener>& l, const char* n, const std::vector<int>& events) {
    printf("%s %s\n", __FUNCTION__, n);
    BigBitSet eventSet, moreSet, mergedSet;
    for(int i=0;i<events.size();i++) {
        int index = ((~EVENT_MASK) & events[i]); // event unmark
        eventSet.markBit(index);
    }
    moreSet = eventSet;
    mergedSet = eventSet;
    printf("events: %0lx\n", mergedSet.getValue());

    printf("get old listener\n");
    // 创建listener
    p_event_listener value = (p_event_listener)hashmapGet(mListenerMap, l.get());
    const std::vector<int> increased;
    if (value == 0) {
        printf("no old listener\n");
        value = new _event_listener;
    } else {
        // find diff events
        moreSet = ((~(value->events)) & eventSet); // moreSet = new event set - old event set
        mergedSet |= value->events; // mregedSet = new event set + old event set
    }
    value->events = mergedSet;
    value->listener = l;
    int len = n == NULL ? 0 : strlen(n);
    value->name = (char*)malloc(len+1);
    memcpy(value->name, n, len);
    value->name[len]=0;

    printf("save listener\n");
    // 将listener存到map中
    hashmapPut(mListenerMap, l.get(), value);

    // 所有对应的event中，加入指向该listener的节点
    addEvents(value, moreSet);
}

void ListenerManager::addEvents(p_event_listener value, const BigBitSet& events) {
    printf("%s\n", __FUNCTION__);
    // 所有对应的event中，加入指向该listener的节点
    if (events.isEmpty()) return;
    int first = events.firstMarkedBit();
    int last = events.lastMarkedBit();

    printf("first %d, last %d\n", first, last);
    for(int i = first; i <= last; i++) {
        List<p_event_listener>* list = mEvents[i];
        if (list == NULL) {
            list = mEvents[i] = new List<p_event_listener>;
            //mEvents[i].replaceAt(list, i);
        }
        list->push_back(value);
    }
}

void ListenerManager::removeEvents(const sp<IEventListener>& l, const BigBitSet& events) {
    printf("%s\n", __FUNCTION__);
    if (events.isEmpty()) return;
    int first = events.firstMarkedBit();
    int last = events.lastMarkedBit();

    for(int i = first; i < last; i++) {
        // 循环mEvents[index]列表，删除 l
        List<p_event_listener>* list = mEvents[i];
        if (list == NULL) continue;
        List<p_event_listener>::iterator it = list->begin();
        for(; it != list->end(); it++) {
            if ((*it)->listener == l) {
                list->erase(it);
                break;
            }
        }
    }
}

void ListenerManager::dispatch(int event, const Parcelable* p) {
    int index = ((~EVENT_MASK) & event);
    printf("%s %d %d\n", __FUNCTION__, event, index);

    const List<p_event_listener>* list = mEvents[index];
    if (list == NULL) return;
    List<p_event_listener>::const_iterator it = list->begin();
    for(; it != list->end(); it++) {
        printf("dispatch event to listener\n");
        SomeArgs* args = (SomeArgs*)p;
        printf("args: %s\n", args->arg1);
        (*it)->listener->onEvent(event, p);
    }
}

static bool callback(void* key, void* value, void* context) {
    const IEventListener* l = (IEventListener*) key;
    ListenerManager::p_event_listener pl = (ListenerManager::p_event_listener) value;
    printf("%p, {%s, %p, %0lx}\n", l, pl->name, pl->listener.get(), pl->events.getValue());
    return true;
}

void ListenerManager::dump() {
    // start dump listeners
    RWLock::AutoRLock rLock(mRWLock);

    printf("Events:\n");
    //for(int i = 0; i < mEvents.size(); i++) {
    for(int i = 0; i < MAX_EVENT_NUM; i++) {
        List<p_event_listener>* list = mEvents[i];
        if (list == NULL) continue;
        printf("\n[%d]", i);
        List<p_event_listener>::iterator it = list->begin();
        for(; it != list->end(); it++) {
            printf("->{%s, %p, %0lx}", (*it)->name, (*it)->listener.get(), (*it)->events.getValue());
        }
    }
    printf("\n");
    printf("Listeners:\n");
    hashmapForEach(mListenerMap, callback, NULL);
    //mListenerMap
}

}; // end namespace android
