#include <stdio.h>
#include <math.h>

float lintp(float *xx, float *yy, float x, int n);

int main() {
    // x_values and y_values from sampled data
    const int num_points = 9;
    float x_values[num_points];
    float y_values[num_points];
    float rand_noise[] = {-0.013534, -0.001902, -0.002960, 0.001617, -0.009852, -0.010003, 0.008348, -0.011097, 0.012050};

    for (int i = 0; i < num_points; i++) {
        x_values[i] = i * M_PI / 4.0;
        y_values[i] = sin(x_values[i]) + rand_noise[i];
//        y_values[i] = sin(x_values[i]);
    }

    // 100 uniformly spaced values between 0 and 2π
    const int num_interpolations = 100;
    float interpolated_values[num_interpolations];
    float step = 2 * M_PI / (num_interpolations - 1);
    float x_interpolate = 0.0;

    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    for (int i = 0; i < num_interpolations; i++) {
        interpolated_values[i] = lintp(x_values, y_values, x_interpolate, num_points);
        fprintf(output_file, "%f %f\n", x_interpolate, interpolated_values[i]);
        x_interpolate += step;
    }

    fclose(output_file);

    printf("Interpolated values written to output.txt.\n");

    return 0;
}

// Function for Lagrange interpolation
float lintp(float *xx, float *yy, float x, int n) {
    float result = 0.0;

    for (int i = 0; i < n; i++) {
        float term = yy[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (x - xx[j]) / (xx[i] - xx[j]);
            }
        }
        result += term;
    }

    return result;
}