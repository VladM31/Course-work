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
// ���� ������� ������
Grup<std::string>* FirstMenu(size_t SizeGrup);
// ������ ������ ������� ������
void FirstMenuPrint(Grup<std::string>* FindName, Grup<std::string>* AllName, Grup<Grup<Student*>*> &GrupStudent);
// ���� ������� ������
void SecondMenu(Grup<Grup<Student*>*>& GrupStudent, Grup<std::string>* AllName);