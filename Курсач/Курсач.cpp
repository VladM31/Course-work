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
        ListGrup.push_back(new Grup<Student*>);// Создаю Групу студентов 
        OpenFile.open((*NameFile)[i].c_str(), ios::in);// Откриваю файл групи
        cout << "Група " << (*NameFile)[i] << " Дипломники?" << endl
            << "Введіть true or false : "; cin >> temp;// Вибираю групу дипломников или без
        for (size_t j = 0; !OpenFile.eof(); j++)
        {
            // Дипломники
            if (temp=="true") 
                ListGrup[i]->push_back(new GraduateSD);   
            // Просто студенти 
            else
                ListGrup[i]->push_back(new Student);
            // Заполняю клас даними из файла 
            (*ListGrup[i])[j]->toScanFile(OpenFile);
            // Если конец файла то удаляем лишний объект класа
            if (OpenFile.eof())
            {
                ListGrup[i]->pop_back();
            }
        }
        OpenFile.close();// Закриваю файл 
        system("cls");// Очистка консоли 
    } 
    for (size_t i = 0; i < ListGrup.GetSize(); i++)
    {
        cout << (*NameFile)[i] << endl;// Вивожу имя групи
        PrintGrupStudent(ListGrup[i]);
    }
    Pause_Use; 
}
