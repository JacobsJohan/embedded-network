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
        //textBrowser_ = new QTextBrowser();
        graph = new GraphWidget();

        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(button_exit, 0, 0);
        mainLayout->addWidget(graph->chartView, 1, 0);
        setLayout(mainLayout);
        setWindowTitle(tr("Qt GUI app"));

        // Connect the button's released signal to the MainWidget's onButtonReleased method.
        //connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));
        connect(button_exit, SIGNAL(released()), this, SLOT(close()));
}

// Destructor
MainWidget::~MainWidget()
{
        delete button_exit;
        //delete textBrowser_;
        delete graph;
}

/* Legacy
// Handler for the button press
void MainWidget::onButtonReleased()
{
        // clear the text in the textBrowser
        textBrowser_->clear();
        textBrowser_->append(tr("Running command:"));

        // Set up our process to write to stdout and run our command
        process_.setCurrentWriteChannel(QProcess::StandardOutput); // Set the write channel
        process_.start("ls -alh /home/johan/Documents"); // Start the program
}


// This is called whenever the QProcess::readyReadStandardOutput() signal is received
void MainWidget::onCaptureProcessOutput()
{
        // Determine whether the object that sent the signal was a pointer to a process
        // sender() returns a pointer to the Qt class that sent us the signal
        // If the sender was a QProcess, we will get a valid QProcess pointer,
        // else, we will get a NULL pointer
        QProcess* process = qobject_cast<QProcess*>(sender());

        // If so, append the output to the textbrowser
        if (process)
                textBrowser_->append(process->readAllStandardOutput());
}
*/
