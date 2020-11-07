#pragma once
#include"linklist.h"
//算法假定链表已按一定规则递增排序
template<typename T>
LinkList<T> retainAll(const LinkList<T>& one, const LinkList<T>& theOther) {
    LinkList<T>result;
    auto thisCur = *one, anotherCur = *theOther;
    while (thisCur && anotherCur) {
        if (thisCur->value == anotherCur->value) {
            result.addNode(thisCur->value);
            thisCur = thisCur->next;
            anotherCur = anotherCur->next;
        }
        else if (thisCur->value < anotherCur->value) {
            thisCur = thisCur->next;
        }
        else {
            anotherCur = anotherCur->next;
        }
    }
    return result;
}
//算法假定链表已按一定规则递增排序
template<typename T>
LinkList<T> addAll(const LinkList<T>& one, const LinkList<T>& theOther) {
    LinkList<T>result;
    auto thisCur = *one, anotherCur = *theOther;
    while (thisCur && anotherCur) {
        if (thisCur->value == anotherCur->value) {
            result.addNode(thisCur->value);
            thisCur = thisCur->next;
            anotherCur = anotherCur->next;
        }
        else if (thisCur->value < anotherCur->value) {
            result.addNode(thisCur->value);
            thisCur = thisCur->next;
        }
        else {
            result.addNode(anotherCur->value);
            anotherCur = anotherCur->next;
        }
    }
    while (thisCur) {
        result.addNode(thisCur->value);
        thisCur = thisCur->next;
    }
    while (anotherCur) {
        result.addNode(anotherCur->value);
        anotherCur = anotherCur->next;
    }
    return result;
}
//算法假定链表已按一定规则递增排序
template<typename T>
void removeAll(LinkList<T>& source, const LinkList<T>& selectSet) {
    auto sourceCur = *source, selectCur = *selectSet;
    decltype(sourceCur) pre = nullptr;
    while (sourceCur && selectCur) {
        if (sourceCur->value == selectCur->value) {
            auto tmp = sourceCur->next;
            source.deleteNodeAfter(pre);
            pre = tmp;
            sourceCur = tmp->next;
            selectCur = selectCur->next;
        }
        else if (sourceCur->value < selectCur->value) {
            pre = sourceCur;
            sourceCur = sourceCur->next;
        }
        else {
            selectCur = selectCur->next;
        }
    }
}