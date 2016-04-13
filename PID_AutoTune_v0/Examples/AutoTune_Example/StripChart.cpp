#include "StripChart.h"
#include <iostream>
#include <stdio.h>
#include <float.h> // to initialize max and min
#include <math.h>
#include <string.h>

StripChart::StripChart(double aStrip_Center_1, double aStrip_Minimum_2, double aStrip_Maximum_2):
// left chart auto scales around the given center (argument 1)
// right chart is fixed by the given minimum and given maximum (arguments 2 and 3)
	Strip_Center_1(aStrip_Center_1), Strip_Minimum_2(aStrip_Minimum_2), Strip_Maximum_2(aStrip_Maximum_2)
    {
    std::cout << __FILE__ << " " <<__DATE__ << " " << __TIME__ << " " << __PRETTY_FUNCTION__ << " line:" << __LINE__ << std::endl;
    Strip_Maximum_1 = -DBL_MAX;
    Strip_Minimum_1 = DBL_MAX;
    printf("[Time msecs] [PV chart min, PV value, PV chart max, PV chart] [Controller chart, Controller chart min, Controller value, Controller chart max]\n");

    }

void StripChart::PrintStripChart(unsigned long Time, double Strip_Data_1, double Strip_Data_2)
// millisecond time value (argument 1)
// left and right chart data (arguments 2 and 3)
    {
    char Strip_Graph_1[24], Strip_Graph_2[24];
    int Strip_Normalized_1, Strip_Normalized_2;
    double Strip_Span_1;
    double Strip_MaxSpan_1, Strip_MinSpan_1;
    double Strip_Span_2, Strip_Center_2;
	
    // graphing Strip_Data_1 =========================================================================
    	strcpy(Strip_Graph_1, " ..........+.......... ");

    	if (Strip_Maximum_1 < Strip_Data_1) Strip_Maximum_1 = Strip_Data_1;
    	if (Strip_Minimum_1 > Strip_Data_1) Strip_Minimum_1 = Strip_Data_1;

    	Strip_MaxSpan_1 = Strip_Maximum_1 - Strip_Center_1;
    	Strip_MinSpan_1 = Strip_Center_1 - Strip_Minimum_1;

    	Strip_Span_1 = 2.* ( fabs(Strip_MaxSpan_1) > fabs(Strip_MinSpan_1)
    		? fabs(Strip_MaxSpan_1) : fabs(Strip_MinSpan_1) );
    	if (Strip_Span_1 == 0) Strip_Span_1 = 1.; // handle first point
    	Strip_Normalized_1 = (int)( ((Strip_Data_1 - Strip_Center_1) > 0 ? .25 : -.25) + 21.*(Strip_Data_1 - Strip_Center_1) / Strip_Span_1);
    	if      (Strip_Normalized_1 < -10) Strip_Graph_1[ 0] = 'X'; // not used if auto max/min to the data
    	else if (Strip_Normalized_1 > +10) Strip_Graph_1[22] = 'X';
    	else                      Strip_Graph_1[11+Strip_Normalized_1] = 'O';
    	// end graphing Strip_Data_1 =====================================================================

    // graphing Strip_Data_2 ========================================================================
    	strcpy(Strip_Graph_2, " ..........+.......... ");
    	Strip_Span_2 = Strip_Maximum_2 - Strip_Minimum_2;
    	Strip_Center_2 = Strip_Minimum_2 + Strip_Span_2/2.;
    	Strip_Normalized_2 = (int)( ((Strip_Data_2 - Strip_Center_2) > 0 ? .25 : -.25) + 21.*(Strip_Data_2 - Strip_Center_2) / Strip_Span_2 );
    	if      (Strip_Normalized_2 < -10) Strip_Graph_2[ 0] = 'X';
    	else if (Strip_Normalized_2 > +10) Strip_Graph_2[22] = 'X';
    	else                      Strip_Graph_2[11+Strip_Normalized_2] = 'O';
    	// end graphing Strip_Data_2 ====================================================================


    // print the graphs =======================================================================
      printf ( "%7lu %8.3f %8.3f %8.3f", Time, Strip_Center_1-(Strip_Span_1/2.), Strip_Data_1, Strip_Center_1+(Strip_Span_1/2.));
      std::cout << "\t" << Strip_Graph_1<< " " << Strip_Graph_2;
      printf ( " %8.3f %8.3f %8.3f", Strip_Minimum_2, Strip_Data_2, Strip_Maximum_2);

    	// end print the graphs ===================================================================
      }



