#include "MyFunk.h"



Grup<ThePersonWhoLearns*>* FillGrup(Grup<std::string>* NameFile, size_t index)
{

	Grup<ThePersonWhoLearns*>* TempGrupS = new Grup<ThePersonWhoLearns*>;
	std::string temp;
	std::fstream OpenFile;//������ object ��� �������� ������
	OpenFile.open((*NameFile)[index].c_str(), std::ios::in);// �������� ���� �����
	// ������ �� �������� ����� .txt
	for (size_t i = 0; i < 4; i++)
	{
		(*NameFile)[index].pop_back();
	}
	// ������� ����� ����������� ��� ���
	std::cout << "����� " << (*NameFile)[index] << " ����������?" << std::endl
		<< "������ true or false : "; std::cin >> temp;
	for (size_t j = 0; !OpenFile.eof(); j++)
	{
		if (!OpenFile.is_open())
		{
			break;
		}
		// ����������
		if (temp == "true" || temp == "1")
			TempGrupS->push_back(new GraduateSD);
		// ������ �������� 
		else
			TempGrupS->push_back(new Student);
		// �������� ���� ������ �� ����� 
		(*TempGrupS)[j]->toScanFile(OpenFile);
		// ���� ����� ����� �� ������� ������ ������ �����
		if (OpenFile.eof()) {
			TempGrupS->pop_back();
		}

	}
	
	OpenFile.close();// �������� ���� 
	ConsoleClear;// ������� ������� 
	return TempGrupS;
}

bool EndMenuProgram()
{
	int Back;
	HANDLE Color_END = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << "��������� � ������� ����?" << std::endl;
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << "�������� 1 , ��� ��������� � ������� ����" << std::endl;
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED);
	std::cout << "�������� 2 , ��� ��������� ��������" << std::endl;
	SetConsoleTextAttribute(Color_END,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	std::cout << "������ ������� >> "; std::cin >> Back;
	ConsoleClear;
	return Back-2;
}
// ���� � ������ ���� "/skip" , �� ������ ������ 
bool FindCommandSkip(std::string& check)
{
	return (check.find("/skip") + 1) ? true : false;
}

Grup<std::string>* FirstMenu(size_t SizeGrup)
{
	using std::cout;
	using std::string;
	string AnswerGrup;
	int AnswerChoose;
	Grup<std::string>* TempGrupS = new Grup<std::string>;
	cout << " 1.������� �� �����;\n";
	cout << " 2.������� ������� ����;\n";
	cout << " 3.������� ���� �����;\n";
	cout << " ������ ���� ������� >> "; std::cin >> AnswerChoose; std::cin.ignore();
	ConsoleClear;
	if (AnswerChoose == 2)
	{
		for (size_t i = 0; i < SizeGrup; i++)
		{
			cout << "������ /skip , ��� �������� �������� ����\n";
			cout << "������ ����� >> "; std::getline(std::cin, AnswerGrup, '\n');
			ConsoleClear;
			if (FindCommandSkip(AnswerGrup))
				return (TempGrupS->GetSize())?TempGrupS:nullptr;
			else
				TempGrupS->push_back(AnswerGrup);
		}
		return TempGrupS;
	}
	else if (AnswerChoose == 3)
	{
		cout << "������ ����� >> "; std::getline(std::cin, AnswerGrup, '\n');
		ConsoleClear;
		TempGrupS->push_back(AnswerGrup);
		return TempGrupS;
	}
	else
		return nullptr;
}

void FirstMenuPrint(Grup<std::string>* FindName, Grup<std::string>* AllName, Grup<Grup<ThePersonWhoLearns*>*> &GrupStudent)
{
	auto AllNameIter = AllName->begin();
	auto GroupList= GrupStudent.begin();
	if (!FindName)//FindName == nullptr
	{
		for (auto i : GroupList)
		{
			std::cout << *AllNameIter << std::endl;
			MyMenu::PrintGrupStudent(i);
			++AllNameIter;
		}
		return;
	}
	auto FindNameIter = FindName->begin();
	
	for (auto i: AllNameIter)
	{
		for (auto j: FindNameIter)
		{
			if (i==j)
			{
				std::cout << i << std::endl;
				MyMenu::PrintGrupStudent(*GroupList);
				continue;
			}
		}
		++GroupList;
	}
	delete FindName;
}

void SecondMenu(Grup<Grup<ThePersonWhoLearns*>*>& GrupStudent, Grup<std::string>* AllName)
{
	using std::cout;
	int SizeNewGrup;
	cout << "������ ������� ����� ���� >> "; std::cin >> SizeNewGrup; std::cin.ignore();
	ConsoleClear;
	if (SizeNewGrup < 1 || SizeNewGrup>25)
	{
		return;
	}
	std::string temp;
	while (SizeNewGrup)
	{
		cout << "������ /skip , ��� �������� ��������\n";
		cout << "������ ����� ����� >> "; std::getline(std::cin, temp, '\n');
		ConsoleClear;
		if (FindCommandSkip(temp))// �������� �� ����
		{
			return;
		}
		GrupStudent.push_back(new Grup<ThePersonWhoLearns*>);// �������� ����� �����
		AllName->push_back(temp);// �������� �������� ����� �����
		--SizeNewGrup;
	}

}

Grup<std::string> MyMenu::FindFileGrup()
// ��������� ���� �� ������� ������ ����
{
	std::ifstream read("Start.txt");
	if (!read.is_open())
	{
		throw std::exception("File dont open!\n");
	}
	std::string temp;
	Grup<std::string> NameGrup;
	std::getline(read, temp, ':');
	std::getline(read, temp, '\n');
	for (size_t i = 0; !read.eof(); i++)
	{
		if (read.eof())
		{
			break;
		}
		std::getline(read, temp, '\n');
		temp = temp + ".txt";
		NameGrup.push_back(temp);
	}
	read.close();
	return  NameGrup;
}


void MyMenu::PrintGrupStudent(Grup<ThePersonWhoLearns*>* glist)
///������� �� ������� ����� ����� 
{
	for (size_t j = 0; j < glist->GetSize(); j++)
	{
		// ������ ���������� � ��������� ����� 
		std::cout << (*glist)[j]->toString() << std::endl << std::endl;
	}
	std::cout << std::endl;
}

int MyMenu::MainMenu()
{
	std::string CheckChoose;
	std::cout << " 1.�������� �����;" << std::endl;
	std::cout << " 2.�������� �����;" << std::endl;
	std::cout << " 3.�������� �����;" << std::endl;
	std::cout << " 4.�������� � ���� ����������;" << std::endl;
	std::cout << " 5.������ ����������;\n";
	std::cout << " 6.������� ��������;\n";
	std::cout << " 7.�������� ��������;\n";
	std::cout << " 8.�������� ��������;\n";
	std::cout << " 9.�������� ����� ����;\n";
	std::cout << " ������ �������: "; std::cin >> CheckChoose;
	ConsoleClear;
	if (FindCommandSkip(CheckChoose))
	{
		return this->ChooseUser;
	}
	this->ChooseUser = atoi(CheckChoose.c_str());
	return this->ChooseUser;
}