#pragma once
#include "iterator.h"


Grup<std::string> FindFileGrup();
// �������� �� ������� ��������� ����� 
void PrintGrupStudent(Grup<Student*>* glist);
// ������ ����� � �������� �
Grup<Student*>* FillGrup(Grup<std::string>* NameFile, size_t index);
// ������� ����
int MainMenu();
// ���� ������ 
bool EndMenuProgram();