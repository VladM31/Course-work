#include "MyFunk.h"

using namespace std;
 

int main() {
    Ukr;
    // Variables to use
    string temp;
    bool WorkСycle = true;
    //******************************
  
    auto  NameFile = new Grup<string>(FindFileGrup());// Создаю лист названий файлов груп
    fstream OpenFile;//Создаю object для открития файлов
    Grup<Grup<Student*>*> ListGrup;
    for (size_t i = 0; i < NameFile->GetSize(); i++)
    { 
        ListGrup.push_back(FillGrup(NameFile,i));// Создаю Групу студентов 
    } 
    //for (size_t i = 0; i < ListGrup.GetSize(); i++)
    //{
    //    cout << (*NameFile)[i] << endl;// Вивожу имя групи
    //    PrintGrupStudent(ListGrup[i]);
    //}
    // =======================================================
    while (WorkСycle)
    {
        switch (MainMenu())
        {
        case 1:
            FirstMenuPrint(FirstMenu(NameFile->GetSize()), NameFile, ListGrup);
            Pause_Use;
            ConsoleClear;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            WorkСycle = EndMenuProgram();
            break;
        }
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
