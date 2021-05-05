

#include "arc.h"
#include <libgen.h>
#include <vector>


using namespace std;


const int PATH_SIZE = 255;
char path_c[PATH_SIZE];
string path;
// string path = "test1";
string real_bin_file;
vector <string> files;


int main() {

    setlocale( LC_ALL, "rus");
    int i;

    cout << "1 - inarch , 2- outarch"<< endl;
    cin >> i;
    if (i==1) {
        cout << "Write path\n";
        cin >> path; 
        strcpy(path_c, path.c_str());
        info(path_c);
        inarch(path_c);

    } else if (i==2)
        outarch(); 
    else 
        cout << "Error! Invaled value" << endl;
        
    

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
    infofile.open(infoname, ios_base::out);
    infofile.clear();

    dir=opendir(path);
    if (dir!= NULL)

    //if ((dir=opendir(path)) !=NULL)
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
                files.push_back(fullPath);
                cout << "size = " << size << endl;

                strsize = to_string(size);
                sizeString += fileName.size() + strsize.size()+4;

                infofile << strsize;
                infofile << "||";
                infofile << fileName;
                infofile << "||";
                
            }

       }
        sizeString += 2; /////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //infofile << "end||";
        string sizeStr;
        sizeStr = to_string(sizeString);
        //int infosize;
        //char *m_size = new char[how(infosize)];
        int lenght;
        lenght = sizeStr.size();
        cout << "string size = " << lenght << endl;
        //lenght += 2;   /////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        string addzero;
        if (lenght<5)  addzero = (string(5-lenght,'0').c_str());
        cout << "howlenght = " << lenght <<endl;
        sizeStr=addzero +sizeStr; 

        
        infofile.close();
        infofile.open(infoname);

        infofile.getline(buff, NUM);
        cout << "buff =" << buff << endl;

        infofile.clear();
        infofile.close();
        infofile.open(infoname);

        infofile << sizeStr;
        infofile << "||";
        infofile << buff; 


        cout << "all = "<< sizeString<< endl;


        // size = infofile.tellg();
        // cout << "size = "<< size <<endl;

   



        


        infofile.close();
        
        closedir(dir);
    } else 
    {
        cout << "Error\n";
        return(0);
    }
return 0;
}

// int how(double w) {
//     int i=0;
//     while (w>10)
//     {
//         i++;
//         w/=10;
//     }
//     return i+1;
    
// }

//архивация
int inarch(const char *path_c){
    cout << "Write archive name " << endl;
    string archname;
    cin >> archname;

    //string path1;
    //char foldPath[PATH_SIZE] = {0};
    //strcpy(foldPath, path_c);
    //path1 = path;

   // const int SIZE = 32;
    //char drive[SIZE] = {0};
    //char dir[SIZE] = {0};

    //_splitpath(foldPath, drive, dir, 0, 0);
    char path1[PATH_SIZE] = {0};
    strcpy(path1, path_c);

    string path2 = dirname (path1);
    string infoname = path2 + "/infofile.txt";

   // path1 = dirname (foldPath);   
    
    // char archname = Path.GetDirectoryName(filename);

//    char archname = Path::GetFileName(path_c);

    real_bin_file = path2 + "/" +  archname + ".arch";

    cout << "real_bin_file " << real_bin_file << endl;
    char byte[1];
    FILE *f;
    FILE *main = fopen((real_bin_file).c_str(), "wb");
    FILE *infofile = fopen ((infoname).c_str(), "rb");

    cout << "path1/infofile.txt  " << (infoname).c_str() << endl;

     while(!feof(infofile))
       if (fread(byte,1,1,infofile)==1) fwrite(byte,1,1,main);
    fclose(infofile);
   // remove ((infoname).c_str());


    // запись в архив архивируемых файлов побайтно 

    for(vector<string>::iterator itr=files.begin();itr!=files.end();++itr)
    {
        f = fopen((*itr).c_str(),"rb");
        if(!f){ cout<<*itr<<" не найден!"<<endl; break;}
        while(!feof(f))
        {
            if(fread(byte,1,1,f)==1) fwrite(byte,1,1,main);
        }
        cout<<*itr<<" добавлен в архив '"<<real_bin_file<<"'."<<endl;
        fclose(f);
    }
    fclose(main);


    return 0;

}

//распаковка
int outarch(){
    char archpath[PATH_SIZE] ={0};
    // char *archpath = mass;
    cout << "Write archive path " <<endl;
    cin >> archpath;
    cout <<"archpath  "<< archpath << endl;
    //string fullpath = archpath;
    // const int NUM = 256;
    // char buff[NUM] = {0};
    //char path1[PATH_SIZE] = {0};
    //strcpy(path1, path_c);
    //string path2 = dirname (path1);
    real_bin_file = archpath;

    //char *chararchpath = archpath[0];
    string path = dirname (archpath);
    cout << "path = " << path << endl;

    
   // real_bin_file = path2 + "/" +  archname + ".arch";
   // real_bin_file = path2 +"/binary.arch";
    FILE *arch = fopen(real_bin_file.c_str(), "rb"); 
    char infosize[5] = {0};
    fread (infosize,1,5,arch);
    // int a = fread (infosize,1,5,arch);
    // cout<< "a = " << a <<endl;
    //arch.getline(buff, NUM);
    int infsz = atoi(infosize);
    cout << "size = " << infsz << endl;

    char *info = new char [infsz];
    fread(info, 1, infsz ,arch);

    vector<string> tokens;
    char *tok = strtok(info,"||");
    int toks = 0;
    while(tok)
    {
        // if(strlen(tok)==0) break;
        if(tok == NULL) break;
        tokens.push_back(tok);
        tok=strtok(NULL,"||");  ///
        toks++;
    }
     if(toks%2==1) toks--;  // удаляем мусор
    int files=toks/2;  // количество обнаруженных файлов в архиве
    cout << "files = " << files << endl;

    char byte[1];   // единичный буфер для считывания одного байта
  

    // Процесс распаковки всех файлов( по правилам полученным из блока с информацией ) :
    for(int i=0;i<files;i++)
    {
        const char* size = tokens[i*2].c_str();
        const char* name = tokens[i*2+1].c_str();
        //char full_path[255];
        //strcpy(full_path, path.c_str());
        //strcat(full_path,name);
        int _sz = atoi(size);
        


        char fullpath[PATH_SIZE] = {0};
        strcpy(fullpath, path.c_str());
        strcat(fullpath, "/");

        strcat(fullpath, name);

        cout<<"--  '"<<name<<"' извлечен в "<< fullpath << endl;

        FILE *curr = fopen(fullpath,"wb");
        for(int r=1;r<=_sz;r++)
        {
            if(fread(byte,1,1,arch)==1) 
              fwrite(byte,1,1,curr);
        }
        fclose(curr);

        // delete size;
        // delete name;
    }
    fclose(arch);


    return 0;

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

