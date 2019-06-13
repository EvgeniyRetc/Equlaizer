#pragma once
#include <vector>
const double PI = 3.14159265359;
enum TypeOfFilter { lowpass, highpass, passband, stopband };
class Filter{
public:
    Filter();
    Filter(std::vector <double> &frequencies_, uint32_t freqSampling_, int order_, TypeOfFilter typeOfFilter_);
    std::vector<double> GetImpulseResponse();
    int GetOrder();
    void SetParams(std::vector <double> &frequencies_, uint32_t freqSampling_, int order_, TypeOfFilter typeOfFilter_);
private:
    TypeOfFilter typeOfFilter;
    std::vector <double> impulseResponse;
    std::vector <double> frequencies;
    uint32_t freqSampling;
    int order;
    void CreateImpulseResponse(std::vector <double> &frequencies_);
    void CreateLowpass(std::vector <double> &frequencies_, std::vector <double> &W, int cntr);
    void CreateHighpass(std::vector <double> &frequencies_, std::vector <double> &W, int cntr);
    void CreatePassband(std::vector <double> &frequencies_, std::vector <double> &W, int cntr);
    void CreateStopband(std::vector <double> &frequencies_, std::vector <double> &W, int cntr);
    void ScaleFilter();

};
