#include "histogram.h"
Histogram::Histogram(size_t l):n(l > 0 ? l : 200), bin(new unsigned int[l > 0 ? l : 200]) {
	memset(bin, 0, n*4);
}

void Histogram::setMinMax(double minrange, double maxrange) {
	min = minrange < maxrange ? minrange : maxrange;
	max = maxrange > minrange ? maxrange : minrange;
	
	memset(bin, 0, n*4);
}

Histogram::~Histogram() {
	delete [] bin;
}

void Histogram::setLength(size_t l) {
	if(l > n) {
		delete [] bin;
		bin = new unsigned int[l];
	}
	n = l;
	memset(bin, 0, l*4);
}

size_t Histogram::getLength() {
	return n;
}

double Histogram::getMax() {
	return max;
}

double Histogram::getMin() {
	return min;
}

unsigned int& Histogram::operator[](const unsigned int& i) const {
	return bin[i];
}

void Histogram::increment(double i) {
	if( i < min || i > max )
		return;
	
	bin[(size_t)((i - min)/(max - min)*((double)n - 1) + 0.5)]++;
	emit updated();
}
