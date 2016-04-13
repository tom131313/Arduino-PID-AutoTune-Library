#ifndef RUNNINGSTATS_H_
#define RUNNINGSTATS_H_

#include <stdio.h> // for the print methods' FILE type and fprintf function

//This file includes both the Running Stats and Running Regression routines

// http://www.johndcook.com/skewness_kurtosis.html

//RunningStats.h
 
/*
Computing skewness and kurtosis in one pass
The code is an extension of the method of Knuth and Welford for computing standard deviation
in one pass through the data. It computes skewness and kurtosis as well with a similar interface.
In addition to only requiring one pass through the data, the algorithm is numerically stable and accurate.

To use the code, create a RunningStats object and use the Push method to insert data values. After
accruing your data, you can obtain sample statistics by calling one of these methods:

•Mean
•Variance
•StandardDeviation
•Skewness
•Kurtosis
You can also combine two RunningStats objects by using the + and += operators. For example, you might
accrue data on several different threads in parallel then add their RunningStats objects together to
create a single object with the state that it would have had if all the data had been accumulated by it
alone.
References:

1.Wikipedia
2.Timothy B. Terriberry. Computing Higher-Order Moments Online.
3.Philippe Pébay. SANDIA REPORT SAND2008-6212 (2008). Formulas for Robust, One-Pass Parallel Computation
 of Co- variances and Arbitrary-Order Statistical Moments.

*/

/*  EXAMPLE
		#include <stats_running.h>
		
		RunningStats sumit;        // construct statistics object
		RunningRegression aLine;   // construct regression object

		fprintf(stdout, "%d, %f\n",i, xm);  // print data point - assumes xm was set above here
		sumit.Push(xm);            // add data point to statistical routine
		aLine.Push(xm, 1.);        // add data point to regression routine - this example assumes data are flat line at 1 (y = 1.) otherwise enter a y value
		
		sumit.Print(stdout, "Raw Signal");  // print statistics
		aLine.Print(stdout, "raw signal regression line vs 1.");  // print regression
*/

class RunningStats{
public:
    RunningStats();
	virtual ~RunningStats();
    void Clear();
    void Push(double x);
    long NumDataValues() const;
    double Mean() const;
    double Variance() const;
    double StandardDeviation() const;
    double Skewness() const;
    double Kurtosis() const;
    double Maximum() const;
    double Minimum() const;
    virtual void Print(FILE * pFile, const char * header) const;
    friend RunningStats operator+(const RunningStats a, const RunningStats b);
    RunningStats& operator+=(const RunningStats &rhs);
private:
    long n;
    double M1, M2, M3, M4;
    double maxdata, mindata;
};
//#endif

//RunningStats.cpp

//#include "RunningStats.h"
//#include <cmath>
//#include <vector>

//http://www.johndcook.com/running_regression.html

// RunningRegression.h

/*
Computing linear regression in one pass
The RunningRegression class is the analog of the RunningStats class described here and uses that class.
You add pairs of (x, y) values by using the Push. At any point along the way you can call the Slope,
Intercept, or Correlation functions to see the current value of these statistics.

You can also combine two RunningRegression objects by using the + and += operators. For example, you might
accrue data on several different threads in parallel then add their RunningRegression objects together.
*/

//#include "RunningStats.h"

class RunningRegression
{
public:
    RunningRegression();
	virtual ~RunningRegression();
    void Clear();
    void Push(double x, double y);
    long NumDataValues() const;
    double Slope() const;
    double Intercept() const;
    double Correlation() const;
    virtual void Print(FILE * pFile, const char *  header) const;
    friend RunningRegression operator+(        const RunningRegression a, const RunningRegression b);
    RunningRegression& operator+=(const RunningRegression &rhs);
private:
    RunningStats x_stats;
    RunningStats y_stats;
    double S_xy;
    long n;
};

class RunningLeastSquares
{

// y = Ax^B 	

// y = A + Blogx
 
// y = Ae^Bx

public:
    RunningLeastSquares();
	virtual ~RunningLeastSquares();
    void Clear();
    void Push(double x, double y);
    long NumDataValues() const;
    double Power_A() const;
    double Power_B() const;
	double Power_Correlation() const;
    double Logarithmic_A() const;
    double Logarithmic_B() const;
    double Exponential_A() const;
    double Exponential_B() const;
    virtual void Print(FILE * pFile, const char *  header) const;
private:
    long n;
    double S_LogxLogy;
    double S_Logx;
    double S_Logy;
    double S_yLogx;
    double S_LogxSqr;
    double S_LogySqr;
    double S_y;
    double S_xSqry;
    double S_yLogy;
    double S_xy;
    double S_xyLogy;
};
#endif
