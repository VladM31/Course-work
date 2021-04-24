#pragma once
#include "ThePersonWhoLearns.h"
typedef std::string sg;
class Student : public ThePersonWhoLearns {
protected:

    size_t vKurs;//����
public:
    // �� ���������
    Student();
    // � �����������
    Student(sg Lastname, sg Name, sg Patronymic, size_t Kurs);
    // �����������
    Student(Student& Second);
    //Get
    virtual sg Get(namS chose);
    size_t Get(valS chose);
    // Set
    // ������������ ������ �����
    virtual void Set(namS chose,sg SetValue) override;
    // ������������ ������ �����
    virtual void Set(valS chose, size_t SetValue)override;

    void SetConsole() override;
    // Metod
    // �������� ��� ������ ����� ������ � ������
    virtual sg toString()override;
    // �������� ������ � ����� 
    bool toScanFile(std::fstream& file)override;
    // ��������� ������ � ����
    bool toPutFile(std::fstream& file)override;
    // Operator
    Student& operator =(const Student& student);
    // ���������� ���� �� 1
    Student& operator ++();
    // �������� ���� �� 1
    Student& operator++(int);
    // ���������� ������� �� 1
    Student& operator--();
    // ��������  ������� �� 1
    Student& operator--(int);

    friend std::ostream& operator << (std::ostream& out, Student& d);
    friend std::istream& operator >> (std::istream& in, Student& d);
    virtual ~Student();
};

// ==================================================
