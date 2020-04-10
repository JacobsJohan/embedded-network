#include <atomic>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

#include <QtWidgets>

#include "graphwidget.h"
#include "mainwidget.h"

std::atomic<GraphState> graphState;

int main(int argc, char *argv[])
{
        int ret { 0 };
        const int time_ms { 1000 };
        graphState = GraphState::idle;

        // Creates an instance of QApplication
        QApplication a(argc, argv);

        // This is our MainWidget class containing our GUI and functionality
        MainWidget w;
        w.show(); // Show main window

        // Try to add a data point from here
        GraphWidget *graph = w.graph;

        // Run function asynchronously and return a std::future that will eventually hold the result of the function call
        // std::launch::async ensures that a new thread is launched to execute the task
        std::future<int> f_int = std::async(std::launch::async, &GraphWidget::addPointPeriodic, \
                                            graph, time_ms, std::ref(graphState));

        // run the application and return execs() return value/code
        ret = a.exec();

        // Notify thread(s) that the GUI has stopped
        graphState = GraphState::terminating;

        // Block until thread has returned
        if (f_int.get())
                ret = -1;

        return ret;
}
