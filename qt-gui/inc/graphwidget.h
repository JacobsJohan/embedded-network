#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include <atomic>

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QWidget>

// Class for our graph widget
class GraphWidget : public QWidget
{
        Q_OBJECT

public:
        explicit GraphWidget(QWidget *parent = nullptr);        // Constructor
        ~GraphWidget();                                         // Destructor
        QtCharts::QChartView *chartView;

        int addPointPeriodic(const int time_ms, std::atomic<bool>& running);

private:
        QtCharts::QLineSeries *series_random;
        QtCharts::QChart *chart;
        QtCharts::QValueAxis *axisX;
        QtCharts::QValueAxis *axisY;

        int axisXMin;
        int axisXMax;
        int axisYMin;
        int axisYMax;
};

#endif /* GRAPHWIDGET_H */
