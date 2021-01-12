#include "dialog.h"
#include "ui_dialog.h"
#include"mainwindow.h"
#include"ui_mainwindow1.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QtDebug>
#include <QSqlQuery>
#include <QEvent>
#include<QDialog>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QStringList drivers = QSqlDatabase::drivers();
    ui->dbcomboBox->addItems(drivers);
    ui->label_2->setText(tr("状态：准备连接数据库"));
}
Dialog::~Dialog()
{
    delete ui;
}
void Dialog::on_submit_clicked()
{
    if(ui->dbcomboBox->currentText().isEmpty())
    {
        ui->label_2->setText(tr("请选择一个数据库驱动"));
        ui->dbcomboBox->setFocus();
    }
    else if(ui->dbcomboBox->currentText()=="QSQLITE")
    {
        creatDB();

    }
    else
        QMessageBox::information(this,tr("数据库"),tr("对不起，目前只有’QSQLITE'驱动可用！"));
}
void Dialog::on_cancel_clicked()
{
    hide();
}
void Dialog::creatDB()
{
    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::applicationDirPath()+"/studentsss");
    db.open();
    if(!db.open())
    {
        err = db.lastError();
        qDebug()<<err.text();
    }
    else
    ui->label_2->setText(tr("创建sqlite数据库成功"));

    QSqlQuery query;
    bool success=query.exec("create table student (number int primary key,name varchar(40),major varchar(40),address varchar(40),telephone varchar(40))");
    if (success)
        qDebug()<<QObject::tr("数据库表创建成功");
    query.exec(QObject::tr("insert into student values(1,'刘芸涵', '物联网',12345,11111)"));
    query.exec(QObject::tr("insert into student values(2,'方芷柔', '计交',123456,222222)"));
    query.exec(QObject::tr("insert into student values(3,'任文瑞', '计卓',1234567,3333333)"));
    query.exec(QObject::tr("insert into student values(4,'刘洋', '软件',12345678,4444444)"));
    query.exec(QObject::tr("insert into student values(5,'李晓琳', '计交',123456789,5555555)"));
}
void Dialog::on_next_clicked()
{
    this ->hide();
    emit nextpage();
}
