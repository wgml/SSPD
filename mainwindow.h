#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "klasy/koordynator.h"
#include "qcustomplot/qcustomplot.h"

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

    Koordynator * master;

    QCustomPlot * plotWorkers, *plotStorage, *plotMachines, *plotOrders;

    QVector<double> dataWorkers, dataStorage1, dataStorage2, dataMachines1,dataMachines2,dataMachines3, dataOrders1, dataOrders2, dataTime;
    void init(); //tworzy obiekt symulacji
    void updateUI(); //aktualizuje wykresy i boxy

    void updatePlots(); //aktualizuje widoczne ploty

private slots:

    void on_simButton_clicked();
    void on_resetButton_clicked();

    void tick(); //symuluje jedna iteracje

    void updateOrderDetais();

    void on_plotWorkersButton_clicked();
    void on_plotStorageButton_clicked();
    void on_plotMachinesButton_clicked();
    void on_plotOrdersButton_clicked();
};

#endif // MAINWINDOW_H
