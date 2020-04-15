#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include <QtWidgets>

extern "C" {
#include <zmq_connection.h>
}

#include <graphwidget.h>

/*************************** Public functions ******************************/

// Constructor
GraphWidget::GraphWidget(QWidget *parent) :
        QWidget(parent)
{
        // Set initial axis sizes
        axisXMin = 0;
        axisXMax = 30;
        axisYMin = 24;
        axisYMax = 26;

        // Create a series of random data points
        series_random = new QtCharts::QLineSeries();

        // Create QChart instance with a few options
        chart = new QtCharts::QChart;
        chart->legend()->hide();
        chart->addSeries(series_random);
        chart->setTitle("Random data chart");

        // Limit x and y range based on initial values
        axisX = new QtCharts::QValueAxis;
        axisX->setRange(axisXMin, axisXMax);
        axisX->setTickCount(7);
        axisX->setLabelFormat("%d");
        axisX->setReverse(true);
        chart->setAxisX(axisX, series_random);

        axisY = new QtCharts::QValueAxis;
        axisY->setRange(axisYMin, axisYMax);
        axisY->setTickCount(4);
        axisY->setLabelFormat("%d");
        chart->setAxisY(axisY, series_random);

        // Create ChartView such that we don't need a QGraphicsView scene
        chartView = new QtCharts::QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
}

// Destructor
GraphWidget::~GraphWidget()
{
        delete series_random;
        delete chart;
        delete axisX;
        delete axisY;
        delete chartView;
}



// Periodically add data points to the graph as long as the Qt app is running
int GraphWidget::addPointPeriodic(const int time_ms, std::atomic<GraphState>& state)
{
        int ret = 0;
        float temp = 0;
        int data_len = 0;
        int port = 5555;
        std::string ip = "raspberrypi.local";
        void *zctx = NULL;
        void *zsock = NULL;

        // Check if we are shutting down
        while (state != GraphState::terminating) {
                // Open client side socket
                ret = init_req_sock(&zctx, &zsock, ip.c_str(), port);
                if (ret < 0) {
                        std::cout << "Error initializing request socket" << std::endl;
                        return -1;
                }

                // Check if we are idle/running
                if (state == GraphState::running) {
                        ret = request_temp(zsock, &temp);
                        if (ret < 0) {
                                std::cout << "Error requesting temperature" << std::endl;
                                return -1;
                        }

                        // Print temperature
                        std::cout << "T: " << temp << " C" << std::endl;
                        data_len = series_random->count();
                        series_random->append(data_len, temp);

                        if (data_len > axisXMax) {
                                // Delete first point
                                series_random->remove(0);

                                // Shift x-values of all other points
                                for (int k = 0; k < data_len; k++) {
                                        series_random->replace(k, k, series_random->at(k).y());
                                }
                        }

                        if (ceil(temp) > axisYMax) {
                                axisYMax = ceil(temp);
                                axisY->setRange(axisYMin, axisYMax);
                        } else if (floor(temp) < axisYMin) {
                                axisYMin = floor(temp);
                                axisY->setRange(axisYMin, axisYMax);
                        }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
        }

        ret = close_sock(zsock);
        if (ret < 0) {
                std::cout << "Error closing socket" << std::endl;
        }

        return ret;
}

/*************************** Public slots ******************************/

// Change graphState from idle to running or vice versa
void GraphWidget::toggleGraphState(void)
{
        switch (graphState) {
        case GraphState::idle:
                // Swap to running
                graphState = GraphState::running;
                break;
        case GraphState::running:
                // Swap to idle
                graphState = GraphState::idle;
                break;
        default:
                graphState = GraphState::terminating;
                std::cout << "Error toggling graph state" << std::endl;
        }
}
