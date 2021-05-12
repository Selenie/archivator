#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <locale.h>
#include <cstring>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>

#include <libgen.h>
#include <vector>

#ifdef __linux__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

using namespace std;

const int PATH_SIZE = 255;
char path_c[PATH_SIZE];
string path;
string bin_file;
vector <string> files;


//получение информации о файлах
int info(const char *path);

//архивация
int inarch(const char *path_c);

//распаковка
int outarch();

//функция получения размера файла в байтах
int64_t getFileSize(const char *fileName);
