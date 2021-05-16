#pragma once
#include "iterator.h"

class MyMenu
{
	int ChooseUser;
	Grup<Grup<ThePersonWhoLearns*>*>* MyListGrup;
public:
	MyMenu(Grup<Grup<ThePersonWhoLearns*>*>* SetMyListGrup, Grup<std::string>* MyNameGrup);

	~MyMenu();
	// ==== ����� ����� ====
	// ������� ����
	int MainMenu();
	// Get
	// ������� ����� 
	Grup<Grup<ThePersonWhoLearns*>*>* GetListGrup();
	 
	// ---- Static ----
	// ����� ������� ���� ����� ���� Start
	static Grup<std::string> FindFileGrup(const char* nameFile = "Start.txt");
	// �������� �� ������� ��������� ����� (����� ����������)
	static void PrintGrupStudent(Grup<ThePersonWhoLearns*>* glist);
	// �������� �� ������� ��������� ����� (�������, ��'�,�� �������)
	static void PrintGrupStudentItem_namA(Grup<ThePersonWhoLearns*>* glist,namA ValurC);
	// �������� �� ������� ��������� ����� (������� ,���� )
	static void PrintGrupStudentItem_valA(Grup<ThePersonWhoLearns*>* glist, valA ValurC);

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
	// 5.������ ���������� ������ ��������
	static void TheFifthMenu(MyMenu* MyMenuGrup);
	// 6.������� ������ ��������
	static void TheSixthMenu(MyMenu* MyMenuGrup);
	// 7.�������� ��������
	static void TheSeventhMenu(MyMenu* MyMenuGrup);
	// 8.�������� ��������
	static void TheEighthMenu(MyMenu* MyMenuGrup);
	// 9.������ ����� �����
	static void NinthItem(MyMenu* MyMenuGrup);
	// 10.�������� �������� �����, � ���� ������ ��������� ����� 80%
	static void TenthMenu(MyMenu* MyMenuGrup);
	// 11.��������� ��������
	static void EleventhMenu(MyMenu* MyMenuGrup);
};


