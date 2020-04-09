#include <chrono>
#include <cstdlib>

#include <QtWidgets>

#include <graphwidget.h>

/*************************** Public functions ******************************/

// Constructor
GraphWidget::GraphWidget(QWidget *parent) :
        QWidget(parent)
{
        // Set initial axis sizes
        axisXMin = 0;
        axisXMax = 30;
        axisYMin = 0;
        axisYMax = 9;

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
int GraphWidget::addPointPeriodic(const int time_ms, std::atomic<bool>& running)
{
        int rand_int = 0;
        int data_len = 0;

        while (running) {
                rand_int = rand() % 10;
                data_len = series_random->count();
                series_random->append(data_len, rand_int);

                if (data_len > axisXMax) {
                        // Delete first point
                        series_random->remove(0);

                        // Shift x-values of all other points
                        for (int k = 0; k < data_len; k++) {
                                series_random->replace(k, k, series_random->at(k).y());
                        }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
        }

        return 0;
}

