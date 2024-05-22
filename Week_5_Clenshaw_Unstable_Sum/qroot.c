#include <stdio.h>
#include <math.h>
#include <complex.h>

int sgn(float alpha) {
    if (alpha > 0) {
        return 1;
    }
    if (alpha < 0) {
        return -1;
    }
    return 0;
    
}

void main() {
    int N = 10000, j;
    double alphas[N], i;
    double complex exact_root_1[N], exact_root_2[N];
    float complex float_root_1[N], float_root_2[N];
    float complex float_acc_root_1[N], float_acc_root_2[N];

    for (i = 0; i <= 100; i = i + 0.01) {
        alphas[j] = i;
        j++;
    }
    
    // Exact Roots with Double Precision
    
    for (j = 0; j < N; j++) {
        double complex discr = 0;
        if (fabs(alphas[j]) < 1) {
            discr = I*sqrt(1-pow(alphas[j],2));
        }
        else {
            discr = sqrt(pow(alphas[j],2)-1);
        }

        exact_root_1[j] = -(alphas[j]) + discr;
        exact_root_2[j] = -(alphas[j]) - discr;
    }
    
    // Roots with Float Precision
    FILE *f1;
    f1 = fopen("error_without_non_cancelling_roots.txt", "w");
    
    for (j = 0; j < N; j++) {
        float complex discr = 0;
        if (fabs(alphas[j]) < 1) {
            discr = I*sqrt(1-pow(alphas[j],2));
        }
        else {
            discr = sqrt(pow(alphas[j],2)-1);
        }

        float_root_1[j] = -(float)(alphas[j]) + discr;
        float_root_2[j] = -(float)(alphas[j]) - discr;
        
        fprintf(f1, "%.15f\t", alphas[j]);
        // fprintf(f1, "%.15f\t", cabs(float_root_1[j]-exact_root_1[j]));
        // fprintf(f1, "%.15f\n", cabs(float_root_2[j]-exact_root_2[j]));
        fprintf(f1, "%.15f\t", cabsf(float_root_1[j]));
        fprintf(f1, "%.15f\n", cabsf(float_root_2[j]));
    }
    fclose(f1);
    
    // More Accurate Roots with Float Precision
    FILE *f2;
    f2 = fopen("error_with_non_cancelling_roots.txt", "w");
    
    for (j = 0; j < N; j++) {
        float complex p = 0;
        if (fabs(alphas[j]) < 1) {
            // float complex discr = sqrt(1-pow(alphas[j],2))*I;
            // float_acc_root_1[j] = -(alphas[j]) + discr;
            // float_acc_root_2[j] = -(alphas[j]) - discr;
            p = I*sqrt(1 - powf((float)alphas[j], 2));
        }
        else {
            // p = -(alphas[j] + sgn(alphas[j]) * sqrt(pow(alphas[j], 2) - 1));
            p = sqrt(powf((float)alphas[j], 2) - 1);
        }
        float_acc_root_1[j] = float_root_1[j];
        float_acc_root_2[j] = 1/(-(float)(alphas[j]) + p);
        
        fprintf(f2, "%.15f\t", alphas[j]);
        // fprintf(f2, "%.15f\t", cabs(float_acc_root_1[j]-exact_root_1[j]));
        // fprintf(f2, "%.15f\n", cabs(float_acc_root_2[j]-exact_root_2[j]));
        fprintf(f1, "%.15f\t", cabsf(float_acc_root_1[j]));
        fprintf(f1, "%.15f\n", cabsf(float_acc_root_2[j]));
    }
    fclose(f2);
}