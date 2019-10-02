#include "plot.h"

Plot::Plot(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout* gbl = new QGridLayout(this);
    cmdprint = new QPushButton("Print");
    qplot = new QwtPlot(this);
    qplot->setTitle(tr("Зависимость q(d)"));
    qplot->setAutoReplot(true);
    qplot->setPalette(Qt::white);

    grid = new QwtPlotGrid();
    grid->enableXMin(true);
    grid->setMajorPen(QPen(Qt::black,0,Qt::DotLine));
    grid->setMinorPen(QPen(Qt::gray,0,Qt::DotLine));
    grid->attach(qplot);

    qplot->setAxisTitle(
        QwtPlot::xBottom,QString::fromLocal8Bit("d, мм"));
    qplot->setAxisScale(QwtPlot::xBottom,2.0,5.5);
    qplot->setAxisTitle(
        QwtPlot::yLeft,QString::fromLocal8Bit("q, %"));
    qplot->setAxisScale(QwtPlot::yLeft,0,30);

    sinPen = new QPen(Qt::red);

    sinFunCurve = new QwtPlotCurve;
    sinFunCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
    sinFunCurve->setPen(*sinPen);
    sinFunCurve->attach(qplot);

    /*d_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                                         QwtPicker::PointSelection | QwtPicker::DragSelection,
                                         QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
                                         qplot->canvas());*/
    d_picker = new QwtPlotPicker(qplot->canvas());
    d_picker->setRubberBandPen(QColor(Qt::green));
    d_picker->setRubberBand(QwtPicker::CrossRubberBand);
    d_picker->setTrackerPen(QColor(Qt::blue));

    QwtSymbol symbol1;
    symbol1.setStyle(QwtSymbol::Ellipse);
    symbol1.setPen(QColor(Qt::blue));
    symbol1.setSize(7);
//    sinFunCurve->setSymbol(symbol1);

 /*   mar= new QwtPlotMarker;
    mar->setLabel(QString::fromLatin1("y = 0"));
    mar->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mar->setLineStyle(QwtPlotMarker::HLine);
    mar->setYValue(5.0);
    mar->attach(qplot);
*/
    gbl->addWidget(qplot);
    gbl->addWidget(cmdprint);
    cmdprint->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    this->setLayout(gbl);
    this->setMinimumWidth(500);
    //sinFunCurve->setVisible(true);
    connect(cmdprint,SIGNAL(released()),this,SLOT(sprint()));
}

void Plot::setdata(pnts pData){
    int N=pData.x.size();
    double xmax=0,xmin=100;
    for (int i=0; i<N; i++){
        if (xmax<pData.x[i]) xmax=pData.x[i];
        if (xmin>pData.x[i]) xmin=pData.x[i];
    }
    qplot->setAxisScale(QwtPlot::xBottom,xmax,xmin);
    //sinFunCurve->setData(pData.x.data(),pData.y.data(),N);
    sinFunCurve->setSamples(pData.x.data(),pData.y.data(),N);
    qplot->replot();
}

void Plot::sprint()
{
    QwtPlotRenderer renderer;
    renderer.setDiscardFlag( QwtPlotRenderer::DiscardBackground );
    renderer.setDiscardFlag( QwtPlotRenderer::DiscardCanvasBackground );
    renderer.setDiscardFlag( QwtPlotRenderer::DiscardCanvasFrame );
    renderer.setLayoutFlag( QwtPlotRenderer::FrameWithScales );
    QPrinter printer;
    printer.setColorMode(QPrinter::Color);
    QPrintDialog dialog(&printer,this);
    if (dialog.exec()){
        QPainter painter(&printer);
        QRect page = printer.pageRect();
        int w = page.width()-page.x();
        QRect rect(page.x(), page.y(), w*0.95, w*1.3);
        renderer.render(qplot,&painter,rect);
    }
}
