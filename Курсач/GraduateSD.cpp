#include "GraduateSD.h"

// GraduateSD ---------------------------------------------- GraduateSD

GraduateSD::GraduateSD() :Student()
{
    this->vDiploma_s_name = new sg("Empty");
    this->vWork = new float(0.01);
}

GraduateSD::GraduateSD(sg Lastname, sg Name, sg Patronymic, size_t Kurs, sg  Diploma_s_name) 
    :Student(Lastname, Name, Patronymic, Kurs)
{
    this->vDiploma_s_name = new sg(Diploma_s_name);
    this->vWork = new float(1.0);
}

GraduateSD::GraduateSD(GraduateSD& temGraduateSD) : Student(temGraduateSD)
{
    *(this->vDiploma_s_name) = (*temGraduateSD.vDiploma_s_name);
    *(this->vWork) = *(temGraduateSD.vWork);
}

GraduateSD& GraduateSD::operator=(GraduateSD& temGraduateSD)
{
    Student::operator=(temGraduateSD);
    *(this->vDiploma_s_name) = (*temGraduateSD.vDiploma_s_name);
    *(this->vWork) = *(temGraduateSD.vWork);
    return *this;
}

void GraduateSD::Set(namG chose, sg SetValue)
{
    if (chose == namG::Dipl)
    {
        *this->vDiploma_s_name = SetValue;
        return;
    }
    Student::Set(static_cast<namA>(chose), SetValue);
}

GraduateSD::~GraduateSD()
{
    if (vDiploma_s_name != nullptr)
    {
        delete vDiploma_s_name;
    }
    if (this->vWork != nullptr)
    {
        delete this->vWork;
    }
}

void GraduateSD::SetWork(float work)
{
    if (work > 100)
    {
        *(this->vWork) = 100;
    }
    else if (work < 0.01)
    {
        *(this->vWork) = (float)0.01;
    }
    else
    {
        *(this->vWork) = work;
    }
}

void GraduateSD::Set(valS chose, size_t SetValue)
{
    if (chose == valS::kur)
    {
        if (SetValue>5)
        {
            this->vKurs = 5;
        }
        else if(SetValue < 4)
        {
            this->vKurs = 4;
        }
        else
        {
            this->vKurs = SetValue;
        }
        return;
    }
    else
    {
        Student::Set(chose, SetValue);
    }
}

void GraduateSD::SetConsole()
{
    std::string tempBuf;
    Student::SetConsole();
    std::cin.ignore();
    std::cout << "����� ������� >> "; std::getline(std::cin, tempBuf, '\n');
    if (!FindCommandSkip(tempBuf))
    {
        *this->vDiploma_s_name = tempBuf;
    }
    std::cout << "������� �������� ������ % >> "; std::cin >> tempBuf;
    if (!FindCommandSkip(tempBuf))
    {
        this->SetWork(atof(tempBuf.c_str()));
    }
}

float GraduateSD::GetWork()
{
    return *(this->vWork);
}

sg GraduateSD::Get(namG chose)
{
    if (chose == namG::Dipl)
    {
        return *this->vDiploma_s_name;
    }
    else
    {
        return ThePersonWhoLearns::Get(static_cast<namA>(chose));
    }
}

sg GraduateSD::Get(namA chose)
{
    if (chose == namA::any)
    {
        return std::to_string(*this->vWork);
    }
    else
    {
        return ThePersonWhoLearns::Get(chose);
    }
    return sg("<GraduateSD Metod Get>: Empty");
}

sg GraduateSD::toString()
{
    return Student::toString()+'\n'
        +"Diploma`s name: "+ (*vDiploma_s_name) + '\n'
        +"Procent work: " + std::to_string(*vWork);
}

bool GraduateSD::toScanFile(std::fstream& file)
{
    char ch;
    try
    {
        //�������� �� ������� ��� �� ��������� nullptr
        Exception_GraduateSD::FindEror(this);
    }
    catch (const Exception_GraduateSD& ex)
    {
        //������� ����� �������
        std::cout << ex.what() << std::endl;
        // ������� ����� ��������� ���������� � ������ ���� ���'��� �� ���� ���
        ex.printInfoIndex();
        switch (ex.printInfoIndex())
        {
        case 1:
            this->vWork = new float(0);
            break;
        case 2:
            this->vDiploma_s_name = new std::string("Empty");
            break;
        case 3:
            this->vWork = new float(0);
            this->vDiploma_s_name = new std::string("Empty");
            break;
        default:
            break;
        }
    }

    try {
        //�������� �� �������� �����
        if (file.eof())
        {
            throw std::fstream::failure("������� ��� ���������");
        }
        // ������ ������� 
        std::getline(file, vLastname, ',');
        // ������ ���
        std::getline(file, vName, ',');
        // ������ �� ������
        std::getline(file, vPatronymic, ',');
        // ������ ����
        file >> vKurs >> ch;
        // �������� �������� �����
        this->Set(valS::kur, vKurs);
        // ������ �������� ���
        file >> vId >> ch;
        // ������ �������� ��������
        file >> vRating >> ch;
        // �������� �������� ��������
        this->Set(valS::rat, vRating);
        if (file.eof())
        {
            throw std::fstream::failure("������� ��� ���������");
        }
        if (ch==';')
        {
            file.get(ch);
            throw std::exception("dont full read");
        }
        std::getline(file, *vDiploma_s_name, ',');
        file >> *vWork >> ch;
        this->SetWork(*vWork);
        file.get(ch);
        return true;
    }
    // ���� ��� ���������� ���������� ���� ���������� �� ����� fstream
    catch (const std::fstream::failure& cat) {
        std::cout << cat.code() << std::endl;
        vLastname = cat.what();
        vName = cat.what();
        vPatronymic = cat.what();
        *vDiploma_s_name = cat.what();
        vKurs = ++IdGlobal;
        vId = IdGlobal;
        vRating = IdGlobal;
        *vWork = IdGlobal;
        return false;
    }
    // ���� � ���� ��� ������� ������� ������� ,�� ����� ��������� ���������� 
    // ���� ������ ���������� ,� ��� ������ ������ ������ ,�� ������ ��� �� �������
    catch (const std::exception& cat) {
        std::cout << cat.what() << std::endl;
        *vDiploma_s_name = cat.what();
        *vWork = -1.0;
        return false;
    }
}

bool GraduateSD::toPutFile(std::fstream& file)
{
    try
    {
        Exception_GraduateSD::FindEror(this);
    }
    catch (const Exception_GraduateSD& ex)
    {
        std::cout << ex.what() << std::endl;
        ex.printInfoIndex();
        switch (ex.printInfoIndex())
        {
        case 1:
            this->vWork = new float(0);
            break;
        case 2:
            this->vDiploma_s_name = new std::string("Empty");
            break;
        case 3:
            this->vWork = new float(0);
            this->vDiploma_s_name = new std::string("Empty");
            break;
        default:
            break;
        }
    }
   
    try
    {
        file << vLastname << "," << vName << ","
            << vPatronymic << "," << vKurs << ","
            << vId << "," << vRating << "," 
            <<*vDiploma_s_name << "," << *vWork << ";\n";
        return true;
    }
    catch (const std::exception& cat)
    {
        std::cout << cat.what() << std::endl;
        return false;
    }
}

std::ostream& operator << (std::ostream& out, GraduateSD& d)
{
    out << "Lastname      - " << d.vLastname << "\n"
        << "Name          - " << d.vName << "\n"
        << "Patronymic    - " << d.vPatronymic << "\n"
        << "Kurs          - " << d.vKurs << "\n"
        << "Id            - " << d.vId << '\n'
        << "Rating        - " << d.vRating << std::endl
        << "Diplom_s_name - " << *(d.vDiploma_s_name) << '\n'
        << "Work          - " << d.GetWork() << std::endl;
    return out;
}

std::istream& operator >> (std::istream& in, GraduateSD& d)
{
    std::cout << "Lastname      :\t"; getline(in, d.vLastname, '\n');
    std::cout << "Name          :\t"; getline(in, d.vName, '\n');
    std::cout << "Patronymic    :\t"; getline(in, d.vPatronymic, '\n');
    std::cout << "Kurs          :\t";  std::cin >> d.vKurs;
    std::cout << "Id            :\t";  std::cin >> d.vId;
    std::cout << "Rating        :\t";  std::cin >> d.vRating;
    std::cout << "Diplom_s_name :\t";  std::cin >> *(d.vDiploma_s_name);
    std::cout << "Work          :\t";  std::cin >> *(d.vWork);
    return in;
}

Exception_GraduateSD::Exception_GraduateSD(const char* string_, const int index)
    : std::exception(string_),index_(index) {}

void Exception_GraduateSD::FindEror(GraduateSD* point)
{
    int index1 = 0;

    if (point->vWork==nullptr)
    {
        index1 += 1;
    }
    if (point->vDiploma_s_name == nullptr)
    {
        index1 += 2;
    }
    if (index1>0)
    {
        throw Exception_GraduateSD("�� ������� ���'��� ��� ���� ��� ����� ������", index1);
    }
}

int Exception_GraduateSD::printInfoIndex() const
{
    switch (index_)
    {
    case 1:
        std::cout << "�������� ���� ,��� ������� �� ��������� �������� ������ ������� nullptr\n";
        break;
    case 2:
        std::cout << "�������� ���� ,��� ������� �� ����� �������� ������ ������� nullptr\n";
        break;
    case 3:
        std::cout << "�������� ���� ,��� ������� �� ��������� �������� ������ ������� nullptr\n";
        std::cout << "�������� ���� ,��� ������� �� ����� �������� ������ ������� nullptr\n";
        break;
    default:
        break;
    }
    return index_;
}




