#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include <atomic>

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QWidget>

enum class GraphState {
        idle,
        running,
        terminating
};

extern std::atomic<GraphState> graphState;

// Class for our graph widget
class GraphWidget : public QWidget
{
        Q_OBJECT

public:
        explicit GraphWidget(QWidget *parent = nullptr);        // Constructor
        ~GraphWidget();                                         // Destructor
        QtCharts::QChartView *chartView;

        int addPointPeriodic(const int time_ms, std::atomic<GraphState>& state);

public slots:
        void toggleGraphState(void);

private:
        QtCharts::QLineSeries *series_temp;
        QtCharts::QChart *chart;
        QtCharts::QValueAxis *axisX;
        QtCharts::QValueAxis *axisY;

        int axisXMin;
        int axisXMax;
        int axisYMin;
        int axisYMax;
};

#endif /* GRAPHWIDGET_H */
