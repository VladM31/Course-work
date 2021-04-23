#pragma once
#include <iostream>
class Rating
{
    int rat;
public:
    Rating(int rat=0)
    {
        if (rat > 100)
        {
            this->rat = 100;
        }
        else if (rat < 0)
        {
            this->rat = 0;
        }
        else
        {
            this->rat = rat;
        }
    }
    Rating(Rating& rat)
    {
        this->rat = rat.rat;
    }
    int& operator *()
    {
        return this->rat;
    }
    // Operator = -----------------  Operator =
    void operator =(int newrat)
    {
        if (newrat > 100)
        {
            this->rat = 100;
        }
        else if (newrat < 0)
        {
            this->rat = 0;
        }
        else
        {
            this->rat = newrat;
        }
    }
    Rating& operator =(Rating rat)
    {
        this->rat = rat.rat;
        return *this;
    }
    // Operator + -----------------  Operator +
    int operator + (int newrat)
    {
        this->rat += newrat;
        if (this->rat > 100)
        {
            this->rat = 100;
        }
        else if (this->rat < 0)
        {
            this->rat = 0;
        }
        return  this->rat;
    }
    Rating operator + (Rating& newrat)
    {
        if (this->rat + newrat.rat > 100)
        {
            this->rat = 100;
        }
        else
        {
            this->rat += newrat.rat;
        }
        return Rating(this->rat);
    }
    // Operator += -----------------  Operator +=
    int& operator += (int newrat)
    {
        this->rat += newrat;
        if (this->rat > 100)
        {
            this->rat = 100;
        }
        else if (this->rat < 0)
        {
            this->rat = 0;
        }
        return this->rat;
    }
    Rating& operator += (Rating& newrat)
    {
        this->rat += newrat.rat;
        if (this->rat > 100)
        {
            this->rat = 100;
        }
        else if (this->rat < 0)
        {
            this->rat = 0;
        }
        return *this;
    }
    // Operator -= -----------------  Operator -=
    int& operator -= (int newrat)
    {
        this->rat -= newrat;
        if (this->rat > 100)
        {
            this->rat = 100;
        }
        else if (this->rat < 0)
        {
            this->rat = 0;
        }
        return this->rat;
    }
    Rating& operator -= (Rating& newrat)
    {
        this->rat -= newrat.rat;
        if (this->rat < 0)
        {
            this->rat = 0;
        }
        return *this;
    }
    // Operator - -----------------  Operator -
    int operator - (int newrat)
    {
        this->rat -= newrat;
        if (this->rat > 100)
        {
            this->rat = 100;
        }
        else if (this->rat < 0)
        {
            this->rat = 0;
        }
        return  this->rat;
    }
    Rating operator - (Rating& newrat)
    {
        int _tempt= this->rat - newrat.rat;
        if (_tempt < 0)
        {
            _tempt = 0;
        }
        return Rating(_tempt);
    }
    // Operator -- -----------------  Operator --
    Rating operator -- ()
    {
        --this->rat;
        if (this->rat < 0)
        {
            this->rat = 0;
        }
        return *this;
    }
    Rating operator -- (int)
    {
        int _Temp = this->rat;
        if (--this->rat < 0)
        {
            this->rat = 0;
        }
        return Rating(_Temp);
    }
    // Operator ++ -----------------  Operator ++
    Rating operator ++ ()
    {
        ++this->rat;
        if (this->rat > 100)
        {
            this->rat = 0;
        }
        return *this;
    }
    Rating operator ++ (int)
    {
        int temp = this->rat;
        ++this->rat;
        if (this->rat > 100)
        {
            this->rat = 0;
        }
        return Rating(temp);
    }
    // Operator () -----------------  ()
    Rating& operator () (int rat)
    {
        if (rat > 100)
        {
            this->rat = 100;
        }
        else if (rat < 0)
        {
            this->rat = 0;
        }
        else
        {
            this->rat = rat;
        }
        return *this;
    }
    // Operator int() -----------------  int()
    operator int()
    {
        return this->rat;
    }
    // ----------------------------------
    friend std::ostream& operator << (std::ostream& out, Rating& d) {
        out << d.rat;
        return out;
    }
    friend std::istream& operator >> (std::istream& out, Rating& d) {
        out >> d.rat;
        return out;
    }
    // BOOL------------------------------------------BOOL
    bool operator ==(int rat)
    {
        return this->rat == rat;
    }
    bool operator !=(int rat)
    {
        return this->rat != rat;
    }
    bool operator >(int rat)
    {
        return this->rat > rat;
    }
    bool operator <(int rat)
    {
        return this->rat < rat;
    }
    bool operator ==(Rating rat)
    {
        return this->rat == rat.rat;
    }
    bool operator !=(Rating rat)
    {
        return this->rat != rat.rat;
    }
    bool operator >(Rating rat)
    {
        return this->rat > rat.rat;
    }
    bool operator <(Rating rat)
    {
        return this->rat < rat.rat;
    }
    /// //---------------------------------------------------------------------------
    ~Rating()
    {

    }
private:
};

