
#include <iostream>
#include "TaskList.h"

using namespace std;

int main()
{
  TaskList tl(TaskList::ASCENDING);
  tl.addTask(6.0, "Wake up");
  tl.addTask(6.75, "Exercise");
  tl.addTask(8.25, "Breakfast");
  cout << "Beginning list" << endl;
  cout << tl << endl;

  tl.deleteTask(6.75);
  cout << "List after deleting the entry at 6.75" << endl;
  cout << tl << endl;

  tl.addTask(6.25, "Go to Gym");
  tl.addTask(9.2, "Study data structures");
  tl.addTask(11.3, "Lunch");
  tl.addTask(15.5, "Play soccer");
  tl.addTask(19, "Data structures class");
  tl.addTask(22.25, "Go to bed");

  cout << "List after adding a bunch of tasks" << endl;
  cout << tl << endl;
  
  tl.deleteTask(15.5);
  cout << "List after deleting the entry at 15.5" << endl;
  cout << tl << endl;

  tl.insertTask(13.5, "Go to library");
  cout << "List after inserting a new entry at 13.5" << endl;
  cout << tl << endl;

  tl.reverse();
  cout << "List after reversing" << endl;
  cout << tl << endl;

  tl.removeAll();
  cout << "List after removing all" << endl;
  cout << tl << endl;
  return 0;
}
