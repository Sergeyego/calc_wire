#include "vol.h"

double x[13] = {0, 5,   10, 20.24, 26.46, 35.5,  45.07, 58.33, 67.89, 74.87, 80.03, 83.87, 86.78};
double y[13] = {0, 15,  58, 171,   181,   220,   269,   318,   377,   406,   436,   441,   446};

double L(double xp,int n,int i) {
    // числитель и знаменатель
    double Chesl;
    double Znam;
    Chesl = 1; Znam = 1;
    int k;
    // вычисление числителя
    for (k = 0; k!= n; k++ ) {
        if ( k == i ) continue;
        // убираем множитель x - x(i)
        Chesl *= xp - x[k];
    }
    // вычисление знаменателя
    for(k= 0; k!= n;k++) {
        if (x[i] == x[k]) continue;
        // убираем, а то ноль в знаменателе
        Znam *= x[i] - x[k];
    }
    return Chesl/Znam;
}

double intr(double px){
    // вычисляем степень полинома
    int n = sizeof(y)/sizeof(double);
    // начальное значение
    double R = 0;
    // вычисляем значение интерполяционного многочлена в точке
    for (int i = 0; i != n; i++) {
        R += y[i]*L(px,n,i);
    }
    return R;
}

Vol::Vol(QWidget *parent, QString n) :
    QWidget(parent)
{
    hbl = new QHBoxLayout(this);
    num = new QLabel(this);
    QLabel* lq= new QLabel("Q=");
    QLabel* ld= new QLabel("D=");
    QLabel* qs= new QLabel("Qs=");
    QLabel* lb= new QLabel(tr("σ="));
    b= new QLineEdit(this);
    q= new QDoubleSpinBox(this);
    d= new QDoubleSpinBox(this);
    qsum= new QLineEdit(this);
    q->setFixedWidth(85);
    d->setFixedWidth(90);
    b->setFixedWidth(75);
    b->setReadOnly(true);
    qsum->setFixedWidth(60);
    qsum->setReadOnly(true);
    q->setRange(0,40);
    q->setDecimals(3);
    q->setSingleStep(0.01);
    q->setValue(15.40);
    d->setRange(0,10);
    d->setSingleStep(0.001);
    d->setDecimals(3);
    q->setSuffix(" %");
    d->setSuffix(" mm");
    hbl->addWidget(num);
    hbl->addWidget(lq);
    hbl->addWidget(q);
    hbl->addWidget(ld);
    hbl->addWidget(d);
    hbl->addWidget(qs);
    hbl->addWidget(qsum);
    hbl->addWidget(lb);
    hbl->addWidget(b);
    num->setText(n);
    num->setFixedWidth(20);
    this->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    this->setLayout(hbl);
    connect(q,SIGNAL(valueChanged(double)),this,SLOT(supd()));
    connect(d,SIGNAL(editingFinished()),this,SLOT(calcq()));
}

void Vol::calc()
{
    d->setValue(dp*sqrt(1-(q->value()*0.01)));
    double qs=(1-((d->value()*d->value())/(dn*dn)))*100;
    qsum->setText(QString::number(qs,0,3));
    b->setText(QString::number(intr(qs)+bn,0,2));
}

void Vol::setdp(double diam)
{
    dp=diam;
}

void Vol::supd()
{
    emit rupd();
}

void Vol::calcq()
{
    q->setValue((1-(d->value()/dp)*(d->value()/dp))*100);
}
