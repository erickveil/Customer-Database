#include "utility.h"

/*
 touch()
 Erick Veil
 10-11-11
 pre: a constant IOFILE with the name of the file
 post: returns 1 if successful, 0 if not
 Acts as a unix touch command, creating the file if
 it does not exist.
 requires: fstream,iostream
*/
int touch(void)
{
 int ret=1;
 fstream file;
 file.open(IOFILE,fstream::in|fstream::out|fstream::app);
 if (file.fail())
 {
 cout<<"\nFile read\\write failed.\n";
 ret = 0;
 }
 file.close();
 return ret;
}


/*
 SaveFile()
 Erick Veil
 10-11-11
 pre: IOFILE as the input file name, list as a vector
 of structures
 post: converts all members of each structure in the vector to
 strings, and appends them to the target file.
*/
void SaveFile()
{/*
 fstream file;

 OpenFile(&file);
 for(int element=0;element<list.size();++element)
 {
 stringstream out; // stream was accumulating values, so they were scoped to here
 string temp;
 //members of the structure
 SaveStr(list[element].decrip);

 // converts int to string before saving
 out<<list[element].qty;
 temp=out.str();
 SaveStr(temp);
 out.str(""); // the magic command that clears out the stream

 // works on floats
 out<<list[element].cost;
 temp=out.str();
 SaveStr(temp);
 out.str("");

 out<<list[element].price;
 temp=out.str();
 SaveStr(temp);
 out.str("");

 SaveStr(list[element].date);
 }*/
}

/*
 SaveStr()
 Erick VEil
 10-11-11
 pre: a string to be saved to a file, a constant IOFILE
 with the name of the file
 post: appends the string to the end of the file with a
 newline character after it. returns either 0 if failed,
 or the size of the string written.
 requires: fstream,iostream,string,cstring
*/
int SaveStr(string str)
{
 int ret;
 fstream file;
 ret=str.size()+1;

 // dynamicaly create an array of characters from the given string
 char* cstrloc;
 cstrloc = new char [ret];
 strcpy(cstrloc, str.c_str());
 cstrloc[ret-1]='\n';

 // open the file for writing
 file.open(IOFILE,fstream::out|fstream::app);
 //file.open(IOFILE,fstream::out);
 if (file.fail())
 {
 cout<<"\nFile read\\write failed.\n";
 ret = 0;
 }
 else
 {
 file.write(cstrloc,ret);
 }
 //clean up and return
 file.close();
 delete[] cstrloc;
 return ret;
}

/*
 DeleteFile()
 Erick Veil
 10-11-11
 pre: a constant IOFILE with the name of the file
 Clears a file of all its contents.
 requires fstream
*/
void DeleteFile(void)
{
 ofstream file;
 file.open(IOFILE,ios::trunc);
 file.close();
}

/*
 LoadFile()
 Erick Veil
 10-11-11
 pre: IOFILE constant defined as the name of the file to load,
 a structure and its members, a global vector called list
 post: vector should be of type THING structures, the members of
 which are loaded with the contents of IOFILE
 note: and str1 member function of THING
 will all have to be customised based on the program this function is
 included in.
 requires: fstream, iostream
*/
int LoadFile(void)
{/*
 RECORD temp;
 fstream file;
 string temp_in;
 file.open(IOFILE,fstream::in);
 if (file.fail())
 {
 cout<<"\nFile read\\write failed: LoadFile()\n";
 exit(777);
 }
 while(!file.eof())
 {
 // one getline statement for each member of the structure
 getline(file,temp.decrip);
 if(!temp.decrip.empty())
 {
 getline(file,temp_in);
 temp.qty=atoi(temp_in.c_str());
 getline(file,temp_in);
 temp.cost=atof(temp_in.c_str());
 getline(file,temp_in);
 temp.price=atof(temp_in.c_str());
 getline(file,temp.date);
 list.push_back(temp);
 }
 }
 file.close();
 return list.size();*/
    return 0;
}

/*
    Pause()
    Erick Veil
    10-01-11
    Simple user continued pause
*/
void Pause(void)
{
    string enter;
    cout<<"\n\n\tPress Enter to continue..";
    getline(cin,enter);
}

/*
    PromptValidInt()
    Erick Veil
    9-30-11
    pre: low is the lowest allowed value to be input. High is the highest.
        prompt is the output prompt given
    post: validated input as an integer within the specified range and
        returns the result
    exception:  exits with an error if low is greater than high
    prereqs: iostream, string, sstream, ctdlib
*/
int PromptValidInt(int low, int high, string prompt)
{
    string input;
    int ret;

    if(low>high)
    {
        cout<<"ERROR: low/high switch in module: PromptValidInt()";
        exit(EXIT_FAILURE);
    }

    while(true)
    {
        cout<<prompt;
        getline(cin,input);
        stringstream inputstream(input);
        if(
            (inputstream >> ret) &&
            (ret <= high) &&
            (ret >=low)
            )
            break;
        cout<<"\tYou must enter an integer between "<<low<<" and "<<high<<": ";
    }
    return ret;
}

/*
    PromptValidInt()
    Erick Veil
    10-05-11
 Overloaded for optional upper limits
    pre: low is the lowest allowed value to be input.
        prompt is the output prompt given
    post: validated input as an integer within the specified range and
        returns the result
    exception:  exits with an error if low is greater than high
    prereqs: iostream, string, sstream, ctdlib
*/
int PromptValidInt(int low, string prompt)
{
    string input;
    int ret;

    if(low>INT_MAX)
    {
        cout<<"ERROR: low value for int exceeds maximum: PromptValidInt()";
        exit(EXIT_FAILURE);
    }

    while(true)
    {
        cout<<prompt;
        getline(cin,input);
        stringstream inputstream(input);
        if(
            (inputstream >> ret) &&
            (ret <= INT_MAX) &&
            (ret >=low)
            )
            break;
        cout<<"\tYou must enter an integer greater than "<<low<<": ";
    }
    return ret;
}

/*
    PromptValidDouble()
    Erick Veil
    10-01-11
    pre: low is the lowest possible value allowed to be entered by
        the user. prompt is the input prompt displayed
    post: a prompt is displayed and the user required to enter a double
        input is validated to be a numeric value within the specified
        scope and returned
*/
double PromptValidDouble(double low, string prompt)
{
    string input;
    double ret;

    while(true)
    {
        cout<<prompt;
        getline(cin,input);
        stringstream inputstream(input);
        if(
            (inputstream >> ret) &&
            (ret >= low)
            )
            break;
        cout<<"\tYou must enter a decimal value of at least "<<low<<": ";
    }
    return ret;
}

/*
    PromptValidString()
    Erick Veil
    10-01-11
    pre: a string to prompt the user for input
    post: recieves a string from the user and validates
        that it is not empty. Returns the valid string.
*/
string PromptValidString(string prompt)
{
    string input;
    while(true)
    {
        cout<<prompt;
        getline(cin,input);
        if(!input.empty())
            break;
        cout<<"\n\tYou cannot have empty values.";
    }
    return input;
}

/*
    GetYN()
    Erick Veil
    9-15-11
    pre: message that will be displayed as a prompt
    post: Prompts the user for input, accepting only a y or an n.
        Returns 1 if y, 0 if n.
 10-05-11
 Added support for entering "yes" or "no"
*/
int GetYN(string msg)
{
    string input;
    int retval=0;

    while (true)
    {
        cout<<msg;
        getline(cin,input);
        if(input.length()==1)
        {
            if(input[0]=='y'||input[0]=='Y'||input[0]=='1')
            {
                retval = 1;
                break;
            }
            else if(input[0]=='n'||input[0]=='N'||input[0]=='0')
            {
                retval = 0;
                break;
            }
        }
 else
 {
 ConvertLineLowerCase(input);
 if(input == "yes")
 {
                retval = 1;
                break;
            }
 else if(input== "no")
 {
                retval = 0;
                break;
            }
 }
        cout<<"\n\tYour input is not valid. Please enter a Y or N: ";
    }
    return retval;
}

/*
    OpenFile()
    Erick Veil
    9-21-11
    pre: provide a pointer to a file object and the name of a file
    post: opens the file and validates that it was opened. exits the program if not
    10-11-11: ammended to use IOFILE as its filename
*/
void OpenFile(fstream* fstrm)
{
 fstrm->open(IOFILE,fstream::in|fstream::out);
    if(fstrm->fail())
    {
        cout<<"\n\nfile open failed. aborting.\n\n";
        exit(777);
    }
}

/*
    ConvertLineLowerCase()
    Erick Veil
    9-21-11
    pre: a string
    post: converts every letter of the line to lower case. Returns the altered string
*/
string ConvertLineLowerCase(string line)
{
    unsigned int t;
    string newstr="";
    for(t=0;t<line.size();++t)
    newstr+=tolower(line[t]);
    return newstr;
}
