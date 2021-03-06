/* This programme is to make time table for school ,
this is applicable for schools having 6 working days with 8 periods.  */



#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<dos.h>
#include<process.h>
#include<stdio.h>
#include<iomanip.h>
#include<string.h>
#include<ctype.h>


class table
   {
   int clas;
   char tname[6][8][25];
   char sname[6][8][25];

   public:
   void read_data();                     //to read data from user.
   void extract_data_by_class_num();     //to read data from file.
   int check_condition(char[],int,int);  //to check time table overlap.
   int return_class();
   void extract_all_data();
   };



/*___________________________RETURNING FUNCTIONS________________________*/

int table:: return_class()
   {
    return(clas);
   }

int no_of_saved_files()
    {
    table t;
     ifstream fin;
     int count_saved_files=0;

     fin.open("ttable.dat",ios::in | ios::binary);
      while(fin.read((char*)&t,sizeof(t)))
      ++count_saved_files;
      fin.close();
      return(count_saved_files);
     }





int table :: check_condition(char teacher_name[], int i, int j)
       {

       table t;
       ifstream fin;
       int a,b,c=0;
       int zero=0, count_saved_files;

       fin.open("ttable.dat",ios::in | ios:: binary);

       fin.seekg(0);
       count_saved_files = no_of_saved_files();


       for(a=0;a<6;++a)
	 {
	 for(b=0;b<8;++b)
	   {

		if(a==i && b==j)
		 {
		      while(zero<count_saved_files)
			 {
		      while(fin.read((char*)&t,sizeof(t)))
		       {
		       if(strcmp(t.tname[a][b],teacher_name)==0)
		      c++;
		      zero++;
		       }

		      } }
		}}
	 fin.close();
	   return (c) ;
    }

int check_digits(char str[])   //function to check digits in
			       //subject or teacher's name.
    {
    int i=0,count=0;
    int l=strlen(str);

      for(i=0;i<l;++i)
	{
	 if(isdigit(str[i]))
	 count++;
	 }
	 return(count);
      }


int check_class_overlap(int cl)
   {
   table t;
   ifstream fin;
   int count=0;

   fin.open("ttable.dat",ios::in | ios::binary) ;
   while(fin.read((char*)&t,sizeof(t)))
	{
	if(t.return_class()==cl)
	count++;
	}
	fin.close();
    return(count);
   }



/* __________________RETURNING FUNCTIONS(END)___________________*/



	     /* READING AND WRITING
 ________________________________________________________________    */


int check_class_in_saved_files(int clas)
   {
   int returning_value=0;
   ifstream fin;
   table t;
   fin.open("ttable.dat",ios::in | ios::binary);
   while(fin.read((char*)&t,sizeof(t)))
      {
      if(t.return_class()==clas)
      returning_value++;
      }

   return(returning_value);
   }


void delete_record_by_class_number(int cl)
    {
     table t,T,tm;
     char ch, choice;
     char found='f';
     ifstream fin,fin2;
     ofstream fout;


int class_found=  check_class_in_saved_files(cl);

if(class_found)
{
cout<<"\n do you want to see the record(y/n):";
cin>>choice;
if(choice=='y' || choice=='y')
  {
  ifstream fin;
  fin.open("ttable.dat",ios::in | ios::binary);
  while(fin.read((char*)&T,sizeof(T)))
     {
      if(T.return_class()==cl)
      break;
     }
     fin.seekg(-1*sizeof(T),ios::cur);
     T.extract_all_data();
     fin.close();
  }

 if(no_of_saved_files())
   {
     ifstream fin;
     fin.open("ttable.dat",ios::in | ios::binary);

     ofstream fout;
     fout.open("temp.dat",ios::out | ios::binary);

	while(fin.read((char*)&t,sizeof(t)))
	{

	 if(t.return_class()==cl)
	  {
	   found='t';
	   cout<<"\n are you sure to delete this record(y/n):";
	   cin>>ch;
	      if(ch=='y' || ch=='Y')
	       {
		 cout<<"\n record deleted.";
		 delay(500);
		 }
	      else
		{
		 fout.write((char*)&t,sizeof(t));
		 cout<<"\n record not deleted.";
		 delay(500);
		}
	     }
	  else
	   fout.write((char*)&t,sizeof(t));

	}
	if(found=='f')
	{
	cout<<"\n no recod with such class is saved.";
	delay(700);
	 }
	fin.close();
	fout.close();

	remove("ttable.dat");
	rename("temp.dat","ttable.dat");

   }
   }
   else
   {
   cout<<"\n no record is saved with such class name.";
   delay(500);
   cout<<"\n press any key to continue.";
   getch();

   }
  }



int incomplete_data=0;

int check_escape(char ch)
   {
   int num;
   num=int(ch);
   if(num==27)
   return(1);
   else
   return(-1);
   }



void week_days(int day, char week[15])            //checking week days.
   {
   switch (day)
      {
      case 0 : strcpy (week,"MONDAY"); break;
      case 1 : strcpy (week,"TUESDAY");  break;
      case 2 : strcpy (week,"WEDNESDAY"); break;
      case 3 : strcpy (week,"THURSDAY"); break;
      case 4 : strcpy (week,"FRIDAY"); break;
      case 5 : strcpy (week,"SATURDAY");break;


      }
   }

void table:: read_data()    //to read data from user.
   {
    main_menu:
   write_class_again:
   table T;
   int i,j , overlap , size_of_tname, size_of_sname ;
   int check_esc;
   char ch , temp1[25], temp2[25],temp3[25];
   int check_class=0;
   char choice;


   ifstream fin;
   fin.open("ttable.dat",ios::in |ios::binary);

	  write_again:


	 cout<<"\n CLASS:";
	 cin>>clas;
	 if(clas>12)
	   {
	    cout<<"\n Please input valid class number(< 12).";
	    cout<<"\n press any key to try again.";
	    getch();
	    goto write_again;
	   }
	check_class= check_class_overlap(clas);
	if(check_class)
	 {
	 cout<<"\n A data with such class number is already saved.";
	 cout<<"\n Delete previous"<<" "<<clas<<" "<<"class record?? (y/n):";
	 cin>>choice;
	 if(choice=='y'|| choice=='Y')
	 delete_record_by_class_number(clas);
	 else
	       {
	       cout<<"\n Write another class name.\n";
	       delay(600);
		goto write_again;
		}
	   }
	 cout<<"\n NOTICE:you can exit the program anytime by pressing Esc command.\n\n" ;
	   getch();
	 for(i=0;i<6;++i)
	   {
	   clrscr();
	     cout<<"\n PLEASE GIVE THE FOLLOWING DETAILS:\n";
	      cout<<"\n";

      for(j=0;j<8;++j)
	  {


	    int count_digits_sub=0 ;
	    int count_digits_teacher=0;

	  delay(50);

	 cout<<"(DAY:"<<i+1<<" ,"<<"PERIOD:"<<j+1<<") ";

	 write_again_sname:   //jumping(goto) statement if sname is not entered.
	 cout<<"SUBJECT:";
	 cin>>sname[i][j];

	 char ch;
	 int sub_length;
	 sub_length=strlen(sname[i][j]) ;
	 ch=sname[i][j][0];
	 if(sub_length==1)
	   {
	  int check=check_escape(ch);
	  if(check!=-1)
	  exit(0);
	  }
	 size_of_sname=strlen(sname[i][j]);


		if(!size_of_sname)
		  {
		    cout<<"\n YOU CAN'T LEFT THIS VACANT.";
		     goto write_again_sname;
		  }

	 strcpy(temp3,sname[i][j]) ;

	 count_digits_sub=check_digits(temp3);

	       if(count_digits_sub)
		   {
		      cout<<"\n please use only ALPHABETS,DIGITS are not allowed.";
		      cout<<"\n TRY AGAIN.";
		      goto write_again_sname;
		   }

	 cout<<" ," ;

	 again:

	 write_again_tname:

	 cout<<"TEACHER:";
	 gets(tname[i][j]);

	 sub_length=strlen(tname[i][j]);
	 ch=tname[i][j][0];
	  if(sub_length==1)
	  {
	   int check=check_escape(ch);
	  if(check!=-1)
	  exit(0);
	  }

	   size_of_tname=strlen(tname[i][j]);

		  if(!size_of_tname)       //if no data is given by user.
		     {
		       cout<<"\n YOU CAN'T LEFT THIS VACANT.";
		       goto  write_again_tname;
		     }

	 strcpy(temp2,tname[i][j]) ;

	 count_digits_teacher = check_digits(temp2);


	 if(count_digits_teacher)         //to check whether teacher's
					  //name contains any digits.

	    {
	     cout<<"\n pelase use only ALPHABETS, DIGITS are not allowed.";
	     cout<<"\n TRY AGAIN.";
	     goto write_again_tname;
	     }

	 strcpy(temp1,tname[i][j]);

	overlap = check_condition(temp1,i,j) ;

	 if(overlap==1)
	     {
	     delay(200);
	     cout<<"\n SORRY!!!";
	     delay(150);
	     cout<<"\n THIS TEACHER IS ALLOTEd CLASS.";
	     delay(100);
	     cout<<"\n WRITE ANOTHER TEACHER'S NAME.";
	     goto again;
	     }

	      }
	  if(i<5)
	  {
	     char week_day[10];
	     int day_num;
	     day_num=i+1;
	     week_days(day_num,week_day);
	     cout<<"\n Press (y/Y) to input "<<week_day<<" "<<"data";
	     cout<<" or press(n/N) to exit:";
	     cin>>ch;


	     if(ch=='y'||ch=='Y')
	     continue;
	     else
	       {
		 cout<<"\n WARNING!!!!.....";
		 cout<<"\n This will erase incomplete given data, CONTINUE and EXIT(y/n):";
		 cin>>ch;
		   if(ch=='y' || ch=='Y')
		    {
		     cout<<"\n DATA IS NOT SAVED.";
		       delay(500);
		      ::incomplete_data++;
		       break;
		     }

		   else
		  cout<<"\n press any key to return to main menu.";
	       }
	       }
   }
}

void write()      //to write the records.
   {
   table t;

    ofstream fout;
    fout.open("ttable.dat",ios::app | ios::binary);
    t.read_data();

    if(!::incomplete_data)
      {
       fout.write((char*)&t,sizeof(t));
       cout<<"\n record saved.";
       delay(600);
     }
    fout.close();

    }

/* _________________________________________________________________ */



/*___________________ EXTRACTING AND DISPLAYING ____________________*/

void table:: extract_data_by_class_num()
    {

    int day , period ,b;
    char ch, week[15];
    int day_num;


    for(day=0; day<6 ;++day)
	{
		clrscr();
		cout<<"\n CLASS:"<<clas;
		delay(50);
		cout<<"\t DAY:"<<day+1;

	      day_num=day;
	      week_days(day_num ,week );    //function to check week days.
	      cout<<" "<<"("<<week<<")";


	      cout<<"\n\n ";
	for(period=0; period<8; ++period)
	  {

	      cout<<"PERIOD:"<<period+1<<" "<<" ";
	      delay(50);
	      cout<<"SUBJECT:"<<sname[day][period]<<" ,"<<setw(10)<<"TEACHER:"<<tname[day][period];
	      cout<<"\n";

	  }
	   delay(100);

	 if(day<5)
	   {
	     cout<<"\n view day"<<" "<< day+2 <<" "<<"time table:(y/n)";
	     cin>>ch;

	   if(ch=='y'|| ch=='Y')
	     {   int a=0 ;
	       while(a<4)
		{
		 clrscr();
		 cout<<"Loading";
		 for(b=0;b<3;++b)
		 {
		   cout<<".";
		   delay(75);
		 }
		 a++;

		}
	     }
	     else
	     exit(0);
	   }
	   else if(day==5)
	   cout<<"\n\n Press any key to return to main menu.";

	  }
	}



void table::extract_all_data()
   {
     int day , period ,b,no_of_saved_records;
     char ch,week_day[15];
     int day_num;

      for(day=0; day<6 ;++day)
	{
	   clrscr();
	   cout<<"\n CLASS:"<<clas;
	   delay(50);

	   day_num=day;
	   week_days(day_num,week_day);
	   cout<<"  "<<"("<<week_day<<")";
	   cout<<"\n\n";
      for(period=0; period<8; ++period)
	 {
	 cout<<"(DAY:"<<day+1<<" "<<"PERIOD:"<<period+1<<") "<<" ";
	 delay(50);

	 cout<<"SUBJECT:"<<sname[day][period]<<" ,"<<setw(15)<<"TEACHER:"<<tname[day][period];
	 cout<<"\n";
	 }
	   delay(100);
	 if(day<6)
	   {
	    if(day<6)
	   cout<<"\n want to load more(y/n):";
	   cin>>ch;

	   if(ch=='y'|| ch=='Y')
	     {   int a=0 ;

	       while(a<4)
		{
		 clrscr();
		 cout<<"Loading";
		 for(b=0;b<3;++b)
		 {
		   cout<<".";
		   delay(75);
		 }
		 a++;

		}
	       continue;
	     }
	     else
	     exit(0);
	   }
	   else
	   cout<<"\n\n Press any key to return to main menu.";

	  }
   }


void display_all_records()
   {
     table t;
     ifstream fin;
     int saved_files;

     saved_files= no_of_saved_files();

     if(!saved_files)
     cout<<"\n no record is saved.";

     else
     {
     fin.open("ttable.dat",ios::in | ios::binary);
     while(fin.read((char*)&t,sizeof(t)))
     t.extract_all_data();

     fin.close();
     }

   }



void show_by_class_num()
  {
   int cl;
   ifstream fin;
   table t;
   char found='f';

   cout<<"\n enter class number:";
   cin>>cl;
   fin.open("ttable.dat",ios::in | ios::binary);
   while(fin.read((char*)&t,sizeof(t)))
       {
	 if(t.return_class()==cl)
	  {
	   found='t';

	   break;
	  }
       }
     fin.seekg(-1*sizeof(t),ios::cur);
    if(found=='t')
       {
	 t.extract_data_by_class_num();
	}

	else
      cout<<"\n NO RECORD WITH SUCH CLASS EXISTS.";
      getch();
    fin.close();

   }


void delete_all_records()
   {
    char ch;
    int saved_files;

    saved_files = no_of_saved_files();

    if(!saved_files)
     {
      cout<<"\n no record is saved.";
      delay(500);
      cout<<"\n press any key to continue.";
      getch();
     }

    else
    {
      cout<<"\n you have"<<" "<<saved_files<<" "<<"record(s).";
      cout<<"\n are you sure you want to delete all records(y/n):";
      cin>>ch;
      if(ch=='y' || ch=='Y')
      {
      ifstream fin;
      fin.open("temp.dat",ios::in | ios::binary);
      fin.open("ttable.dat",ios::in | ios::binary);

      remove("ttable.dat");
      rename("temp.dat","ttable.dat") ;
      fin.close();

      cout<<"\n All records deleted.";
      delay(500);
      }
      else
      {
      cout<<"\n Records not deleted.";
      delay(500);
      }
    }


   }


void instructions()
   {
   clrscr();
   cout<<"\n\t\t\t\t INSTRUCTIONS";
   cout<<"\n\t\t______________________________________________";
   cout<<"\n";
   cout<<"\n\t\t 1> Use a single name for a particular";
   cout<<"\n\t\t    teacher, while entering data.";

   cout<<"\n\n\t\t 2>In case two or more teachers are having same";
   cout<<"\n\t\t    name, try to change  the name by abbreviating it";
   cout<<"\n\t\t    and use the same name for refering that particular " ;
   cout<<"\n\t\t    teacher while entering data.";

   cout<<"\n\n\t\t 3>This software treats uppercase and lowercase letters";
   cout<<"\n\t\t      differently,\n\t\t i.e. abc and ABC both are two different words.";

    cout<<"\n\n\t\t 4> Try to minimise spelling mistakes,";
   cout<<"\n\t\t    it can't be detected by the software.";

    cout<<"\n\n\t\t 5> Do not exit without entering";
   cout<<"\n\t\t    complete data(option 1) ,it won't be saved.";

   cout<<"\n\n\t\t  6> You can exit the program anytime while entering the";
   cout<<"\n\t\t      data by pressing Esc command.";

   cout<<"\n\t\t_______________________________________________";
   cout<<setw(15)<<"\n\n\t\t  press any key to go back";
   getch();
   }


void show_no_of_saved_files()
   {
   cout<<"\n  saved file(s):"<<no_of_saved_files();
   ifstream fin;
   table t;
   fin.open("ttable.dat",ios::in | ios::binary);
   cout<<"\n classes:";
   while(fin.read((char*)&t,sizeof(t)))
      {
       cout<<t.return_class();
       cout<<" ";
      }

      fin.close();
      getch();
   }

/*_______________________________________________________________________ */



void main()
   {

   give_choice_again:

  char choice;
  int clas;

    do
     {
     again:
     clrscr();


     cout<<"\n\t\t\t\t TIME TABLE MENU\n";
     cout<<"\n\t\t__________________________________________________";
     delay(75);
     cout<<"\n";

     cout<<setw(15)<<"\n\t\t 1> Create new time table.";

     delay(50);

     cout<<setw(15)<<"\n\t\t 2> Show all saved records.";
     delay(30);

     cout<<setw(15)<<"\n\t\t 3> Show records by class number.";
      delay(20);

     cout<<setw(15)<<"\n\t\t 4> Delete all saved records.";
      delay(15);

      cout<<setw(15)<<"\n\t\t 5> Show number of saved records.";

      cout<<setw(15)<<"\n\t\t 6> Delete record by class number.";
       cout<<setw(15)<<"\n\t\t 7> Instructions.";
      delay(10);
     cout<<setw(15) <<"\n\t\t 8> Exit.";
      delay(150);

      cout<<"\n\n\t\t KINDLY READ THE INSTRUCTIONS FIRST(7).";
      cout<<"\n\t\t__________________________________________________";

      cout<<setw(15)<<"\n\n\n\t\t Enter your choice:";
      cin>>choice;

     if(!isdigit(choice))
       {
       printf("\ninvalid input.");
       printf("\ntry again...");
       delay(1000);
       goto give_choice_again;
       }
      else
	{
	 if(choice=='1')
	    write();

	 else if(choice=='2')
	     {
	     int saved_files;
	     saved_files=no_of_saved_files();
		if(saved_files)
	       display_all_records();
	       else
	       cout<<"\n No record is saved.";
	       cout<<"\n press any key to proceed.";
	       getch();
	      }
	 else if(choice=='8')
	 exit(0);

	 else if(choice=='3')
	  show_by_class_num();

	 else if(choice=='4')
	 delete_all_records();

	 else if(choice=='7')
	 instructions();

	 else if(choice == '5')
	  show_no_of_saved_files();

	  else if(choice =='6')
	  {
	  if(no_of_saved_files())
	  {
	  cout<<"\n enter class number whose record is to be deleted:";
	  cin>>clas;
	  delete_record_by_class_number(clas);
	  }
	   else
	  cout<<"\n no record is saved.";
	   }
	   }
	 }while(1) ;
      }