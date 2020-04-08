#include <cstdlib>

#include <QtWidgets>

#include <graphwidget.h>

// Constructor
GraphWidget::GraphWidget(QWidget *parent) :
        QWidget(parent)
{
        // Create a series of random data points
        series_random = new QtCharts::QLineSeries();
        addGraphData();

        // Create QChart instance with a few options
        chart = new QtCharts::QChart;
        chart->legend()->hide();
        chart->addSeries(series_random);
        chart->setTitle("Random data chart");

        // Limit x range to [0, 100] and y range to [0, 9]
        axisX = new QtCharts::QValueAxis;
        axisX->setRange(0, 100);
        axisX->setTickCount(7);
        axisX->setLabelFormat("%d");
        chart->setAxisX(axisX, series_random);

        axisY = new QtCharts::QValueAxis;
        axisY->setRange(0, 9);
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

// Slot function to add data point
void GraphWidget::onButtonReleased()
{
        int rand_int = 0;
        int data_len = 0;

        rand_int = rand() % 10;
        data_len = series_random->count();

        series_random->append(data_len, rand_int);
}


void GraphWidget::addGraphData()
{
        int rand_int = 0;
        for (int i = 0; i < 10; i++) {
                rand_int = rand() % 10;
                series_random->append(i, rand_int);
        }
}
