#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

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
        explicit GraphWidget(QWidget *parent = nullptr); // Constructor
        ~GraphWidget(); // Destructor
        QtCharts::QChartView *chartView;

public slots:
        void onButtonReleased(void);

private:
        QtCharts::QLineSeries *series_random;
        QtCharts::QChart *chart;
        QtCharts::QValueAxis *axisX;
        QtCharts::QValueAxis *axisY;

        // Functions
        void addGraphData();
};

#endif /* GRAPHWIDGET_H */
