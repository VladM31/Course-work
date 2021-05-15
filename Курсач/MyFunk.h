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
	// ���� ������� ������
	static Grup<std::string>* FirstMenu(MyMenu * menu);
	// ������ ������ ������� ������
	static void FirstMenuPrint(Grup<std::string>* FindName, MyMenu* MyMenuGrup);
	// ���� ������� ������
	static void SecondMenu(MyMenu* MyMenuGrup);
	// ������ ����� ����
	static void TheThirdMenu(MyMenu * MyMenuGrup);
	// ���� ������ 
	static bool EndMenuProgram();
	// ������ ����� � �������� �
	static Grup<ThePersonWhoLearns*>* FillGrup(Grup<std::string>* NameFile, size_t index, int &ChooseUser);
	// ��������� � ���� (���� ������)
	static void SaveFile(MyMenu* MyMenuGrup);
	// Meny five
	static void TheFifthMenu(MyMenu* MyMenuGrup);
	// ����� ���� ����� 9
	static void NinthItem(MyMenu* MyMenuGrup);
	// ����� ���� ����� 10
	static void TenthMenu(MyMenu* MyMenuGrup);
};


