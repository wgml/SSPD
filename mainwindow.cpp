#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    master = NULL;
    plotMachines = plotOrders = plotStorage = plotWorkers = NULL;

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

    if(this->timer->isActive()) {
        //stop
        this->timer->stop();

        this->ui->simButton->setText("Symuluj");

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


    if(this->plotMachines) {
        delete this->plotMachines;
        this->plotMachines = NULL;
    }
    if(this->plotWorkers) {
        delete this->plotWorkers;
        this->plotWorkers = NULL;
    }
    if(this->plotOrders) {
        delete this->plotOrders;
        this->plotOrders = NULL;
    }
    if(this->plotStorage) {
        delete this->plotStorage;
        this->plotStorage = NULL;
    }

    this->dataMachines.clear();
    this->dataOrders.clear();
    this->dataStorage.clear();
    this->dataWorkers.clear();
}

void MainWindow::tick() {

    if(!this->master) {
        this->init();
    }

    this->master->sim(this->ui->simStepSpin->value());
    this->updateUI();

    this->updatePlots();
}
void MainWindow::updatePlots() {
    this->dataWorkers.push_back(this->master->get(Parameter::lPracownikow) - this->master->get(Parameter::LWP));

    if(this->plotWorkers != NULL && this->plotWorkers->isVisible()) {
        this->plotWorkers->replot();
    }
}

void MainWindow::init() {
    if(this->master){
        delete this->master;
        this->master = NULL;
    }
    unsigned lp, lm1, lm2, lm3, dlSym;
    lp = this->ui->numWokers->value();
    lm1 = this->ui->numMachines1->value();
    lm2 = this->ui->numMachines1->value();
    lm3 = this->ui->numMachines1->value();
    dlSym = 1000;

    this->master = new Koordynator(lp, lm1, lm2, lm3, dlSym);

}

void MainWindow::updateUI() {
    this->ui->employeesFree->setText(QString::number(this->master->get(Parameter::LWP)));
    this->ui->employeeBusy->setText(QString::number(this->master->get(Parameter::lPracownikow) - this->master->get(Parameter::LWP)));

    this->ui->machines1Free->setText(QString::number(this->master->get(Parameter::LWM1)));
    this->ui->machines1Busy->setText(QString::number(this->master->get(Parameter::lMaszyn1) - this->master->get(Parameter::LWM1)));
    this->ui->machines2Free->setText(QString::number(this->master->get(Parameter::LWM2)));
    this->ui->machines2Busy->setText(QString::number(this->master->get(Parameter::lMaszyn2) - this->master->get(Parameter::LWM2)));
    this->ui->machines3Free->setText(QString::number(this->master->get(Parameter::LWM3)));
    this->ui->machines3Busy->setText(QString::number(this->master->get(Parameter::lMaszyn3) - this->master->get(Parameter::LWM3)));

    this->ui->chairsPhase1->setText(QString::number(this->master->get(Parameter::PrK)));
    this->ui->chairsFinished->setText(QString::number(this->master->get(Parameter::LKM)));

    this->ui->wardrobesPhase1->setText(QString::number(this->master->get(Parameter::PrSz)));
    this->ui->wardrobesPhase2->setText(QString::number(this->master->get(Parameter::PrSz2)));
    this->ui->wardrobesFinished->setText(QString::number(this->master->get(Parameter::LSzM)));

    this->ui->currentTime->setText(QString::number(this->master->get(Parameter::aktualnyCzas)));
    this->ui->currentOrder->setText(QString::number(this->master->get(Parameter::i)));
    this->ui->numOrders->setText(QString::number(this->master->get(Parameter::j)));

    for(int n = this->ui->ordersComboBox->count(); n < this->master->get(Parameter::j); n++) {
        this->ui->ordersComboBox->addItem(QString::number(n) + QString("., w kolejce."));
    }
    //aktualizuj tekst dla zamowien
    for(int n = this->ui->ordersComboBox->currentIndex(); n < this->master->get(Parameter::i); n++) {
        this->ui->ordersComboBox->setItemText(n, QString::number(n) + QString("., zakończone."));
    }
    this->ui->ordersComboBox->setItemText(this->master->get(Parameter::i), QString::number(this->master->get(Parameter::i)) + QString("., w trakcie."));

    this->updateOrderDetais();
}

void MainWindow::updateOrderDetais() {
    int time, chairs, wardrobes, id;
    id = this->ui->ordersComboBox->currentIndex();
    chairs = this->master->getOrderChairs(id);
    wardrobes = this->master->getOrderWardrobes(id);
    time = this->master->getOrderTime(id);

    if(id < this->master->get(Parameter::i)) {
        this->ui->chairsFinishedOrder->setText(QString::number(chairs));
        this->ui->wardrobesFinishedOrder->setText(QString::number(wardrobes));
    }
    else if(id == this->master->get(Parameter::i)) {
        this->ui->chairsFinishedOrder->setText(QString::number(this->master->get(Parameter::LKM)));
        this->ui->wardrobesFinishedOrder->setText(QString::number(this->master->get(Parameter::LSzM)));
    }
    else {
        this->ui->chairsFinishedOrder->setText(QString::number(0));
        this->ui->wardrobesFinishedOrder->setText(QString::number(0));
    }
    this->ui->chairsOrdered->setText(QString::number(chairs));
    this->ui->wardrobesOrdered->setText(QString::number(wardrobes));
    this->ui->orderTime->setText(QString::number(time));
}

void MainWindow::on_plotWorkersButton_clicked() {
    if(this->plotWorkers == NULL) {
        this->plotWorkers = new QCustomPlot;

        this->plotWorkers->xAxis->setLabel("Czas");
        this->plotWorkers->yAxis->setLabel(QString::fromUtf8("Zajęci pracownicy"));
        this->plotWorkers->setGeometry(QRect(100, 100, 800, 200));
        this->plotWorkers->setWindowTitle(QString::fromUtf8("Wykorzystanie pracowników"));

        this->plotWorkers->addGraph();

//        this->plotWorkers->graph(0)->setData(dataTime, dataWorkers);
        this->plotWorkers->xAxis->setRange(0, dataTime.back());
    }
    this->plotWorkers->show();
}

void MainWindow::on_plotStorageButton_clicked() {

}

void MainWindow::on_plotMachinesButton_clicked() {

}

void MainWindow::on_plotOrdersButton_clicked() {

}
