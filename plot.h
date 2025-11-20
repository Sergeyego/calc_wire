#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <QtGui>
#include "qwt/qwt_plot.h"
#include "qwt/qwt_plot_curve.h"
#include "qwt/qwt_plot_grid.h"
#include "qwt/qwt_symbol.h"
#include "qwt/qwt_plot_picker.h"
#include "qwt/qwt_plot_marker.h"
#include "qwt/qwt_plot_renderer.h"
#include <QPushButton>
#include <QGridLayout>
#include <QPrinter>
#include <QPrintDialog>

struct pnts{
    QVector<double> x;
    QVector<double> y;
};

class Plot : public QWidget
{
    Q_OBJECT
private:
    QPushButton* cmdprint;
public:
    Plot(QWidget *parent=0);
    QwtPlot* qplot;
    QwtPlotGrid* grid;
    QPen* sinPen;
    QPalette* myPalette;
    QwtPlotCurve* sinFunCurve;
    QwtPlotPicker* d_picker;    
    void setdata(pnts pData);
    QwtPlotMarker* mar;
signals:

private slots:
    void sprint();

};

#endif // PLOT_H
