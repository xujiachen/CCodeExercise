// 分别用梯度下降法和牛顿法求x*sin(x)极值,范围端点正好取到极值点时可能会出错

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

double big = DBL_MIN;
double small = DBL_MAX;
double rec_x1 = 0;
double rec_x2 = 0;
const double left = -6.0;
const double right = 8.0;

double Derivatives(double x) {
	return sin(x) + x * cos(x);
}

double D2(double x) {
	return 2 * cos(x) - x * sin(x); 
}
//注意：求的是一阶导为0的点，不是y/Derivatives(x)
double Newton(double x) {
	return x - Derivatives(x) / D2(x);
}

double Gradient(double x, double alpha) {
	return x - alpha * Derivatives(x);
}

double getValue(double x) {
	return x * sin(x);
}

void Newton_Train(double x1, double x2) {
	double d1 = Derivatives(x1) / D2(x1);
	double d2 = Derivatives(x2) / D2(x2);
	int i = 0;
	while (fabs(d1) > 0.0001 || fabs(d2) > 0.0001) {
		i++;
		if (x1 < left) {
			x1 = x1 + i * 0.2;
		}
		if (x1 > right) {
			break;
		}
		if (x2 > right) {
			x2 = x2 - i * 0.2;
		}
		if (x2 < left) {
			break;
		}

		if (fabs(d1) > 0.0001 && x1 >= left && x1 <= right) {
			double y1 = getValue(x1);
            if (y1 < small) {
		    	small = y1;
		    	rec_x1 = x1;
	    	}
	    	else if (y1 > big) {
		    	big = y1;
		    	rec_x2 = x1;
		    }
		    x1 = Newton(x1);
	      	d1 = Derivatives(x1) / D2(x1);
		}
		if (fabs(d2) > 0.0001 && x2 >= left && x2 <= right) {
		    double y2 = getValue(x2);
	     	if (y2 < small) {
		    	small = y2;
		    	rec_x1 = x2;
	    	}
	    	else if (y2 > big) {
		    	big = y2;
		    	rec_x2 = x2;
	    	}		
			x2 = Newton(x2);
			d2 = Derivatives(x2) / D2(x2);
		}
		printf("%d: \n", i);
		printf("biggest %lf x: %lf\n", big, x2);
		printf("smallest %lf x: %lf\n", small, x1);
		printf("d1: %lf  d2: %lf\n", d1, d2);
    }
}
//  取多点，跳值
void Gradient_Train(double x1, double x2, double alpha) {
	double d1 = Derivatives(x1);
	double d2 = Derivatives(x2);
	double old1 = 0;
	double old2 = 0;
	double alpha1 = alpha;
	double alpha2 = alpha;
	int i = 0;
	while (fabs(d1) > 0.001 || fabs(d2) > 0.001) {
		i++;
//		printf("d1: %lf  d2: %lf\n", d1, d2);
		if (x1 < left) {
			x1 = x1 + 0.02 * i;
		}
		if (x1 > right) {
			break;
		}
		if (x2 > right) {
			x2 = x2 - 0.02 * i;
		}
		if (x2 < left) {
			break;
		}
		if (fabs(d1) > 0.001 && x1 >= left && x1 <= right) {
        	double y1 = getValue(x1);
	    	if (y1 < small) {
		    	small = y1;
		    	rec_x1 = x1;
	    	}
	    	else if (y1 > big) {
		    	big = y1;
		    	rec_x2 = x1;
	    	}		
			x1 = Gradient(x1, alpha1);
			d1 = Derivatives(x1);
			if (old1 * d1 < 0) {
				alpha1 /= 3;
			}
			old1 = d1;
		}
		if (fabs(d2) > 0.001 && x2 >= left && x2 <= right) {
            double y2 = getValue(x2);
		    if (y2 < small) {
		    	small = y2;
		    	rec_x1 = x2;
	    	}
	    	else if (y2 > big) {
		    	big = y2;
		    	rec_x2 = x2;
	    	}	
			x2 = Gradient(x2, alpha2);
			d2 = Derivatives(x2);
			if (old2 * d2 < 0) {
				alpha2 /= 3; 
			}
			old2 = d2;
		}
		printf("%d: \n", i);
		printf("biggest %lf x: %lf\n", big, rec_x2);
		printf("smallest %lf x: %lf\n", small, rec_x1);
	}

}

int main() {
	double alpha = 0.01;
	double x1 = left;
	double x2 = right;

	printf("Gradient:\n");
	Gradient_Train(x1, x2, alpha);

	x1 = left;
	x2 = right;
	big = DBL_MIN;	
	small = DBL_MAX;
	rec_x1 = 0;
	rec_x2 = 0;
	printf("Newton:\n");
	Newton_Train(x1, x2);

	return 0;
}

