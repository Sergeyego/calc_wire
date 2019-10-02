#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <QtGui>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_marker.h>
#include <QPushButton>
#include <QGridLayout>
#include <QPrinter>
#include <QPrintDialog>
#include <qwt_plot_renderer.h>

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
