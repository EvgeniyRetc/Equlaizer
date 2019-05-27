#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
QVector<double> VectorToQVector(std::vector<double> vector_){
    QVector<double> out(vector_.size(),0);
    for(int i=0; i < vector_.size();i++){
        out[i] = vector_[i];
    }
    return out;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // инициалзация графика спектра до
    ui->specterBefore->addLayer("abovemain", ui->specterBefore->layer("main"), QCustomPlot::limAbove);
    ui->specterBefore->addLayer("belowmain", ui->specterBefore->layer("main"), QCustomPlot::limBelow);

    ui->specterBefore->xAxis->grid()->setLayer("belowmain");
    ui->specterBefore->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    ui->specterBefore->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->specterBefore->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->specterBefore->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->specterBefore->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->specterBefore->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->specterBefore->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->specterBefore->xAxis->setTickLabelColor(Qt::white);
    ui->specterBefore->yAxis->setTickLabelColor(Qt::white);
    ui->specterBefore->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->specterBefore->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->specterBefore->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->specterBefore->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->specterBefore->xAxis->grid()->setSubGridVisible(true);
    ui->specterBefore->yAxis->grid()->setSubGridVisible(true);
    ui->specterBefore->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->specterBefore->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->specterBefore->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->specterBefore->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(20, 30, 48));
    plotGradient.setColorAt(1, QColor(36, 59, 85));
    ui->specterBefore->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(20, 30, 48));
    axisRectGradient.setColorAt(1, QColor(36, 59, 85));
    ui->specterBefore->axisRect()->setBackground(axisRectGradient);

    ui->specterBefore->rescaleAxes();
    ui->specterBefore->xAxis->setRange(0, 22000);
    ui->specterBefore->yAxis->setRange(0, 2);


    // иницилазция спектра после

    ui->specterAfter->addLayer("abovemain", ui->specterAfter->layer("main"), QCustomPlot::limAbove);
    ui->specterAfter->addLayer("belowmain", ui->specterAfter->layer("main"), QCustomPlot::limBelow);

    ui->specterAfter->xAxis->grid()->setLayer("belowmain");
    ui->specterAfter->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    ui->specterAfter->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->specterAfter->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->specterAfter->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->specterAfter->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->specterAfter->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->specterAfter->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->specterAfter->xAxis->setTickLabelColor(Qt::white);
    ui->specterAfter->yAxis->setTickLabelColor(Qt::white);
    ui->specterAfter->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->specterAfter->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->specterAfter->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->specterAfter->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->specterAfter->xAxis->grid()->setSubGridVisible(true);
    ui->specterAfter->yAxis->grid()->setSubGridVisible(true);
    ui->specterAfter->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->specterAfter->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->specterAfter->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->specterAfter->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(20, 30, 48));
    plotGradient.setColorAt(1, QColor(36, 59, 85));
    ui->specterAfter->setBackground(plotGradient);
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(20, 30, 48));
    axisRectGradient.setColorAt(1, QColor(36, 59, 85));
    ui->specterAfter->axisRect()->setBackground(axisRectGradient);

    ui->specterAfter->xAxis->setRange(0, 22000);
    ui->specterAfter->yAxis->setRange(0, 2000);
    try {
        InitEqulaizer();
    } catch (std::invalid_argument& e) {
        ui->statusBar->showMessage("Construction of Filter failed");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::InitEqulaizer(){
    std::vector <double> freq0 = {200};
    Equlaizer[0].SetParams(freq0, freqSamp, ORDER, lowpass);
    std::vector <double> freq1 = {200, 400};
    Equlaizer[1].SetParams(freq1, freqSamp, ORDER, passband);
    std::vector <double> freq2 = { 400, 800 };
    Equlaizer[2].SetParams(freq2, freqSamp, ORDER, passband);
    std::vector <double> freq3 = { 800, 1500 };
    Equlaizer[3].SetParams(freq3, freqSamp, ORDER, passband);
    std::vector <double> freq4 = { 1500, 3000 };
    Equlaizer[4].SetParams(freq4, freqSamp, ORDER, passband);
    std::vector <double> freq5 = { 3000, 5000 };
    Equlaizer[5].SetParams(freq5, freqSamp, ORDER, passband);
    std::vector <double> freq6 = { 5000, 7000 };
    Equlaizer[6].SetParams(freq6, freqSamp, ORDER, passband);
    std::vector <double> freq7 = { 7000, 10000 };
    Equlaizer[7].SetParams(freq7, freqSamp, ORDER, passband);
    std::vector <double> freq8 = { 10000, 15000 };
    Equlaizer[8].SetParams(freq8, freqSamp, ORDER, passband);
    std::vector <double> freq9 = { 15000 };
    Equlaizer[9].SetParams(freq9, freqSamp, ORDER, highpass);

}


std::vector<double> MainWindow::Filtering(std::vector<double> signalIn_, Filter filter_, double gain_) {
    std::vector<double>ImpulseResponse = filter_.GetImpulseResponse();
    std::vector<double>signalOut(signalIn_.size());
    for (int i = 0; i < signalIn_.size(); i++) {
        signalOut[i] = 0;
        for (int j = 0; j < ImpulseResponse.size(); j++) {
            if (i - j >= 0) {
                signalOut[i] += ImpulseResponse[j] * signalIn_[i - j];
            }
        }
        signalOut[i] *= gain_;
    }
    return signalOut;
}

std::vector<double> MainWindow::SumOfChannel(std::vector<std::vector<double> > signalOnChannel_) {
    std::vector<double> signalOut(signalOnChannel_[0].size());
    #pragma omp parallel for
    for (int j = 0; j < signalOnChannel_[0].size(); j++) {

        signalOut[j] = signalOnChannel_[0][j] + signalOnChannel_[1][j] + signalOnChannel_[2][j] + signalOnChannel_[3][j] + signalOnChannel_[4][j] +
            signalOnChannel_[5][j] + signalOnChannel_[6][j] + signalOnChannel_[7][j] + signalOnChannel_[8][j] + signalOnChannel_[9][j];
    }
    return signalOut;
}

std::vector<double> MainWindow::WorkEqulaizer(std::vector<double> signalIn_){
    std::vector<std::vector<double> > signalOnChannel(NUM_OF_CHANNEL, std::vector<double>(signalIn_.size()));
    #pragma omp parallel for
    for (int i = 0; i < NUM_OF_CHANNEL; i++) {
        signalOnChannel[i] = Filtering(signalIn_, Equlaizer[i], gainArray[i]);
    }

    return SumOfChannel(signalOnChannel);
}
std::vector<double> MainWindow::FFTAnalysis(std::vector<double> signalIn,  int numOfElements, int Nft) {

    if ((numOfElements != 0) && ((numOfElements & (~numOfElements + numOfElements)) == numOfElements)) {//является ли степеню двойки
        int i = numOfElements;
        int newSize = 1;
        while (i != 0) {
            i = i / 2;
            newSize*= 2;
        }
        signalIn.resize(newSize, 0);
        numOfElements = newSize;
        Nft = newSize;
    }
    int i, j, n, m, Mmax, Istp;
    double tmpReal, tmpImag, Wtmp, Theta;
    double Wpr, Wpi, Wr, Wi;
    std::vector< double> complexSignal(2*numOfElements);
    std::vector< double> signalOut(numOfElements);


    n = 2 * numOfElements;
    for (i = 0; i < n; i += 2) {
        complexSignal[i] = 0;
        complexSignal[i + 1] = signalIn[i / 2];
    }

    i = 1; j = 1;
    while (i < n) {
        if (j > i) {
            tmpReal = complexSignal[i]; complexSignal[i] = complexSignal[j]; complexSignal[j] = tmpReal;
            tmpReal = complexSignal[i + 1]; complexSignal[i + 1] = complexSignal[j + 1]; complexSignal[j + 1] = tmpReal;
        }
        i = i + 2; m = numOfElements;
        while ((m >= 2) && (j > m)) {
            j = j - m; m = m >> 1;
        }
        j = j + m;
    }

    Mmax = 2;
    while (n > Mmax) {
        Theta = -2*PI / Mmax; Wpi = sin(Theta);
        Wtmp = sin(Theta / 2); Wpr = Wtmp * Wtmp * 2;
        Istp = Mmax * 2; Wr = 1; Wi = 0; m = 1;

        while (m < Mmax) {
            i = m; m = m + 2; tmpReal = Wr; tmpImag = Wi;
            Wr = Wr - tmpReal * Wpr - tmpImag * Wpi;
            Wi = Wi + tmpReal * Wpi - tmpImag * Wpr;

            while (i < n) {
                j = i + Mmax;
                tmpReal = Wr * complexSignal[j] - Wi * complexSignal[j - 1];
                tmpImag = Wi * complexSignal[j] + Wr * complexSignal[j - 1];

                complexSignal[j] = complexSignal[i] - tmpReal; complexSignal[j - 1] = complexSignal[i - 1] - tmpImag;
                complexSignal[i] = complexSignal[i] + tmpReal; complexSignal[i - 1] = complexSignal[i - 1] + tmpImag;
                i = i + Istp;
            }
        }

        Mmax = Istp;
    }

    for (i = 0; i < Nft; i++) {
        j = i * 2; signalOut[i] = 2 * sqrt(pow(complexSignal[j], 2) + pow(complexSignal[j + 1], 2)) / numOfElements;
    }
    return signalOut;
}
void MainWindow::PlotSpectr(std::vector<double> spectr, QString type){
    if(type =="before"){
        QVector<double> freq(spectr.size()/2,0);
        for(int i = 0; i < freq.size(); i++){
            freq[i] = static_cast<double>(i)/freq.size()*(freqSamp/2);
        }
        QVector<double> qSpectr(spectr.size()/2,0);
        std::vector<double>spectrReal(spectr.begin(), spectr.begin()+ spectr.size()/2);
        qSpectr = VectorToQVector(spectrReal);
        ui->specterBefore->addGraph();
        ui->specterBefore->graph(0)->setData(freq, qSpectr);
        ui->specterBefore->graph(0)->setPen(QColor(21, 115, 88, 255));//задаем цвет точки
        double maxY = qSpectr[0];
        for (int i=1; i < qSpectr.size(); i++){
           if (qSpectr[i]>maxY) maxY = qSpectr[i];
        }
        ui->specterBefore->yAxis->setRange(0, maxY*1.5);
        ui->specterBefore->replot();
    }
    else if(type =="after"){
        ui->specterAfter->yAxis->setRange(0, 20000);
        QVector<double> freq(spectr.size()/2,0);
        for(int i = 0; i < freq.size(); i++){
            freq[i] = static_cast<double>(i)/freq.size()*(freqSamp/2);
        }
        QVector<double> qSpectr(spectr.size()/2,0);
        std::vector<double>spectrReal(spectr.begin(), spectr.begin()+ spectr.size()/2);
        qSpectr = VectorToQVector(spectrReal);
        ui->specterAfter->addGraph();
        ui->specterAfter->graph(0)->setData(freq, qSpectr);
        ui->specterAfter->graph(0)->setPen(QColor(21, 115, 88, 255));//задаем цвет точки
        double maxY = qSpectr[0];
        for (int i=1; i < qSpectr.size(); i++){
           if (qSpectr[i]>maxY) maxY = qSpectr[i];
        }
        ui->specterAfter->yAxis->setRange(0, maxY*1.5);
        ui->specterAfter->replot();
     }
    else{}

}



void MainWindow::on_gainRange1_valueChanged(int value)
{
    ui->gain1->setText(QString::number(value));
    gainArray[0] = pow(10,0.05*static_cast<double>(value));
}

void MainWindow::on_gainRange2_valueChanged(int value)
{
    ui->gain2->setText(QString::number(value));
    gainArray[1] = pow(10,0.05*static_cast<double>(value));
}

void MainWindow::on_gainRange3_valueChanged(int value)
{
    ui->gain3->setText(QString::number(value));
    gainArray[2] = pow(10,0.05*static_cast<double>(value));
}

void MainWindow::on_gainRange4_valueChanged(int value)
{
    ui->gain4->setText(QString::number(value));
    gainArray[3] = pow(10,0.05*static_cast<double>(value));
}


void MainWindow::on_gainRange5_valueChanged(int value)
{
    ui->gain5->setText(QString::number(value));
    gainArray[4] = pow(10,0.05*static_cast<double>(value));
}

void MainWindow::on_gainRange6_valueChanged(int value)
{
    ui->gain6->setText(QString::number(value));
    gainArray[5] = pow(10,0.05*static_cast<double>(value));
}


void MainWindow::on_gainRange7_valueChanged(int value)
{
    ui->gain7->setText(QString::number(value));
    gainArray[6] = pow(10,0.05*static_cast<double>(value));
}


void MainWindow::on_gainRange8_valueChanged(int value)
{
    ui->gain8->setText(QString::number(value));
    gainArray[7] = pow(10,0.05*static_cast<double>(value));
}



void MainWindow::on_gainRange9_valueChanged(int value)
{
    ui->gain9->setText(QString::number(value));
    gainArray[8] = pow(10,0.05*static_cast<double>(value));
}


void MainWindow::on_gainRange10_valueChanged(int value)
{
    ui->gain10->setText(QString::number(value));
    gainArray[9] = pow(10,0.05*static_cast<double>(value));
}


void MainWindow::on_loadFile_clicked()
{
    QDir path;
    path.cdUp();

    fileName = QFileDialog::getOpenFileName(
                this,
                tr("Выбрите файл"),
                path.absolutePath() + "/Equlaizer/files",
                "Text files (*.txt);; Data files (*.dat);; Wave file (*.wav)"
                );
    ui->filePath->setText(fileName);
    if (!fileName.isEmpty()){
        ui->start->setEnabled(true);
    }
}
void MainWindow::on_start_clicked(bool checked)
{
    if(!checked){
        ui->statusBar->showMessage("кнопка отжата");
        ui->start->setStyleSheet(
                                  "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(44, 62, 80, 255), stop:1 rgba(71, 161, 175, 255));"
                                  "border-style: outset;"
                                  "border-width: 2px;"
                                  "border-color: rgb(0, 135, 106);"
                                  "border-radius: 8px"
                                  );
        ui->start->setText("FILTER");
    }
    else{
        ui->statusBar->showMessage("кнопка нажата");
        ui->start->setStyleSheet(
                                  "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.111732 rgba(29, 47, 63, 255), stop:1 rgba(38, 70, 86, 255));"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: rgb(0, 135, 106);"
                                  "border-radius: 8px;"
                                  "color: rgb(0, 135, 106);"
                                  );
         ui->start->setText("FILTERING");

         std::vector<double> fromFile;
         std::string tmp;
         tmp = fileName.toStdString();
         std::ifstream inputFile(fileName.toStdString());
         std::istream_iterator<double> input(inputFile);
         std::copy(input, std::istream_iterator<double>(), std::back_inserter(fromFile));
         std::vector<double> spectrIn(fromFile.size());
         spectrIn = FFTAnalysis(fromFile,fromFile.size(), fromFile.size());
         PlotSpectr(spectrIn, "before");
         std::vector<double> signalFiltered(spectrIn.size()), spectrOut(spectrIn.size());
         signalFiltered = WorkEqulaizer(fromFile);
         spectrOut = FFTAnalysis(signalFiltered,signalFiltered.size(), signalFiltered.size());
         PlotSpectr(spectrOut, "after");



         ui->start->setChecked(false);
         ui->statusBar->showMessage("кнопка отжата");
         ui->start->setStyleSheet(
                                   "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(44, 62, 80, 255), stop:1 rgba(71, 161, 175, 255));"
                                   "border-style: outset;"
                                   "border-width: 2px;"
                                   "border-color: rgb(0, 135, 106);"
                                   "border-radius: 8px"
                                   );
         ui->start->setText("FILTER");

    }
}



void MainWindow::on_loadFile_pressed()
{
    ui->loadFile->setStyleSheet(
                              "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.111732 rgba(50, 63, 75, 255), stop:1 rgba(60, 99, 116, 255));"
                              "border-style: outset;"
                              "border-width: 3px;"
                              "border-color: rgb(0, 135, 106);"
                              "border-radius: 8px;"
                              "color: rgb(0, 135, 106);"
                              );
}



void MainWindow::on_loadFile_released()
{
    ui->loadFile->setStyleSheet(
                              "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(44, 62, 80, 255), stop:1 rgba(71, 161, 175, 255));"
                              "border-style: outset;"
                              "border-width: 2px;"
                              "border-color: rgb(0, 135, 106);"
                              "border-radius: 8px"
                              );
}


