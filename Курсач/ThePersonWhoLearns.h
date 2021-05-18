#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

// ���� � ������ ���� "/skip" , �� ������ ������ 
bool FindCommandSkip(std::string check, const char* findCommand = "/skip");
typedef std::string sg;
enum class namA
{
    Last, Name, Patr, any
};
enum class valA {
   id, rat
};
class ThePersonWhoLearns
{
protected:
    sg vLastname;//������
    sg vName;//�����
    sg vPatronymic;//�� �������
    size_t vId;//�������������� ����� 
    size_t vRating;//�������
    static size_t IdGlobal;//�������� ������ , ��� � ��'���� ����� ,�� ���� ������� ������������� �� ��������� , ��� 
public:
    ThePersonWhoLearns();
    ThePersonWhoLearns(sg Lastname, sg Name, sg Patronymic);
    ThePersonWhoLearns(const ThePersonWhoLearns & Second);
    // Set 
    virtual void Set(namA chose, sg SetValue)=0;
    virtual void Set(valA chose, size_t SetValue);
    // Get
    virtual sg Get(namA chose);
    virtual size_t Get(valA chose);
    //
    virtual void SetConsole();
    virtual sg toString()=0;
    virtual bool toScanFile(std::fstream& file) = 0;
    virtual bool toPutFile(std::fstream& file)=0;
    virtual ~ThePersonWhoLearns() {}

};



