
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

bool TaskList::atPoint(TaskListNode* curr, float aTimeStamp) {
  if (mOrder == TaskList::ASCENDING) {
    return curr->timeStamp() <= aTimeStamp;
  } else {
    return curr->timeStamp() >= aTimeStamp;
  }
}; 

// Insert a new task at an appropriate position
void TaskList::insertTask(float aTimeStamp, std::string aTaskTitle)
{
  // Store prev value
  TaskListNode * prev;
  TaskListNode * curr = mHead;

  while(!atPoint(curr, aTimeStamp)) {
    prev = curr;
    curr = curr->next();
  }
  curr = new TaskListNode(aTimeStamp, aTaskTitle, curr);
  prev->setNext(curr);
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
  if (mHead == nullptr) return;

  TaskListNode * curr = mHead;
  TaskListNode * next;
    while(curr != nullptr) {
    next = curr->next();
    delete curr;
    curr = next;
  }
  mHead = nullptr;
}

// Destructor
TaskList::~TaskList()
{
  removeAll();
}

// Reverse the list
void TaskList::reverse()
{
  if (mOrder == TaskList::DESCENDING) {
    mOrder = TaskList::ASCENDING;
   } else {
    mOrder = TaskList::DESCENDING;
   }  
  if (mHead == nullptr) return;

  recursiveReverse(mHead);
}

void TaskList::recursiveReverse(TaskListNode* head_ref) {
  if (head_ref == nullptr) return;
  TaskListNode* rest = (head_ref)->next();
  if (rest == nullptr) {
    mHead = head_ref;
    return;
  }  
  recursiveReverse(rest);
  rest->setNext(head_ref);
  head_ref->setNext(nullptr);
 
  head_ref = rest;
}

std::ostream& operator<<(std::ostream& s, const TaskList& aTaskList)
{
  aTaskList.output(s);
  return s;
}
