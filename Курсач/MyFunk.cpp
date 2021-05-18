#include "MyFunk.h"

Grup<ThePersonWhoLearns*>* MyMenu::FillGrup(Grup<std::string>* NameFile, size_t index, int &ChooseUser)
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
	// ��������� � ����� �� ��������
	TempGrupS->SetNameGroop((*NameFile)[index]);
	if (ChooseUser)
	{
		for (size_t j = 0; !OpenFile.eof(); j++)
		{
			if (!OpenFile.is_open())
			{
				break;
			}
			// ����������
			if (ChooseUser==1)
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
	// ������� ����� ����������� ��� ���
	std::cout << "����� " << (*NameFile)[index] << " ����������?" << std::endl
		<< "������ true or false : "; std::cin >> temp;
	if (FindCommandSkip(temp,"/all(1)"))//�� ���� ������ ���������� �� ����������
	{
		ChooseUser = 1;
	}
	if (FindCommandSkip(temp, "/all(0)"))//�� ���� ������ ���������� �� ��������
	{
		ChooseUser = 2;
	}
	//���� ���� �� ��������� ,��������� �����
	for (size_t j = 0; !OpenFile.eof(); j++)
	{
		//�������� �� �������� �����
		if (!OpenFile.is_open())
		{
			break;
		}
		// ����������
		if (temp == "true" || temp == "1" || ChooseUser == 1)
		{
			TempGrupS->push_back(new GraduateSD);
		}
		else	// ������ �������� 
		{
			TempGrupS->push_back(new Student);
		}
			
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

bool MyMenu::EndMenuProgram()
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

Grup<std::string>* MyMenu::FirstMenu(MyMenu* menu)
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
	if (menu->MyListGrup->GetSize() ==1)
	{
		return nullptr;
	}
	if (AnswerChoose == 2)
	{
		for (int i = 0; i < menu->MyListGrup->GetSize(); i++)
		{
			cout << "������ /skip , ��� �������� �������� ����\n";
			cout << " ����� :\n";
			for (auto k: menu->MyListGrup->begin())
			{
				cout << " " << k->GetNameGroop() << std::endl;
			}
			cout << "[/skip] ������ ����� >> "; std::getline(std::cin, AnswerGrup, '\n');
			ConsoleClear;
			if (FindCommandSkip(AnswerGrup))
				return (TempGrupS->GetSize()/*���� ���� ������ ���� �������*/)?TempGrupS:nullptr;
			else
			{
				bool find = false, Check_for_identity = false;
				//TempGrupS->push_back(AnswerGrup);
				// �������� ���� �� ����� �����
				for (auto it: menu->MyListGrup->begin())
				{
					if (it->GetNameGroop() == AnswerGrup)
					{
						find = true;
						break;
					}
					else {

						find = false;
					}
				}

				if (!i && find)// ���� ������ ������ �� ����� � ����� ����� ���� �� ������� �����
				{
					TempGrupS->push_back(AnswerGrup);
				}
				else if (find)// ���� �� ������ ������ �� ����� � ����� ����� ���� 
				{
					// �������� �� ������������
					for (size_t v = 0; v < i; v++)
					{
						if (TempGrupS->operator[](v) == AnswerGrup)
						{
							Check_for_identity = true;
							// ���� �� ���������  , �� ������� � �����
							break;
						}
						else
						{
							Check_for_identity = false;
						}
					}

					if (Check_for_identity)
					{
						std::cout << "����� " << AnswerGrup <<" ���� ��� ������� !!" << std::endl;
						i--;
					}
					else
					{
						TempGrupS->push_back(AnswerGrup);
					}
				}
				else
				{
					std::cout << "����� " << AnswerGrup << " �� � � ������� !!" << std::endl;
					i--;
				}
			}
				
		}
		return TempGrupS;
	}
	else if (AnswerChoose == 3)
	{
		cout << " ����� :\n";
		for (auto k : menu->MyListGrup->begin())
		{
			cout <<" "<< k->GetNameGroop() << std::endl;
		}
		cout << "������ ����� >> "; std::getline(std::cin, AnswerGrup, '\n');
		ConsoleClear;
		TempGrupS->push_back(AnswerGrup);
		return TempGrupS;
	}
	else
		return nullptr;
}

void  MyMenu::FirstMenuPrint(Grup<std::string>* FindName, MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->GetListGrup()->empty())// == 0
	{
		std::cout << "���� ���� !!" << std::endl;
		Pause_Use;
		delete FindName;
		ConsoleClear;
	}
	//auto AllNameIter = MyMenuGrup->GetNameGrup()->begin();

	size_t ChoosePrint;
	using std::cout, std::endl, std::cin;
	cout << "1.������� ��� ����������" << endl;
	cout << "2.������� ����� �������" << endl;
	cout << "3.������� ������� � ��'�" << endl;
	cout << "4.������� ������� � �� �������" << endl;
	cout << "5.������� ������� � ID" << endl;
	cout << "6.������� ������� � �������" << endl;
	cout << "7.������� ����� ����" << endl;
	cout << "[Input] >> "; cin >> ChoosePrint;
	ConsoleClear;


	auto GroupList= MyMenuGrup->GetListGrup()->begin();
	if (!FindName)//FindName == nullptr
	{
		for (auto &i : GroupList)
		{
			std::cout << "***=======================================***" << std::endl;
			std::cout << "\t\t"<<i->GetNameGroop() << std::endl;
			std::cout << "***=======================================***" << std::endl;
			if (ChoosePrint >= 2 && ChoosePrint < 5)
			{
				//ChoosePrint-=2;
				MyMenu::PrintGrupStudentItem_namA(i, (namA)(ChoosePrint-2));
			}
			else if (ChoosePrint == 5 || ChoosePrint == 6)
			{
				//ChoosePrint -= 5;
				MyMenu::PrintGrupStudentItem_valA(i, (valA)(ChoosePrint-5));
			}
			else if (ChoosePrint==7)
			{
				std::cout << std::endl;
			}
			else
			{
				MyMenu::PrintGrupStudent(i);
			}
			
		}
		return;
	}
	auto FindNameIter = FindName->begin();
	
	for (auto i: MyMenuGrup->GetListGrup()->begin())
	{
		for (auto j: FindNameIter)
		{
			if (i->GetNameGroop()==j)
			{
				std::cout << "***=======================================***" << std::endl;
				std::cout << "\t\t" << i->GetNameGroop() << std::endl;
				std::cout << "***=======================================***" << std::endl;
				if (ChoosePrint >= 2 && ChoosePrint < 5)
				{
					//ChoosePrint -= 2;
					MyMenu::PrintGrupStudentItem_namA(*GroupList, (namA)(ChoosePrint-2));
				}
				else if (ChoosePrint == 5 || ChoosePrint == 6)
				{
					//ChoosePrint -= 5;
					MyMenu::PrintGrupStudentItem_valA(*GroupList, (valA)(ChoosePrint - 2));
				}
				else if (ChoosePrint == 7)
				{
					std::cout << std::endl;
				}
				else
				{
					MyMenu::PrintGrupStudent(*GroupList);
				}
				//MyMenu::PrintGrupStudent(*GroupList);
				continue;
			}
		}
		++GroupList;
	}
	delete FindName;
}

void MyMenu::SecondMenu(MyMenu* MyMenuGrup)
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
		
		MyMenuGrup->MyListGrup->push_back(new Grup<ThePersonWhoLearns*>);// �������� ����� �����
		///***Delete***/MyMenuGrup->GetNameGrup()->push_back(temp);// �������� �������� ����� �����
		MyMenuGrup->MyListGrup->operator[](MyMenuGrup->MyListGrup->GetSize())->SetNameGroop(temp);// �������� �������� ����� �����
		--SizeNewGrup;
	}

}

Grup<std::string> MyMenu::FindFileGrup(const char * nameFile)
// ��������� ���� �� ������� ������ ����
{
	std::ifstream read(nameFile);
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

void MyMenu::TheThirdMenu(MyMenu* MyMenuGrup)
{
	using std::cout; using  std::endl; using  std::cin;
	size_t indexRemove = 0;// ������ ��� ��������� 
	size_t numberGrupDelete;// ʳ������ ���� ��� ���������
	std::string InPutUser;
	cout << "������ ������� ���� ��� ��������� "; cin >> InPutUser; cin.ignore();
	ConsoleClear;
	if (MyMenuGrup->MyListGrup->empty() | FindCommandSkip(InPutUser)/*���� �� ����*/ |
		((numberGrupDelete = atoi(InPutUser.c_str())/* �������� �������� �������� ���� ��� ���������*/) > 
			MyMenuGrup->MyListGrup->GetSize(/*���� ����� ���� ��� �������� ������ ��� ����*/)
		|| !numberGrupDelete/* == 0*/))
	{
		return;
	}

	while (numberGrupDelete)
	{
		cout << "������ ����: " << endl;
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			cout << i->GetNameGroop() << endl;
		}
		cout << "������ ����� ��� ��������� >> ";
		std::getline(cin, InPutUser,'\n');
		// � ��� , �� ����� �������
		if (FindCommandSkip(InPutUser))
		{
			return;
		}
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			// ������� ����� ��� ��������� � ���� ,����� �
			if (i->GetNameGroop() == InPutUser)
			{
				MyMenuGrup->MyListGrup->removeAt(indexRemove);
				///***Delete***/MyMenuGrup->MyNameGrup->removeAt(indexRemove);
				indexRemove = 0;
				break;
			}
			++indexRemove;
		}
		ConsoleClear;
		// ���� ����� ���� , �� �� ������� ��������� �����������
		if (MyMenuGrup->MyListGrup->empty())
		{
			cout << "������ ���� ����!!!!" << endl;
			Pause_Use;
			ConsoleClear;
			break;
		}
		// ���� ��� ������� �� ���� �������� ����� , �� �������� ����������� ,
		// �� ����� ���� �� ��������
		else if (indexRemove == MyMenuGrup->MyListGrup->GetSize())
		{
			cout << "����� " << InPutUser << " �� ��������!!!!" << endl;
			++numberGrupDelete;
		}
		// ���� ���� ��������� ��� �� ������ ����������� ��� ��
		else
		{
			cout << "����� " << InPutUser << " ��������!" << endl;
		}
		Pause_Use;
		ConsoleClear;
		--numberGrupDelete;
	}



}

void MyMenu::PrintGrupStudent(Grup<ThePersonWhoLearns*>* g_list)
///������� �� ������� ����� ����� 
{
	for (size_t j = 0; j < g_list->GetSize(); j++)
	{
		// ������ ���������� � ��������� ����� 
		std::cout << (*g_list)[j]->toString() << std::endl << std::endl;
	}
	std::cout << std::endl;
}

void MyMenu::PrintGrupStudentItem_valA(Grup<ThePersonWhoLearns*>* g_list, valA ValurC)
///������� �� ������� ����� ����� 
{
	for (auto i : g_list->begin())
	{
		switch (ValurC)
		{
		case valA::id:
			std::cout << i->Get(namA::Last);// �������  �������
			for (size_t j = 0; j < 39 - i->Get(namA::Last).length(); j++)// ����� ��������
			{
				std::cout << ' ';
			}
			std::cout << " " << i->Get(valA::id) << std::endl;//������� id
			break;
		case valA::rat:
			std::cout << i->Get(namA::Last);// �������  �������
			for (size_t j = 0; j < 39 - i->Get(namA::Last).length(); j++)// ����� ��������
			{
				std::cout << ' ';
			}
			std::cout << " " << i->Get(valA::rat) << std::endl;//������� rat
			break;
		default:
			break;
		}
	}
	std::cout << std::endl;
}

void MyMenu::PrintGrupStudentItem_namA(Grup<ThePersonWhoLearns*>* g_list, namA ValurC)
///������� �� ������� ����� ����� 
{
	for (auto i: g_list->begin())
	{
		switch (ValurC)
		{
		case namA::Last:
			// ������� ����� �������
			std::cout << i->Get(namA::Last) << std::endl;
			break;
		case namA::Name:
			std::cout << i->Get(namA::Last);// �������  �������
			for (size_t j = 0; j < 39- i->Get(namA::Last).length(); j++)// ����� ��������
			{
				std::cout << ' ';
			}
			std::cout << " " << i->Get(namA::Name) << std::endl;//������� ��'�
			break;
		case namA::Patr:
			std::cout << i->Get(namA::Last);// �������  �������
			for (size_t j = 0; j < 39 - i->Get(namA::Last).length(); j++)// ����� ��������
			{
				std::cout << ' ';
			}
			std::cout << " " << i->Get(namA::Patr) << std::endl;// ������� �� ������
			break;
		case namA::any:
			break;
		default:
			break;
		}
	}
	std::cout << std::endl;
	
}

int MyMenu::MainMenu()
{
	std::string CheckChoose;// ����� ��� �����'���������� ������ 
	std::cout << " 1.�������� �����;" << std::endl;
	std::cout << " 2.�������� �����;" << std::endl;
	std::cout << " 3.�������� �����;" << std::endl;
	std::cout << " 4.�������� � ���� ����������;" << std::endl;
	std::cout << " 5.������ ���������� ������ ��������;\n";
	std::cout << " 6.������� ������ �������� ;\n";
	std::cout << " 7.�������� ��������;\n";
	std::cout << " 8.�������� ��������;\n";
	std::cout << " 9.������ ����� �����;\n";
	std::cout << " 10.�������� �������� �����, � ���� ������ ��������� ����� 80%;\n";
	std::cout << " 11.��������� �������� ;\n";
	std::cout << " [/skip][/end]������ �������: "; std::cin >> CheckChoose;
	ConsoleClear;
	if (FindCommandSkip(CheckChoose))
	{
		return this->ChooseUser;
	}
	else if (FindCommandSkip(CheckChoose,"/end"))
	{
		return this->ChooseUser=111;
	}
	this->ChooseUser = atoi(CheckChoose.c_str());
	return this->ChooseUser;
}

MyMenu::MyMenu(Grup<Grup<ThePersonWhoLearns*>*>* SetMyListGrup, Grup<std::string>* SetMyNameGrup) : ChooseUser(0),MyListGrup(SetMyListGrup)
{
	for (size_t i = 0; i < SetMyNameGrup->GetSize(); i++)
	{
		MyListGrup->push_back(FillGrup(SetMyNameGrup, i,this->ChooseUser));// ������ ����� ��������� 
	}
	/* �������� ��� ����� ������ ���� ����� Grup<std::string>* SetMyNameGrup*/
	delete SetMyNameGrup;
}

Grup<Grup<ThePersonWhoLearns*>*>* MyMenu::GetListGrup()
{
	return this->MyListGrup;
}

MyMenu::~MyMenu()
{
	for (size_t i = 0; i < MyListGrup->GetSize(); i++)
	{
		while (0 < (*MyListGrup)[i]->GetSize())
		{
			delete (*((*MyListGrup)[i]))[0];
			(*MyListGrup)[i]->pop_front();
		}
	}
	delete MyListGrup;
}

void MyMenu::SaveFile(MyMenu* MyMenuGrup)
{
	if (!MyMenuGrup->MyListGrup->GetSize())
	{
		std::cout << "���� , �� �������" << std::endl;
		Pause_Use;
		ConsoleClear;
		return;
	}
	std::cout << "����� ���� " << std::endl;
	for (auto NameGrup: MyMenuGrup->MyListGrup->begin())
	{
		std::cout << NameGrup->GetNameGroop() << std::endl;
	}

	std::cout << "������ ����� ���� ��� ����������!" << std::endl;
	/// 
	Grup<std::string> NameFileSave;
	std::string temp;
	bool allSave = false;
	auto NameGrupCkl = MyMenuGrup->MyListGrup->begin();
	std::fstream FilePut;
	/// 
	while (NameFileSave.GetSize() <= MyMenuGrup->MyListGrup->GetSize())
	{
		std::cout << "[/skip][/all][Input] >> "; std::cin >> temp;
		if (FindCommandSkip(temp))
		{
			break;
		}
		if (FindCommandSkip(temp,"/all"))
		{
			allSave = true;
			break;
		}
		for (auto NameGrup : MyMenuGrup->MyListGrup->begin())
		{
			if (temp == NameGrup->GetNameGroop())
			{
				NameFileSave.push_back(temp);
				break;
			}
		}
	}
	ConsoleClear;
	if (allSave)
	{
		for (auto Grup : MyMenuGrup->MyListGrup->begin())
		{
			temp = (*NameGrupCkl)->GetNameGroop() + "_Save.txt";
			FilePut.open(temp, std::ios::out);
			for (auto StudentGrup : Grup->begin())
			{
				StudentGrup->toPutFile(FilePut);
			}
			FilePut.close();
			NameGrupCkl++;
	
		}
		return;
	}
	else
	{
		if (!NameFileSave.GetSize())
		{
			return;
		}
		auto Grupp = MyMenuGrup->MyListGrup->begin();
		for (auto findName: NameFileSave.begin())
		{
			if ((*NameGrupCkl)->GetNameGroop() == (findName))
			{
				NameGrupCkl = NameGrupCkl.begin();
				FilePut.open(findName + "_Save.txt");
				for (auto StudentGrup : (*Grupp)->begin())
				{
					StudentGrup->toPutFile(FilePut);
				}

			}
		}

	}
}

void MyMenu::TheFifthMenu(MyMenu* MyMenuGrup)
{
	//----------------//
	std::string tempUse;
	size_t indexs=0,number=1;
	bool Exit = false;
	//----------------//
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "���� , �� ������!" << std::endl;
		Pause_Use;
		ConsoleClear;
		return;
	}
	while (true)
	{
		std::cout << "����� ���� " << std::endl;
		// ������� �� ������� ����� ����
		for (auto NameGrup : MyMenuGrup->MyListGrup->begin())
		{
			std::cout << NameGrup->GetNameGroop() << std::endl;
		}
		std::cout << "������ ����� >> "; std::cin >> tempUse;
		// �������� �� ������� /���
		if (FindCommandSkip(tempUse))
		{
			ConsoleClear;
			std::cout << "���������� � ������� ����" << std::endl;
			Pause_Use;
			ConsoleClear; return;
		}
		// �������� �� ��������� ������� �����
		for (auto i: MyMenuGrup->MyListGrup->begin())
		{
			if (tempUse==i->GetNameGroop())
			{
				//���� ����� ���� �������� , �� ���� ���� ��� �������� �� ������
				Exit = true;
				break;
			}
			++indexs;
		}
		ConsoleClear;
		// 
		if (Exit)
		{
			break;
		}
		else
		{
			std::cout << "����� " << tempUse << " �� �������� !!!" << std::endl;
			indexs = 0;
			Pause_Use;
			ConsoleClear;
		}
	}
	using std::cout, std::endl,std::cin;
	while (true)
	{
		cout << "������� �������� (������ �����)" << endl;
		for (auto i : MyMenuGrup->MyListGrup->operator[](indexs)->begin())
		{
			cout << number++ <<")"<< i->Get(namA::Last) << " " << i->Get(namA::Name).at(0) << "." << i->Get(namA::Patr).at(0) << ".\n";
		}
		cout << "������ ���� >> "; std::cin >> tempUse;
		if (FindCommandSkip(tempUse))
		{
			ConsoleClear;
			std::cout << "���������� � ������� ����" << std::endl;
			Pause_Use;
			ConsoleClear; return;
		}
		number = static_cast<size_t>(atoi(tempUse.c_str()));
		if (number<1 || number>MyMenuGrup->MyListGrup->operator[](indexs)->GetSize())
		{
			cout << "�� �� �����!!!������ ����" << endl;
			Pause_Use;
			ConsoleClear;
		}
		else
		{
			break;
		}
	}
	ConsoleClear;
	auto ChangesInTheStudent = MyMenuGrup->MyListGrup->operator[](indexs)->operator[](number - 1);
	while (true)
	{
		cout << "1.������ �������" << endl;
		cout << "2.������ Id" << endl;
		cout << "3.������ �������" << endl;
		cout << "4.������ ��'�" << endl;
		cout << "5.������ �� �������" << endl;
		cout << "6.������ ��� ����" << endl;
		cout << "Imput chose >> "; std::cin >> tempUse; std::cin.ignore();
		ConsoleClear;
		if (FindCommandSkip(tempUse))
		{
			return;
		}
		switch (atoi(tempUse.c_str()))
		{
		case 1:
			cout << "������ ������" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(valA::rat, atoi(tempUse.c_str()));
			break;
		case 2:
			cout << "������ Id" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(valA::id, atoi(tempUse.c_str()));
			break;
		case 3:
			cout << "������ �������" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(namA::Last, tempUse);
			break;
		case 4:
			cout << "������ ��'�" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(namA::Name, tempUse);
			break;
		case 5:
			cout << "������ �� �������" << endl;
			std::getline(cin, tempUse, '\n');
			if (FindCommandSkip(tempUse))
			{
				return;
			}
			ChangesInTheStudent->Set(namA::Patr, tempUse);
			break;
		default:
			ChangesInTheStudent->SetConsole();
			break;
		}
		ConsoleClear;
	}

}

void MyMenu::TheSixthMenu(MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "���� ����" << std::endl;
		Pause_Use;
		ConsoleClear;
	}
	using std::cin, std::cout, std::endl; cin.ignore();
	std::string value;
	bool find = true;
	size_t indexGrup = 0;// ������ ����� �������� ��������
	size_t indexStudent = 0;
	//**********************
	// ---------------- �������� � �� ���� ����� � ������� ----------------
	do
	{
		cout << " ���������� ����:" << endl;
		// ������� �� ������� �� �����
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			cout << "- " << i->GetNameGroop() << endl;
		}
		cout << "[/skip] ������ ������� >> "; std::getline(cin, value, '\n');
		if (FindCommandSkip(value))
		{
			ConsoleClear;
			cout << "���������� � ������� ����" << endl;
			Pause_Use;
			ConsoleClear; return;
		}
		ConsoleClear;
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			
			if (i->GetNameGroop() == value)
			{
				find = false;
				break;
			}
			++indexGrup;
		}
		if (find)
		{
			cout << "����a " << value << " ���� � ���" << endl;
			indexGrup = 0;
		}
	} while (find);
	// ---------------- �������� � �� ���� ����� � ������� ----------------


	// ================ �������� � �� ���� ��� � �������
	find = true;
	do
	{
		for (auto i : (*MyMenuGrup->MyListGrup)[indexGrup]->begin())
		{
			cout << i->Get(namA::Last) << " " << i->Get(namA::Name)[0] << "." << i->Get(namA::Patr)[0] << ".";
			for (size_t j = 0; j < 33 - i->Get(namA::Last).length(); j++)
			{
				cout << " ";
			}
			cout << "Id: " << i->Get(valA::id) << endl;
		}
		cout << "[/skip][ Id ] >> "; std::getline(cin, value, '\n');

		if (FindCommandSkip(value))
		{
			ConsoleClear;
			cout << "���������� � ������� ����" << endl;
			Pause_Use;
			ConsoleClear; return;
		}
		ConsoleClear;
		for (auto i : (*MyMenuGrup->MyListGrup)[indexGrup]->begin())
		{
			if (i->Get(valA::id)== atoi(value.c_str()))
			{
				find = false;
				break;
			}
			++indexStudent;
			
		}

		if (find)
		{
			cout << "Id " << value << " ���� � ���" << endl;
			indexStudent = 0;
		}

	} while (find);
	ConsoleClear;

	HANDLE Color_END = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Color_END, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

	cout << "==============================================\n";
	cout << "\t\t" << (*MyMenuGrup->MyListGrup)[indexGrup]->GetNameGroop() << endl;
	cout << "==============================================\n";
	// ���������� ������ ����
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "������� : " << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(namA::Last) << endl;
	cout << "��'� : " << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(namA::Name) << endl;
	cout << "�� ������� : " << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(namA::Patr) << endl;
	// ���������� ���������� ����
	SetConsoleTextAttribute(Color_END, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "==============================================\n";
	if ((*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(valA::rat)<60)
	{
		// ���������� �������� ���� ,���� ������� ����� 60
		SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED);
	}
	else
	{
		// ���������� ������� ���� ,���� ������� ����� ��� ������� 60
		SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	}
	cout << "Rating : " << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(valA::rat) << endl;
	// ���������� ���������� ����
	SetConsoleTextAttribute(Color_END, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "==============================================\n";
	cout<<"Id : "<< (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(valA::id) << endl;
	cout << "==============================================\n";
	if (std::string("class GraduateSD") == typeid(*(*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)).name())
	{
		if (atoi((*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(namA::any).c_str()) < 80)
		{
			SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED);
		}
		else
		{
			SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		}
		cout << "�������� ������ �������� �� : " << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->Get(namA::any) << endl;
		SetConsoleTextAttribute(Color_END, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		cout << "==============================================\n";
	}
	cout << "����� ���������� : " << endl;
	SetConsoleTextAttribute(Color_END, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << (*MyMenuGrup->MyListGrup)[indexGrup]->operator[](indexStudent)->toString();
	SetConsoleTextAttribute(Color_END, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "\n==============================================\n";
	Pause_Use; 
	ConsoleClear;
}

void MyMenu::TheSeventhMenu(MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "���� ����" << std::endl;
		Pause_Use;
		ConsoleClear;
	}
	using std::cin, std::cout, std::endl; cin.ignore();
	std::string value;
	bool find = true;
	size_t indexGrup = 0;// ������ ����� �������� ��������
	//**********************
	// ---------------- �������� � �� ���� ����� � ������� ----------------
	do
	{
		cout << " ���������� ����:" << endl;
		// ������� �� ������� �� �����
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			cout << "- " << i->GetNameGroop() << endl;
		}
		cout << "[/skip] ������ ������� >> "; std::getline(cin, value, '\n');
		if (FindCommandSkip(value))
		{
			ConsoleClear;
			cout << "���������� � ������� ����" << endl;
			Pause_Use;
			ConsoleClear; return;
		}
		ConsoleClear;
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{

			if (i->GetNameGroop() == value)
			{
				find = false;
				break;
			}
			++indexGrup;
		}
		if (find)
		{
			cout << "����a " << value << " ���� � ���" << endl;
			indexGrup = 0;
		}
	} while (find);
	// ---------------- �������� � �� ���� ����� � ������� ----------------
	ConsoleClear;
	cout << "==============================================\n";
	cout << "\t����� " << (*MyMenuGrup->MyListGrup)[indexGrup]->GetNameGroop() << endl;
	cout << "==============================================\n";
	cout << "�������� ��������? ������ true ��� false \n";
	cout << "[Input] >> "; std::getline(cin, value, '\n');

	if (!FindCommandSkip(value,"true") )
	{
		ConsoleClear;
		cout << "���������� � ������� ����" << endl;
		Pause_Use;
		ConsoleClear;
		return;
	}
	ConsoleClear;

	cout<<"������� ��������� ? ������ true ��� false \n";
	cout << "[Input] >> "; std::getline(cin, value, '\n');
	if (FindCommandSkip(value, "true") || FindCommandSkip(value, "1"))
	{
		(*MyMenuGrup->MyListGrup)[indexGrup]->push_back(new GraduateSD);
	}
	else
	{
		(*MyMenuGrup->MyListGrup)[indexGrup]->push_back(new Student);
	}
	ConsoleClear;

	cout << "�������� ���� ��������! ����-����� �� �������������� ������� /skip!" << endl;
	(*MyMenuGrup->MyListGrup)[indexGrup]->operator[]((*MyMenuGrup->MyListGrup)[indexGrup]->GetSize() - 1)->SetConsole();
	Pause_Use;
	ConsoleClear;
}

void MyMenu::TheEighthMenu(MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "���� ����" << std::endl;
		Pause_Use;
		ConsoleClear;
	}
	using std::cin, std::cout, std::endl; cin.ignore();
	std::string value;
	bool find = true;
	size_t indexGrup = 0;// ������ ����� �������� ��������
	size_t indexStudent = 0;// ������ �������� ��������
	//**********************
	// ---------------- �������� � �� ���� ����� � ������� ----------------
	do
	{
		cout << " ���������� ����:" << endl;
		// ������� �� ������� �� �����
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			cout << "- " << i->GetNameGroop() << endl;
		}
		cout << "[/skip] ������ ������� >> "; std::getline(cin, value, '\n');
		if (FindCommandSkip(value))
		{
			ConsoleClear;
			cout << "���������� � ������� ����" << endl;
			Pause_Use;
			ConsoleClear; return;
		}
		ConsoleClear;
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{

			if (i->GetNameGroop() == value)
			{
				find = false;
				break;
			}
			++indexGrup;
		}
		if (find)
		{
			cout << "����a " << value << " ���� � ���" << endl;
			indexGrup = 0;
		}
	} while (find);
	// ---------------- �������� � �� ���� ����� � ������� ----------------


	// ================ �������� � �� ���� ��� � ������� =================
	find = true;
	do
	{
		for (auto i : (*MyMenuGrup->MyListGrup)[indexGrup]->begin())
		{
			cout << i->Get(namA::Last) << " " << i->Get(namA::Name)[0] << "." << i->Get(namA::Patr)[0] << ".";
			for (size_t j = 0; j < 33 - i->Get(namA::Last).length(); j++)
			{
				cout << " ";
			}
			cout << "Id: " << i->Get(valA::id) << endl;
		}
		cout << "[/skip][ Id ] >> "; std::getline(cin, value, '\n');

		if (FindCommandSkip(value))
		{
			ConsoleClear;
			cout << "���������� � ������� ����" << endl;
			Pause_Use;
			ConsoleClear; return;
		}
		ConsoleClear;
		for (auto i : (*MyMenuGrup->MyListGrup)[indexGrup]->begin())
		{
			if (i->Get(valA::id) == atoi(value.c_str()))
			{
				find = false;
				break;
			}
			++indexStudent;

		}

		if (find)
		{
			cout << "Id " << value << " ���� � ���" << endl;
			indexStudent = 0;
		}

	} while (find);
	// ================ �������� � �� ���� ��� � ������� =================
	ConsoleClear;
	cout<<"������� "<< (*(*MyMenuGrup->MyListGrup)[indexGrup])[indexStudent]->Get(namA::Last)
		<<" " << (*(*MyMenuGrup->MyListGrup)[indexGrup])[indexStudent]->Get(namA::Name)[0]
		<<"." << (*(*MyMenuGrup->MyListGrup)[indexGrup])[indexStudent]->Get(namA::Patr)[0]
		<< ". Id : " << (*(*MyMenuGrup->MyListGrup)[indexGrup])[indexStudent]->Get(valA::id)<< " ��� ���������" << endl;
	(*(*MyMenuGrup->MyListGrup)[indexGrup]).removeAt(indexStudent);
	Pause_Use;
	ConsoleClear;
}

void MyMenu::NinthItem(MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "���� ����" << std::endl;
		Pause_Use;
		ConsoleClear;
	}
	std::cin.ignore();
	std::string value;
	bool Find = true;
	while (true)
	{
		Find = true;
		std::cout << "����� :" << std::endl; 
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			std::cout <<"- "<< i->GetNameGroop() << std::endl;
		}
		std::cout << " ĳ� :" << std::endl;
		std::cout << "1.������ ����� �����" << std::endl;
		std::cout << "2.����������  � ������� ����" << std::endl;
		std::cout << "                                      <<\r"; std::cout << "������ >> ";
		std::getline(std::cin, value, '\n');
		ConsoleClear;
		if (FindCommandSkip(value,"1") || FindCommandSkip(value, "������"))
		{
			std::cout << "����� :" << std::endl;
			for (auto i : MyMenuGrup->MyListGrup->begin())
			{
				std::cout << i->GetNameGroop() << std::endl;
			}
			std::cout << "                                       <<\r"; 
			std::cout << "������ ����� >> "; std::getline(std::cin, value, '\n');
			if (FindCommandSkip(value))
			{
				return;
			}
			ConsoleClear;
			for (auto &i : MyMenuGrup->MyListGrup->begin())
			{
				if (i->GetNameGroop() == value)
				{
					std::cout << "                                       <<\r";
					std::cout << "������ ���� ����� >> "; std::getline(std::cin, value, '\n');
					if (FindCommandSkip(value))
					{
						return;
					}
					ConsoleClear;
					std::cout << "����� ������ � " << i->GetNameGroop() << " �� "<< value << std::endl;
					i->SetNameGroop(value);
					Find = false;
				}
			}
			if (Find)
			{
				std::cout << "����� " << value << " ����!!!" << std::endl;
			}
			Pause_Use;
			ConsoleClear;
		}
		else
		{
			ConsoleClear;
			return;
		}
	}
}

void PrintOfWork(Grup<ThePersonWhoLearns*>* i)
{
	const std::string checkThatTheStudentIsA_SD("class GraduateSD");
	for (auto j : i->begin())
	{
		// �������� �� ������� �� ������
		if (checkThatTheStudentIsA_SD == typeid(*j).name())
		{
			if (atof(j->Get(namA::any).c_str()) > 80)
			{
				std::cout << j->Get(namA::Name) << " " <<  j->Get(namA::any) << std::endl;
			}
		}
		// ���� ���� �� ������� ��� �� �����������
		else
		{
			std::cout << "������� " << j->Get(namA::Last)<<" "<<j->Get(namA::Name)<< " " << j->Get(namA::Patr)
				<<" �� � �����������" << std::endl;
		}
	}
}

void MyMenu::TenthMenu(MyMenu* MyMenuGrup)
{
	if (MyMenuGrup->MyListGrup->empty())
	{
		std::cout << "���� ����" << std::endl;
		Pause_Use;
		ConsoleClear;
	}
	std::string value;
	bool Find=true;
	auto NameAllGrup = MyMenuGrup->MyListGrup->begin();
	//***************
	std::cout << "����� :" << std::endl; std::cin.ignore();
	for (auto i : MyMenuGrup->MyListGrup->begin())
	{
		std::cout << i->GetNameGroop() << std::endl;
	}
	std::cout << "������ ����� ����� ��� ������ /all , ��� ������� �� ����� " << std::endl;
	std::cout << "���� >> "; std::getline(std::cin, value, '\n');
	ConsoleClear;
	if (FindCommandSkip(value,"/all"))
	{
		for (auto i: MyMenuGrup->MyListGrup->begin())
		{
			std::cout << "����� "<< i->GetNameGroop() << std::endl;
			PrintOfWork(i);
			++NameAllGrup;
		}
	}
	else if (FindCommandSkip(value))
	{
		ConsoleClear;
		return;
	}
	else
	{
		for (size_t i = 0; i < MyMenuGrup->MyListGrup->GetSize(); i++,++NameAllGrup)
		{
			if (value == (*NameAllGrup)->GetNameGroop())
			{
				PrintOfWork(MyMenuGrup->MyListGrup->operator[](i));
				Find = false;
				break;
			}
		}
		if (Find)
		{
			std::cout << "����� "<< value <<" ����!!!" << std::endl;
		}
	}
	Pause_Use;
	ConsoleClear;
	return;
}

void SortGrup(Grup<ThePersonWhoLearns*>* i,size_t index)
{
	bool Sort = true;
	iterator_g<ThePersonWhoLearns*> j = i->begin();
	iterator_g<ThePersonWhoLearns*> k = (++i->begin());
	while(Sort)
	{ 
		Sort = false;
		for (; k != k.end(); ++j, ++k)
		{
			switch (index)
			{
			case 1:
				if ((*j)->Get(namA::Last) > (*k)->Get(namA::Last))
				{
					std::swap(*j, *k); Sort = true;
				}
				break;
			case 2:
				if ((*j)->Get(namA::Name) > (*k)->Get(namA::Name))
				{
					std::swap(*j, *k); Sort = true;
				}
				break;
			case 3:
				if ((*j)->Get(namA::Patr) > (*k)->Get(namA::Patr))
				{
					std::swap(*j, *k); Sort = true;
				}
				break;
			case 4:
				if ((*j)->Get(valA::rat) > (*k)->Get(valA::rat))
				{
					std::swap(*j, *k); Sort = true;
				}
				break;
			case 5:
				if ((*j)->Get(valA::id) > (*k)->Get(valA::id))
				{
					std::swap(*j, *k); Sort = true;
				}
				break;
			default:
				std::cout << "!!!  Eror  !!!" << std::endl;
				break;
			}
		}
		j = i->begin();
		k = (++i->begin());
	}
}

void MyMenu::EleventhMenu(MyMenu* MyMenuGrup)
{
	using std::cout, std::endl, std::cin;
	std::cin.ignore();
	std::string value;
	bool flag = true;
	//*************************************************************************************//
	if (MyMenuGrup->MyListGrup->GetSize()>1)
	{
		std::cout << "1.��������� �� �����" << std::endl;
		std::cout << "2.��������� ������� ����" << std::endl;
		std::cout << "3.��������� ����" << std::endl;
		std::cout << "������ ������� >> "; std::getline(std::cin, value, '\n');
		if (FindCommandSkip(value))
		{
			ConsoleClear;
			std::cout << "����������� � ������� ���� \n";
			Pause_Use;
			ConsoleClear;
			return;
		}
		//Pause_Use;
		ConsoleClear;
	}
	//���� ���� ����
	else if(MyMenuGrup->MyListGrup->empty())
	{
		ConsoleClear;
		std::cout << "���� ����!!" << std::endl;
		Pause_Use;
		ConsoleClear;
		return;
	}
	// ���� � ����� ���� �����
	else
	{
		std::cout << "� ����� ���� ����� " << MyMenuGrup->MyListGrup->operator[](0)->GetNameGroop() << std::endl;
		flag = false;
	}
	//*************************************************************************************//
	Grup<std::string> nameSort;
	std::string NameSortGroop;
	int temp = 0;
	bool flag2 = false;
	//=====================================================================================//
	if (value == "2" || value == "3")
	{
		flag = false;
		cout << "������ ����: " << endl;
		for (auto i : MyMenuGrup->MyListGrup->begin())
		{
			cout << i->GetNameGroop() << endl;
		}
		if (value == "2")
		{
			do
			{
				cout << "[/skip ��� ������][������ �����] \n>> "; std::getline(std::cin, value, '\n');

				if (FindCommandSkip(value))
				{
					if (!temp)
					{
						ConsoleClear;
						cout << "�� ���� ������� �����" << endl;
						Pause_Use;
						ConsoleClear;
					}
				}

				// �������� � �� ����� ����� �������������
				for (auto j : MyMenuGrup->MyListGrup->begin())
				{
					if (j->GetNameGroop() == value)
					{
						flag2 = true;
					}
				}
				if (!nameSort.empty())
				{
					//�������� ,�� �� ������������ ������� �����
					for (auto k : nameSort)
					{
						if (k == value)
						{
							flag2 = false;
						}
					}
				}
				else
				{
					nameSort.push_front(value);
					temp++;
				}
				if (flag2)
				{
					nameSort.push_front(value);
					temp++;
				}
				else
				{
					cout << value << " ���� ����� ��� ��������� ��� �� ���� ����� �������������\n";
				}
				flag2 = false;

			} while (nameSort.GetSize()>= MyMenuGrup->MyListGrup->GetSize());
		}
		else
		{
			do
			{
				cout << "[������ �����] >> "; std::getline(std::cin, NameSortGroop, '\n');

				// �������� � �� ����� ����� �������������
				for (auto j : MyMenuGrup->MyListGrup->begin())
				{
					if (j->GetNameGroop() == NameSortGroop)
					{
						flag2 = true;
					}
				}
				
				if (flag2)
				{
					break;

				}
				else
				{
					cout << NameSortGroop << " ���� ����� ���� \n";
					flag2 = false;
				}

			} while (!flag2);
		}
	}
	else
	{
		flag = true;
	}
	//=====================================================================================//

	ConsoleClear;
	std::cout << "��������� �������� � ���� �� :" << std::endl;
	std::cout << "1.��������� �� ��������" << std::endl;
	std::cout << "2.��������� �� ��'��" << std::endl;
	std::cout << "3.��������� �� �� �������" << std::endl;
	std::cout << "4.��������� �� ���������" << std::endl;
	std::cout << "5.��������� �� Id" << std::endl;
	if (flag)
	{
		std::cout << "6.��������� �� ����� �� ������" << std::endl;
	}
	cout << "[/skip][������ �����] \n>> "; std::getline(std::cin, value, '\n');
	if (FindCommandSkip(value))
	{
		ConsoleClear;
		cout << "����������� �� ������� ���� ��� ����������" << endl;
		Pause_Use;
		ConsoleClear;
	}
	temp = atoi(value.c_str());
	if (temp<1 || temp>6)
	{
		ConsoleClear;
		cout << "����������� �� ������� ���� ��� ����������, �� ������� �� �� ��������" << endl;
		Pause_Use;
		ConsoleClear;
	}
	
	if (flag)
	{
		auto j = MyMenuGrup->MyListGrup->begin();
		auto k = ++MyMenuGrup->MyListGrup->begin();
		bool Sortt = true;
		switch (temp)
		{
		case 6:
			
			while (Sortt)
			{
				Sortt = false;
				for ( ;k != k.end(); ++j, ++k)
				{
					if ((*j)->GetNameGroop() > (*k)->GetNameGroop())
					{
						std::swap(*j, *k); Sortt = true;
					}
				}
				j = MyMenuGrup->MyListGrup->begin();
				k = ++MyMenuGrup->MyListGrup->begin();
			}
			break;
		default:
			for (auto it : MyMenuGrup->MyListGrup->begin())
			{
				SortGrup(it, temp);
			}
			break;
		}
	
	}
	else if (!nameSort.empty())
	{
		auto j = nameSort.begin();
		for (auto i = MyMenuGrup->MyListGrup->begin(); i!= i.end();++i)
		{
			if ((*j)==(*i)->GetNameGroop())
			{
				SortGrup(*i, temp);
				++j; i = MyMenuGrup->MyListGrup->begin();
			}
		}
	}
	else if (!NameSortGroop.empty())
	{
		for (auto &i : MyMenuGrup->MyListGrup->begin())
		{
			if (NameSortGroop ==i->GetNameGroop() )
			{
				SortGrup(i, temp);
				break;
			}
		}
	}
	else
	{
		cout << "eror !!!" << endl;
		Pause_Use;
		ConsoleClear;
	}
	ConsoleClear;
	cout << "���������� ������ !!!" << endl;
	Pause_Use;
	ConsoleClear;
}