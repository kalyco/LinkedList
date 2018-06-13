
#ifndef TASK_LIST_H
#define TASK_LIST_H

#include <iostream>

class TaskListNode {

 public:
  // Constructors
  TaskListNode(float aTimeStamp, std::string& aTaskTitle);
  TaskListNode(float aTimeStamp, std::string& aTaskTitle, TaskListNode* aNext);

  // Getters
  float timeStamp() const { return mTimeStamp; }
  const std::string& taskTitle() const { return mTaskTitle; }
  TaskListNode* next() { return mNext; }
  const TaskListNode* next() const { return mNext; }

  // Setter
  void setNext(TaskListNode* aNext) { mNext = aNext; }

  // Insert after this node
  void insertAfter(float aTimeStamp, std::string& aTaskTitle);

  // Delete the node after this node
  void removeAfter();

 private:
  float mTimeStamp;
  std::string mTaskTitle;
  TaskListNode* mNext;
};

class TaskList {
 public:

  enum Order {
    ASCENDING,
    DESCENDING
  };

  TaskList(); 
  TaskList(TaskList::Order aOrder);
  ~TaskList();

  void recursiveReverse(TaskListNode*);

  // Check if empty
  bool isEmpty() const;

  // Add new task
  void addTask(float aTimeStamp, 
	  std::string aTaskTitle);
	       
  // Remove the front element
  void removeFront();

  // Delete a task matching a particular time-stamp
  void deleteTask(float aTimeStamp);

  // Insert a new task at an appropriate position
  void insertTask(float aTimeStamp, std::string aTaskTitle);

  // Output the task list
  void output(std::ostream& s) const;

  // Delete all
  void removeAll();

  // Reverse the list
  void reverse();

  bool atPoint(TaskListNode* curr, float aTimeStamp);

 private:
  TaskListNode* mHead;
  TaskList::Order mOrder;
};

std::ostream& operator<<(std::ostream& s, const TaskList& aTaskList);

#endif
