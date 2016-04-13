#include "stats_running.h"
#include <stdio.h>
#include <float.h> // to initialize max and min
#include <math.h>

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

RunningStats::RunningStats()
    {
    Clear();
    }
RunningStats::~RunningStats()
    {
    }
void RunningStats::Clear()
    {
    n = 0;
    M1 = M2 = M3 = M4 = 0.0;
    maxdata = -DBL_MAX;
    mindata =  DBL_MAX;
    }
void RunningStats::Push(double x)
    {
    double delta, delta_n, delta_n2, term1;
    long n1 = n;
    n++;
    delta = x - M1;
    delta_n = delta / n;
    delta_n2 = delta_n * delta_n;
    term1 = delta * delta_n * n1;
    M1 += delta_n;
    M4 += term1 * delta_n2 * (n*n - 3*n + 3) + 6 * delta_n2 * M2 - 4 * delta_n * M3;
    M3 += term1 * delta_n * (n - 2) - 3 * delta_n * M2;
    M2 += term1;
    if (maxdata < x) maxdata = x;
    if (mindata > x) mindata = x;
    }
long RunningStats::NumDataValues() const
    {
    return n;
    }
double RunningStats::Mean() const
    {
    return M1;
    }
double RunningStats::Variance() const
    {
    return M2/(n-1.0);
    }
double RunningStats::StandardDeviation() const
    {
    return sqrt( Variance() );
    }
double RunningStats::Skewness() const
    {
    return sqrt(double(n)) * M3/ pow(M2, 1.5);
    }
double RunningStats::Kurtosis() const
    {
    return double(n)*M4 / (M2*M2) - 3.0;
    }
RunningStats operator+(const RunningStats a, const RunningStats b)
    {
    RunningStats combined;
    combined.n = a.n + b.n;
    double delta = b.M1 - a.M1;
    double delta2 = delta*delta;
    double delta3 = delta*delta2;
    double delta4 = delta2*delta2;
    combined.M1 = (a.n*a.M1 + b.n*b.M1) / combined.n;
    combined.M2 = a.M2 + b.M2 + delta2 * a.n * b.n / combined.n;
    combined.M3 = a.M3 + b.M3 + delta3 * a.n * b.n * (a.n - b.n)/(combined.n*combined.n);
    combined.M3 += 3.0*delta * (a.n*b.M2 - b.n*a.M2) / combined.n;
    combined.M4 = a.M4 + b.M4 + delta4*a.n*b.n * (a.n*a.n - a.n*b.n + b.n*b.n) /
	    (combined.n*combined.n*combined.n);
    combined.M4 += 6.0*delta2 * (a.n*a.n*b.M2 + b.n*b.n*a.M2)/
	    (combined.n*combined.n) + 4.0*delta*(a.n*b.M3 - b.n*a.M3) / combined.n;
    combined.maxdata = a.maxdata > b.maxdata ? a.maxdata : b.maxdata;
    combined.mindata = a.mindata < b.mindata ? a.mindata : b.mindata;
    return combined;
    }
RunningStats& RunningStats::operator+=(const RunningStats& rhs)
    {
    RunningStats combined = *this + rhs;
    *this = combined;
    return *this;
    }
double RunningStats::Maximum() const
    {
    return maxdata;
    }
double RunningStats::Minimum() const
    {
    return mindata;
    }
void RunningStats::Print(FILE * pFile, const char * header) const
    {
    fprintf (pFile, "\n%s\n", header);
    fprintf (pFile, "NumDataValues:     %ld\n", NumDataValues());
    fprintf (pFile, "Mean:              %f\n", Mean());
    fprintf (pFile, "Variance:          %f\n", Variance());
    fprintf (pFile, "StandardDeviation: %f\n", StandardDeviation());
    fprintf (pFile, "Skewness:          %f\n", Skewness());
    fprintf (pFile, "Kurtosis:          %f\n", Kurtosis());
    fprintf (pFile, "Maximum:           %f\n", Maximum());
    fprintf (pFile, "Minimum:           %f\n", Minimum());
    return;
    }

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

RunningRegression::RunningRegression()
    {
    Clear();
    }
RunningRegression::~RunningRegression()
    {
    }
void RunningRegression::Clear()
    {
    x_stats.Clear();
    y_stats.Clear();
    S_xy = 0.0;
    n = 0;
    }
void RunningRegression::Push(double x, double y)
    {
    S_xy += (x_stats.Mean() -x)*(y_stats.Mean() - y)*double(n)/double(n+1);
    x_stats.Push(x);
    y_stats.Push(y);
    n++;
    }
long RunningRegression::NumDataValues() const
    {
    return n;
    }
double RunningRegression::Slope() const
    {
    double S_xx = x_stats.Variance()*(n - 1.0);
    return S_xy / S_xx;
    }
double RunningRegression::Intercept() const
    {
    return y_stats.Mean() - Slope()*x_stats.Mean();
    }
double RunningRegression::Correlation() const
    {
    double t = x_stats.StandardDeviation() * y_stats.StandardDeviation();
    return S_xy / ( (n-1) * t );
    }
RunningRegression operator+(const RunningRegression a, const RunningRegression b)
    {
    RunningRegression combined;
    combined.x_stats = a.x_stats + b.x_stats;
    combined.y_stats = a.y_stats + b.y_stats;
    combined.n       = a.n       + b.n;
    double delta_x = b.x_stats.Mean() - a.x_stats.Mean();
    double delta_y = b.y_stats.Mean() - a.y_stats.Mean();
    combined.S_xy = a.S_xy + b.S_xy +         double(a.n*b.n)*delta_x*delta_y/double(combined.n);
    return combined;
    }
RunningRegression& RunningRegression::operator+=(const RunningRegression &rhs)
    {
    RunningRegression combined = *this + rhs;
    *this = combined;
    return *this;
    }
void RunningRegression::Print(FILE * pFile, const char * header) const
    {
    fprintf (pFile, "\n%s\n", header);
    fprintf (pFile, "NumDataValues: %ld\n", NumDataValues());
    fprintf (pFile, "y = A + Bx ==> y = %g %+gx\n", Intercept(), Slope());
    fprintf (pFile, "Slope:           %f\n", Slope());
    fprintf (pFile, "Intercept:       %f\n", Intercept());
    fprintf (pFile, "r^2 Correlation: %f\n", Correlation());
    return;
    }

/*
 3 non-linear least squares fits:

 Power Law    y = Ax^B

 Logarithmic  y = A + Blogx

 Exponenetial y = Ae^Bx

 Look at Wolfram Mathematica site for the equations already worked out
 */

RunningLeastSquares::RunningLeastSquares()
    {
    Clear();
    }
RunningLeastSquares::~RunningLeastSquares()
    {
    }
void RunningLeastSquares::Clear()
    {
    n = 0;
    S_LogxLogy = 0.0;
    S_LogxSqr = 0.0;
    S_LogySqr = 0.0;
    S_Logx = 0.0;
    S_Logy = 0.0;
    S_yLogx = 0.0;
    S_y = 0.0;
    S_xSqry = 0.0;
    S_yLogy = 0.0;
    S_xy = 0.0;
    S_xyLogy = 0.0;
    }

void RunningLeastSquares::Push(double x, double y)
    {
    n++;
    S_LogxLogy += log(x) * log(y);
    S_LogxSqr += pow(log(x), 2);
    S_LogySqr += pow(log(y), 2);
    S_Logx += log(x);
    S_Logy += log(y);
    S_yLogx += y * log(x);
    S_y += y;
    S_xSqry += pow(x, 2) * y;
    S_yLogy += y * log(y);
    S_xy += x * y;
    S_xyLogy += x * y * log(y);
    }
	
long RunningLeastSquares::NumDataValues() const
    {
    return n;
    }

double RunningLeastSquares::Power_A() const
    {
    return exp((S_Logy - Power_B() * S_Logx) / n);
    }

double RunningLeastSquares::Power_B() const
    {
    return (n * S_LogxLogy - S_Logx * S_Logy) / (n * S_LogxSqr - pow(S_Logx, 2));
    }

	double RunningLeastSquares::Power_Correlation() const
    {
    return pow((n*S_LogxLogy - S_Logx*S_Logy), 2)/((n*S_LogxSqr - pow(S_Logx, 2)) * (n*S_LogySqr - pow(S_Logy, 2) ));
    }
	
double RunningLeastSquares::Logarithmic_A() const
    {
    return (S_y - Logarithmic_B() * S_Logx) / n;
    }

double RunningLeastSquares::Logarithmic_B() const
    {
    return (n * S_yLogx - S_y * S_Logx) / (n * S_LogxSqr - pow(S_Logx, 2));
    }

double RunningLeastSquares::Exponential_A() const
    {
	// Regular fit equation gives greater weight to small values.
	// It is often better to weight points equally by minimizing SUM(y*(ln(y) - a - b*x)**2) which yields:
    return exp((S_xSqry * S_yLogy - S_xy * S_xyLogy) / (S_y * S_xSqry - pow(S_xy, 2)));
    }

double RunningLeastSquares::Exponential_B() const
    {
	// Regular fit equation gives greater weight to small values.
	// It is often better to weight points equally by minimizing SUM(y*(ln(y) - a - b*x)**2) which yields:
    return (S_y * S_xyLogy - S_xy * S_yLogy) / (S_y * S_xSqry - pow(S_xy, 2));
    }

void RunningLeastSquares::Print(FILE * pFile, const char * header) const
    {
    fprintf (pFile, "\n%s\n", header );
    fprintf (pFile, "NumDataValues: %ld\n", NumDataValues() );
    fprintf (pFile, "y = Ax^B ==> y = %gx^%g   r^2 Correlation: %f\n\n", Power_A(), Power_B(), Power_Correlation() );
    fprintf (pFile, "y = A + Blog(x) ==> y = %g %+gLog(x)\n", Logarithmic_A(), Logarithmic_B() );
    fprintf (pFile, "y = Ae^Bx ==> y = %ge^%gx\n", Exponential_A(), Exponential_B() );
    return;
    }
