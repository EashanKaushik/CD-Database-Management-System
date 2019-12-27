#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>

class cd_Info
{
 long cdNum;
 char cdName[50];
 char AName[20];
 public:
 void Createcd()
 {
  gotoxy(33,2);
  cout<<"NEW CD ENTRY";
  cout<<endl<<"I******************************************************************************I"<<endl<<endl;
  cout<<"Enter the CD Number      : ";
  cin>>cdNum;
  cout<<endl;
  cout<<"Enter the Name of the CD : ";
  gets(cdName);
  cout<<endl;
  cout<<"Enter the Director's Name    : ";
  gets(AName);
  cout<<endl;
  cout<<"CD Registered."<<endl<<endl;
 }
 void cdDetails()
 {
  cout<<"CD Number : "<<cdNum<<endl;
  cout<<"CD Name   : "<<cdName<<endl;
  cout<<"Director Name : "<<AName<<endl<<endl;
 }
 void ModifycdDetails()
 {
  cout<<"CD Number             : ";
  cin>>cdNum;
  cout<<endl;
  cout<<"Modify CD Name to     : ";
  gets(cdName);
  cout<<endl;
  cout<<"Modify Director's Name to : ";
  gets(AName);
  cout<<endl<<endl;
 }
 long ReturncdNumber()
 {
  return cdNum;
 }
 void report()
 {
  cout<<setw(15)<<cdNum<<setw(30)<<cdName<<setw(30)<<cdName<<endl;
 }
};

class Student_Info
{
 long AdmissionNum;
 char Name[20];
 long StudentcdNum;
 int Issue;
 public:
 void RegisterStudent()
 {
  clrscr();
  gotoxy(33,2);
  cout<<"NEW STUDENT ENTRY";
  cout<<endl<<"I******************************************************************************I"<<endl<<endl;
  cout<<"Enter the Admission Number    : ";
  cin>>AdmissionNum;
  cout<<endl;
  cout<<"Enter the Name of the Student : ";
  gets(Name);
  cout<<endl;
  Issue=0;
  StudentcdNum=0;
  cout<<"Student Registered."<<endl<<endl;
 }
 void StudentDetails()
 {
  cout<<"Admission Number       : "<<AdmissionNum<<endl;
  cout<<"Student Name           : ";
  puts(Name);
  cout<<"Number of CDs issued : "<<Issue<<endl;
  if(Issue==1)
  {
   cout<<"cd Number            : "<<StudentcdNum<<endl<<endl;
  }
 }
 void ModifyStudentDetails()
 {
  cout<<"Admission Number          : ";
  cin>>AdmissionNum;
  cout<<endl<<"Modify Student Name : ";
  gets(Name);
  cout<<endl<<endl;
 }
 long ReturnAdmissionNum()
 {
  return AdmissionNum;
 }
 long ReturnStudentcdNum()
 {
  return StudentcdNum;
 }
 int ReturnIssue()
 {
  return Issue;
 }
 void Issued()
 {
  Issue=1;
 }
 void ResetIssue()
 {
  Issue=0;
 }
 void AcceptStudentcdNum(long t)
 {
  StudentcdNum=t;
 }
 void report()
 {
  cout<<setw(15)<<AdmissionNum<<setw(30)<<Name<<setw(20)<<Issue<<endl;
 }
};

fstream f,f1;
cd_Info b;
Student_Info s;

void WriteTocd()
{
 char ch;
 f.open("cd.dat",ios::out|ios::app|ios::binary);
 do
 {
  clrscr();
  b.Createcd();
  f.write((char*)&b,sizeof(b));
  cout<<endl;
  cout<<"Do you want to add more records? (y/n): ";
  cin>>ch;
  cout<<endl<<endl;
 }
 while(ch=='y'||ch=='Y');
 f.close();
}

void WriteToStudent()
{
 char ch;
 f.open("Student.dat",ios::out|ios::app|ios::binary);
 do
 {
  s.RegisterStudent();
  f.write((char*)&s,sizeof(s));
  cout<<endl;
  cout<<"Do you want to add more records? (y/n): ";
  cin>>ch;
 }
 while(ch=='y'||ch=='Y');
 f.close();
}

void SpecialcdDisplay(long n)
{
 cout<<endl<<endl<<"CD DETAILS";
 cout<<endl<<endl;
 int flag=0;
 f1.open("cd.dat",ios::in|ios::binary);
 while(f1.read((char*)&b,sizeof(cd_Info)))
 {
  if(n==b.ReturncdNumber())
  {
   b.cdDetails();
   flag=1;
   break;
  }
 }
 f1.close();
 if(flag==0)
 {
  cout<<endl<<"CD does not exist";
 }
 getch();
}

void SpecialStudentDisplay(long n)
{
 gotoxy(37,2);
 cout<<endl<<endl<<"STUDENT DETAILS"<<endl<<endl;
 int flag=0;
 f.open("Student.dat",ios::in|ios::binary);
 while(f)
 {
  f.read((char*)&s,sizeof(Student_Info));
  if(n==s.ReturnAdmissionNum())
  {
   s.StudentDetails();
   flag=1;
   break;
  }
 }
 f.close();
 if(flag==0)
 {
  cout<<endl<<"Student does not exist.";
 }
 getch();
}

void Modify_cd()
{
 long n;
 int found=0,x;
 clrscr();
 gotoxy(31,2);
 cout<<"MODIFY CD RECORD";
 cout<<endl<<"I******************************************************************************I"<<endl;
 cout<<endl<<endl<<"Enter the CD number : ";
 cin>>n;
 f1.open("cd.dat",ios::in|ios::ate|ios::out|ios::binary);
 f1.seekg(0);
 f1.read((char*)&b,sizeof(cd_Info));
 while(f1)
 {
  found=f1.tellg()-sizeof(cd_Info);
  if(n==b.ReturncdNumber())
  {
   cout<<endl<<"Previous Details:"<<endl<<endl;
   b.cdDetails();
   cout<<endl<<"Modify Details:"<<endl<<endl;
   b.ModifycdDetails();
   f1.seekg(found);
   f1.write((char*)&b,sizeof(cd_Info));
   cout<<endl<<endl<<"Record Updated.";
   x=1;
   break;
  }
 f1.read((char*)&b,sizeof(cd_Info));
 }
 f1.close();
 if(x==0)
 {
  cout<<endl<<"Record not found";
 }
 getch();
}

void Modify_Student()
{
 long n;
 int found=0,x=0;
 clrscr();
 gotoxy(30,2);
 cout<<"MODIFY STUDENT RECORD"<<endl;
 cout<<"I******************************************************************************I"<<endl;
 cout<<endl<<endl<<"Enter the Admission Number of the student: ";
 cin>>n;
 f.open("Student.dat",ios::in|ios::out|ios::binary);
 f.seekg(0);
 f.read((char*)&s,sizeof(Student_Info));
 while(f)
 {
  found=f.tellg()-sizeof(Student_Info);
  if(n==s.ReturnAdmissionNum())
  {
   cout<<"Previous Details:"<<endl<<endl;
   s.StudentDetails();
   cout<<"Modify Details:"<<endl<<endl;
   s.ModifyStudentDetails();
   f.seekg(found);
   f.write((char*)&s,sizeof(Student_Info));
   cout<<endl<<endl<<"Record Updated";
   x=1;
   break;
  }
  f.read((char*)&s,sizeof(Student_Info));
 }
 f.close();
 if(x==0)
 {
  cout<<endl<<"Record not found.";
 }
 getch();
}

void DisplayAllStudents()
{
 clrscr();
 f.open("Student.dat",ios::in|ios::binary);
 if(!f)
 {
  cout<<"Error. File couldn't be accessed.";
  getch();
  return;
 }
 cout<<endl<<endl<<"STUDENT LIST"<<endl<<endl;
 cout<<"|==============================================================================|"<<endl;
 cout<<setw(20)<<"Admission No."<<setw(20)<<"Name"<<setw(30)<<"CD Issued"<<endl<<endl;
 cout<<"|==============================================================================|"<<endl<<endl;
 while(f.read((char*)&s,sizeof(Student_Info)))
 {
  s.report();
 }
 f.close();
 getch();
}

void DisplayAllcd()
{
 clrscr();
 f1.open("cd.dat",ios::in|ios::binary);
 f1.seekg(0);
 f1.read((char*)&b,sizeof(cd_Info));
 cout<<endl<<endl<<"CD LIST"<<endl<<endl;
 cout<<"|==============================================================================|"<<endl;
 cout<<setw(18)<<"CD Number"<<setw(22)<<"CD Name"<<setw(30)<<"Director"<<endl<<endl;
 cout<<"|==============================================================================|"<<endl<<endl;
 while(f1)
 {
  b.report();
  f1.read((char*)&b,sizeof(cd_Info));
 }
 f1.close();
 getch();
}

void cdIssue()
{
 long sn,bn,t;
 int found=0,flag=0;
 clrscr();
 gotoxy(35,2);
 cout<<"CD ISSUE";
 cout<<endl<<"I******************************************************************************I"<<endl;
 cout<<endl<<endl<<"Enter the student's Admission Number: ";
 cin>>sn;
 f.open("Student.dat",ios::in|ios::out|ios::binary);
 f1.open("Book.dat",ios::in|ios::out|ios::binary);
 while(f.read((char*)&s,sizeof(Student_Info)) && found==0)
 {
  if(sn==s.ReturnAdmissionNum())
  {
   found=1;
   if(s.ReturnIssue()==0)
   {
    cout<<"Enter the CD Number: ";
    cin>>bn;
    while(f1.read((char*)&b,sizeof(cd_Info)) && flag==0)
    {
     if(bn==b.ReturncdNumber())
     {
      b.cdDetails();
      flag=1;
      s.Issued();
      t=b.ReturncdNumber();
      s.AcceptStudentcdNum(t);
      int pos=f.tellg()-sizeof(s);
      f.seekp(pos);
      f.write((char*)&s,sizeof(Student_Info));
      cout<<endl<<endl<<"CD Issued."<<endl<<"Please Note: Write the current date on the registor of the CD. Please retrun the CD within 15 days to avoid fine. Fine - Rs. 5 per extra day.";
     }
    }
    if(flag==0)
    cout<<"The CD does not exist";
   }
   else
   cout<<"Previous CD has not yet been deposited.";
  }
 }
 if(found==0)
 {
  cout<<"Student record does not exist.";
 }
 getch();
 f.close();
 f1.close();
}

void cdDeposit()
{
 long sn,bn;
 int found=0,flag=0,day,fine,pos;
 clrscr();
 gotoxy(35,2);
 cout<<"CD DEPOSIT"<<endl;
 cout<<"I******************************************************************************I"<<endl<<endl;
 cout<<endl<<endl<<"Student's Admission Number: ";
 cin>>sn;
 f.open("Student.dat",ios::in|ios::out|ios::binary);
 f1.open("cd.dat",ios::in|ios::out|ios::binary);
 while((f.read((char*)&s,sizeof(Student_Info))) && (found==0))
 {
  if(sn==s.ReturnAdmissionNum())
  {
   found=1;
   if(s.ReturnIssue()==1)
   {
    while(f1.read((char*)&b,sizeof(cd_Info)) && flag==0)
    {
     if(s.ReturnStudentcdNum()==b.ReturncdNumber())
     {
      b.cdDetails();
      flag=1;
      cout<<endl<<endl<<"Number of days after which the CD has been deposited: ";
      cin>>day;
      if(day>15)
      {
       fine=(day-15)*5;
       cout<<endl<<endl<<"Fine: Rs."<<fine;
      }
      s.ResetIssue();
      pos=f.tellg()-sizeof(s);
      f.seekp(pos);
      f.write((char*)&s,sizeof(Student_Info));
      cout<<endl<<endl<<"CD Deposited.";
     }
    }
   if (flag==0)
   cout<<"CD doesn't exist.";
   }
   else
   cout<<"No CD issued.";
  }
 }
 if(found==0)
 {
  cout<<"Student record does not exist.";
 }
 getch();
 f.close();
 f1.close();
}

void intro()
{
 clrscr();
 gotoxy(23,7);
 cout<<"CD/DVD DATABASE MANAGEMENT SOFTWARE";
 gotoxy(60,11);
 cout<<"*******";
 gotoxy(60,12);
 cout<<"*_____*";
 gotoxy(60,13);
 cout<<"*_____*";
 gotoxy(60,14);
 cout<<"*_____*";
 gotoxy(60,15);
 cout<<"*_____*";
 gotoxy(60,16);
 cout<<"*_____*";
 gotoxy(60,17);
 cout<<"*_____*";
 gotoxy(60,18);
 cout<<"*******";
 gotoxy(45,11);
 cout<<"*******";
 gotoxy(45,12);
 cout<<"*_____*";
 gotoxy(45,13);
 cout<<"*_____*";
 gotoxy(45,14);
 cout<<"*_____*";
 gotoxy(45,15);
 cout<<"*_____*";
 gotoxy(45,16);
 cout<<"*_____*";
 gotoxy(45,17);
 cout<<"*_____*";
 gotoxy(45,18);
 cout<<"*******";
 gotoxy(30,11);
 cout<<"*******";
 gotoxy(30,12);
 cout<<"*_____*";
 gotoxy(30,13);
 cout<<"*_____*";
 gotoxy(30,14);
 cout<<"*_____*";
 gotoxy(30,15);
 cout<<"*_____*";
 gotoxy(30,16);
 cout<<"*_____*";
 gotoxy(30,17);
 cout<<"*_____*";
 gotoxy(30,18);
 cout<<"*******";
 gotoxy(15,11);
 cout<<"*******";
 gotoxy(15,12);
 cout<<"*_____*";
 gotoxy(15,13);
 cout<<"*_____*";
 gotoxy(15,14);
 cout<<"*_____*";
 gotoxy(15,15);
 cout<<"*_____*";
 gotoxy(15,16);
 cout<<"*_____*";
 gotoxy(15,17);
 cout<<"*_____*";
 gotoxy(15,18);
 cout<<"*******";
 gotoxy(10,22);
 cout<<"MADE BY:Eashan Kaushik";
 gotoxy(31,23);
 cout<<"Vellore";
 getch();}

void AdminMenu()
{
 clrscr();
 int ch2;
 gotoxy(35,2);
 cout<<"\bADMINISTRATOR MENU"<<endl;
 cout<<endl<<endl<<endl<<"\t1.Create Student Record";
 cout<<endl<<endl<<"\t2.Display the Details of All Students";
 cout<<endl<<endl<<"\t3.Display the Records of a Specific Student";
 cout<<endl<<endl<<"\t4.Modify Student Records";
 cout<<endl<<endl<<"\t5.Create a CD Record";
 cout<<endl<<endl<<"\t6.Display All CD";
 cout<<endl<<endl<<"\t7.Display a Specific CD";
 cout<<endl<<endl<<"\t8.Modify CD";
 cout<<endl<<endl<<"\t9.Back to the Main Menu";
 cout<<endl<<endl<<endl<<"Please Enter Your Choice (1-9): ";
 cin>>ch2;
 switch(ch2)
 {
  case 1: clrscr();
	  WriteToStudent();
	  break;
  case 2: DisplayAllStudents();
	  break;
  case 3: long num;
	  clrscr();
	  cout<<"Please Enter The Admission Number: ";
	  cin>>num;
	  SpecialStudentDisplay(num);
	  break;
  case 4: Modify_Student();
	  break;
  case 5: clrscr();
	  WriteTocd();
	  break;
  case 6: DisplayAllcd();break;
  case 7: {
	   long num;
	   clrscr();
	   cout<<endl<<"Please Enter The CD Number: ";
	   cin>>num;
	   SpecialcdDisplay(num);
	   break;
	  }
  case 8: Modify_cd();

  case 9: return;
  default:cout<<endl<<"Invalid Choice";
 }
 int abc;
 cout<<endl<<"Would you like to\n1.Return to menu\n2.Exit";
 cin>>abc;
 switch(abc)
 {
 case 1 :  AdminMenu();break;
 case 2 :  exit(0);
 }
}

void main()
{
 int ch;
 textcolor(7);
 intro();
 do
 {
  clrscr();
cout<<"I******************************************************************************I";
gotoxy(37,3);
  cout<<"\bMAIN MENU"<<endl<<endl;
cout<<"I******************************************************************************I"<<endl<<endl;
  cout<<"\t1. CD Issue"<<endl<<endl;
  cout<<"\t2. CD Deposit"<<endl<<endl;
  cout<<"\t3. Administrator Menu"<<endl<<endl;
  cout<<"\t4. Exit"<<endl<<endl<<endl<<endl;
  gotoxy(60,11);
  cout<<"*******";
  gotoxy(60,12);
  cout<<"(_____)";
  gotoxy(60,13);
  cout<<"(_____)";
  gotoxy(60,14);
  cout<<"(_____)";
  gotoxy(60,15);
  cout<<"(_____)";
  gotoxy(60,16);
  cout<<"(_____)";
  gotoxy(60,17);
  cout<<"(_____)";
  gotoxy(60,18);
  cout<<"*******";
  cout<<endl<<"Please Select Your Option (1-4): ";
  cin>>ch;
  switch(ch)
  {
   case 1:clrscr();
	  cdIssue();
	  break;
   case 2:cdDeposit();
	  break;
   case 3:AdminMenu();
	  break;
   case 4:exit(0);
   default:cout<<"Invalid Choice";  } }
 while(ch!='4');
 getch();
}
