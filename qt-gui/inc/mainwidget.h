#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QProcess>

class QPushButton;
class QTextBrowser;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cc
class MainWidget : public QWidget
{
    Q_OBJECT // Pre-processor macro used by QT build tools

public:
    explicit MainWidget(QWidget *parent = 0); //Constructor
    ~MainWidget(); // Destructor

private slots:
        void onButtonReleased();

private:
   QPushButton* button_;
   QTextBrowser* textBrowser_;
};

#endif // MAINWIDGET_H
