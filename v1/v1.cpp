#include <iostream>
#include<winsock.h>
#include<mysql.h>
#include<windows.h>
#include<sstream>
#include<stdio.h>
#include<string.h>
#include<cstdio>


using namespace std;


int main()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect (conn, "10.11.21.201", "rootv1", "rootv1", "law", 0, NULL, 0 );
    string dummy;
    if(conn)
    {
        int qstate=0, srno, charge;
        string invno,case1,lawyer,judge;
        char minutes[1000],status[1000];
        cout<<"SR NO.:";
        cin>>srno;
        cout<<"INVOICE NO.:;
        cin>>invno;
        cout<<"CASE TYPE:";
        cin>>case1;
        cout<<"LAWYER'S NAME:";
        cin>>lawyer;
        cout<<"JUDGE'S NAME:";
        cin>>judge;
        cout<<"MINUTES:";
        fflush(stdin);
        gets(minutes);
        cout<<"STATUS:";
        gets(status);
        cout<<"CHARGE:";
        cin>>charge;
        stringstream ss;
        ss<<"INSERT INTO error404v1(sr_no, invoice_no, case_type, lawyer, judge, minutes, status, charge) VALUES('"<<srno<<"','"<<invno<<"','"<<case1<<"','"<<lawyer<<"','"<<judge<<"','"<<minutes<<"','"<<status<<"','"<<charge<<"')";
        string query=ss.str();
        const char* q=query.c_str();
        qstate= mysql_query(conn,q);
        if(qstate==0)
        {
            cout<<"Record Inserted"<<endl;
            cout<<"Press B to go back";
            cin>>dummy;
        }
        else if(qstate!=0){
            cout<<"insert error"<< mysql_error(conn)<<endl;
            cout<<"press B to go back";
            cin>>dummy;
        }
        else{
            cout<<"Connection error"<<endl;
            cout<<"press B to go back";
            cin>>dummy;
        }
    }
   return 0;

}


