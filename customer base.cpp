#include "utility.h"

using namespace std;

enum {MENU_TYPE_MAIN,MENU_TYPE_SUB};
#define TAB '\t'



map<string,string> mymap;
map<string,string>::iterator iter;

class MENU
{
private:
    int menutype;
    string entry[4];
    int selection;
public:
    MENU();
    MENU(int type);
    void PrintMenu(void);
    void PromptForSelection(int max);
    void ParseSelection();
};

class DATABASE
{
private:
    fstream file;
    string entry;
public:
    DATABASE(void);
    ~DATABASE(void);
    void PromptForData(void);
    void WriteEntry(void);
    void PrintRecord(void);
    void SaveMap(void);
    string BuildKey(string company);
};



int main(void)
{
    DATABASE data;
    MENU mainmenu(MENU_TYPE_MAIN);

    // output map
    cout<<"Map output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        //(*pointer to iterator value).first is the key
        //pointer to iteraror value->second is the record
        cout<<(*iter).first << " is the key in the record " <<endl<< iter->second << endl;
    }

    /*
    // add an element to the map
    RECORD r4("Dd","Doug Dee");
    // map[key value]
    mymap["Dd"] = r4;
    cout<<"Second output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        cout<<(*iter).first << " is the key in the record " <<endl<< iter->second << endl;
    }

    //adding a third element

    RECORD r5("Cc","Zach Black");
     mymap["Cc"] = r5;

    cout << "third output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        cout<<(*iter).first << " is the key in the record " <<endl<< iter->second << endl;
    }
    */


    Pause();
    return 0;
}

/*
 LoadFile()
 Erick Veil
 10-22-11

*/
DATABASE::DATABASE(void)
{
     string temp_in,key;
     file.open(IOFILE,fstream::in);
     if (file.fail())
     {
         cout<<"\nFile read\\write failed: LoadFile()\n";
         exit(777);
     }
     while(!file.eof())
     {
         // one getline statement for each member of the map
         getline(file,temp_in);
         key = temp_in.substr(0,temp_in.find('\t'));
         mymap[key] = temp_in; 
     }
}

DATABASE::~DATABASE(void)
{
    file.close();
}

void DATABASE::PromptForData(void)
{
    string key,in;
    cout<<"Company Name: ";
    getline(cin,in);
    key = this->BuildKey(in);
    entry = key+TAB+in;

    cout<<"Contact Name: ";
    getline(cin,in);
    entry += TAB+in;

}

void DATABASE::WriteEntry(void)
{
}

void DATABASE::PrintRecord(void)
{
}

void DATABASE::SaveMap(void)
{
}

string DATABASE::BuildKey(string company)
{
    return "";
}

MENU::MENU(int type)
{
}

void MENU::PrintMenu(void)
{
}

void MENU::PromptForSelection(int max)
{
}

void MENU::ParseSelection()
{
}


