#include "mainwindow.h"
#include <QApplication>
#include "myFilter.h"
#include <vector>
#include <array>

const int NUMBER_OF_CHANNELS = 10;


void InitEqulaizer(std::array <Filter,NUMBER_OF_CHANNELS > & equlaizer_, uint32_t freqSamp_) {
    int order = 1024;
    std::vector <double> freq0 = {200};
    equlaizer_[0].SetParams(freq0, freqSamp_, order, lowpass);
    std::vector <double> freq1 = {200, 400};
    equlaizer_[1].SetParams(freq1, freqSamp_, order, passband);
    std::vector <double> freq2 = { 400, 800 };
    equlaizer_[2].SetParams(freq2, freqSamp_, order, passband);
    std::vector <double> freq3 = { 800, 1500 };
    equlaizer_[3].SetParams(freq3, freqSamp_, order, passband);
    std::vector <double> freq4 = { 1500, 3000 };
    equlaizer_[4].SetParams(freq4, freqSamp_, order, passband);
    std::vector <double> freq5 = { 3000, 5000 };
    equlaizer_[5].SetParams(freq5, freqSamp_, order, passband);
    std::vector <double> freq6 = { 5000, 7000 };
    equlaizer_[6].SetParams(freq6, freqSamp_, order, passband);
    std::vector <double> freq7 = { 7000, 10000 };
    equlaizer_[7].SetParams(freq7, freqSamp_, order, passband);
    std::vector <double> freq8 = { 10000, 15000 };
    equlaizer_[8].SetParams(freq8, freqSamp_, order, passband);
    std::vector <double> freq9 = { 15000 };
    equlaizer_[9].SetParams(freq9, freqSamp_, order, highpass);
}

int main(int argc, char *argv[])
{

    uint32_t freqSamp = 44e3;
    std::array <Filter, NUMBER_OF_CHANNELS> equlaizer;
    InitEqulaizer(equlaizer, freqSamp);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
