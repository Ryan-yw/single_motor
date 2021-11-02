#include "./plot/include/plot.h"
#include "ui_plot.h"


std::atomic<double> imu_angle[3] = {0,0,0};

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow),
  mPlot(nullptr),
  mTag1(nullptr),
  mTag2(nullptr),
  mTag3(nullptr)
{
    ui->setupUi(this);

    mPlot = new QCustomPlot(this);
    setCentralWidget(mPlot);


    // configure plot to have two right axes:
    mPlot->yAxis->setTickLabels(false);
    connect(mPlot->yAxis2, SIGNAL(rangeChanged(QCPRange)), mPlot->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    mPlot->yAxis2->setVisible(true);
    mPlot->axisRect()->addAxis(QCPAxis::atRight);
    mPlot->axisRect()->addAxis(QCPAxis::atRight);
    mPlot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    mPlot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags
    mPlot->axisRect()->axis(QCPAxis::atRight, 2)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph1 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph2 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 1));
    mGraph3 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 2));
    mGraph1->setPen(QPen(QColor(Qt::red)));
    mGraph2->setPen(QPen(QColor(Qt::blue)));
    mGraph3->setPen(QPen(QColor(Qt::green)));
    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag1 = new AxisTag(mGraph1->valueAxis());
    mTag1->setPen(mGraph1->pen());
    mTag2 = new AxisTag(mGraph2->valueAxis());
    mTag2->setPen(mGraph2->pen());
    mTag3 = new AxisTag(mGraph3->valueAxis());
    mTag3->setPen(mGraph3->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(40);
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::timerSlot()
{
    mPlot->resize(this->size().width(),this->size().height());
    // calculate and add a new data point to each graph:
    mGraph1->addData(mGraph1->dataCount(), imu_angle[0]);
    mGraph2->addData(mGraph2->dataCount(), imu_angle[1]);
    mGraph3->addData(mGraph3->dataCount(), imu_angle[2]);
    // make key axis range scroll with the data:
    mPlot->xAxis->rescale();
    mGraph1->rescaleValueAxis(false, true);
    mGraph2->rescaleValueAxis(false, true);
    mGraph3->rescaleValueAxis(false, true);
    mPlot->xAxis->setRange(mPlot->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph1Value = mGraph1->dataMainValue(mGraph1->dataCount()-1);
    double graph2Value = mGraph2->dataMainValue(mGraph2->dataCount()-1);
    double graph3Value = mGraph3->dataMainValue(mGraph3->dataCount()-1);
    mTag1->updatePosition(graph1Value);
    mTag2->updatePosition(graph2Value);
    mTag3->updatePosition(graph3Value);
    mTag1->setText(QString::number(graph1Value, 'f', 2));
    mTag2->setText(QString::number(graph2Value, 'f', 2));
    mTag3->setText(QString::number(graph3Value, 'f', 2));

    mPlot->replot();
}
