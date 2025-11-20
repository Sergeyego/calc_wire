#include "vsr.h"

Vsr::Vsr(QWidget *parent) :
    QWidget(parent)
{
    rbt = new QRadioButton;
    QGridLayout* gbl = new QGridLayout();
    QLabel* tvr = new QLabel(tr("σ0, кгс/мм2"));
    QLabel* tvc = new QLabel(tr("σ, кгс/мм2"));
    vsn0 = new QDoubleSpinBox;
    vsn1 = new QDoubleSpinBox;
    vsn0->setRange(0,999);
    vsn1->setRange(0,999);
    vsn0->setValue(40);
    vsn1->setValue(42);
    vsc0 = new QLineEdit;
    vsc1 = new QLineEdit;
    vsc0->setReadOnly(true);
    vsc1->setReadOnly(true);
    gbl->addWidget(tvr,0,0);
    gbl->addWidget(vsn0,0,1);
    gbl->addWidget(vsn1,0,2);
    gbl->addWidget(tvc,1,0);
    gbl->addWidget(vsc0,1,1);
    gbl->addWidget(vsc1,1,2);

    this->setLayout(gbl);
    this->setMaximumWidth(240);
    this->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    connect(vsn0,SIGNAL(valueChanged(double)),this,SLOT(calc()));
    connect(vsn1,SIGNAL(valueChanged(double)),this,SLOT(calc()));
}

Vsr::~Vsr()
{
}

void Vsr::calc()
{
    double bn0=vsn0->value();
    double bn1=vsn1->value();
    double qed=100-exp(4.605-(4.605/n)+log10(100-qsum)/(0.43429*n));

    double b0=bn0+1.29*sqrt((bn0*9.8)/(1-qed/100))*(qed/100)*n+0.1*bn0*sqrt(qsum/100);
    double b1=bn1+1.29*sqrt((bn1*9.8)/(1-qed/100))*(qed/100)*n+0.1*bn1*sqrt(qsum/100);
    vsc0->setText(QString::number(b0));
    vsc1->setText(QString::number(b1));
}
