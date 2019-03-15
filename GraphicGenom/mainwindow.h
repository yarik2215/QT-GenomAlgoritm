#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QThread>
#include <genomalgoritm.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QtCharts::QChartView *getChartView() const;
    void setChartView(QtCharts::QChartView *value);

private slots:
    void replotChart();

    void on_pushButton_clicked();

private:

    void plotChart();

    Ui::MainWindow *ui;
    GenomAlgoritm *genom;
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartView;
    QtCharts::QSplineSeries *etalonSeria;
    QtCharts::QSplineSeries *genomSeria;
    QThread *thread1;

signals:
    void startCalculation(int maxItterations);
};

#endif // MAINWINDOW_H
