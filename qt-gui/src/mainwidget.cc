#include <cstdlib>
#include <iostream>

#include <QtWidgets>

#include "graphwidget.h"
#include "mainwidget.h"

// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) :
        QWidget(parent)
{
        buttonExit = new QPushButton(tr("Exit"));
        buttonChangeState = new QPushButton(tr("Start/stop measuring"));
        graph = new GraphWidget();

        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(buttonChangeState, 0, 0);
        mainLayout->addWidget(buttonExit, 1, 0);
        mainLayout->addWidget(graph->chartView, 2, 0);
        setLayout(mainLayout);
        setWindowTitle(tr("Qt GUI app"));

        // Connect the button's released signal to the MainWidget's onButtonReleased method.
        connect(buttonExit, SIGNAL(released()), this, SLOT(close()));
        connect(buttonChangeState, SIGNAL(released()), graph, SLOT(toggleGraphState()));
}

// Destructor
MainWidget::~MainWidget()
{
        delete buttonExit;
        delete buttonChangeState;
        delete graph;
}

