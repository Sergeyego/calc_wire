#include "plotwind.h"
#include <math.h>

PlotWind::PlotWind(QWidget *parent)
    : QWidget(parent)
{
    int sH = QApplication::desktop()->screenGeometry().height();
    QGridLayout* tbl = new QGridLayout();
    QVBoxLayout* vbl = new QVBoxLayout();
    QHBoxLayout* hbl = new QHBoxLayout();
    QColor* u1l = new QColor(Qt::red);
    QColor* u2l = new QColor(Qt::blue);
    QColor* d1l = new QColor(Qt::black);
    QColor* d2l = new QColor(Qt::green);
    QColor* bk = new QColor(210,210,210);
    QColor* ln = new QColor(50,150,50);
    int Nx=10, Ny=4;
    int marg=sH/60;
    Np=2;
    pC = new PlotSrc*[Np];
    pC[0] =  new PlotSrc(this,QString(tr("q()")),u1l,bk,sH);
    pC[1] =  new PlotSrc(this,QString(tr("q()")),u1l,bk,sH);
    plot = new Plot(this,QString(tr("Маршрут волочения")), marg*2,marg,Nx,Ny,bk->rgb(), ln->rgb());
    double Ymn=0,Ymx=400.0;
    plot->setYmn(Ymn);
    plot->setYmx(Ymx);
    plot->setXmn(0.0);
    plot->setXmx(21.0);
    plot->setMinimumSize(500,400);
    edtNx = new QSpinBox();
    edtNx->setValue(Nx);
    edtNy = new QSpinBox();
    edtNy->setValue(Ny);
    edtYmx = new QDoubleSpinBox();
    edtYmx->setValue(Ymx);
    edtYmn = new QDoubleSpinBox();
    edtYmn->setValue(Ymn);
    QLabel* txtNx = new QLabel("Nx:");
    QLabel* txtNy = new QLabel("Ny:");
    QLabel* txtYmx = new QLabel("Ymx:");
    QLabel* txtYmn = new QLabel("Ymn:");
    edtNx->setRange(1,50);
    edtNy->setRange(1,50);
    txtNx->setFixedSize(40,25);
    edtNx->setFixedSize(60,25);
    txtNy->setFixedSize(40,25);
    edtNy->setFixedSize(60,25);
    txtYmx->setFixedSize(40,25);
    edtYmx->setFixedSize(60,25);
    txtYmn->setFixedSize(40,25);
    edtYmn->setFixedSize(60,25);
    for(int i=0; i<Np; i++) vbl->addWidget(pC[i]->pBox());
    tbl->addWidget(txtNx,0,0);
    tbl->addWidget(edtNx,0,1);
    tbl->addWidget(txtNy,1,0);
    tbl->addWidget(edtNy,1,1);
    tbl->addWidget(txtYmx,2,0);
    tbl->addWidget(edtYmx,2,1);
    tbl->addWidget(txtYmn,3,0);
    tbl->addWidget(edtYmn,3,1);
    vbl->addLayout(tbl);
    hbl->addWidget(plot);
    hbl->addLayout(vbl);

    connect(edtNx, SIGNAL(valueChanged(int)),this->plot, SLOT(setNx(int)));
    connect(edtNy, SIGNAL(valueChanged(int)),this->plot, SLOT(setNy(int)));
    connect(edtYmx, SIGNAL(valueChanged(double)),this->plot, SLOT(setYmx(double)));
    connect(edtYmn, SIGNAL(valueChanged(double)),this->plot, SLOT(setYmn(double)));
    this->setLayout(hbl);
}

PlotWind::~PlotWind()
{

}

void PlotWind::paint(QVector<pnts> pD, int nx)
{
    pData=pD;
    //pData
    //qDebug()<<pD.size();
    //plot->setNx(nx);
}

