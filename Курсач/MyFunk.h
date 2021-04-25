#pragma once
#include "iterator.h"


Grup<std::string> FindFileGrup();
// ¬виводит на консоль студентов групи 
void PrintGrupStudent(Grup<Student*>* glist);
// —оздаю групу и заполн€ю еЄ
Grup<Student*>* FillGrup(Grup<std::string>* NameFile, size_t index);
// √лавное меню
int MainMenu();
// ћеню виходу 
bool EndMenuProgram();
// ћеню первого пункта
Grup<std::string>* FirstMenu(size_t SizeGrup);
// ¬вивод данных первого пункта
void FirstMenuPrint(Grup<std::string>* FindName, Grup<std::string>* AllName, Grup<Grup<Student*>*> &GrupStudent);
// ћеню второго пункта
void SecondMenu(Grup<Grup<Student*>*>& GrupStudent, Grup<std::string>* AllName);