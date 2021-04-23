#include "MyFunk.h"

using namespace std;
;

int main() {
    Ukr;
    Grup<string> *NameFile= new Grup<string>(FindFileGrup());
    Grup<ifstream*> OpenFile;
    for (size_t i = 0; i < NameFile->GetSize(); i++)
    {
        OpenFile.push_back(new ifstream(NameFile->operator[](i).c_str()));
    }
    Pause_Use;
}
