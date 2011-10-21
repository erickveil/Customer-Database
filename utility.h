#ifndef UTILITY
#define UTILITY

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <limits.h>
#include <fstream>
#include <cstring>

using namespace std;

#define IOFILE "Customers.txt"


extern int PromptValidInt(int low, int high, string prompt);
extern int PromptValidInt(int low, string prompt);
extern string PromptValidString(string prompt);
extern double PromptValidDouble(double low, string prompt);
extern int GetYN(string msg);
extern void Pause(void);
extern string ConvertLineLowerCase(string line);

extern void OpenFile(fstream* fstrm);
extern int LoadFile(void);
extern void DeleteFile(void);
extern int SaveStr(string str);
extern void SaveFile();
extern int touch(void);


#endif