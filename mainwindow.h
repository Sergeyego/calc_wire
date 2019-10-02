#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "vol.h"
#include <QtGui>
#include "plot.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    QSpinBox* skvo;
    QDoubleSpinBox* d0;
    QDoubleSpinBox* b0;
    Vol** mrc;
    Plot* volplot;
signals:
    void rplot();
public slots:
    void replot();
    void setKvo();
    void updv();
};

#endif // MAINWINDOW_H
