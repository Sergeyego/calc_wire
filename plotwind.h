#ifndef PLOTWIND_H
#define PLOTWIND_H

#include <QtGui>
#include "plot.h"

class PlotWind : public QWidget
{
    Q_OBJECT

public:
    PlotWind(QWidget *parent);
    ~PlotWind();
    PlotSrc* getSrc(int i){return pC[i];}
    int getN(){return Np;}
    QVector<pnts>* getData(){return &pData;}
    Plot* getPlot(){return plot;}
    void paint(QVector<pnts> pData, int nx);
protected:
    int Np;
    PlotSrc **pC;
    Plot* plot;
    QVector<pnts> pData;
    QSpinBox* edtNx;
    QSpinBox* edtNy;
    QDoubleSpinBox* edtYmx;
    QDoubleSpinBox* edtYmn;
public slots:

};

#endif // PLOTWIND_H
