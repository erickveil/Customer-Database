#include "utility.h"

using namespace std;

enum {MENU_TYPE_MAIN,MENU_TYPE_SUB};
#define TAB '\t'

map<string,string> mymap;
map<string,string>::iterator iter;

class DATABASE;
void Quit(DATABASE* data);

class MENU
{
private:
    int menutype;
    int selection;
    int maxoptions;
public:
    MENU();
    MENU(int type);
    void PrintMenu(void);
    void PromptForSelection(DATABASE* data);
    void ParseSelection(DATABASE* data);
};

class DATABASE
{
private:
    fstream file;
    string entry;
    string key;
public:
    DATABASE(void);
    ~DATABASE(void);
    void PromptForData(void);
    void PromptForData(string key);
    void WriteEntry(void);
    void PrintRecord(void);
    void SaveMap(void);
    string GetKey(void);
    string BuildKey(string company);
};



int main(void)
{
    DATABASE data;
    MENU mainmenu(MENU_TYPE_MAIN);

    do{
        mainmenu.PrintMenu();
        mainmenu.PromptForSelection(&data);
    }while(true);

    return 0;
}

DATABASE::DATABASE(void)
{
     string temp_in,key;
     file.open(IOFILE,fstream::in);
     if (file.fail())
     {
         cout<<"\nFile read\\write failed: DATABASE() constructor\n";
         exit(777);
     }
     while(!file.eof())
     {
         // one getline statement for each member of the map
         getline(file,temp_in);
         key = temp_in.substr(0,temp_in.find('\t')); // should get first word in the line
         mymap[key] = temp_in; 
     }
     file.close();
}

DATABASE::~DATABASE(void)
{
    file.close();
}

void DATABASE::PromptForData(void)
{
    string in;
    in = PromptValidString("Company Name: ");
    key = this->BuildKey(in);
    entry = key+TAB+in;

    entry += TAB+ PromptValidString("Contact Name: ");
    entry += TAB+ PromptValidString("Contact Title: ");
    entry += TAB+ PromptValidString("Address: ");
    entry += TAB+ PromptValidString("City: ");
    entry += TAB+ PromptValidString("Region: ");
    entry += TAB+ PromptValidString("Postal Code: ");
    entry += TAB+ PromptValidString("Country: ");
    entry += TAB+ PromptValidString("Phone: ");
    entry += TAB+ PromptValidString("Fax: ");
    this->WriteEntry();
}

void DATABASE::PromptForData(string key)
{
    entry = key;
    entry +=TAB+ PromptValidString("Company Name: ");
    entry += TAB+ PromptValidString("Contact Name: ");
    entry += TAB+ PromptValidString("Contact Title: ");
    entry += TAB+ PromptValidString("Address: ");
    entry += TAB+ PromptValidString("City: ");
    entry += TAB+ PromptValidString("Region: ");
    entry += TAB+ PromptValidString("Postal Code: ");
    entry += TAB+ PromptValidString("Country: ");
    entry += TAB+ PromptValidString("Phone: ");
    entry += TAB+ PromptValidString("Fax: ");
    this->WriteEntry();
}

void DATABASE::WriteEntry(void)
{
    mymap[key] = entry;
}

void DATABASE::PrintRecord(void)
{
    string cell;
    int pos = 0;
    do
    {
        key=PromptValidString("Enter record Key: ");
        key=ConvertLineUpperCase(key);
        if(mymap.count(key)==0)
        {
            cout<<"That key does not exist."<<endl;
        }
    }while(mymap.count(key)==0);

    iter = mymap.find(key);
    // assign record to a string
    entry=iter->second;
    // parse string
    

    cout<<"ID: "<<Parse(entry, TAB, &pos)<<endl;
    cout<<"Company Name: "<<Parse(entry, TAB, &pos)<<endl;
    cout<<"Contact Name: "<<Parse(entry, TAB, &pos)<<endl;
    cout<<"Contact Title: "<<Parse(entry, TAB, &pos)<<endl;
    cout<<"Address: "<<Parse(entry, TAB, &pos)<<endl;
    cout<<"City: "<<Parse(entry, TAB, &pos)<<endl;
    cout<<"Region: "<<Parse(entry, TAB, &pos)<<endl;    
    cout<<"PostalCode: "<<Parse(entry, TAB, &pos)<<endl;
    cout<<"Country: "<<Parse(entry, TAB, &pos)<<endl;
    cout<<"Phone: "<<Parse(entry, TAB, &pos)<<endl;
    cout<<"Fax: "<<Parse(entry, TAB, &pos)<<endl;    
}

void DATABASE::SaveMap(void)
{
    string temp;
    char* cstr;
    ofstream file;

    file.open(IOFILE,ios::trunc);

    if (file.eof())
        cout<<"eofbit set"<<endl;
    if (file.fail())
        cout<<"failbit set"<<endl;
    if (file.bad())
        cout<<"badbit set"<<endl;
    
     if (file.fail())
     {
         cout<<"\nFile read\\write failed: SaveMap()\n";
         exit(777);
     }
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
     {
         temp = iter->second;

         // converting string to array
         cstr = new char [temp.size()+1];
         strcpy(cstr,temp.c_str());
         cstr[temp.size()]='\n';

        file.write(cstr,temp.size()+1);
        delete cstr;
     }
    file.close();
    cout<<"File saved."<<endl;
}

string DATABASE::BuildKey(string company)
{
    key.clear();
    key.resize(5);
    int entryplace=0;
    for (int letter = 0; letter<5;++letter)
    {
        if(entry[entryplace] >= 65 ||   // upper case letters
            entry[entryplace] <= 90 ||
            entry[entryplace] >=97 ||   // lower case letters
            entry[entryplace] <=122
            )
        {
            key[letter]=entry[entryplace];
        }
        ++entryplace;
    }
    ConvertLineUpperCase(key);
    cout << "Built key: "<<key<<endl;
    return key;
}

string DATABASE::GetKey(void)
{
    return key;
}

MENU::MENU(int type)
{
    menutype=type;
    maxoptions=3;
}

void MENU::PrintMenu(void)
{
    switch(this->menutype)
    {
    case MENU_TYPE_MAIN:
        cout<<"\t*** Customer Database by Erick Veil ***"<<endl<<endl;
        cout<<"\t1. Show a Record"<<endl<<"\t2. New Record"<<endl
            <<"\t3. Quit"<<endl<<endl;
        break;
    case MENU_TYPE_SUB:
        cout<<"\t1. Edit record"<<"\t2. Return to Main Menu"
            <<"\t3. Quit"<<endl<<endl;
        break;
    }
}

void MENU::PromptForSelection(DATABASE* data)
{
    selection = PromptValidInt(1, 3, "Enter your selection: ");
    this->ParseSelection(data);
}

void MENU::ParseSelection(DATABASE* data)
{
    MENU submenu(MENU_TYPE_SUB);
    switch(this->menutype)
    {
    case MENU_TYPE_MAIN:
        switch(this->selection)
        {
        case 1:
            data->PrintRecord();
            submenu.PrintMenu();
            PromptForSelection(data);
            break;
        case 2:
            data->PromptForData();
            break;
        case 3:
            Quit(data);
            break;
        }
        break;
    case MENU_TYPE_SUB:
        switch(this->selection)
        {
        case 1:
            cout<<"key: "<<data->GetKey()<<endl;
            data->PromptForData();
            break;
        case 2:
            break;
        case 3:
            Quit(data);
            break;
        }
        break;
    }
}

void Quit(DATABASE* data)
{
    data->SaveMap();
    Pause();
    exit(0);
}


