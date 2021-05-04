#pragma once
#include "iterator.h"

class MyMenu
{

	int ChooseUser;
public:
	MyMenu() : ChooseUser(0) {}

	// ==== ����� ����� ====
	// ������� ����
	int MainMenu();

	// ---- Static ----
	// ����� ������� ���� ����� ���� Start
	static Grup<std::string> FindFileGrup();
	// �������� �� ������� ��������� ����� 
	static void PrintGrupStudent(Grup<ThePersonWhoLearns*>* glist);
	// ������ ����� ����
	static void TheThirdMenu(Grup<Grup<ThePersonWhoLearns*>*>& GrupStudent, Grup<std::string>* AllName);
};

// ������ ����� � �������� �
Grup<ThePersonWhoLearns*>* FillGrup(Grup<std::string>* NameFile, size_t index);
// ���� ������ 
bool EndMenuProgram();
// ���� ������� ������
Grup<std::string>* FirstMenu(size_t SizeGrup);
// ������ ������ ������� ������
void FirstMenuPrint(Grup<std::string>* FindName, Grup<std::string>* AllName, Grup<Grup<ThePersonWhoLearns*>*> &GrupStudent);
// ���� ������� ������
void SecondMenu(Grup<Grup<ThePersonWhoLearns*>*>& GrupStudent, Grup<std::string>* AllName);