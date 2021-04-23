#include "MyFunk.h"

using namespace std;
 

int main() {
    Ukr;
    string temp;
    Grup<string> *NameFile= new Grup<string>(FindFileGrup());// Создаю лист названий файлов груп
    Grup<ifstream*> OpenFile;//Создаю лист для открития файлов
    Grup<Grup<Student*>*> ListGrup;
    for (size_t i = 0; i < NameFile->GetSize(); i++)
    { 
        ListGrup.push_back(new Grup<Student*>);
        OpenFile.push_back(new ifstream((*NameFile)[i].c_str()));
        cout << "Група " << (*NameFile)[i] << " Дипломники?" << endl
            << "Введіть true or false : "; cin >> temp;
        while (!OpenFile[i]->eof())
        {
            if (temp=="true")
            {

            }
        }
    } 
    
    Pause_Use; 
}
