 #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myFilter.h"
#include <QLinearGradient>
#include "qcustomplot.h"
#include <array>
#include <fstream>
#include <iterator>
#include <sstream>
#include <math.h>



const int ORDER = 1024;
const int NUM_OF_CHANNEL = 10;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_gainRange1_valueChanged(int value);

    void on_gainRange2_valueChanged(int value);

    void on_gainRange3_valueChanged(int value);

    void on_gainRange4_valueChanged(int value);

    void on_gainRange5_valueChanged(int value);

    void on_gainRange6_valueChanged(int value);

    void on_gainRange10_valueChanged(int value);

    void on_gainRange7_valueChanged(int value);

    void on_gainRange8_valueChanged(int value);

    void on_gainRange9_valueChanged(int value);

    void on_loadFile_clicked();

    void on_start_clicked(bool checked);

    void on_loadFile_pressed();

    void on_loadFile_released();


private:
    Ui::MainWindow *ui;
    std::array<Filter, NUM_OF_CHANNEL> Equlaizer;
    QString fileName;
    std::array<double, NUM_OF_CHANNEL> gainArray = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int freqSamp = 44000;
    void InitEqulaizer();

    std::vector<double> Filtering(std::vector<double> signalIn_, Filter filter_, double gain_);
    std::vector<double> SumOfChannel(std::vector<std::vector<double> > signalOnChannel_);
    std::vector<double> FFTAnalysis(std::vector<double> signalIn, int numOfElements, int Nft);
    std::vector<double> WorkEqulaizer(std::vector<double> signalIn_);
    void PlotSpectr(std::vector<double> spectr, QString type);



};

#endif // MAINWINDOW_H
