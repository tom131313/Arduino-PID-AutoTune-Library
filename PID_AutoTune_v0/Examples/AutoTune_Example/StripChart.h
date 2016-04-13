#include <iostream>
#include <stdio.h>
#include <float.h> // to initialize max and min
#include <math.h>
#include <string.h>

class StripChart
    {
    double Strip_Minimum_1, Strip_Center_1, Strip_Maximum_1;
    double Strip_Minimum_2, Strip_Maximum_2;

 public:
	StripChart(double aStrip_Center_1, double aStrip_Minimum_2, double aStrip_Maximum_2);
	// left chart auto scales around the given center (argument 1)
	// right chart is fixed by the given minimum and given maximum (arguments 2 and 3)

	void PrintStripChart(unsigned long Time, double Strip_Data_1, double Strip_Data_2);
	// millisecond time value (argument 1)
	// left and right chart data (arguments 2 and 3)
    };


