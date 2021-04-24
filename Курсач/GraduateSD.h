#pragma once
#include "Student.h"
#pragma warning(disable : 4996)
#define ConsoleClear std::system("cls")
#define Ukr SetConsoleCP(1251); SetConsoleOutputCP(1251)
#define Pause_Use system("pause")
enum class namG
{
    Last, Name, Patr,Dipl
};

class GraduateSD : public Student
{

protected:
    sg * vDiploma_s_name;//����� �������
    float* vWork;//³������ �������� ������
public:
    // �� ���������
    GraduateSD();
    // � �����������
    GraduateSD(sg Lastname, sg Name, sg Patronymic, size_t Kurs, sg  Diploma_s_name);
    // �����������
    GraduateSD(GraduateSD& temGraduateSD);

    // --------------
    GraduateSD& operator = (GraduateSD& temGraduateSD);
    // Set
    void Set(namG chose, sg SetValue);
    // ������������ �������� ������� ��������� ������ �����
    void SetWork(float work);
    void Set(valS chose, size_t SetValue) override;
    void SetConsole() override;
    // Get
    // ��������� �������� ������� ��������� ������ �����
    float GetWork();
    sg Get(namG chose);
    //
    sg toString() override;
    bool toScanFile(std::fstream& file)override;
    bool toPutFile(std::fstream& file)override;
    // operator
    friend std::ostream& operator << (std::ostream& out, GraduateSD& d);
    friend std::istream& operator >> (std::istream& in, GraduateSD& d);
    ~GraduateSD();

};

