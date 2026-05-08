#include "../include/file_handling.h"
#include "../include/const.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>

using namespace std;
using namespace constants;

struct Task
{
      int id;
      char taskName[50];
      int status;
      char createdAt[50];
      char updatedAt[50];
};

void setCurrentTime(char *currentTime)
{
      time_t timeObj = time(nullptr);
      tm *localTime = localtime(&timeObj);
      strftime(currentTime, 50, "%F %R", localTime);
}

string tasksToString(vector<Task> tasks)
{
      string taskBuff = "";
      for (int i = 0; i < tasks.size(); i++)
      {
            char currentTask[256];
            sprintf(currentTask, "{\"id\":\"%d\",\"status\":\"%d\",\"taskName\":\"%s\",\"createdAt\":\"%s\",\"updatedAt\":\"%s\"}", tasks[i].id, tasks[i].status, tasks[i].taskName, tasks[i].createdAt, tasks[i].updatedAt);
            taskBuff += currentTask;
            if (i != tasks.size() - 1)
            {
                  taskBuff += ",";
            }
      }
      return taskBuff;
}

vector<Task> getAllTasks()
{
      string data(readFileContent());
      int index = data.find_first_of(':');
      if (index < 0)
      {
            cout << "File is empty\n";
            return {};
      }
      data = data.substr(index + 2, data.substr(index + 2).length() - 2);

      vector<Task> res;
      while (data.find_first_of(openBrace) != data.npos && data.find_first_of(closeBrace) != data.npos)
      {
            int leftIndex = data.find_first_of(openBrace);
            int rightIndex = data.find_first_of(closeBrace);
            int count = data.length() - data.substr(rightIndex).length() - 1;

            string currentTask = data.substr(leftIndex + 1, count);
            char *taskBuff = (char *)malloc(currentTask.size() + 1);
            currentTask.copy(taskBuff, currentTask.size());
            taskBuff[currentTask.size()] = '\0';

            int id, status;
            char taskName[50], createdAt[50], updatedAt[50];
            sscanf(taskBuff, "\"id\":\"%d\",\"status\":\"%d\",\"taskName\":\"%[^\"]\",\"createdAt\":\"%[0-9- :]\",\"updatedAt\":\"%[0-9- :]\"", &id, &status, taskName, createdAt, updatedAt);
            struct Task newTask;
            newTask.id = id;
            newTask.status = status;
            strcpy(newTask.taskName, taskName);
            strcpy(newTask.createdAt, createdAt);
            strcpy(newTask.updatedAt, updatedAt);
            res.push_back(newTask);
            if (rightIndex >= data.length() - 1)
                  break;
            data = data.substr(rightIndex + 2);
      }
      return res;
}

string addTask(vector<Task> tasks, char *taskName)
{
      Task newTask;
      if (tasks.empty())
      {
            newTask.id = 1;
      }
      else
      {
            newTask.id = tasks.back().id + 1;
      }
      strcpy(newTask.taskName, taskName);
      newTask.status = 0;

      char currentTime[50];
      setCurrentTime(currentTime);
      strcpy(newTask.createdAt, currentTime);
      strcpy(newTask.updatedAt, currentTime);

      tasks.push_back(newTask);

      return tasksToString(tasks);
}

string updateTask(vector<Task> tasks, int taskId, char *taskName)
{
      for (int i = 0; i < tasks.size(); i++)
      {
            if (tasks[i].id == taskId)
            {
                  strcpy(tasks[i].taskName, taskName);
                  char currentTime[50];
                  setCurrentTime(currentTime);
                  strcpy(tasks[i].updatedAt, currentTime);
                  break;
            }
      }

      return tasksToString(tasks);
}

int main(int argc, char *argv[])
{
      if (argc < 2)
      {
            cout << "Incomplete command\n";
            return 1;
      }

      vector<Task> tasks = getAllTasks();
      string res = "";
      string addStr = "add", uptStr = "update";
      if (addStr.compare(argv[1]) == 0)
      {
            res = addTask(tasks, argv[2]);
      }
      else if (uptStr.compare(argv[1]) == 0)
      {
            res = updateTask(tasks, atoi(argv[2]), argv[3]);
      }
      else
      {
            cout << "Incorrect action\n";
      }
      writeFileContent(res);
      return 0;
}