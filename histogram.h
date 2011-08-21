#ifndef _HISTOGRAM_H_
#define _HISTOGRAM_H_

#include <iostream>

using namespace std;

#include <QtCore/QObject>

class Histogram : public QObject {
	Q_OBJECT
	
	double min, max;
	size_t n;
	unsigned int* bin;
	
	public:
		Histogram(size_t l=200);
		~Histogram();
		
		void setMinMax(double,double);
		
		double getMin();
		double getMax();
		
		void setLength(size_t l);
		size_t getLength();
		
		void increment(double);
		unsigned int& operator[](const unsigned int& i) const;
		
	signals:
		void updated();
};


#endif
