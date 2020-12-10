#include<fstream>
#include<iostream>
#include<conio.h>
#include<ctype.h>
#include<stdio.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include<cstring>
#include<windows.h>

using namespace std;

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

class item
{

	public:
   	float price;
   	int n;
   	long code;
   	char iname[25];
   	int hbid;
   	char diss[30];
   	char status[15];


   void input()//Read item details
	{
   	getch();
   	
		ofstream fout("item.dat",ios::binary|ios::app);
      gotoxy(3,3);
		cout<<"Item Name: ";
      gotoxy(3,6);
		cout<<"Item Description: ";
      gotoxy(3,9);
      cout<<"Price: ";
      gotoxy(14,3);
		fgets(iname, 25, stdin);
      gotoxy(21,6);
		fgets(diss, 25, stdin);
      gotoxy(10,9);
		cin>>price;
      strcpy(status,"Available");
      hbid=0;
	}
   void output()//display item details
   {
		cout<<"\n\nItem Name: "<<iname;
      cout<<"\nDescription: "<<diss;
      cout<<"\nPrice: "<<price;
      cout<<"\tHighest Bid: "<<hbid;
      cout<<"\nCode: "<<code;

   }

};


class customer
{

    public:
    char pass[10];
    long tlno;
    int n;
    int blcno,stno,bldno;
    char area[15], state[15];
    long code;
    char email[20];

};

struct bid
{
	long amt;
	long code;//Same as sellers
   long code1;  //Same as buyers
	int n;
   int sno;
   long tlno;
};
void disp(bid b)//display bid details
{

   cout<<"\n"<<setw(15)<<b.amt;
	cout<<setw(15)<<b.tlno;
   cout<<setw(10)<<b.code1;
}

void bidd(customer c)//add a bid to bid.dat
{
   item e;
   long code;
   fstream est("item.dat",ios::binary|ios::out|ios::in);
   cout<<"\n\tEnter item code: ";
   cin>>code;
   int g(0);
   while(est.read((char*)&e,sizeof(e)))
   {
   	if(e.code==code)
      {
      	bid b;
         b.code1=c.code;
      	ofstream fout("bid.dat",ios::binary|ios::app);
			cout<<"\n\tEnter amount to bid: ";
   		cin>>b.amt;
         if(e.hbid<b.amt)
         {
         	e.hbid=b.amt;
            est.seekg(-sizeof(e),ios::cur);
            est.write((char*)&e,sizeof(e));
         }
   		b.code=e.code;
   		b.n=e.n;
         b.tlno=c.tlno;
   		fout.write((char*)&b,sizeof(b));
			cout<<"\n\tBid added\n";
         fout.close();
         g++;
         break;
      }
   }
   if(g==0)
   	cout<<"\n\n\tItem not found.";
   est.close();

}



customer ret_obj(int &f) //login page
{
	customer c;
   int i;
	char passe[10];
	long tele;
	ifstream fin("cus.dat",ios::binary);
   cout<<"\n\t\t\t**LOGIN**\n\n";
	cout<<"\n\t\tEnter pass: ";
   for(i=0;i<8;i++)
   {
   	passe[i]=getch();
      cout<<"*";
   }
   passe[i]='\0';
   cout<<"\n\t\tEnter Telephone Number: ";
   cin>>tele;
   if(tele==1478)
   {
      c.tlno=1478;
      f=1;
      fin.close();
      return c;
   }
	else
   	while(fin.read((char*)&c,sizeof(c)))
   	{
   		if((strcmp(c.pass,passe))==0&&c.tlno==tele)
         {
         	f=1;
            fin.close();
            return c;
         }
		}
	if(f==0)
   {
      fin.close();
   	return c;

   }
}

void viewbid(customer c)//view bids made on items 
{
	item e;
   bid b;
   long ce=c.code;


   	ifstream f("item.dat",ios::binary);
		while(f.read((char*)&e,sizeof(e)))
		{

   		if(e.code==ce&&(strcmpi(e.status,"Available")==0))
      	{
        		e.output();
            ifstream fin("bid.dat",ios::binary);
         	cout<<"\n\n"<<setw(15)<<"Amount";
				cout<<setw(15)<<"Telephone No."<<setw(10)<<"Code";
      		while(fin.read((char*)&b,sizeof(b)))
      		{
      			if(e.code==b.code&&e.n==b.n)
               {
               	disp(b);
                  cout<<"\n";
               }
         	}
            fin.close();
            ce++;
      	}
   	}
      f.close();


}

void search(int &o,customer c)//search based on each word entered by user and compare to item name and discription.
{
	char name[15],disr[25];
	ifstream fin("Item.dat",ios::binary);
   item e;
	cout<<"\n\tEnter Name: ";
   fgets(name, 25, stdin);                               //Going to compare every word
   cout<<"\n\tEnter Desciption: ";
   fgets(disr, 25, stdin);
   getch();
   
   while(fin.read((char*)&e,sizeof(e)))
   {
   	if(e.code==c.code)
      {
      	continue;
      }
      else
      {
   	 int p=0;
       if(strcmpi(e.status,"Sold")==0)
       	break;
   	 for(int i=0;i<strlen(e.iname);i++)
   	 {
      	int j=0,k(0),l(0);
         char s[15],a[25];
      	while(!isspace(e.iname[i])&&e.iname[i]!='\0')
      	{
      		s[j]=e.iname[i];
         	j++;
         	i++;
      	}
      	s[j]='\0';
         for(l=0;l<strlen(name);i++)
   		{
      		k=0;
      		while(!isspace(name[l])&&name[l]!='\0')
      		{
      			a[k]=name[l];
         		k++;
         		l++;
      		}
      		a[k]='\0';
      	}
			if(strcmpi(a,s)==0)
         {
         	e.output();
            o++;
         	p++;
            break;

         }
      }

   	 for(int i=0;p==0&&i<strlen(e.diss);i++)
   	 {
      	int j=0,k(0),l(0);
         char s[15],a[25];
      	while(!isspace(e.diss[i])&&e.diss[i]!='\0')
      	{
      		s[j]=e.diss[i];
         	j++;
         	i++;
      	}
      	s[j]='\0';
         for(l=0;l<strlen(disr);i++)
   		{
      		k=0;
      		while(!isspace(disr[l])&&disr[l]!='\0')
      		{
      			a[k]=disr[l];
         		k++;
         		l++;
      		}
      		a[k]='\0';
      	}
			if(strcmpi(a,s)==0)
      	{
         	e.output();
            o++;
            break;
         }
      }
    }
   }
   fin.close();
   getch();
}


int main()//program execution starts here
{
   customer c;
   int o;
   int f;
   Login:
   f=0;
   int ch;
   getch();
   
   cout<<"\n\t\t~~~STANLEY & CO. TRADING PLATFORM~~~\n\n\n";
	cout<<"\n\t\t\t1.Login";
   cout<<"\n\t\t\t2.Create account";
   cout<<"\n\t\t\t0.Exit";
   cout<<"\n\n\t\tEnter your choice: ";
   cin>>ch;
   if(ch==1)
   {
   	c=ret_obj(f);
      if(f==0)
      {	cout<<"\tMatch Not found\n";
         cout<<"\n\tEnter to proceed to login page";
         getch();
         goto Login;
      }

   }
   else if(ch==2)
   {
   	customer d;
      char pass1[10];
      int b,y;
      Details:
      getch();
      
      int g(0);
      gotoxy(8,3);
      cout<<"Password(Alphabets/Numbers,8 characters) :";
      gotoxy(8,6);
      cout<<"Confirm Password :";
      gotoxy(8,9);
      cout<<"Telephone No :";
      gotoxy(8,12);
      cout<<"Email :";
      gotoxy(8,15);
		cout<<"Area: ";
   	gotoxy(35,15);
		cout<<"State: ";
      gotoxy(8,18);
		cout<<"Block number: ";
      gotoxy(35,18);
		cout<<"Street number: ";
      gotoxy(8,21);
		cout<<"Building number: ";

      gotoxy(51,3);
      for(b=0;b<8;b++)
   	{
   		c.pass[b]=getch();
      	cout<<"*";
   	}
      c.pass[b]='\0';
      gotoxy(27,6);
      for(y=0;y<8;y++)
   	{
   		pass1[y]=getch();
      	cout<<"*";
   	}
      pass1[y]='\0';
      if(strcmp(pass1,c.pass)!=0)
      {
      	cout<<"\n\tPasswords Not matching!";
         getch();
         goto Details;
      }
      gotoxy(23,9);
      cin>>c.tlno;
      gotoxy(16,12);
      fgets(c.email, 25, stdin);
      gotoxy(14,15);
		fgets(c.area, 25, stdin);
      gotoxy(42,15);
		fgets(c.state, 25, stdin);
      gotoxy(22,18);
		cin>>c.blcno;
      gotoxy(50,18);
		cin>>c.stno;
      gotoxy(25,21);
		cin>>c.bldno;
      if(c.tlno/10000.0<1.0)
      {
      	cout<<"\n\tInvalid Telephone Number. Enter again.";
         getch();
         goto Details;
      }
      c.code=c.tlno/5000;
      c.n=0;

      fstream	fout("cus.dat",ios::binary|ios::in);
      while(fout.read((char*)&d,sizeof(d)))
      {
      	if(c.tlno==d.tlno)
         {
         	cout<<"\n\tTelephone No. Repeat. Enter again.";
            getch();
            g=1;
            fout.close();
            goto Details;
         }
      }
      fout.close();
      fout.open("cus.dat",ios::binary|ios::out|ios::app);
      if(g!=1)
       	fout.write((char*)&c,sizeof(c));
      fout.close();
   }
   else if(ch==0)
   {
      char cp;
   	cout<<"\n\n\t\tDo you really wish to exit?[Y/N]";
      cin>>cp;
      if(cp=='Y'||cp=='y')
      {
      	getch();
      	exit(0);
      }
      else if(cp=='n'||cp=='N')
      {
      	goto Login;
      }
      else
      {
      	cout<<"\n\tInvalid Answer";
         goto Login;
      }
   }
   else
   {
   	cout<<"\n\n\tInvalid Choice";
      getch();
      goto Login;
   }

   if(c.tlno==1478)
   {
      do{
      	getch();
         
         cout<<"\n\n\tAdministrator Menu\n";
   		cout<<"\n\t\t1.View all items";
      	cout<<"\n\t\t2.View all bids";
      	cout<<"\n\t\t3.View all customers";
      	cout<<"\n\t\t4.Logout";
      	cout<<"\n\n\tEnter choice: ";
      	cin>>ch;

      	if(ch==1)
      	{  
      		item e;
      		ifstream fin("item.dat",ios::binary);
            while(fin.read((char*)&e,sizeof(e)))
            {
         		e.output();
               cout<<"\tStatus: "<<e.status<<"\n\n";
            }
            cout<<"\n\n\tEnter to go back to menu ";
            fin.close();
            getch();
      	}
      	else if(ch==2)
      	{
      		bid b;
         	ifstream fin("bid.dat",ios::binary);
         	cout<<"\n\n"<<setw(15)<<"Amount";
				cout<<setw(15)<<"Telephone No.";
            cout<<setw(10)<<"B Code";
            cout<<setw(10)<<"S Code";
         	while(fin.read((char*)&b,sizeof(b)))
            {
      			disp(b);
               cout<<setw(10)<<b.code<<"\n\n";
            }
            cout<<"\n\n\tEnter to go back to menu ";
            fin.close();
            getch();
      	}
      	else if(ch==3)
      	{
				ifstream fin("cus.dat",ios::binary);
   			customer c;
   			cout<<setw(15)<<"Customer code";
            cout<<setw(20)<<"Telephone No.";
      		cout<<setw(26)<<"Customer email";
            cout<<setw(6)<<"No.\n\n";
				while(fin.read((char*)&c,sizeof(c)))
            {
					cout<<setw(15)<<c.code;
					cout<<setw(20)<<c.tlno;
					cout<<setw(26)<<c.email;
               cout<<setw(6)<<c.n<<"\n";
				}
				fin.close();
            cout<<"\n\n\tEnter to go back to menu ";
            getch();
      	}
         else if(ch==4)
         	{
            	goto Login;
            }
      	else
      		cout<<"Invalid choice";

      }while(ch!=4);
   }
   else
   {
   	Menu:
      do{
      	getch();
         
         cout<<"\n\n\t\t~~~MENU~~~\n\n";
   		cout<<"\n\t\t1.Add item to sell";
      	cout<<"\n\t\t2.Conclude Sale of Item";
      	cout<<"\n\t\t3.Search for item";
         cout<<"\n\t\t4.View bids made";
         cout<<"\n\t\t5.View bought Items";
      	cout<<"\n\t\t6.Logout";

      	cout<<"\n\n\tEnter choice: ";
      	cin>>ch;
      	if(ch==1)
      	{
         	item e;
            customer z;
      		e.input();
            e.code=c.code+c.n;
            ofstream fot("item.dat",ios::binary|ios::app);
            fot.write((char*)&e,sizeof(e));
            cout<<"\n\tItem Added";
				fot.close();
            c.n++;
            fstream cu("cus.dat",ios::binary|ios::in|ios::out);
            while(cu.read((char*)&z,sizeof(z)))
            	if(z.code==c.code)
               	break;
            cu.seekg(-sizeof(z),ios::cur);
            cu.write((char*)&c,sizeof(c));
            cu.close();
            cout<<"\n\n\tEnter to go back to menu ";
            getch();
      	}
      	else if(ch==2)
      	{
      		viewbid(c);
            long cod,bc;
            char y;
            int p(0),z(0);
            Bi:
            cout<<"\n\n\tDo you wish to sell an item?[Y/N] ";
            cin>>y;
            if(y=='Y'||y=='y')
				{
            	cout<<"\nEnter item code: ";
            	cin>>cod;
            	cout<<"\nEnter bid code: ";
            	cin>>bc;
            	item e;
   				bid b;
            	char ans;
               p=0;
					fstream g("item.dat",ios::binary|ios::in|ios::out);
					ifstream gud("bid.dat",ios::binary);
					while(g.read((char*)&e,sizeof(e)))
					{
   					if(e.code==cod&&strcmpi(e.status,"NA")!=0)
      				{
                  	while(gud.read((char*)&b,sizeof(b)))
      					{
      						if(b.code1==bc&&e.n==b.n&&b.amt==e.hbid)
                     	{
                        	p++;
                     		cout<<"\n\nDo you wish to sell the following item: \n";
                        	e.output();
                        	cout<<"\n\nOn the following bid?: \n ";
                           cout<<"\n"<<setw(15)<<"Amount";
									cout<<setw(15)<<"Telephone No."<<setw(10)<<"Code";
                        	disp(b);
                        	cout<<"\n\n\t[Y/N]: ";
                        	cin>>ans;
                        	if(ans=='Y'||ans=='y')
                        	{
                           	cout<<"\n\n\tItem Sold";
                              z=b.code;
                           	e.code=b.code1;
                           	e.n=0;
                           	strcpy(e.status,"Sold");
                              g.seekg(g.tellg() - sizeof(e));
                              g.write((char*)&e,sizeof(e));
                              getch();
                              gud.close();
            						g.close();
                              break;

                        	}

                        	else if(ans=='N'||ans=='n')
                           {
                              gud.close();
                              g.close();
                        		goto Bi;
                           }
                        	else
                        	{
                        		cout<<"Invalid Choice";
                           	gud.close();
                           	g.close();
                           	goto Bi;
                        	}

                      	}
                     }
                  }
               }
            }
            else if(y=='n'||y=='N')
            {
            	goto Menu;
            }
            else
            {
            	cout<<"\tInvalid Answer";
               goto Bi;
            }
            if(p==0)
            {
            	cout<<"\n\tMatch Not Found";
               goto Bi;
            }
            if(z!=0)
            {
            	bid bd;
            	ifstream ta("bid.dat",ios::binary);
               ofstream temp("temp.dat",ios::binary);
               while(ta.read((char*)&bd,sizeof(bd)))
               {
                  if(bd.code!=z)
                  {
                  	temp.write((char*)&bd,sizeof(bd));
                  }
               }
               temp.close();
               ta.close();
               remove("bid.dat");
               rename("temp.dat","bid.dat");
            }
      	}
      	else if(ch==3)
      	{
         	o=0;
      		search(o,c);
            if(o!=0)
            {
            	char y;
            	cout<<"\n\n\tDo you wish to bid?[Y/N] ";
            	cin>>y;
            	if(y=='Y'||y=='y')
					{
            		bidd(c);
               	cout<<"\n\n\tEnter to go back to menu ";
            		getch();
               	goto Menu;
            	}
            	else if(y=='n'||y=='N')
            		continue;
            	else
            	{
            		cout<<"\nInvalid Answer";
               	continue;
            	}
            }
            else
            {
            	cout<<"\n\tNo Items Found ";
               cout<<"\n\n\tEnter to go back to menu ";
            	getch();
            }
      	}
         else if(ch==4)
         {
            item e;
  			   bid b;
            char y;
            int w(0);
				ifstream f("item.dat",ios::binary);
				ifstream fin("bid.dat",ios::binary);
				while(fin.read((char*)&b,sizeof(b)))
				{
   				if(b.code1==c.code)
      			{
               	while(f.read((char*)&e,sizeof(e)))
      				{
      					if(e.code==b.code&&e.n==b.n)
                     {
         					e.output();
                        break;
                     }
         			}
         			cout<<"\n\tYour bid: ";
						cout<<b.amt;
                  w++;

      			}
   			}
   			f.close();
   			fin.close();
            if(w==0)
            {
            	cout<<"\n\n\tNo Bids Found";
               getch();
               continue;
            }
            cout<<"\n\nDo you wish to bid again?[Y/N] ";
            cin>>y;
            if(y=='Y'||y=='y')
				{
            	bidd(c);
               cout<<"\n\n\tEnter to go back to menu ";
            	getch();
            }
            else if(y=='n'||y=='N')
            	continue;
            else
            {
            	cout<<"\n\tInvalid Answer";
               getch();
               continue;
            }

         }
         else if(ch==5)
         {
         	ifstream d("item.dat",ios::binary);
            item e;
            int q(0);
            while(d.read((char*)&e,sizeof(e)))
            {
            	if(c.code==e.code&&(strcmpi(e.status,"Sold")==0))
               {
               	e.output();
                  q++;
               }
            }
            if(q==0)
            	cout<<"\n\nNo items bought.";
            d.close();
            cout<<"\n\n\tEnter to go back to menu ";
            getch();

         }


         else if(ch==6)
         {
         	goto Login;
         }
         else
         	cout<<"Invalid Choice";
      }while(ch!=1478);
   }
getch();
return 0;

}

























