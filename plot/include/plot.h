#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "axistag.h"

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();

private slots:
  void timerSlot();


private:
    Ui::PlotWindow *ui;

    //plot //
    QCustomPlot *mPlot;
    QPointer<QCPGraph> mGraph1;
    QPointer<QCPGraph> mGraph2;
    QPointer<QCPGraph> mGraph3;
    AxisTag *mTag1;
    AxisTag *mTag2;
    AxisTag *mTag3;
    QTimer mDataTimer;
};

#endif // DIALOG_H
