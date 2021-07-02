//
// GCD.cpp
// ds_hw2_array_gcd
//
#include "GCD.h"
#include<iostream>
#include<stdlib.h>
#include <stdio.h>

using namespace std;

void polcpy(long *A, long *B, int a)
{
	for (int i = 0; i <= a; i++) {
                A[i] = B[i];
        }
}

long gcd(long a, long b)
{
        if (a == 0) {
                return b;
        }
        return gcd(b % a, a);
}

long Lcm(long a, long b)
{
	return a * b / gcd(a, b);
}

void factor(long *C, int n)
{
        long result = C[0];
        for (int i = 1; i <= n; i++) {
                result = gcd(C[i], result);
                if (result == 1) {
                        return;
                }
        }
        for (int i = 0; i <= n; i++) {
                C[i] /= result;
        }
}

void mul(long *A, int n, long t) 
{
	for (int i = n; i >= 0; i--) {
		A[i] *= t;
	}
}

long* GCD::FindGCD(long *in1, long *in2, int deg1, int deg2)
{
        int flag = 0, t, flag2 = 0;
        long temp, lcm, mul1, mul2;
	//make deg1 higher than deg2
	long *T = new long[1000]();
	if (deg1 < deg2 ) {
		polcpy(T, in1, deg1);
		polcpy(in1, in2, deg2);
		polcpy(in2, T, deg1);
		t = deg1;
		deg1 = deg2;
		deg2 = t;
	}
	delete [] T;
        //define quotient and remainder
        int nh_deg, nr_deg;
	long *nh_coeff = new long[1000]();
        long *nr_coeff = new long[1000]();
        
	while(1) {
                flag = 1;
                nr_deg = deg1;
                polcpy(nr_coeff, in1, deg1);
                factor(nr_coeff, nr_deg);
                factor(in2, deg2);
                nh_deg = deg1 - deg2;
                for (int i = nh_deg; i >= 0; i--) {
			if (nr_coeff[nr_deg] % in2[deg2] != 0) {
				factor(nr_coeff, nr_deg);
                		factor(in2, deg2);
				lcm = Lcm(nr_coeff[nr_deg], in2[deg2]);
				mul1 = lcm / nr_coeff[nr_deg];
				mul2 = lcm / in2[deg2];
				mul(nr_coeff, nr_deg, mul1);
				mul(in2, deg2, mul2);
				
			}
			if (in2[deg2] == 0) {
				flag2 = 1;
				break;
			}
                        nh_coeff[i] = nr_coeff[nr_deg] / in2[deg2];
                        for (int j = i; j <= nr_deg; j++) {
                                temp = nh_coeff[i] * in2[j - i];
                                nr_coeff[j] = nr_coeff[j] - temp;
                        }
                        if (nr_deg > 0) {
                                nr_deg--;
                        }
                }
		if (flag2) {
			break;
		}
                for (int i = nr_deg; i >= 0; i--) {
                        if (nr_coeff[i] != 0) {
                                flag = 0;
                                break;
                        }
                }
                if (flag) {
                        break;
                } else {
                        deg1 = deg2;
                        polcpy(in1, in2, deg2);
			while (nr_coeff[nr_deg] == 0) {
                                nr_deg--;
                        }
                        deg2 = nr_deg;
                        polcpy(in2, nr_coeff, nr_deg);
        	}
	}
        delete [] nr_coeff;
        delete [] nh_coeff;
	for (int i = ARRAY_MAX; i > deg2; i--) {
		in2[i] = 0;
	}
	if (in2[deg2] < 0) {
		for (int i = deg2; i >= 0; i--) {
			in2[i] = -in2[i];
		}
	}	
        return in2;
}



