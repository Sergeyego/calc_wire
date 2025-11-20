#ifndef VSR_H
#define VSR_H

#include <QtGui>

class Vsr : public QWidget
{
    Q_OBJECT
    int n;
    double qsum;
public:
    Vsr(QWidget *parent = 0);
    ~Vsr();
    void setn(int nvl){n=nvl;}
    void setqsum(double qs){qsum=qs;}
protected:
    QDoubleSpinBox* vsn0;
    QDoubleSpinBox* vsn1;
    QLineEdit* vsc0;
    QLineEdit* vsc1;
    QRadioButton* rbt;
signals:

public slots:
    void calc();

};

#endif // VSR_H
