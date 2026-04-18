#include "../include/file_handling.h"
#include "../include/const.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;
using namespace constants;

FILE *openTaskFile(const char *mode)
{
      FILE *filePtr = fopen("tasks.json", mode);
      if (!filePtr)
      {
            cout << "Failed to open file\n";
            return nullptr;
      }
      else
      {
            char displayMode[10] = "write";
            if (strcmp(mode, readMode) == 0)
            {
                  strcpy(displayMode, "read");
            }
            cout << "File opened successfully in " << displayMode << " mode\n";
            return filePtr;
      }
}

void closeTaskFile(FILE *fp)
{
      int res = fclose(fp);
      if (res == 0)
      {
            cout << "File closed successfully\n";
      }
      else
      {
            cout << "File close failed\n";
      }
}

char *readFileContent()
{
      FILE *filePtr = openTaskFile(readMode);
      if (filePtr == nullptr)
      {
            return {};
      }
      fseek(filePtr, 0, SEEK_END);
      long fileSize = ftell(filePtr);
      char *buffer = (char *)malloc(sizeof(char) * fileSize);
      rewind(filePtr);

      int bytes = fread(buffer, sizeof(char), fileSize, filePtr);
      if (bytes == fileSize)
      {
            cout << "File read successfully\n";
      }
      else
      {
            cout << "Failed to read the entire file\n";
      }

      closeTaskFile(filePtr);
      return buffer;
}

void writeFileContent(string taskBuff)
{
      FILE *filePtr = openTaskFile(writeMode);
      int res = fprintf(filePtr, "{\"data\":[%s]}", taskBuff.c_str());
      if (res >= 0)
      {
            cout << "Task added successfully\n";
      }
      else
      {
            cout << "Task add failed\n";
      }

      closeTaskFile(filePtr);
}