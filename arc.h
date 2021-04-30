#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <locale.h>
#include <cstring>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>


#ifdef __linux__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif



int info(const char *path);
int inarch(const char *path_c);
int64_t getFileSize(const char *fileName);