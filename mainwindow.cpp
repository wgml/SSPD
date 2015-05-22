#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <iostream>

using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    master = new Dummy();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(tick()));

    connect(this->ui->ordersComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateOrderDetais()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_simButton_clicked() {
    cout << "a" << endl;

    if(this->timer->isActive()) {
        //stop
        this->timer->stop();

        this->ui->simButton->setText("Symuluj");

//        this->ui->numWokers->setEnabled(true);
//        this->ui->numMachines1->setEnabled(true);
//        this->ui->numMachines2->setEnabled(true);
//        this->ui->numMachines3->setEnabled(true);
//        this->ui->tasksFreq->setEnabled(true);
//        this->ui->simStepSpin->setEnabled(true);
        this->ui->resetButton->setEnabled(true);

    }
    else {
        //start
        this->ui->simButton->setText("Przerwij");

        this->ui->numWokers->setEnabled(false);
        this->ui->numMachines1->setEnabled(false);
        this->ui->numMachines2->setEnabled(false);
        this->ui->numMachines3->setEnabled(false);
        this->ui->tasksFreq->setEnabled(false);
        this->ui->simStepSpin->setEnabled(false);
        this->ui->resetButton->setEnabled(false);


        this->timer->start(100);
    }
}

void MainWindow::on_resetButton_clicked() {
    this->ui->simButton->setText("Symuluj");

    this->ui->numWokers->setEnabled(true);
    this->ui->numMachines1->setEnabled(true);
    this->ui->numMachines2->setEnabled(true);
    this->ui->numMachines3->setEnabled(true);
    this->ui->tasksFreq->setEnabled(true);
    this->ui->simStepSpin->setEnabled(true);
    this->ui->resetButton->setEnabled(true);

    if(this->master){
        delete this->master;
        this->master = NULL;
    }

    this->ui->ordersComboBox->clear();

    this->ui->employeesFree->setText(QString::null);
    this->ui->employeeBusy->setText(QString::null);

    this->ui->machines1Free->setText(QString::null);
    this->ui->machines1Busy->setText(QString::null);
    this->ui->machines2Free->setText(QString::null);
    this->ui->machines2Busy->setText(QString::null);
    this->ui->machines3Free->setText(QString::null);
    this->ui->machines3Busy->setText(QString::null);

    this->ui->chairsPhase1->setText(QString::null);
    this->ui->chairsFinished->setText(QString::null);

    this->ui->wardrobesPhase1->setText(QString::null);
    this->ui->wardrobesPhase2->setText(QString::null);
    this->ui->wardrobesFinished->setText(QString::null);

    this->ui->currentTime->setText(QString::null);
    this->ui->currentOrder->setText(QString::null);
    this->ui->numOrders->setText(QString::null);

    this->ui->chairsFinishedOrder->setText(QString::null);
    this->ui->wardrobesFinishedOrder->setText(QString::null);
    this->ui->chairsOrdered->setText(QString::null);
    this->ui->wardrobesOrdered->setText(QString::null);
    this->ui->orderTime->setText(QString::null);


}

void MainWindow::tick() {
    cout << "c" << endl;

    if(!this->master) {
        this->init();
    }

    this->master->sim(this->ui->simStepSpin->value());
    this->updateUI();
}

void MainWindow::init() {
    if(this->master){
        delete this->master;
        this->master = NULL;
    }
    this->master = new Dummy;
    this->master->set(lPracownikow, this->ui->numWokers->value());
    this->master->set(lMaszyn1, this->ui->numMachines1->value());
    this->master->set(lMaszyn2, this->ui->numMachines2->value());
    this->master->set(lMaszyn3, this->ui->numMachines3->value());
    this->master->set(czstZamowien, this->ui->tasksFreq->value());

}

void MainWindow::updateUI() {
    this->ui->employeesFree->setText(QString::number(this->master->get(LWP)));
    this->ui->employeeBusy->setText(QString::number(this->master->get(lPracownikow) - this->master->get(LWP)));

    this->ui->machines1Free->setText(QString::number(this->master->get(LWM1)));
    this->ui->machines1Busy->setText(QString::number(this->master->get(lMaszyn1) - this->master->get(LWM1)));
    this->ui->machines2Free->setText(QString::number(this->master->get(LWM2)));
    this->ui->machines2Busy->setText(QString::number(this->master->get(lMaszyn2) - this->master->get(LWM2)));
    this->ui->machines3Free->setText(QString::number(this->master->get(LWM3)));
    this->ui->machines3Busy->setText(QString::number(this->master->get(lMaszyn3) - this->master->get(LWM3)));

    this->ui->chairsPhase1->setText(QString::number(this->master->get(PrK)));
    this->ui->chairsFinished->setText(QString::number(this->master->get(LKM)));

    this->ui->wardrobesPhase1->setText(QString::number(this->master->get(PrSz1)));
    this->ui->wardrobesPhase2->setText(QString::number(this->master->get(PrSz2)));
    this->ui->wardrobesFinished->setText(QString::number(this->master->get(LSzM)));

    this->ui->currentTime->setText(QString::number(this->master->get(aktualnyCzas)));
    this->ui->currentOrder->setText(QString::number(this->master->get(i)));
    this->ui->numOrders->setText(QString::number(this->master->get(j)));

    for(int n = this->ui->ordersComboBox->count(); n < this->master->get(j); n++) {
        this->ui->ordersComboBox->addItem(QString::number(n) + QString("., w kolejce."));
    }
    //aktualizuj tekst dla zamowien
    for(int n = this->ui->ordersComboBox->currentIndex(); n < this->master->get(i); n++) {
        this->ui->ordersComboBox->setItemText(n, QString::number(n) + QString("., zakończone."));
    }
    this->ui->ordersComboBox->setItemText(this->master->get(i), QString::number(this->master->get(j)) + QString("., w trakcie."));

    this->updateOrderDetais();
}

void MainWindow::updateOrderDetais() {
    int time, chairs, wardrobes, id;
    id = this->ui->ordersComboBox->currentIndex();
    chairs = this->master->getOrderChairs(id);
    wardrobes = this->master->getOrderWardrobes(id);
    time = this->master->getOrderTime(id);

    if(id < this->master->get(i)) {
        this->ui->chairsFinishedOrder->setText(QString::number(chairs));
        this->ui->wardrobesFinishedOrder->setText(QString::number(wardrobes));
    }
    else if(id == this->master->get(i)) {
        this->ui->chairsFinishedOrder->setText(QString::number(this->master->get(LKM)));
        this->ui->wardrobesFinishedOrder->setText(QString::number(this->master->get(LSzM)));
    }
    else {
        this->ui->chairsFinishedOrder->setText(QString::number(0));
        this->ui->wardrobesFinishedOrder->setText(QString::number(0));
    }
    this->ui->chairsOrdered->setText(QString::number(chairs));
    this->ui->wardrobesOrdered->setText(QString::number(wardrobes));
    this->ui->orderTime->setText(QString::number(time));
}
