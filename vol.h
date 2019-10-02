#ifndef VOL_H
#define VOL_H

#include <QWidget>
#include <QtGui>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>

class Vol : public QWidget
{
    Q_OBJECT
    double dp;
    double dn;
    double bn;
public:
    Vol(QWidget *parent, QString n);
    QHBoxLayout* hbl;
    QLabel* num;
    QDoubleSpinBox* q;
    QDoubleSpinBox* d;
    QLineEdit* b;
    QLineEdit* qsum;
    void setdp(double diam);
    void setdn(double dna){dn=dna;}
    void setbn(double bna){bn=bna;}
    void calc();
signals:
    void rupd();
public slots:
    void supd();
    void calcq();
};

#endif // VOL_H
