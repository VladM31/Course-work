#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
typedef std::string sg;
enum class namS
{
    Last, Name, Patr,another
};
enum class valS {
    kur, id, rat, another
};
class ThePersonWhoLearns
{
protected:
    sg vLastname;//������
    sg vName;//�����
    sg vPatronymic;//�� �������
    size_t vId;//�������������� ����� 
    size_t vRating;//�������
    static size_t IdGlobal;
public:
    ThePersonWhoLearns();
    ThePersonWhoLearns(sg Lastname, sg Name, sg Patronymic);
    ThePersonWhoLearns(const ThePersonWhoLearns & Second);
    // Set 
    virtual void Set(namS chose, sg SetValue)=0;
    virtual void Set(valS chose, size_t SetValue)=0;
    virtual void SetConsole();
    virtual sg toString()=0;
    virtual bool toScanFile(std::fstream& file) = 0;
    virtual bool toPutFile(std::fstream& file)=0;
    virtual ~ThePersonWhoLearns() {}

};

