#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QPushButton;
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

private:
        QPushButton* buttonExit;
        QPushButton* buttonChangeState;
};

#endif /* MAINWIDGET_H */
