#include <iostream>
#include<stdlib.h>
#include <conio.h>
#include <fstream>
using namespace std;

class adminMode
{
public:
    void showAtndncTable();
    void setDate();
    void seeLogDetails();
    //void searchEmployee();
    void writeAttendance();
};

static int logInNum,logOutNum;
static const int dirSize=10;
class Employee
{
private:

    string firstName[dirSize]= {"Ravi","Priya","Rohit","Nisha","Rajesh","Meera","Sanjay","Pooja","Siddharth","Shalini"};
    string surName[dirSize]= {"Sharma","Patel","Singh","Gupta","Kumar","Iyer","Verma","Choudhary","Mishra","Dubey"};
    string password[dirSize]= {"123","456","789","135","246","791","135","257","975","387"};
public:
    string enteredFirstName,enteredSurName,enteredPassword;
    int nmeSrchr;
    void readName();
    void chkName();
    void readPassword();
    void chkPassword();
    void rechkName();
    /*This is an adminMode feature*/void searchEmployee();
    friend class adminMode;
};
//member functions of Employee
void Employee::readName()
{
    cout<<"Please Enter Your USERNAME:";
    cin>>enteredFirstName;
    cin>>enteredSurName;
    chkName();
}

void Employee::chkName()
{
    for(nmeSrchr=0; nmeSrchr<=dirSize; nmeSrchr++)
    {
        if(enteredFirstName==firstName[nmeSrchr] && enteredSurName==surName[nmeSrchr])
        {
            readPassword();
            return;
        }
        else if (nmeSrchr==dirSize)
        {
            cout<<"Name Not Found in the Directory. Please Try again or Contact the Administrator."<<endl;
        }
        else continue;
    }
}

void Employee::readPassword()
{
    cout<<"Welcome "<<firstName[nmeSrchr]<<" "<<surName[nmeSrchr]<<".Please Enter your Password:";
    cin>>enteredPassword;
    chkPassword();

}
void Employee::chkPassword()
{
    if(enteredPassword==password[nmeSrchr])
    {
        rechkName();
    }
    else
    {
        int triesLeft=3;
        while (enteredPassword!=password[nmeSrchr] && triesLeft!=0)
        {
            cout<<"Incorrect Password. Please try Again("<<triesLeft<<" attempts left.):";
            cin>>enteredPassword;
            triesLeft--;
        }
        if(enteredPassword==password[nmeSrchr])
        {
            rechkName();
        }
        else if(triesLeft==0)cout<<"LOGIN UNSUCCESSFUL."<<endl;
    }
}
static int addName;
static string atndncArray[dirSize][3];


void Employee::rechkName()
{
    for(int i=0; i<=dirSize; i++)
    {
        if(i==10)
        {
            atndncArray[addName][0]=enteredFirstName;
            atndncArray[addName][1]=enteredSurName;
            atndncArray[addName][2]="Logged In";
            cout<<"LOGGED IN.Have a Good Day"<<endl;
            logInNum++;
            break;
        }
        else if(enteredFirstName==atndncArray[i][0] && enteredSurName==atndncArray[i][1])
        {
            string resp;
            cout<<"You are LOGGED IN. Do you wish to LOGOUT?(y/n)";
            cin>>resp;
            if(resp=="y" || resp=="Y")
            {
                atndncArray[addName][0]=enteredFirstName;
                atndncArray[addName][1]=enteredSurName;
                atndncArray[addName][2]="Logged Out";
                cout<<"LOGGED OUT. Enjoy your day "<<enteredFirstName<<" "<<enteredSurName<<endl;
                logOutNum++;
                if(logInNum!=0) logInNum--;
                break;
            }
            else if(resp=="n" || resp=="N")continue;
            else
            {
                cout<<"Invalid Response"<<endl;
                continue;
            }
        }
        else if(enteredFirstName!=atndncArray[i][0] || enteredSurName!=atndncArray[i][1])continue;
    }
    addName++;

}
;
//end of member functions of Employee


//member functions of adminMode
static string date;
void adminMode::showAtndncTable()
{
    if(date.length()==0)date="Unset";
    cout<<"\nDate:"<<date<<endl;
    cout<<"\n*********************************************\n";
    cout<<"Event No."<< "     "<<" Name"<<"                "<< "Status"<<endl;
    for(int i=0; i<addName; i++)
    {
        cout<<"   "<<i+1<<"\t";
        for(int j=0; j<3; j++)
        {
            if(j==1)cout<<atndncArray[i][j]<<"     ";
            else cout<<"     "<<atndncArray[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"\n*********************************************\n";
    return;
}
void adminMode::seeLogDetails()
{
    cout<<"Logged In: "<<logInNum<<endl;
    cout<<"Logged Out: "<<logOutNum<<endl;
}
//contribution to setDate() function made by Anurag Yadav
void adminMode::setDate()
{
    int day, month, year;
    string monthArray[13]= {"null","January","February","March","April","May","June","July","August","September","October","November","December"};
    string weekDay[7]= { "Sunday", "Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday"};
    cin>>day ;
    cin>>month ;
    cin>>year;
    int year_0 = year - (14 - month) / 12;
    int leap_year_adjustment = year_0/4 - year_0/100 + year_0/400;
    int month_0 = month + 12 * ((14 - month) / 12) - 2;
    int day_of_week = (day + leap_year_adjustment + (31*month_0)/12) % 7;
    date=weekDay[day_of_week]+", "+to_string(day)+" "+monthArray[month]+" "+to_string(year);
}

void Employee::searchEmployee()
{
    string fName,sName;
    cin>>fName;
    cin>>sName;
    int foundName=0;
    for(int i=0; i<=dirSize; i++)
    {
        if(i==dirSize)
        {
            break;
        }
        else if(fName==atndncArray[i][0] && sName==atndncArray[i][1])
        {
            foundName++;
        }
        else continue;
    }
    if(foundName==0){cout<<fName<<" "<<sName<<" has Not Logged In."<<endl; return ;}
    else if(foundName==1 || foundName%2!=0){cout<<fName<<" "<<sName<<" has Logged In."<<endl; return ;}
    else if(foundName==2 || foundName%2==0){cout<<fName<<" "<<sName<<" has Logged Out."<<endl; return ;}
}
void adminMode::writeAttendance()
{
    ofstream file("AttendanceTable.csv",ios::app); //replace the filename"AttendanceTable.csv" with the name of the csv file in your directory
    if(!file.is_open())
    {
        cout<<"Could not open file"<<endl;
        return ;
    }
    else
    {
        if(date.length()==0)
        {

            cout<<endl;
            date="Unset";
            file<<date<<endl;
        }
        else
        {
            cout<<endl;
            file<<"Date:"<<","<<date<<endl;
        }
        file<<"Event No."<<","<<","<<"Name"<<","<<","<<","<< "Status"<<endl;
        for(int i=0; i<addName; i++)
        {
            file<<i+1<<","<<","<<atndncArray[i][0]<<","<<atndncArray[i][1]<<","<<","<<atndncArray[i][2]<<endl;
        }
    }
    file.close();

    return ;
}
//prototyped a function which is defined beneath main()
void adminModeFunction()

//end of member functions of adminMode
;
int main()
{
    static int loginCount;
    for(int i=0;; i++)
    {
        string resp;
        cout<<"*******************************************************************************"<<endl;
        cout<<"Do You Wish to LOGIN/LOGOUT?(y/n) ";
        cin>>resp;
        cout<<"*******************************************************************************"<<endl;
        if(resp=="y" || resp=="Y")
        {
            cout<<"Login Number: "<<++loginCount<<endl;
            Employee emp[i+1];
            emp[i].readName();
            cout<<"Press Any Key to Continue:";
            getch();
            system("cls");
        }
        else if(resp=="n" || resp=="N")continue;
        else if(resp=="$adminMode_enter")
        {
            adminModeFunction();
        }
        else
        {
            cout<<"Invalid Response"<<endl;
            continue;
        }

    }
}
void adminModeFunction()
{
    cout<<"Administrator Privileges Granted.\n";
    adminMode adminEvent;
    Employee adminEvent2;
    for(int i=0;; i++)
    {
        cout<<"$adminMode_getCommand=>";
        string command;
        cin>>command;
        if (command=="getAttendanceLog")adminEvent.showAtndncTable();
        if (command=="getLogDetails")adminEvent.seeLogDetails();
        if(command=="setDate")adminEvent.setDate();
        if(command=="searchEmployee")adminEvent2.searchEmployee();
        if(command=="writeAttendance")adminEvent.writeAttendance();
        if(command=="clearConsole")
        {
            system("cls");
            main();
        }

    }

}
