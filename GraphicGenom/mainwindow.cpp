#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chart(new QtCharts::QChart),
    chartView(new QtCharts::QChartView),
    etalonSeria(new QtCharts::QSplineSeries),
    genomSeria(new QtCharts::QSplineSeries),
    thread1(new QThread)
{
    ui->setupUi(this);
    gen_t etalArr[GEN_LENGTH];
    qreal x = 0;
    for(int i = 0; i < GEN_LENGTH; ++i) {
        etalArr[i] = exp(sqrt(x) + 1) * sqrt(cos(log(x + 1)) + 3);
        etalonSeria->append(x,etalArr[i]);
        x += 0.1;
    }
    genom = new GenomAlgoritm(etalArr);
    genom->moveToThread(thread1);
    connect(genom,SIGNAL(plot()),this,SLOT(replotChart()));
    connect(this,SIGNAL(startCalculation(int)),genom,SLOT(calculate(int)));

    ui->verticalLayout_2->addWidget(chartView);
    plotChart();
    thread1->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QtCharts::QChartView *MainWindow::getChartView() const
{
    return chartView;
}

void MainWindow::setChartView(QtCharts::QChartView *value)
{
    chartView = value;
}

void MainWindow::plotChart()
{
    etalonSeria->setName("etalon");
    genomSeria->setName("gen algoritm");
    chart->addSeries(etalonSeria);
    chart->addSeries(genomSeria);
    chart->createDefaultAxes();

    chartView->setChart(chart);
}

void MainWindow::replotChart()
{

    qreal max = 0, min = 0;
    gen_t *tempArr = genom->getGenom()->getGenArr();
    for(int i = 0; i < GEN_LENGTH; ++i) {
        if(tempArr[i] > max)
            max = tempArr[i];
        if(tempArr[i] < min)
            min = tempArr[i];
    }
    chart->axisY()->setRange(min,max);

    genomSeria->clear();
    gen_t x = 0.0;
    for (int i = 0; i < GEN_LENGTH; ++i) {
        genomSeria->append(x,genom->getGenom()->getGenArr()[i]);
        x += 0.1;
    }
    chartView->update();
}

void MainWindow::on_pushButton_clicked()
{
    thread1->exit();
    thread1->start();
    genom->fillRandom();
    genom->setMutateChance(ui->spinBox->value());
    genom->setEuqlidDist(ui->doubleSpinBox->value());
    emit startCalculation(10000000);
    //genom->printEuqlid();

    //replotChart();
}
