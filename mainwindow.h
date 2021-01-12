#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_addbutton_clicked();

    void on_changebutton_clicked();

    void on_deletebutton_clicked();

    void on_checkbutton_clicked();

    void on_checkallbytton_clicked();
    void shownextpage();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
