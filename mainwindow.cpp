#include "mainwindow.h"

const int Nv=18;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* hbl = new QHBoxLayout(/*this*/);
    QVBoxLayout* vbl = new QVBoxLayout(/*this*/);
    QGridLayout* gbl = new QGridLayout(/*this*/);
    QLabel* tkvo = new QLabel(tr("Кол-во волок"),this);
    QLabel* td0 = new QLabel(tr("Нач. диаметр"),this);
    QLabel* tsop = new QLabel(tr("Нач. предел проч.,  Н/мм2"),this);
    this->setWindowTitle(tr("Расчёт маршрута волочения"));
    volplot = new Plot(this);
    skvo = new QSpinBox(this);
    d0 = new QDoubleSpinBox(this);
    b0= new QDoubleSpinBox(this);
    b0->setRange(0,10000);
    b0->setValue(392);
    d0->setSingleStep(0.5);
    d0->setDecimals(3);
    d0->setRange(0,10);
    d0->setValue(5);
    d0->setSuffix(" mm");
    skvo->setRange(1,Nv);
    skvo->setValue(10);
    gbl->addWidget(tkvo,0,0);
    gbl->addWidget(skvo,0,1);
    gbl->addWidget(td0,1,0);
    gbl->addWidget(d0,1,1);
    gbl->addWidget(tsop,2,0);
    gbl->addWidget(b0,2,1);
    vbl->addLayout(gbl);
    mrc = new Vol*[Nv];
    for (int i=0; i<Nv; i++){
        mrc[i]= new Vol(this,QString::number(i+1));
        vbl->addWidget(mrc[i]);
    }
    hbl->addLayout(vbl);
    hbl->addWidget(volplot);
    this->setLayout(hbl);
    tkvo->setFixedWidth(90);

    connect(skvo,SIGNAL(valueChanged(int)),this,SLOT(setKvo()));
    for (int i=0; i<Nv; i++)
        connect(mrc[i],SIGNAL(rupd()),this,SLOT(updv()));
    connect(d0,SIGNAL(valueChanged(double)),this,SLOT(updv()));
    connect(this,SIGNAL(rplot()),this,SLOT(replot()));
    connect(b0,SIGNAL(valueChanged(double)),this,SLOT(updv()));
    setKvo();
    updv();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setKvo()
{
    for (int i=0; i<Nv; i++)
        mrc[i]->setDisabled(i>=skvo->value());
    updv();
}

void MainWindow::updv()
{
    mrc[0]->setdp(d0->value());
    mrc[0]->setdn(d0->value());
    mrc[0]->setbn(b0->value());
    mrc[0]->calc();
    for (int i=1; i<skvo->value(); i++){
        mrc[i]->setdp(mrc[i-1]->d->value());
        mrc[i]->setdn(d0->value());
        mrc[i]->setbn(b0->value());
        mrc[i]->calc();
    }
    emit rplot();
}

void MainWindow::replot()
{
    pnts voldata;
    voldata.x.resize(skvo->value());
    voldata.y.resize(skvo->value());
    for (int i=0; i<skvo->value(); i++){
        voldata.x[i]=mrc[i]->d->value();
        voldata.y[i]=mrc[i]->q->value();;
    }
    volplot->setdata(voldata);
}

