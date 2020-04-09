#include <cstdlib>
#include <iostream>

#include <QtWidgets>

#include "graphwidget.h"
#include "mainwidget.h"

// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) :
        QWidget(parent)
{
        button_exit = new QPushButton(tr("Exit"));
        graph = new GraphWidget();

        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(button_exit, 0, 0);
        mainLayout->addWidget(graph->chartView, 1, 0);
        setLayout(mainLayout);
        setWindowTitle(tr("Qt GUI app"));

        // Connect the button's released signal to the MainWidget's onButtonReleased method.
        connect(button_exit, SIGNAL(released()), this, SLOT(close()));
}

// Destructor
MainWidget::~MainWidget()
{
        delete button_exit;
        delete graph;
}

