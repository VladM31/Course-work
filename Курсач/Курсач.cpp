#include "MyFunk.h"

using namespace std;
 

int main() {
    Ukr;
    string temp;
    Grup<string> *NameFile= new Grup<string>(FindFileGrup());// Создаю лист названий файлов груп
    fstream OpenFile;//Создаю object для открития файлов
    Grup<Grup<Student*>*> ListGrup;
    for (size_t i = 0; i < NameFile->GetSize(); i++)
    { 
        ListGrup.push_back(new Grup<Student*>);
        OpenFile.open((*NameFile)[i].c_str(), ios::in);
        cout << "Група " << (*NameFile)[i] << " Дипломники?" << endl
            << "Введіть true or false : "; cin >> temp;
        for (size_t j = 0; !OpenFile.eof(); j++)
        {
            if (temp=="true") 
            {
                ListGrup[i]->push_back(new GraduateSD);   
            }
            else
            {
                ListGrup[i]->push_back(new Student);
            }
            (*ListGrup[i])[j]->toScanFile(OpenFile);
            if (OpenFile.eof())
            {
                ListGrup[i]->pop_back();
            }
        }
        OpenFile.close();
        system("cls");
    } 
    for (size_t i = 0; i < ListGrup.GetSize(); i++)
    {
        cout << (*NameFile)[i] << endl;
        for (size_t j = 0; j < ListGrup[i]->GetSize(); j++)
        {
            cout << (*ListGrup[i])[j]->toString() << endl << endl;
        }
        cout  << endl;
    }
    Pause_Use; 
}
