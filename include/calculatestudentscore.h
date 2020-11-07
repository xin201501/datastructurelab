#pragma once
#include<initializer_list>
#include<exception>
#include<functional>
#include"linklist.h"
class StudentScore {
private:
    LinkList<double> scores;
public:
    StudentScore() = default;
    StudentScore(std::initializer_list<double>scoreSet) {
        for (const auto& x : scoreSet) {
            if (x < 0) {
                throw std::invalid_argument(std::string("score number can't below zero!the number is:") + std::to_string(x));
            }
            scores.addNode(x);
        }
    }
    double getMaxGrade() {
        LinkNode<double>* cur = *scores;
        double maxValue = cur->value;
        cur = cur->next;
        while (cur) {
            if (cur->value > maxValue) {
                maxValue = cur->value;
            }
            cur = cur->next;
        }
        return maxValue;
    }
    double getMinGrade() {
        LinkNode<double>* cur = *scores;
        double minValue = cur->value;
        cur = cur->next;
        while (cur) {
            if (cur->value < minValue) {
                minValue = cur->value;
            }
            cur = cur->next;
        }
        return minValue;
    }
    double getAverage() {
        LinkNode<double>* cur = *scores;
        double sum = 0;size_t count = 0;
        while (cur) {
            sum += cur->value;
            count++;
            cur = cur->next;
        }
        return sum / count;
    }
    void sort(const std::function<bool(double, double)>& rule = [](double x1, double x2) {
        return x1 < x2;
        }) {
        scores.sort(rule);
    }
    void displayAllScores() {
        std::cout << scores;
    }
};