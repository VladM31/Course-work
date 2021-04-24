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
//
void FirstMenuPrint(Grup<std::string>* FindName, Grup<std::string>* AllName, Grup<Grup<Student*>*> &GrupStudent);