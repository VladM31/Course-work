#pragma once
#include <fstream>
#include <windows.h>
#include "iterator.h"


Grup<std::string> FindFileGrup();
// ¬виводит на консоль студентов групи 
void PrintGrupStudent(Grup<Student*>* glist);

