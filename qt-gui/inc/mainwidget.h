#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QProcess>
#include <QWidget>

class QPushButton;
class QTextBrowser;
class QProcess;
class GraphWidget;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cc
class MainWidget : public QWidget
{
        Q_OBJECT // Pre-processor macro used by Qt build tools

public:
        explicit MainWidget(QWidget *parent = nullptr); //Constructor
        ~MainWidget(); // Destructor

        // graph must be public to be able to add points from main
        GraphWidget *graph;

private slots:
        //void onCaptureProcessOutput(); // Handler for process output

private:
        QPushButton* button_exit;
        //QTextBrowser* textBrowser_;
        //QProcess process_; // Run a process after pressing the button
};

#endif /* MAINWIDGET_H */
