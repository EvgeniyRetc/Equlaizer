#include "myFilter.h"
#include "math.h"
#include <omp.h>
Filter::Filter(std::vector <double> frequencies_, uint32_t freqSampling_, int order_, TypeOfFilter typeOfFilter_) {
	frequencies = frequencies_;
	typeOfFilter = typeOfFilter_;
	order = order_;
	freqSampling = freqSampling_;
	uint32_t N = frequencies.size();
	std::vector <double> freqNorm(N);
	for (uint32_t i = 0; i < frequencies.size(); i++ ){
		freqNorm[i] = frequencies[i]/freqSampling;
	}
	impulseResponse.assign(order, 0.0);
	CreateImpulseResponse(freqNorm);
}
Filter::Filter() {
	std::vector<double> freqTmp;
	frequencies = freqTmp;
	typeOfFilter = lowpass;
	order = 0;
	freqSampling = 0;
	impulseResponse.assign(order, 0.0);
}
void Filter::SetParams(std::vector <double> frequencies_, uint32_t freqSampling_, int order_, TypeOfFilter typeOfFilter_) {
	frequencies = frequencies_;
	typeOfFilter = typeOfFilter_;
	order = order_;
	freqSampling = freqSampling_;
	uint32_t N = frequencies.size();
	std::vector <double> freqNorm(N);
	for (uint32_t i = 0; i < frequencies.size(); i++) {
		freqNorm[i] = frequencies[i] / freqSampling;
	}
	impulseResponse.assign(order, 0.0);
	CreateImpulseResponse(freqNorm);
}


void Filter::CreateImpulseResponse(std::vector <double> frequencies_){
	int cntr = order/2 + order%2; // находим индекс центрального 3центральный элемент 
	std::vector <double> W(order); // весовая функция Блэкмана
	double fCut, fLow, fHigh;
	switch (typeOfFilter){
		//************  LOWPASS ************
		case lowpass:
			if (frequencies_.size() != 1){
				throw std::invalid_argument("wrong number of frequencies");
			}
			fCut = frequencies_[0];
			for(int i = 0; i < order; i++){
				if (i != cntr){
					impulseResponse[i] = sin(2*PI*fCut*(i - cntr))/(PI*(i - cntr));
                }
				else{
					impulseResponse[i] = 2*fCut;
				}
				W[i] = 0.42 - 0.5*cos(2*PI*(i - cntr)/(order - 1)) + 0.8*cos(4*PI*(i - cntr)/(order - 1));// весовая функция Блэкмана
				impulseResponse[i] = impulseResponse[i]*W[i];
			} 
			break;

		// ************ HIGHPASS ************
		case highpass:
			if (frequencies_.size() != 1){
				throw std::invalid_argument("wrong number of frequencies");
			}
			fCut = frequencies_[0];
			for(int i = 0; i < order; i++){
				if (i != cntr){
					impulseResponse[i] = -sin(2*PI*fCut*(i - cntr))/(PI*(i - cntr));	
				}
				else{
					impulseResponse[i] = 1 - 2*fCut;
				}
				W[i] = 0.42 - 0.5*cos(2*PI*(i - cntr)/(order - 1)) + 0.8*cos(4*PI*(i - cntr)/(order - 1));
				impulseResponse[i] = impulseResponse[i]*W[i];
			} 
			break;
		// ************ PASSBAND ************
		case passband:
			if (frequencies_.size() != 2){
				throw std::invalid_argument("wrong number of frequencies");
			}
			if (frequencies_[0] < frequencies_[1]){
				fLow  = frequencies_[0];
				fHigh = frequencies_[1];
			}else{
				fLow  = frequencies_[1];
				fHigh = frequencies_[0];	
			}
			for(int i = 0; i < order; i++){
				if (i != cntr){
					impulseResponse[i] = sin(2*PI*fHigh*(i - cntr))/(PI*(i - cntr))  - sin(2*PI*fLow*(i - cntr))/(PI*(i - cntr));	
				} 
				else{
					impulseResponse[i] = 2*(fHigh - fLow);
				}
				W[i] = 0.42 - 0.5*cos(2*PI*(i - cntr)/(order - 1)) + 0.8*cos(4*PI*(i - cntr)/(order - 1));
				impulseResponse[i] = impulseResponse[i]*W[i];
				
			} 
			break;
		// ************ STOPBAND ************
		case stopband:
			if (frequencies_.size() != 2){
				throw std::invalid_argument("wrong number of frequencies");
			}
			if (frequencies_[0] < frequencies_[1]){
				fLow  = frequencies_[0];
				fHigh = frequencies_[1];
			}else{
				fLow  = frequencies_[1];
				fHigh = frequencies_[0];	
			}
			for(int i = 0; i < order; i++){
				if (i != cntr){
					impulseResponse[i] = sin(2*PI*fLow*(i - cntr))/(PI*(i - cntr))  - sin(2*PI*fHigh*(i - cntr))/(PI*(i - cntr));	
				}
				else{
					impulseResponse[i] = 1 - 2*(fHigh - fLow);
				}
				W[i] = 0.42 - 0.5*cos(2*PI*(i- cntr)/(order - 1)) + 0.8*cos(4*PI*(i - cntr)/(order - 1));
				impulseResponse[i] = impulseResponse[i]*W[i]; 
			} 
			break;
	}
	ScaleFilter();
}

std::vector<double> Filter::GetImpulseResponse() {
	return impulseResponse;
}

int Filter::GetOrder() {
	return order;
}

void Filter::ScaleFilter() {
	double tmpSin = 0;
	double tmpCos = 0;
	double coef = 1;
	double f0;
	switch (typeOfFilter){
		case lowpass:
			coef = 0;
			for (int i = 0; i < order; i++) {
				coef += impulseResponse[i];
			}
			break;
		case highpass:
			f0 = 1;
			for (int i = 0; i < order; i++) {
				tmpCos += cos(2 * PI*i*f0/2)*impulseResponse[i];
				tmpSin -= sin(2 * PI*i*f0/2)*impulseResponse[i];
			}
			coef = sqrt(tmpCos*tmpCos + tmpSin * tmpSin);
			break;
		case passband:
			if (frequencies[0] < frequencies[1]) {
				f0 = (frequencies[1] + frequencies[0])/freqSampling/2;
			}
			else {
				f0 = (frequencies[0] + frequencies[1])/freqSampling/2;
			}
			
			for (int i = 0; i < order; i++) {
				tmpCos += cos(2 * PI*i*f0)*impulseResponse[i];
				tmpSin -= sin(2 * PI*i*f0)*impulseResponse[i];
			}
			coef = sqrt(tmpCos*tmpCos + tmpSin * tmpSin);
			break;
		case stopband:
			coef = 0;
			for (int i = 0; i < order; i++) {
				coef += impulseResponse[i];
			}
			break;
		default:
			break;
	}
	for (int i = 0; i < order; i++) {
		impulseResponse[i] = impulseResponse[i]/coef;
	}

}

