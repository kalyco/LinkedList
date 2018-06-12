
#include <iostream>
#include <cmath>
#include "TaskList.h"

using namespace std;

////////////////////////////////////////////////////////
// TaskListNode

TaskListNode::TaskListNode(float aTimeStamp,
			   std::string& aTaskTitle)
  : mTimeStamp(aTimeStamp), mTaskTitle(aTaskTitle), mNext(nullptr)
{
}

TaskListNode::TaskListNode(float aTimeStamp,
			   std::string& aTaskTitle,
			   TaskListNode* aNext)
  : mTimeStamp(aTimeStamp), mTaskTitle(aTaskTitle), mNext(aNext)
{
}

// Insert after this node
void TaskListNode::insertAfter(float aTimeStamp, string& aTaskTitle)
{
  mNext = new TaskListNode(aTimeStamp, aTaskTitle, mNext);
}

// Delete the node after this node
void TaskListNode::removeAfter()
{
  TaskListNode* temp = next();
  mNext = mNext->next();
  delete temp;
}

////////////////////////////////////////////////////////
// TaskList

TaskList::TaskList()
  : mHead(nullptr), mOrder(TaskList::ASCENDING)
{
}

TaskList::TaskList(TaskList::Order aOrder)
  : mHead(nullptr), mOrder(aOrder)
{
}

bool TaskList::isEmpty() const 
{
  return (mHead == nullptr);
}

// Adding to the front of the list
void TaskList::addTask(float aTimeStamp, 
		       string aTaskTitle)
{
  if (mHead != nullptr) {
    if (aTimeStamp == mHead->timeStamp()) {
      cerr << "Attempt to enter a conflicting task." << endl;
      cerr << "Not doing anything." << endl;
      return;
    }
    if (mOrder == TaskList::ASCENDING) {
      // Entering tasks in the ascending order
      if (aTimeStamp < mHead->timeStamp()) {
	cerr << "The enforced ordering is Ascending. Invalid entry."
	     << endl;
	cerr << "Not doing anything" << endl;
	return;
      }
    } else {
      // Entering tasks in the descending order
      if (aTimeStamp > mHead->timeStamp()) {
	cerr << "The enforced ordering is Descending. Invalid entry."
	     << endl;
	cerr << "Not doing anything." << endl;
	return;
      }
    }
  }
  mHead = new TaskListNode(aTimeStamp, aTaskTitle, mHead);
}

// Remove the front element
void TaskList::removeFront()
{
  TaskListNode* temp = mHead;
  mHead = mHead->next();
  delete temp;
}

// Delete a task matching a particular time-stamp
void TaskList::deleteTask(float aTimeStamp)
{
  TaskListNode* prev = mHead;
  for (; prev->next()->next()->timeStamp() == aTimeStamp; prev = prev->next());
  if (prev->next() != nullptr) {
    prev->removeAfter();
  } else {
    cerr << "No task matching timestamp." << endl;
  }
}

// Insert a new task at an appropriate position
void TaskList::insertTask(float aTimeStamp, std::string aTaskTitle)
{
   // Your implementation goes here
}

// Output the task list
void TaskList::output(std::ostream& s) const
{
  cout << "TODAY'S TASK LIST" << endl;
  if (mOrder == TaskList::ASCENDING) {
    // When the list is added in the ascending order
    // the list is stored in descending order
    cout << "(Descending Order)" << endl;
  } else {
    // vice versa
    cout << "(Ascending Order)" << endl;
  }
  if (isEmpty()) {
    cout << "No agenda!" << endl;
  }
  for (TaskListNode* currNode = mHead;
       currNode != nullptr; currNode = currNode->next()) {
    float taskTime = currNode->timeStamp();
    int hour = static_cast<int>(floor(taskTime));
    bool afternoon = false;
    int min = static_cast<int>(floor((taskTime-hour)*60));
    if (hour > 12) {
      afternoon = true;
      hour -= 12;
    }
    cout << hour << ":";
    if (min < 10) {
      cout << "0"; // padding a 0 for formatting
    }
    cout << min;
    cout << (afternoon? " PM" : " AM");
    cout << " - ";
    cout << currNode->taskTitle() << endl;
  }
}

// Delete all
void TaskList::removeAll()
{
   // Your implementation goes here
}

// Destructor
TaskList::~TaskList()
{
  removeAll();
}

// Reverse the list
void TaskList::reverse()
{
  TaskListNode * head = mHead;
  int count = 0;
  recursiveReverse(head, count);
  mOrder = TaskList::DESCENDING;  
}

void TaskList::recursiveReverse(TaskListNode* head_ref, int c) {
  TaskListNode * temp;
  if (head_ref == nullptr) {
    cout << "head nullptr, returning" << c << endl;
    return;
  }
  // divide list into 2 parts
  TaskListNode* first = head_ref;
  TaskListNode* rest = (head_ref)->next();
  c += 1;
  if (rest == nullptr) {
    return;
  }  

  // reverse the rest of the list and put 1st elem at end
  recursiveReverse(rest, c);
  cout << "count: " << c << endl;
  cout << "rest: " << rest->timeStamp() << endl; 
  cout << "first: " << first->timeStamp() << endl;
  // make new first (old last) and link to last in reversed rest.
  TaskListNode * cur = first->next();
  cur->setNext(first);
  first->setNext(nullptr);
 
  // rest always points to the last
  head_ref = rest;
  cout << "header " << (rest->timeStamp()) << endl;
}

std::ostream& operator<<(std::ostream& s, const TaskList& aTaskList)
{
  aTaskList.output(s);
  return s;
}
