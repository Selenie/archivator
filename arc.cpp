

#include "arc.h"
#include <libgen.h>
#include <vector>


using namespace std;


const int PATH_SIZE = 64;
char path_c[PATH_SIZE];
string path;
// string path = "test1";
string real_bin_file;
vector <string> files;


int main() {

    setlocale( LC_ALL, "rus");
    cout << "Write path\n";
    cin >> path; 

    strcpy(path_c, path.c_str());
    
    info(path_c);
    inarch(path_c);

    return(0);
}

//получение информации о файлах
int info(const char *path) {
  
    int64_t  size;
    DIR *dir;
    struct dirent *file;
    string fileName;
    char fileName_c[64] = {0};
    string archName;
    char archName_c[64] = {0};
    int sizeString,i;
    sizeString = 0;
    i=0;
    string strsize;
    string non;
    const int NUM = 256;
    char buff[NUM] = {0};
    char path1[PATH_SIZE] = {0};
    strcpy(path1, path_c);

    string path2 = dirname (path1);
    fstream infofile;
    string infoname = path2 + "/infofile.txt";
    //infofile.open("infoname", ios_base::out);
    infofile.open(infoname, ios_base::out);
    cout << "infoname = " << infoname << endl;
    infofile.clear();
    cout << "path =" << path << endl;
    if ((dir=opendir(path)) !=NULL)
    {
        while ( (file = readdir(dir)) !=NULL )
        {   
            if (!file->d_name || file->d_name[0] != '.')
            {
                fileName = file->d_name;
                cout << "имя файла " << fileName << endl;
                strcpy(fileName_c, fileName.c_str());
                char fullPath[64] = {0};
                strcpy(fullPath, path_c);
                strcat(fullPath, "/");
                strcat(fullPath, fileName_c);

                size = getFileSize(fullPath);
                cout << "size = " << size << endl;

                strsize = to_string(size);
                sizeString =  sizeString + fileName.size() + strsize.size();

                infofile << fileName ;
                infofile << "||";
                infofile << size ;
                infofile << "||";
                
                // infofile << fileName ;
                // infofile << "||";
                // infofile << size ;
                // infofile << "||";

            }

       }
        infofile << "end||";
        string sizeStr;
        sizeStr = to_string(sizeString);
        
        infofile.close();
        infofile.open("infofile.txt");

        infofile.getline(buff, NUM);
        cout << "buff " << buff << endl;

        infofile.clear();
        infofile.close();
        infofile.open("infofile.txt");

        infofile << sizeStr;
        infofile << "||";
        infofile << buff; 


        cout << "all = "<< sizeString<< endl;
        infofile.close();
        
        closedir(dir);
    } else 
    {
        cout << "Error\n";
        return(0);
    }
return(0);
}

//архивация
int inarch(const char *path_c){
    string path1;
    char foldPath[PATH_SIZE] = {0};
    strcpy(foldPath, path_c);
    //path1 = path;

   // const int SIZE = 32;
    //char drive[SIZE] = {0};
    //char dir[SIZE] = {0};

    //_splitpath(foldPath, drive, dir, 0, 0);
    path1 = dirname (foldPath);   

    real_bin_file = path1 +"/binary.arch";

    cout << "real_bin_file " << real_bin_file << endl;
    char byte[1];
    FILE *f;
    FILE *main = fopen((real_bin_file).c_str(), "wb");
    FILE *infofile = fopen ((path1 +"/infofile.txt").c_str(), "rb");

    cout << "path1/infofile.txt  " << (path1 +"/infofile.txt").c_str() << endl;

   // while(!feof(infofile))
   //     if (fread(byte,1,1,infofile)==1) fwrite(byte,1,1,main);
    fclose;
    //remove ((path1 +"/infofile.txt").c_str());

    //for (vector<string>::iteration itr);

    return(0);

}



int64_t getFileSize(const char *fileName)
{
    int64_t file_size = 0;
    FILE *fd = fopen(fileName, "rb");
    //  FILE *fd = fopen("test1/text1.txt", "rb");

    if (fd == NULL)
      file_size = -1;
    else
      {
          while(getc(fd) != EOF)
            file_size++;
        fclose(fd);        
      }
    return file_size;
}

