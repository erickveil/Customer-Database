/*
    Customer Database
    Erick Veil

    A file-based database of customers that can be viewed, saved,
    edited, and erased.
    Demostrates the use of the map object and oop programming structure
*/
#include "utility.h"

using namespace std;

enum {MENU_TYPE_MAIN,MENU_TYPE_SUB};
#define TAB '\t'

map<string,string> mymap;
map<string,string>::iterator iter;

class DATABASE;
void Quit(DATABASE* data);
/*
    MENU
    Menu class can be one of two menus, depending
    on which type it is assigned. Selection holds the 
    users current menu selection.
*/
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

/*
    DATABASE
    Handles the manipulation of the data map and file
    entry holds the current entry being worked with
    key holds the current key
*/
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

// entry point
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

/*
    DATABASE
    constructor
    opens the data file and fills the map
*/

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

/*
    ~DATABASE
    destructor
    closes the data file if left open
*/
DATABASE::~DATABASE(void)
{
    file.close();
}

/*
    PromptForData
    out/in prompts to fill a record in the database
    if no parameter is passed, then a key is generated from the company name
*/
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

/*
    PromptForData
    out/in prompts to fill a record in the database
    overloaded to accept a key string for editing existing entries
*/
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

/*
    WriteEntry
    takes a preformatted string from the obect's entry member and 
    records it to the map as a data entry. This will either overwrite an 
    existing entry or make a new one depending on if the key exists or not
*/
void DATABASE::WriteEntry(void)
{
    mymap[key] = entry;
}

/*
    PrintRecord
    prompts user for a record key and then displays that record to
    the screen if found in the map
*/
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

/*
    SaveMap
    overwrites the data file with a current version of the map
*/
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

/*
    BuildKey
    generates a new customer key from the company name
*/
string DATABASE::BuildKey(string company)
{
    key.clear();
    int entryplace=0;
    while(key.size()<5)
    {
        if(
            (company[entryplace] >= 65 &&   // upper case letters
            company[entryplace] <= 90) ||
            (company[entryplace] >=97 &&   // lower case letters
            company[entryplace] <=122)
            )
        {
            key+=company[entryplace];
        }
        ++entryplace;
    }
    key=ConvertLineUpperCase(key);
    cout << "Client's key: "<<key<<endl;
    return key;
}


/*
    GetKey
    returns the current key for the entry being worked with
*/
string DATABASE::GetKey(void)
{
    return key;
}

/*
    MENU
   constructor
   type takes either MENU_TYPE_MAIN or MENU_TYPE_SUB
   which determines if this menu will be the main menu or
   the sub menu
*/
MENU::MENU(int type)
{
    menutype=type;
    if(type==MENU_TYPE_MAIN)
        maxoptions=3;
    if(type==MENU_TYPE_SUB)
        maxoptions=4;
}

/*
   PrintMenu
   Prints a menu to the screen, depending on its type
*/
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
        cout<<"1. Edit this record"<<"\t2. Return to Main Menu"
            <<"\t3. Erase this record"<<"\t4. Quit"<<endl<<endl;
        break;
    }
}

/*
   PromptForSelection
  Prompts the user for a valid menu item selection
*/
void MENU::PromptForSelection(DATABASE* data)
{
    selection = PromptValidInt(1, maxoptions, "Enter your selection: ");
    this->ParseSelection(data);
}

/*
   ParseSelection
   Reads the selection member value and determines what action is
   taken based off of which menu this is.
*/
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
            submenu.PromptForSelection(data);
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
            // should just pass through to go to the main menu.
            break;
        case 3:
            if(GetYN("Are you sure you want to erase this? (Y/N): "))
            {
                mymap.erase(data->GetKey());
                cout<<"Record erased."<<endl;
            }
            break;
        case 4:
            Quit(data);
            break;
        }
        break;
    }
}

/*
   Quit
   The exit point of the program
   Saves the data file, closes the program
*/
void Quit(DATABASE* data)
{
    data->SaveMap();
    Pause();
    exit(0);
}


