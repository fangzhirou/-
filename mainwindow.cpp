#include "mainwindow.h"
#include "ui_mainwindow1.h"
#include "dialog.h"
#include "ui_dialog.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QtDebug>
#include <QSqlQuery>
#include <QEvent>
#include<QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addbutton_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString address = ui->lineEdit_address->text();
    QString telephone = ui->lineEdit_telephone->text();
    int number = ui->lineEdit_number->text().toInt();
    QString major = ui->lineEdit_major->text();
    if(name == NULL || number == 0 || ui->lineEdit_address == NULL||ui->lineEdit_telephone==NULL||ui->lineEdit_major==NULL) //插入信息的时候需要输入完整的信息
    {
        ui->textEdit->setText("请输入完整的信息");
    }
    else
    {
        QString str = QString("insert into student(number, name, major,telephone,address) values('%1', '%2', '%3','%4','%5')").arg(number).arg(name).arg(major).arg(telephone).arg(address);
        QSqlQuery query;
        query.exec(str);
        ui->lineEdit_number->clear();
        ui->lineEdit_name->clear();
        ui->lineEdit_major->clear();
        ui->lineEdit_telephone->clear();
        ui->lineEdit_address->clear();
        ui->textEdit->setText("插入成功");

    }
    QString str = QString("insert into student(number, name, major,telephone,address) values('%1', '%2', '%3','%4','%5')").arg(number).arg(name).arg(major).arg(telephone).arg(address);
    QSqlQuery query;
    query.exec(str);
    ui->textEdit->setText("插入成功");
}

void MainWindow::on_changebutton_clicked()
{
       QString updatename = ui->lineEdit_name->text();
       QString address = ui->lineEdit_address->text();
       QString telephone = ui->lineEdit_telephone->text();
       int number = ui->lineEdit_number->text().toInt();
       QString major = ui->lineEdit_major->text();
       if(updatename==NULL||number==0||ui->lineEdit_major->text()==NULL||ui->lineEdit_telephone->text()==NULL|| ui->lineEdit_address->text()==NULL)
       {
           ui->textEdit->setText("请输入需要修改的人的全部信息");
       }
       else
           {
               QString temp = QString("select * from student where name = '%1'").arg(updatename);

               QSqlQuery query;
               query.exec(temp);// 查询信息
               QString a;
               while (query.next())
               {
                   a = query.value(1).toString();
               }

               if(a == NULL)
               {
                   QString x;
                   x=QString("defeat,can't find this man").arg(updatename);
                   ui->textEdit->setText(x);
                   ui->lineEdit_number->clear();
                   ui->lineEdit_name->clear();
                   ui->lineEdit_major->clear();
                   ui->lineEdit_telephone->clear();
                   ui->lineEdit_address->clear();
               }

               else
               {
                   QString temp;
                   QSqlQuery query;
                   temp = QString("update student set number='%2',major='%3',address='%4',telephone='%5' where name='%1';").arg(number).arg(major).arg(telephone).arg(address).arg(updatename);
                   query.exec(temp);//执行修改信息的操作

                   ui->textEdit->setText("修改成功");
               }

          }
}

void MainWindow::on_deletebutton_clicked()
{
    QString name = ui->lineEdit_name->text();//从行编辑框中获取需要删除的人名
       if(name ==  NULL)
       {
           ui->textEdit->setText("请输入需要删除的人的名字"); //删除的时候需要输入姓名
       }

       else
       {
           QSqlQuery query;
           QString temp = QString("select * from student where name = '%1'").arg(name);
           query.exec(temp);
           QString deletename;
           while(query.next())
           {
               deletename = query.value(1).toString();
           }
           if(deletename==NULL)
           {
               QString a = QString("没有叫%1的人，删除失败").arg(name);
               ui->textEdit->setText(a);
               ui->lineEdit_number->clear();
               ui->lineEdit_name->clear();
               ui->lineEdit_major->clear();
               ui->lineEdit_telephone->clear();
               ui->lineEdit_address->clear();

           }
           else
           {
               QString str =  QString("delete from student where name = '%1'").arg(name);
               query.exec(str);//删除信息
                       ui->lineEdit_number->clear();
                       ui->lineEdit_name->clear();
                       ui->lineEdit_major->clear();
                       ui->lineEdit_telephone->clear();
                       ui->lineEdit_address->clear();
                       ui->textEdit->setText("删除成功");
            }
       }
}

void MainWindow::on_checkbutton_clicked()
{
    QString searchname = ui->lineEdit_name->text();

            if(searchname == NULL)
            {
                ui->textEdit->setText("请输入需要查询的人名");
            }
            else
            {
                QString str = QString("select *from student where name = '%1'").arg(searchname);
                QSqlQuery query;
                query.exec(str);
                int number;
                QString name;
                QString major;
                QString telephone;
                QString address;
                while (query.next())
                {
                    number = query.value(0).toInt();
                    name = query.value(1).toString();
                    major = query.value(2).toString();
                    telephone = query.value(3).toString();
                    address = query.value(4).toString();

                }
                if(name==NULL)
                {
                    QString a = QString("没有叫%1的人，请重新输入人名").arg(searchname);
                    ui->textEdit->setText(a);
                    ui->lineEdit_number->clear();
                    ui->lineEdit_name->clear();
                    ui->lineEdit_major->clear();
                    ui->lineEdit_telephone->clear();
                    ui->lineEdit_address->clear();
                }
                else
                {
                    ui->lineEdit_name->setText(name);
                    ui->lineEdit_number->setText(QString().setNum(number));
                    ui->lineEdit_major->setText(major);
                    ui->lineEdit_telephone->setText(telephone);
                    ui->lineEdit_address->setText(address);
                    ui->textEdit->setText("查询成功");

                }
            }
}





void MainWindow::on_checkallbytton_clicked()
{
    QString name[100];//用来存储从数据库中找出来的信息
            int number[100];
            QString major[100];
            QString telephone[100];
            QString address[100];
            int i = 0;
            QSqlQuery query;
            query.exec("select * from student");//查询所有的信息
            while(query.next())
            {
                number[i] = query.value(0).toInt();
                name[i] = query.value(1).toString();
                major[i] = query.value(2).toString();
                telephone[i] = query.value(3).toString();
                address[i] = query.value(4).toString();

                i++;
            }
            ui->textEdit->clear();
            int j = 0;
            for(j = 0; j < i; j++)//将这些信息都显示在下方的文本编辑框中
            {
                QString str = QString("学号：%1   姓名：%2  系别：%3  电话：%4  邮箱：%5").arg(number[j]).arg(name[j]).arg(major[j]).arg(telephone[j]).arg(address[j]);
                ui->textEdit->append(str);
            }
}
void MainWindow::shownextpage()
{
    this->show();
}

