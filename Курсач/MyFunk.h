#pragma once
#include "iterator.h"

class MyMenu
{
	int ChooseUser;
	Grup<Grup<ThePersonWhoLearns*>*>* MyListGrup;
	Grup<std::string>* MyNameGrup;
public:
	MyMenu(Grup<Grup<ThePersonWhoLearns*>*>* SetMyListGrup, Grup<std::string>* MyNameGrup);

	~MyMenu();
	// ==== ����� ����� ====
	// ������� ����
	int MainMenu();
	// Get
	// ������� ��� ��������
	Grup<std::string>* GetNameGrup();
	// ������� ����� 
	Grup<Grup<ThePersonWhoLearns*>*>* GetListGrup();
	 
	// ---- Static ----
	// ����� ������� ���� ����� ���� Start
	static Grup<std::string> FindFileGrup(const char* nameFile = "Start.txt");
	// �������� �� ������� ��������� ����� 
	static void PrintGrupStudent(Grup<ThePersonWhoLearns*>* glist);
	// ������ ����� ����
	static void TheThirdMenu(MyMenu * MyMenuGrup);
};

// ������ ����� � �������� �
Grup<ThePersonWhoLearns*>* FillGrup(Grup<std::string>* NameFile, size_t index);
// ���� ������ 
bool EndMenuProgram();
// ���� ������� ������
Grup<std::string>* FirstMenu(size_t SizeGrup);
// ������ ������ ������� ������
void FirstMenuPrint(Grup<std::string>* FindName, MyMenu* MyMenuGrup);
// ���� ������� ������
void SecondMenu(MyMenu* MyMenuGrup);