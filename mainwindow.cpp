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

    this->dataMachines1.clear();
    this->dataMachines2.clear();
    this->dataMachines3.clear();
    this->dataOrders1.clear();
    this->dataOrders2.clear();
    this->dataStorage1.clear();
    this->dataStorage2.clear();
    this->dataWorkers.clear();
    this->dataTime.clear();
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
    this->dataMachines1.push_back(this->master->get(Parameter::lMaszyn1) - this->master->get(Parameter::LWM1));
    this->dataMachines2.push_back(this->master->get(Parameter::lMaszyn2) - this->master->get(Parameter::LWM2));
    this->dataMachines3.push_back(this->master->get(Parameter::lMaszyn3) - this->master->get(Parameter::LWM3));
    this->dataStorage1.push_back(this->master->get(Parameter::LKM));
    this->dataStorage2.push_back(this->master->get(Parameter::LSzM));
    this->dataOrders1.push_back(this->master->get(Parameter::i));
    this->dataOrders2.push_back(this->master->get(Parameter::j));

    this->dataTime.push_back(this->master->get(Parameter::aktualnyCzas));

    if(this->plotWorkers != NULL && this->plotWorkers->isVisible()) {
        this->plotWorkers->xAxis->setRange(0, dataTime.back());
        this->plotWorkers->graph(0)->setData(dataTime, dataWorkers);
        this->plotWorkers->replot();
    }
    if(this->plotStorage != NULL && this->plotStorage->isVisible()) {
        this->plotStorage->xAxis->setRange(0, dataTime.back());
        this->plotStorage->graph(0)->setData(dataTime, dataStorage1);
        this->plotStorage->graph(1)->setData(dataTime, dataStorage2);
        this->plotStorage->replot();
    }
    if(this->plotOrders != NULL && this->plotOrders->isVisible()) {
        this->plotOrders->xAxis->setRange(0, dataTime.back());
        this->plotOrders->graph(0)->setData(dataTime, dataOrders1);
        this->plotOrders->graph(1)->setData(dataTime, dataOrders2);
        this->plotOrders->replot();
    }
    if(this->plotMachines != NULL && this->plotMachines->isVisible()) {
        this->plotMachines->xAxis->setRange(0, dataTime.back());
        this->plotMachines->graph(0)->setData(dataTime, dataMachines1);
        this->plotMachines->graph(1)->setData(dataTime, dataMachines2);
        this->plotMachines->graph(2)->setData(dataTime, dataMachines3);
        this->plotMachines->replot();
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

        this->plotWorkers->graph(0)->setData(dataTime, dataWorkers);
        this->plotWorkers->graph(0)->setPen(QPen(Qt::red));
        this->plotWorkers->xAxis->setRange(0, dataTime.back());
        this->plotWorkers->yAxis->setRange(-1, this->master->get(Parameter::lPracownikow));
        this->plotWorkers->replot();
    }
    this->plotWorkers->show();
}

void MainWindow::on_plotStorageButton_clicked() {
    if(this->plotStorage == NULL) {
        this->plotStorage = new QCustomPlot;

        this->plotStorage->xAxis->setLabel("Czas");
        this->plotStorage->yAxis->setLabel(QString::fromUtf8("Meble w magazynie"));
        this->plotStorage->setGeometry(QRect(100, 200, 800, 200));
        this->plotStorage->setWindowTitle(QString::fromUtf8("Stan magazynu"));

        this->plotStorage->addGraph();
        this->plotStorage->addGraph();

        this->plotStorage->graph(0)->setData(dataTime, dataStorage1);
        this->plotStorage->graph(0)->setPen(QPen(Qt::red));
        this->plotStorage->graph(0)->setName("Krzesła");

        this->plotStorage->graph(1)->setData(dataTime, dataStorage2);
        this->plotStorage->graph(1)->setPen(QPen(Qt::green));
        this->plotStorage->graph(1)->setName("Szafy");

        this->plotStorage->xAxis->setRange(0, dataTime.back());
        this->plotStorage->yAxis->setRange(-1, 20);
        this->plotStorage->legend->setVisible(true);

        this->plotStorage->replot();
    }
    this->plotStorage->show();
}

void MainWindow::on_plotMachinesButton_clicked() {
    if(this->plotMachines == NULL) {
        unsigned max = this->master->get(Parameter::lMaszyn1);
        max = (max < this->master->get(Parameter::lMaszyn2)) ? this->master->get(Parameter::lMaszyn2) : max;
        max = (max < this->master->get(Parameter::lMaszyn3)) ? this->master->get(Parameter::lMaszyn3) : max;
        this->plotMachines = new QCustomPlot;

        this->plotMachines->xAxis->setLabel("Czas");
        this->plotMachines->yAxis->setLabel(QString::fromUtf8("Wykorzystanie maszyn"));
        this->plotMachines->setGeometry(QRect(100, 300, 800, 200));
        this->plotMachines->setWindowTitle(QString::fromUtf8("Wykorzystanie maszyn"));

        this->plotMachines->addGraph();
        this->plotMachines->addGraph();
        this->plotMachines->addGraph();

        this->plotMachines->graph(0)->setData(dataTime, dataMachines1);
        this->plotMachines->graph(0)->setPen(QPen(Qt::red));
        this->plotMachines->graph(0)->setName("Maszyny typu I");

        this->plotMachines->graph(1)->setData(dataTime, dataMachines2);
        this->plotMachines->graph(1)->setPen(QPen(Qt::green));
        this->plotMachines->graph(1)->setName("Maszyny typu II");

        this->plotMachines->graph(2)->setData(dataTime, dataMachines3);
        this->plotMachines->graph(2)->setPen(QPen(Qt::blue));
        this->plotMachines->graph(2)->setName("Maszyny typu III");

        this->plotMachines->xAxis->setRange(0, dataTime.back());
        this->plotMachines->yAxis->setRange(-1, max + 1);

        this->plotMachines->legend->setVisible(true);
        this->plotMachines->replot();
    }
    this->plotMachines->show();
}

void MainWindow::on_plotOrdersButton_clicked() {
    if(this->plotOrders == NULL) {
        this->plotOrders = new QCustomPlot;

        this->plotOrders->xAxis->setLabel("Czas");
        this->plotOrders->yAxis->setLabel(QString::fromUtf8("Przebieg zleceń"));
        this->plotOrders->setGeometry(QRect(100, 400, 800, 200));
        this->plotOrders->setWindowTitle(QString::fromUtf8("Dane na temat zleceń"));

        this->plotOrders->addGraph();
        this->plotOrders->addGraph();

        this->plotOrders->graph(0)->setData(dataTime, dataOrders1);
        this->plotOrders->graph(0)->setPen(QPen(Qt::red));
        this->plotOrders->graph(0)->setName("Aktualne zlecenie");


        this->plotOrders->graph(1)->setData(dataTime, dataOrders2);
        this->plotOrders->graph(1)->setPen(QPen(Qt::green));
        this->plotOrders->graph(1)->setName("Wszystkie zlecenia");


        this->plotOrders->xAxis->setRange(0, dataTime.back());
        this->plotOrders->yAxis->setRange(-1, this->master->get(Parameter::j) + 1);
        this->plotOrders->legend->setVisible(true);

        this->plotOrders->replot();
    }
    this->plotOrders->show();
}
