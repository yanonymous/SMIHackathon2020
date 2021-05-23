#include <iostream>
#include<winsock.h>
#include<mysql.h>
#include<windows.h>
#include<sstream>
#include<stdio.h>
#include<string.h>
#include<cstdio>

using namespace std;

void addrec();
void editrec();
void viewrec();
void delrec();
void viewallrec();

int main()
{
    int a;
    cout<<"ENTER THE QUERY YOU WANT TO PERFORM"<<endl;
    cout<<"1.ADD CASE RECORD"<<endl<<"2.EDIT CASE RECORD"<<endl<<"3.VIEW RECORDS"<<endl<<"4.VIEW ALL RECORDS"<<endl<<"5.DELETE RECORD"<<endl<<"6.END"<<endl;
    cin>>a;
    switch(a)
    {
        case 1: addrec();
                break;
        case 2: editrec();
                break;
        case 3: viewrec();
                break;
        case 4: viewallrec();
                break;
        case 5: delrec();
                break;
        case 6: exit(0);
                break;
        default: cout<<"WRONGGGGGG CHOICEEEEEEEEEEEE!!!!!!!!!";
    }
    return 0;

}
void editrec()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect (conn, "10.11.21.201", "rootv1", "rootv1", "law", 0, NULL, 0 );
    string dummy;
    stringstream ss;
    if(conn)
    {
        int qstate=0, srno, charge,s;
        string invno,case1,lawyer,judge;
        char minutes[1000],status[1000],answer;
        cout<<"ENTER INVOICE OF THE CASE YOU WANT TO EDIT:"<<endl;
        cin>>invno;
        do{
            cout<<"WHAT DO YOU WANT TO EDIT?"<<endl;
            cout<<"1.CASE TYPE"<<endl<<"2.LAWYER"<<endl<<"3.JUDGE"<<endl<<"4.MINUTES"<<endl<<"5.STATUS"<<endl<<"6.CHARGE"<<endl;
            cin>>s;
            switch(s)
            {
            case 1:
                cout<<"CASE TYPE:";
                cin>>case1;
                ss<<"UPDATE error404v1 SET case_type='"<<case1<<"'WHERE invoice_no='"<<invno<<"'";
                break;
            case 2:
                cout<<"LAWYER:";
                cin>>lawyer;
                ss<<"UPDATE error404v1 SET lawyer='"<<lawyer<<"'WHERE invoice_no='"<<invno<<"'";
                break;
            case 3:
                cout<<"JUDGE:";
                cin>>judge;
                ss<<"UPDATE error404v1 SET judge='"<<judge<<"'WHERE invoice_no='"<<invno<<"'";

                break;
            case 4:
                cout<<"Minutes:";
                fflush(stdin);
                gets(minutes);
                ss<<"UPDATE error404v1 SET minutes='"<<minutes<<"'WHERE invoice_no='"<<invno<<"'";
                break;
            case 5:
                cout<<"Status:";
                cin>>status;
                ss<<"UPDATE error404v1 SET status='"<<status<<"'WHERE invoice_no='"<<invno<<"'";
                break;
            case 6:
                cout<<"Charge:";
                cin>>charge;
                ss<<"UPDATE error404v1 SET charge='"<<charge<<"'WHERE invoice_no='"<<invno<<"'";
                break;
            default:cout<<"Wrong choice!"<<endl;
            }
            cout<<"DO you want to continue editing details?";
            cin>>answer;

        }while(answer=='Y'||answer=='y');
        string query=ss.str();
        const char* q=query.c_str();
        qstate= mysql_query(conn,q);
        if(qstate==0)
        {
            cout<<"RECORD UPDATED!"<<endl;
            cout<<"Press B to go back";
            cin>>dummy;
        }
        else if(qstate!=0){
            cout<<"UPDATE error"<< mysql_error(conn)<<endl;
            cout<<"press B to go back";
            cin>>dummy;

        }
    }
}

void addrec()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect (conn, "10.11.21.201", "rootv1", "rootv1", "law", 0, NULL, 0 );
    string dummy;
    if(conn)
    {
        int qstate=0, srno, charge;
        string invno,case1;
        char minutes[1000],status[1000],lawyer[50],judge[50];
        cout<<"SR NO.:";
        cin>>srno;
        cout<<"INVOICE NO.:";
        cin>>invno;
        cout<<"CASE TYPE:";
        cin>>case1;
        cout<<"LAWYER'S NAME:";
        fflush(stdin);
        gets(lawyer);
        cout<<"JUDGE'S NAME:";
        fflush(stdin);
        gets(judge);
        cout<<"MINUTES:";
        fflush(stdin);
        gets(minutes);
        cout<<"STATUS:";
        fflush(stdin);
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
}
void viewrec()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    string invno;
    conn = mysql_init(0);
    conn = mysql_real_connect (conn, "10.11.21.201", "rootv1", "rootv1", "law", 0, NULL, 0 );
    stringstream ss;
        if(conn)
        {
        int qstate=0;
        string invno;
        cout<<"ENTER INVOICE OF THE CASE YOU WANT TO WANT RECORD OF:"<<endl;
        cin>>invno;
        ss<<"SELECT * FROM error404v1 WHERE invoice_no='"<<invno<<"'";
        string query=ss.str();
        const char* q=query.c_str();
        qstate= mysql_query(conn,q);
        if(qstate==0){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
            cout << row[0] <<"\t | \t" << row[1] <<"\t | \t" << row[2] <<"\t | \t" << row[3] <<"\t | \t" << row[4] <<"\t | \t" << row[5] <<"\t | \t" << row[6] <<"\t | \t" << row[7] << endl << endl;
            }
        }
        else{
            cout<<"error";
        }
    }
}
void delrec()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect (conn, "10.11.21.201", "rootv1", "rootv1", "law", 0, NULL, 0 );
    string dummy;
    stringstream ss;
    if(conn)
    {
        int qstate=0;
        string invno;
        cout<<"ENTER INVOICE OF THE CASE YOU WANT TO DELETE:"<<endl;
        cin>>invno;
        ss<<"DELETE FROM error404v1 WHERE invoice_no='"<<invno<<"'";
        string query=ss.str();
        const char* q=query.c_str();
        qstate= mysql_query(conn,q);
        if(qstate==0)
        {
            cout<<"RECORD Deleted!"<<endl;
            cout<<"Press B to go back"<<endl;
            cin>>dummy;
        }
        else if(qstate!=0){
            cout<<"Delete error"<< mysql_error(conn)<<endl;
            cout<<"press B to go back"<<endl;
            cin>>dummy;

        }
    }
}
void viewallrec()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    string invno;
    conn = mysql_init(0);
    conn = mysql_real_connect (conn, "10.11.21.201", "rootv1", "rootv1", "law", 0, NULL, 0 );

    if(conn)
    {
        int qstate = mysql_query(conn, "SELECT * FROM error404v1");

        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
                cout << row[0] <<"\t | \t" << row[1] <<"\t | \t" << row[2] <<"\t | \t" << row[3] <<"\t | \t" << row[4] <<"\t | \t" << row[5] <<"\t | \t" << row[6] <<"\t | \t" << row[7] << endl << endl;
                }
        }
    }
}







