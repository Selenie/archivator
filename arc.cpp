#include "arc.h"


int main() {

    setlocale( LC_ALL, "rus");
    int i;

    cout << "1 - inarch , 2- outarch"<< endl; // 1 -архивация, 2 - распаковка
    cin >> i;
    if (i==1) {
        
        cout << "Write path\n";
        cin >> path; 
        strcpy(path_c, path.c_str()); 
        if ( info(path_c) != 1)  //получение информации об архивируемых файлах
            return 0;

        inarch(path_c); //архивация

    } else if (i==2)
        outarch(); //распаковка
    else 
        cout << "Error! Invaled value" << endl;
        
    return 1;
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
    
    int sizeString = 0, i = 0;
    string strsize;
    string non;

    char buff[PATH_SIZE] = {0};
    char path1[PATH_SIZE] = {0};
    strcpy(path1, path_c);

    string path2 = dirname (path1); //получение пути папки в которой создержатся архивируемые файлы
    fstream infofile; 
    string infoname = path2 + "/infofile.txt"; // создаем файл, в котором будет информация об архивируемых файлах (размер и название)
    infofile.open(infoname, ios_base::out); 
    infofile.clear();

    dir = opendir(path);
    if (dir!= NULL) //если директория не пуста

    {
        while ( (file = readdir(dir)) != NULL )
        {   
            if (!file->d_name || file->d_name[0] != '.')
            {
                fileName = file->d_name; //получаем имя файла
                // cout << "имя файла " << fileName << endl;
                strcpy(fileName_c, fileName.c_str());
                char fullPath[64] = {0};
                strcpy(fullPath, path_c);
                strcat(fullPath, "/");
                strcat(fullPath, fileName_c);//полный путь до файла 

                size = getFileSize(fullPath); //размер файла
                files.push_back(fullPath); //добавляем путь до файла в вектор files
                // cout << "size = " << size << endl;

                strsize = to_string(size);
                sizeString += fileName.size() + strsize.size()+4; //считаем размер строки с данными о файле (имя и размер (+4 - размер разделителей))

                //записываем данные в инфофайл
                infofile << strsize; 
                infofile << "||";
                infofile << fileName;
                infofile << "||";
                
            }

       }
        sizeString += 2; //добавляем размер одного разделителя
        string sizeStr;
        sizeStr = to_string(sizeString);

        int lenght;
        lenght = sizeStr.size();//размер переменной, содержащей размер строки с информацией о файлах
        // cout << "string size = " << lenght << endl;
  
        // проверка размера переменной
        string addzero;
        if (lenght<5)  addzero = (string(5-lenght,'0').c_str()); //считаем сколько необходимо дописать нулей, чтобы размер переменной был равен 5
        //cout << "howlenght = " << lenght <<endl;
        sizeStr=addzero +sizeStr; 

        infofile.close();
        infofile.open(infoname);

        infofile.getline(buff, PATH_SIZE);// копируем данные из инфофайла
        //cout << "buff =" << buff << endl;

        infofile.clear();
        infofile.close();
        infofile.open(infoname);

        infofile << sizeStr; //добавляем переменную с размером информации о файлах 
        infofile << "||";
        infofile << buff; 

        infofile.close();
        closedir(dir);
    } 
    else {
        cout << "Error\n";

        return 0;
    }
return 1;
}


//архивация
int inarch(const char *path_c){
    cout << "Write archive name " << endl;
    string archname;
    cin >> archname;

    char path1[PATH_SIZE] = {0};
    strcpy(path1, path_c);
    string path2 = dirname (path1);
    string infoname = path2 + "/infofile.txt";

    bin_file = path2 + "/" +  archname + ".arch"; //файл - архив

    //cout << "bin_file " << bin_file << endl;
    char byte[1];
    FILE *f;
    FILE *main = fopen((bin_file).c_str(), "wb"); 
    FILE *infofile = fopen ((infoname).c_str(), "rb"); // открываем файл с информацией

    //cout << "path1/infofile.txt  " << (infoname).c_str() << endl;

    //раписываем побайтно информацию в архив

     while(!feof(infofile)) {                                   // Error 404
       if (fread(byte,1,1,infofile)==1) 
            fwrite(byte,1,1,main);
    }
    
    fclose(infofile);
    remove ((infoname).c_str()); //удаляем файл с информацией


    // запись в архив архивируемых файлов побайтно 
    for(vector<string>::iterator itr=files.begin(); itr!=files.end(); ++itr)
    {
        f = fopen((*itr).c_str(),"rb");
        if(!f){ cout<<*itr<<" не найден!"<<endl; break;}
        while(!feof(f))
        {
            if(fread(byte,1,1,f)==1) fwrite(byte,1,1,main);
        }
        cout<<*itr<<" добавлен в архив '"<<bin_file<<"'."<<endl;
        fclose(f);
    }
    fclose(main);

    return 1;

}

//распаковка
int outarch(){
    char archpath[PATH_SIZE] = {0}; //путь до архива
    cout << "Write archive path " <<endl;
    cin >> archpath;
    //cout <<"archpath  "<< archpath << endl;
    bin_file = archpath;

    string path = dirname (archpath);
    //cout << "path = " << path << endl;


    FILE *arch = fopen(bin_file.c_str(), "rb"); // отурываем архив в режиме чтения
    char infosize[5] = {0}; 
    fread (infosize,1,5,arch); // считываем переменную с размером информации

    int infsz = atoi(infosize); // преобразуем буфер в число
    //cout << "size = " << infsz << endl;

    char *info = new char [infsz];
    fread(info, 1, infsz ,arch);

    // считываем информацию о файлах
    vector<string> tokens;
    char *tok = strtok(info,"||");
    int toks = 0;
   
    while(tok)
    {
        if(tok == NULL) break;
        tokens.push_back(tok); //добавляем информацию в вектор
        tok=strtok(NULL,"||");  
        toks++;
    }
    if (toks%2==1) toks--;  // удаляем мусор
    
    int files = toks/2;  // количество обнаруженных файлов в архиве
    cout << "files = " << files << endl;


    // Распаковка файлов
    char byte[1];   // единичный буфер для считывания одного байта

    for(int i=0;i<files;i++)
    {
        const char* size = tokens[i*2].c_str();
        const char* name = tokens[i*2+1].c_str();
    
        int _sz = atoi(size);

        char fullpath[PATH_SIZE] = {0};
        strcpy(fullpath, path.c_str());
        strcat(fullpath, "/");
        strcat(fullpath, name); // полный путь до распаковываемого файла

        cout<<name<<"' извлечен в "<< fullpath << endl;

        //открывем файл по полному пути и в него записываем побайто из архива 
        FILE *curr = fopen(fullpath,"wb");
        
        for(int r=1;r<=_sz;r++)
        {
            if(fread(byte,1,1,arch)==1) 
                fwrite(byte,1,1,curr);
        }
        fclose(curr);
    }
    fclose(arch);

    return 1;
}


//функция получения размера файла в байтах
int64_t getFileSize(const char *fileName)
{
    int64_t file_size = 0;
    FILE *fd = fopen(fileName, "rb");

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

