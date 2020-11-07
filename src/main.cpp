#include<iostream>
#include"calculatestudentscore.h"
#include"setoperation.h"
using std::cin;
using std::endl;
using std::cout;
int main(int argc, char const* argv[])
{
    StudentScore scores = { 20,80,70,40,50,60,70 };
    cout << scores.getMaxGrade() << " " << scores.getMinGrade() << " " << scores.getAverage() << endl;
    scores.sort();
    scores.displayAllScores();
    cout << endl;
    LinkList<int> l1{ 20,42,14,25,36 };
    cout << l1 << endl;
    LinkList<int> l2{ 10,50,25,70 };
    cout << l2 << endl;
    l1.sort();
    l2.sort();
    removeAll(l1, l2);
    cout << l1;
}