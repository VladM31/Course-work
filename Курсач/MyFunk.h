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