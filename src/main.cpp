#include "../include/file_handling.h"
#include "../include/const.h"
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
using namespace constants;

char startQuote[50] = "\"";
const char endQuote[5] = "\"";

struct Task
{
      int id;
      char taskName[50];
      char status[20];
      char *createdAt[20];
      char *updatedAt[20];
};

vector<Task> getTasks(string data)
{
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

            int id;
            char taskName[50];
            sscanf(taskBuff, "\"id\":\"%d\",\"taskName\":%s", &id, taskName);
            struct Task newTask;
            newTask.id = id;
            strcpy(newTask.taskName, taskName);

            res.push_back(newTask);
            if (rightIndex >= data.length() - 1)
                  break;
            data = data.substr(rightIndex + 2);
      }
      return res;
}

vector<Task> readData()
{
      string str(readFileContent());
      int index = str.find_first_of(':');
      if (index < 0)
      {
            cout << "File is empty\n";
            return {};
      }
      str = str.substr(index + 2, str.substr(index + 2).length() - 2);
      return getTasks(str);
}

void handleAddAction(char *taskName)
{
      vector<Task> tasks = readData();
      Task newTask;
      if (tasks.empty())
      {
            newTask.id = 1;
      }
      else
      {
            newTask.id = tasks.back().id + 1;
      }
      strcpy(newTask.taskName, strcat(startQuote, strcat(taskName, endQuote)));

      tasks.push_back(newTask);

      string taskBuff = "";
      for (int i = 0; i < tasks.size(); i++)
      {
            char currentTask[200];
            sprintf(currentTask, "{\"id\":\"%d\",\"taskName\":%s}", tasks[i].id, tasks[i].taskName);
            taskBuff += currentTask;
            if (i != tasks.size() - 1)
            {
                  taskBuff += ",";
            }
      }
      writeFileContent(taskBuff);
}

int main(int argc, char *argv[])
{
      if (argc < 2)
      {
            cout << "Incomplete command\n";
            return 1;
      }

      string addStr = "add";
      if (addStr.compare(argv[1]) == 0)
      {
            handleAddAction(argv[2]);
      }
      else
      {
            cout << "Incorrect action\n";
      }
      cout << "\n";
      return 0;
}