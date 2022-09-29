#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<process.h>
#include<string.h>

class bank
{
   int custno,transno;
   char custname[20],address[30],type[20];
   float amount,transamount,phoneno;

  public:
   void customermenu();
   void transactionmenu();
   void reportmenu();
   void aboutus();
   void addition();
   void allcust();
   void indcust();
   void modification();
   void deletion();
   void deposit();
   void indtrans();
   void alltrans();
   void withdrawal();
   void customerreport();
   void transactionreport();
   int check(int);
   int returntransno();
};

long pos;

int bank::check(int z)
{
  bank b5;
  int flag=0;
  ifstream ifile;
  ifile.open("CUSTOMER.DAT",ios::binary);
  if(!ifile)
  {
    cout<<"Could not open file.";
    exit(0);
  }
  while(ifile.read((char*)&b5,sizeof(b5)))
  {
    pos=ifile.tellg();
    if(b5.custno==z)
    {
      flag=1;
      break;
    }
  }
  if(flag==0)
    return(0);
  else
    return(1);
}

void bank::addition()
{
  clrscr();
  bank b1;
  int x,c;
  ofstream ofile;
  ofile.open("CUSTOMER.DAT",ios::binary|ios::app|ios::in|ios::out);
  if(!ofile)
  {
    cout<<"Could not open the file.";
    exit(0);
  }
  cout<<"Enter customer number: ";
  cin >> c;
  x=check(c);
  if(x>0)
       {

	 cout<<"Already existing.";
	 getch();

       }
      ofile.close();

  if(x==0)
  {
    ofile.open("CUSTOMER.DAT",ios::binary|ios::app);
    b1.custno=c;
    cout<<"Enter customer name: ";
    gets(b1.custname);
    cout<<"Enter customer address: ";
    gets(b1.address);
    cout<<"Enter customer phone number: ";
    cin>>b1.phoneno;
    cout<<"Enter customer amount: ";
    cin>>b1.amount;
    ofile.write((char*)&b1,sizeof(b1));
    ofile.close();
    getch();
  }

}

void bank::modification()
{
  clrscr();
  int cm,x1,ch;
  float s;
  long pos;
  char n[50],ch1;
  bank b;
  cout<<"Enter the customer number to modify: ";
  cin>>cm;
  fstream file;
  file.open("CUSTOMER.DAT",ios::binary|ios::in|ios::out);
  int flag=0;
  while(!file.eof())
  {
    pos=file.tellg();
    file.read((char*)&b,sizeof(b));
    if(b.custno==cm)
    {
      flag=1;
      cout<<"Customer name: "<<b.custname;
      cout<<"\n Do you want to modify the name(Y,y/N,n):";
      cin>>ch1;
      if(ch1=='Y'||ch1=='y')
	{
	  cout<<"\n Enter the new name: ";
	  gets(n);
	  strcpy(b.custname,n);
	}
	cout<<"\n Customer address: "<<b.address;
	cout<<"\n Do you want to modify the address(Y,y/N,n): ";
	cin>>ch1;
	if(ch1=='Y'||ch1=='y')
	{
	  cout<<"\n Enter the new address: ";
	  gets(n);
	  strcpy(b.address,n);
	}
	cout<<"\n Customer amount: "<<b.amount;
	cout<<"\n Do you want to modify the amount(Y,y/N,n): ";
	cin>>ch1;
	if(ch1=='Y'||ch1=='y')
	{
	  cout<<"\n Enter the new amount: ";
	  cin>>s;
	  b.amount=s;
	}
	cout<<"\n Customer phone number: "<<b.phoneno;
	cout<<"\n Do you want to modify the phone number(Y,y/N,n): ";
	cin>>ch1;
	if(ch1=='Y'||ch1=='y')
	{
	  cout<<"\n Enter the new phone nummber: ";
	  cin>>s;
	  b.phoneno=s;
	}
	file.seekg(pos);
	file.write((char*)&b,sizeof(b));
	break;
    }

  }
  if(flag==0)
   {
     cout<<"Not existing.";
     getch();
   }
     file.seekg(0);
     file.close();
  getch();
}

void bank::deletion()
{
  clrscr();
  bank b;
  int ch;
  cout<<"Enter the customer number to be deleted: ";
  cin>>ch;
  ifstream ifile;
  ifile.open("CUSTOMER.DAT",ios::binary);
  ofstream ofile;
  ofile.open("TEMP.DAT",ios::binary);
  char ch2;
  int flag=0,flag1=0;
  while(ifile.read((char*)&b,sizeof(b)))
  {
    if(b.custno==ch)
    {
      cout<<"\n Customer number: "<<b.custno;
      cout<<"\n Customer name: "<<b.custname;
      cout<<"\n Customer address: "<<b.address;
      cout<<"\n Customer phone number: "<<b.phoneno;
      cout<<"\n Total amount: "<<b.amount;
      cout<<"\n";
      flag=1;
      cout<<"\n Do you want to delete the above record ?(Y,y/N,n): " ;
      cin>>ch2;
      if(ch2=='Y'||ch2=='y')
	 flag1=1;

    }
  }
  ifile.close();
  ifstream ifile1;
  ifile1.open("CUSTOMER.DAT",ios::binary);
  if(flag1==1)
    {
     while(ifile1.read((char*)&b,sizeof(b)))
	if(b.custno!=ch)
	  ofile.write((char*)&b,sizeof(b));
    ifile1.close();
    ofile.close();
    remove("CUSTOMER.DAT");
    rename("TEMP.DAT","CUSTOMER.DAT");
    cout<<"Deleted successfully.";
    }
  if(flag==0)
    cout<<"Not found.";
  getch();
}

void bank::deposit()
{
  clrscr();
  int no,no2,pos,flag=0,f;
  bank b;
  fstream file1;
  file1.open("CUSTOMER.DAT",ios::binary|ios::in|ios::out);
  fstream file2;
  file2.open("TRANSACTION.DAT",ios::binary|ios::app|ios::in|ios::out);
  cout<<"Enter the transaction number: ";
  cin>>no;
  while(file2.read((char*)&b,sizeof(b)))
  {
    if(b.transno==no)
    {
      f=1;
    }
  }
  file2.close();
  file2.open("TRANSACTION.DAT",ios::binary|ios::app|ios::in|ios::out);
  if(f==1)
    {
    cout<<"Already existing transaction number.";
    getch();
    }
  else
  {
  cout<<"Enter the customer number: ";
  cin>>no2;
  while(!file1.eof())
  {
    pos=file1.tellg();
    file1.read((char*)&b,sizeof(b));
    if(b.custno==no2)
    {
      flag=1;
      cout<<"Existing amount: "<<b.amount;
      cout<<"\n Enter the amount to be deposited: ";
      cin>>b.transamount;
      b.amount=b.amount+b.transamount;
      file1.seekg(pos);
      file1.write((char*)&b,sizeof(b));
      file1.seekg(0);
      strcpy(b.type,"Deposit");
      b.transno=no;
      file2.write((char*)&b,sizeof(b));
      break;
     }
  }
  if(flag==1)
  {
    cout<<"Deposited successfully.";
    getch();
  }
  if(flag==0)
  {
    cout<<"Customer number not existing.";
    cout<<"\n Transaction not possible.";
  }
 }
     file1.close();
     file2.close();
  getch();
}

void bank::withdrawal()
{
  clrscr();
  int no,no2,pos,flag=0,c,flag1=0,f;
  float v;
  bank b;
  fstream file1;
  file1.open("CUSTOMER.DAT",ios::binary|ios::in|ios::out);
  fstream file2;
  file2.open("TRANSACTION.DAT",ios::binary|ios::app|ios::in|ios::out);
  cout<<"Enter transaction number: ";
  cin>>no;
  while(file2.read((char*)&b,sizeof(b)))
  {
    if(b.transno==no)
      f=1;
  }
  file2.close();
  file2.open("TRANSACTION.DAT",ios::binary|ios::app|ios::in|ios::out);
  if(f==1)
    {
      cout<<"Already existing transaction number.";
      getch();
    }
  else
  {
  cout<<"Enter the customer number: ";
  cin>>no2;
  while(!file1.eof())
  {
    pos=file1.tellg();
    file1.read((char*)&b,sizeof(b));
    if(b.custno==no2)
    {
      flag=1;
      cout<<"Your balance: "<<b.amount;
      cout<<"\n Enter the amount to be withdrawed: ";
      cin>>b.transamount;
      b.amount=b.amount-b.transamount;
      v=b.amount;
      if(v>=500)
      {
	flag1=1;
	file1.seekg(pos);
	file1.write((char*)&b,sizeof(b));
	file1.seekg(0);
	strcpy(b.type,"Withdrawal");
	b.transno=no;
	file2.write((char*)&b,sizeof(b));
	break;
      }
    }
  }
  if(flag1==1)
  {
    cout<<"Withdrawed successfully.";
  }
  if(flag==0)
  {
    cout<<"Customer number not existing.";
  }
  if(flag1==0)
    cout<<"\n Transaction not possible.";
     file1.close();
     file2.close();
   }
  getch();
}


void bank::allcust()
{
  clrscr();
  bank b;
  ifstream ifile;
  ifile.open("CUSTOMER.DAT",ios::binary);
  if(!ifile)
  {
    cout<<"Could not open yhe file.";
    exit(0);
  }
  int r=2;
  gotoxy(3,r);
  cout<<"CUSTNO";
  gotoxy(11,r);
  cout<<"CUSTNAME";
  gotoxy(35,r);
  cout<<"ADDRESS";
  gotoxy(55,r);
  cout<<"PHONENO";
  gotoxy(75,r);
  cout<<"AMOUNT";
  while(ifile.read((char*)&b,sizeof(b)))
  {
    r=r+1;
    gotoxy(3,r);
    cout<<b.custno;
    gotoxy(11,r);
    cout<<b.custname;
    gotoxy(35,r);
    cout<<b.address;
    gotoxy(55,r);
    cout<<b.phoneno;
    gotoxy(75,r);
    cout<<b.amount;
  }
  ifile.close();
  getch();
}

void bank::indcust()
{
  clrscr();
  bank b4;
  int y,flag=0;
  ifstream ifile;
  ifile.open("CUSTOMER.DAT",ios::binary);
  if(!ifile)
  {
    cout<<"Could not open the file.";
    getch();
    exit(0);
  }
  cout<<"Enter the customer number: ";
  cin>>y;
  while(ifile.read((char*)&b4,sizeof(b4)))
  {
   if(b4.custno==y)
   {
      cout<<"\n Customer number: "<<b4.custno;
      cout<<"\n Customer name: "<<b4.custname;
      cout<<"\n Customer address: "<<b4.address;
      cout<<"\n Customer phone number: "<<b4.phoneno;
      cout<<"\n Total amount: "<<b4.amount;
      cout<<"\n";
      flag=1;
      getch();
    }
  }
   if(flag==0)
     {
       cout<<"Customenr number not found.";
       getch();
     }
    ifile.close();
}

void bank::customerreport()
{
  bank b;
  int ch5;
  do{
      clrscr();
      cout<<"CUSTOMER DETAILS";
      cout<<"\n 1.All customer details." ;
      cout<<"\n 2.Individual individual details.";
      cout<<"\n 3.Exit.";
      cout<<"\n Enter choice: ";
      cin>>ch5;
      switch(ch5)
      {
	case 1:b.allcust();
	       break;
	case 2:b.indcust();
	       break;
	case 3:return;
	default:cout<<"\n Wrong choice.";
	getch();
      }
    }while(ch5!=3);
}


void bank::alltrans()
{
  clrscr();
  bank b;
  ifstream ifile;
  ifile.open("TRANSACTION.DAT",ios::binary);
  int r1=2;
  gotoxy(3,r1);
  cout<<"TRANS NUMBER";
  gotoxy(21,r1);
  cout<<"AMOUNT";
  gotoxy(41,r1);
  cout<<"TYPE";
  while(ifile.read((char*)&b,sizeof(b)))
  {
    r1=r1+1;
    gotoxy(3,r1);
    cout<<b.transno;
    gotoxy(21,r1);
    cout<<b.transamount;
    gotoxy(41,r1);
    cout<<b.type;

  }
  ifile.close();
  getch();
}

void bank::indtrans()
{
  clrscr();
  bank b;
  int no,flag=0;
  ifstream ifile;
  ifile.open("TRANSACTION.DAT",ios::binary);
  cout<<"Enter the transaction number: ";
  cin>>no;
  while(ifile.read((char*)&b,sizeof(b)))
  {
    if(b.transno==no)
    {
      flag=1;
      cout<<"\n Transaction number: "<<b.transno;
      cout<<"\n Transaction amount: "<<b.transamount;
      cout<<"\n Transaction type: "<<b.type;
      cout<<"\n";
    }
  }
  if(flag==0)
    cout<<"Transaction number not found.";
    getch();
}

void bank::transactionreport()
{
  int ch4;
  bank b4;
  do{
      clrscr();
      cout<<"TRANSACTION";
      cout<<"\n 1.All transaction details." ;
      cout<<"\n 2.Individual transaction details.";
      cout<<"\n 3.Exit.";
      cout<<"\n Enter choice: ";
      cin>>ch4;
      switch(ch4)
      {
	case 1:b4.alltrans();
	       break;
	case 2:b4.indtrans();
	       break;
	case 3:return;
	default:cout<<"Wrong choice.";
	getch();
      }
    }while(ch4!=3);
}

void bank::aboutus()
{
  clrscr();
  cout<<"\n This program done by:";
  cout<<"\n i)ANIRUDH SURESH.";
  cout<<"\n ii)BALASURYA.";
  cout<<"\n iii)ARJUN RAMESH.";
  getch();
}

void bank::customermenu()
{
  int ch1;
  bank b;
  do{
     clrscr();
     cout<<"CUSTOMER MENU";
     cout<<"\n 1.Addition.";
     cout<<"\n 2.Modification.";
     cout<<"\n 3.Deletion.";
     cout<<"\n 4.Exit.";
     cout<<"\n Enter choice: ";
     cin>>ch1;
     switch(ch1)
     {
       case 1:b.addition();
	      break;
       case 2:b.modification();
	      break;
       case 3:b.deletion();
	      break;
       case 4:return;
       default:cout<<"Wrong choice.";
       getch();
       }
     }while(ch1!=4);
}

void bank::transactionmenu()
{
  int ch2;
  bank b;
  do{
      clrscr();
      cout<<"TRANSACTION MENU";
      cout<<"\n 1.Deposit.";
      cout<<"\n 2.Withdrawal.";
      cout<<"\n 3.Exit.";
      cout<<"\n Enter choice: ";
      cin>>ch2;
      switch(ch2)
      {
	case 1:b.deposit();
	       break;
	case 2:b.withdrawal();
	       break;
	case 3:return;
	default:cout<<"Wrong choice.";
	getch();
      }
    }while(ch2!=3);
}

void bank::reportmenu()
{
  int ch3;
  bank b;
  do{
      clrscr();
      cout<<"REPORT MENU";
      cout<<"\n 1.Customer report.";
      cout<<"\n 2.Transaction report.";
      cout<<"\n 3.Exit.";
      cout<<"\n Enter choice: ";
      cin>>ch3;
      switch(ch3)
      {
	case 1:b.customerreport();
	       break;
	case 2:b.transactionreport();
	       break;
	case 3:return;
	default:cout<<"Wrong choice.";
	getch();
      }
    }while(ch3!=3);
}

void main()
{
  bank b;
  int choice;
  clrscr();
  gotoxy(30,10);
  cout<<"WELCOME TO SBI BANK";
  getch();
  gotoxy(27,11);
  cout<<"Your perfect banking partner";
  getch();
  do{
      clrscr();
      cout<<"BANK MENU";
      cout<<"\n 1.Customer.";
      cout<<"\n 2.Transaction.";
      cout<<"\n 3.Report.";
      cout<<"\n 4.About us.";
      cout<<"\n 5.Exit.";
      cout<<"\n Enter the choice: ";
      cin>>choice;
      switch(choice)
      {
	case 1:b.customermenu();
	       break;
	case 2:b.transactionmenu();
	       break;
	case 3:b.reportmenu();
	       break;
	case 4:b.aboutus();
	       break;
	case 5:exit(0);
	default:cout<<"Wrong choice.";
	getch();
      }
    }while(choice!=5);
}

