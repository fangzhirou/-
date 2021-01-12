#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void creatDB();//建立数据库



private slots:


    void on_cancel_clicked();

    void on_submit_clicked();

    void on_next_clicked();
signals:
    void nextpage();



private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

