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
    void WriteEntry(void);
    void PrintRecord(void);
    void SaveMap(void);
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

void DATABASE::WriteEntry(void)
{
    mymap[key] = entry;
}

void DATABASE::PrintRecord(void)
{
    string cell;
    istream sstream;
    do
    {
        key=PromptValidString("Enter record Key: ");
        iter = mymap.find(key);

        // check for key found
    }while(false);
    // assign record to a string
    entry=iter->second;
    // parse string
    istringstream iss(entry);
    copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             ostream_iterator<string>(cout, "\t"));

    cout<<"ID: "<<getline(sstream,250,'\t')<<endl;
    cout<<"Company Name: "<<getline(sstream,250,'\t')<<endl;
    cout<<"Contact Name: "<<getline(sstream,250,'\t')<<endl;
    cout<<"Contact Title: "<<getline(sstream,250,'\t')<<endl;
    cout<<"Address: "<<getline(sstream,250,'\t')<<endl;
    cout<<"City: "<<getline(sstream,250,'\t')<<endl;
    cout<<"Region: "<<getline(sstream,250,'\t')<<endl;    
    cout<<"PostalCode: "<<getline(sstream,250,'\t')<<endl;
    cout<<"Country: "<<getline(sstream,250,'\t')<<endl;
    cout<<"Phone: "<<getline(sstream,250,'\t')<<endl;
    cout<<"Fax: "<<getline(sstream,250,'\t')<<endl;    
}

void DATABASE::SaveMap(void)
{
    file.close();
    file.open(IOFILE,fstream::trunc);
    string temp;
     if (file.fail())
     {
         cout<<"\nFile read\\write failed: LoadFile()\n";
         exit(777);
     }
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
     {
         temp = iter->second;
        file.write(temp,sizeof(temp));
     }
    cout<<"File saved."<<endl;
}

string DATABASE::BuildKey(string company)
{
    return "";
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
        cout<<"\t1. Edit record"<<endl<<"\t2. Return to Main Menu"
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
    switch(this->menutype)
    {
    case MENU_TYPE_MAIN:
        switch(this->selection)
        {
        case 1:
            data->PrintRecord();
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


