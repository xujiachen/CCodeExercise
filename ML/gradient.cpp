#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

using namespace std;

double Derivatives(double k) {
	return sin(k) + k * cos(k);
}

double Train(double k, double dervvatives, double alpha) {
	return k - alpha * dervvatives;
}

double getVal(double k) {
	return k * sin(k);
}

int main() {
	double alpha1 = 0.01;
	double alpha2 = 0.01;
	double left = 3.0;
	double right = 6.0;
	double big = DBL_MIN;
	double small = DBL_MAX;
	double x1 = 0;
	double x2 = 0;

	double k1 = left;
	double k2 = right;
	double d1 = 100;
	double d2 = 100;
	double old1 = 0;
	double old2 = 0;
	int num = 0;
	while (d1 > 0.001 || d2 > 0.001) {
		num++;
		if (k1 >= left &&  k1 <= right && d1 > 0.001) {
           	double y1 = getVal(k1);
			if (y1 < small) {
				small = y1;
				x1 = k1;
			}
			if (y1 > big) {
				big = y1;
				x2 = k1;
			}
		    d1 = Derivatives(k1);
			if (d1 * old1 < 0) {
				alpha1 /= 3;
			}
			old1 = d1;
		    k1 = Train(k1, d1,alpha1);
		}
		if (k2 >= left &&  k2 <= right && d2 > 0.001) {
			double y2 = getVal(k2);
			if (y2 < small) {
				small = y2;
				x1 = k2;
			}
			if (y2 > big) {
				big = y2;
				x2 = k2;
			}
		    d2 = Derivatives(k2);
			if (d2 * old2 < 0) {
				alpha2 /= 3;
			}
			old2 = d2;
		    k2 = Train(k2, d2, alpha2);
		}
		printf("%d: \n", num);
    	printf("biggest: %lf x: %lf\n", big, x2);
    	printf("smallest: %lf x: %lf\n", small, x1);
	}
	//printf("%d: \n", num);
	//printf("biggest: %lf\n", big);
	//printf("smallest: %lf\n", small);
	return 0;
}

