#include "GraduateSD.h"

// GraduateSD ---------------------------------------------- GraduateSD

GraduateSD::GraduateSD() :Student()
{
    this->vDiploma_s_name = new sg("Empty");
    this->vWork = new float(0.01);
}

GraduateSD::GraduateSD(sg Lastname, sg Name, sg Patronymic, size_t Kurs, sg  Diploma_s_name) :Student(Lastname, Name, Patronymic, Kurs)
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
        *(this->vWork) = 0.01;
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
    std::cout << "Diploma`s name >> "; std::getline(std::cin, tempBuf, '\n');
    if (!FindCommandSkip(tempBuf))
    {
        *this->vDiploma_s_name = tempBuf;
    }
    std::cout << "Work % >> "; std::cin >> tempBuf;
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

sg GraduateSD::toString()
{
    return Student::toString()+'\n'
        +"Diploma`s name: "+ (*vDiploma_s_name) + '\n'
        +"Procent work: " + std::to_string(*vWork);
}

bool GraduateSD::toScanFile(std::fstream& file)
{
    char ch;
    try {
        if (file.eof())
        {
            return false;
        }
        std::getline(file, vLastname, ',');
        std::getline(file, vName, ',');
        std::getline(file, vPatronymic, ',');
        file >> vKurs >> ch;
        this->Set(valS::kur, vKurs);
        file >> vId >> ch;
        file >> vRating >> ch;
        this->Set(valS::rat, vRating);
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