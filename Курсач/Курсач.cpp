#include "MyFunk.h"

using namespace std;
 

int main() {
    Ukr;
    string temp;
    Grup<string> *NameFile = new Grup<string>(FindFileGrup());// Создаю лист названий файлов груп
    fstream OpenFile;//Создаю object для открития файлов
    Grup<Grup<Student*>*> ListGrup;
    for (size_t i = 0; i < NameFile->GetSize(); i++)
    { 
        ListGrup.push_back(FillGrup(NameFile,i));// Создаю Групу студентов 
    } 
    for (size_t i = 0; i < ListGrup.GetSize(); i++)
    {
        cout << (*NameFile)[i] << endl;// Вивожу имя групи
        PrintGrupStudent(ListGrup[i]);
    }






    Pause_Use; 
    // Очищаю динамическую память 
    for (size_t i = 0; i < ListGrup.GetSize(); i++)
    {
        while (0< ListGrup[i]->GetSize())
        {
            delete (*(ListGrup[i]))[0];
            ListGrup[i]->pop_front();
        }
    }
    delete NameFile, ListGrup;
}
