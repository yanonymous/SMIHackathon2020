#include <stdio.h>
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
    printf("ENTER THE QUERY YOU WANT TO PERFORM\n");
    printf("1.ADD CASE RECORD\n2.EDIT CASE RECORD\n3.VIEW RECORDS\n4.VIEW ALL RECORDS\n5.DELETE RECORD\n6.END\n");
    scanf("%d",a);
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
        default: printf("WRONGGGGGG CHOICEEEEEEEEEEEE!!!!!!!!!");
    }
    return 0;

}
void editrec()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect (conn, "192.168.1.104", "rootv1", "rootv1", "law", 0, NULL, 0 );
    string dummy;
    stringstream ss;
    if(conn)
    {
        int qstate=0, srno, charge,s;
        string invno,case1,lawyer,judge;
        char minutes[1000],status[1000],answer;
        printf("ENTER INVOICE OF THE CASE YOU WANT TO EDIT:\n");
        gets(invno);
        do{
            printf("WHAT DO YOU WANT TO EDIT?\n");
            printf("1.CASE TYPE\n2.LAWYER\n3.JUDGE\n4.MINUTES\n5.STATUS\n6.CHARGE\n");
            scanf("%d",s);
            switch(s)
            {
            case 1:
                printf("CASE TYPE:");
                gets(case1);
                ss("UPDATE error404v1 SET case_type=");
                ss(case1);
                ss("WHERE invoice_no=");
                ss(invno);
                break;
            case 2:
                printf("LAWYER:");
                gets(lawyer);
                ss("UPDATE error404v1 SET lawyer=");
                ss(lawyer);
                ss("WHERE invoice_no=");
                ss(invno);
                break;
            case 3:
                printf("JUDGE:");
                gets(judge);
                ss("UPDATE error404v1 SET judge=");
                ss(judge);
                ss("WHERE invoice_no=");
                ss(invno);
                break;
            case 4:
                printf("Minutes:");
                fflush(stdin);
                gets(minutes);
                ss("UPDATE error404v1 SET minutes=");
                ss(minutes);
                ss("WHERE invoice_no=");
                ss(invno);
                break;
            case 5:
                printf("Status:");
                gets(status);
                 ss("UPDATE error404v1 SET status=");
                ss(status);
                ss("WHERE invoice_no=");
                ss(invno);

                break;
            case 6:
                printf("Charge:");
                scanf("%d",charge);
                 ss("UPDATE error404v1 SET charge=");
                ss(charge);
                ss("WHERE invoice_no=");
                ss(invno);

                break;
            default:printf("Wrong choice!\n");
            }
            printf("DO you want to continue editing details?");
            scanf("%c",answer);

        }while(answer=='Y'||answer=='y');
        string query=ss.str();
        const char* q=query.c_str();
        qstate= mysql_query(conn,q);
        if(qstate==0)
        {
            printf("RECORD UPDATED!\n");
            printf("Press B to go back");
            scanf("%s",dummy);
        }
        else if(qstate!=0){
            printf("UPDATE error");
            puts(mysql_error(conn));
            printf("press B to go back\n");
            scanf("%s",dummy);

        }
    }
}

void addrec()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect (conn, "192.168.1.104", "rootv1", "rootv1", "law", 0, NULL, 0 );
    string dummy;
    if(conn)
    {
        int qstate=0, srno, charge;
        string invno;
        char minutes[1000],status[1000],lawyer[50],judge[50],case1[1000];
        printf("SR NO.:");
        scanf("%d",srno);
        printf("INVOICE NO.:");
        scanf("%s",invno);
        printf("CASE TYPE:");
        fflush(stdin);
        gets(case1);
        printf("LAWYER'S NAME:");
        fflush(stdin);
        gets(lawyer);
        printf("JUDGE'S NAME:");
        fflush(stdin);
        gets(judge);
        printf("MINUTES:");
        fflush(stdin);
        gets(minutes);
        printf("STATUS:");
        fflush(stdin);
        gets(status);
        printf("CHARGE:");
        scanf("%d"charge);
        stringstream ss;
        ss(INSERT INTO error404v1(sr_no, invoice_no, case_type, lawyer, judge, minutes, status, charge) VALUES(srno,invno,case1,lawyer,judge,minutes,status,charge));
        string query=ss.str();
        const char* q=query.c_str();
        qstate= mysql_query(conn,q);
        if(qstate==0)
        {
            printf("Record Inserted\n");
            printf("Press B to go back");
            scanf("%s",dummy);
        }
        else if(qstate!=0){
            printf("insert error");
            puts(mysql_error(conn));
            printf("press B to go back");
            scanf("%s",dummy);
        }
        else{
            printf("Connection error\n");
            printf("press B to go back");
            scanf("%s",dummy);
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
    conn = mysql_real_connect (conn, "192.168.1.104", "rootv1", "rootv1", "law", 0, NULL, 0 );
    stringstream ss;
        if(conn)
        {
        int qstate=0;
        string invno;
        printf("ENTER INVOICE OF THE CASE YOU WANT TO WANT RECORD OF:\n");
        scanf("%s",invno);
        ss("SELECT * FROM error404v1 WHERE invoice_no=",invno);
        string query=ss.str();
        const char* q=query.c_str();
        qstate= mysql_query(conn,q);
        if(qstate==0){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){

            printf("SR_NO:",row[0]);
            printf("\nINVOICE_NO:",row[1]);
            printf("\nCASE_TYPE:",row[2]);
            printf("\nLAWYER:",row[3]);
            printf("\nJUDGE:",row[4]);
            printf("\nMINUTES:",row[5]);
            printf("\nSTATUS:",row[6]);
            printf("\nCHARGE:",row[7]);

            }
        }
        else{
            printf("error");
        }
    }
}
