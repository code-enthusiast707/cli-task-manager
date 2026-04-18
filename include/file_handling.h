#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdio.h>
#include <string>

FILE *openTaskFile(const char *mode);

void closeTaskFile(FILE *fp);

char *readFileContent();

void writeFileContent(std::string taskBuff);

#endif