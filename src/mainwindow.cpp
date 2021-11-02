/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2021 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 29.03.21                                             **
**          Version: 2.1.0                                                **
****************************************************************************/
#include <iostream>
#include "mainwindow.h"
#include "JoystickTest.h"
#include "plot.h"

#include "ui_mainwindow.h"


#include <QWidget>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // joy stick //
  connect(ui->game_pad_btn,SIGNAL(clicked()),this,SLOT(on_btn_game_pad()));


  // plot //
  connect(ui->plot_btn,SIGNAL(clicked()),this,SLOT(on_btn_plot()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_game_pad()
{
    JoystickTestWindow* window = new JoystickTestWindow(gameController_);
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
//    window->exec();
//    delete window;
}


void MainWindow::on_btn_plot()
{
    PlotWindow* window = new PlotWindow;
    //window->
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->resize(600,400);
}
