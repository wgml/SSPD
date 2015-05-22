#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dummy.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    Ui::MainWindow *ui;

    QTimer * timer;

    Dummy * master;

    void init(); //tworzy obiekt symulacji
    void updateUI(); //aktualizuje wykresy i boxy


private slots:

    void on_simButton_clicked();
    void on_resetButton_clicked();

    void tick(); //symuluje jedna iteracje

    void updateOrderDetais();
};

#endif // MAINWINDOW_H
