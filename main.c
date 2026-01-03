#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 800
#define FRAMES 120
#define RANGE 6.9

typedef struct {
    int rows, cols;
    double* data;
} Mat;

double randd() {
    return ((double)rand() / (double)RAND_MAX) * RANGE * 2 - RANGE;
}

Mat mat_init(int r, int c) {
    return (Mat){ .rows = r, .cols = c, .data = malloc(r * c * sizeof(double)) };
}

void mat_rand(Mat m) {
    for (int i = 0; i < m.rows * m.cols; i++) m.data[i] = randd();
}

double activate(double x, int layer) {
    if (layer == 0) return sin(x);
    if (layer == 1) return 1.0 / (1.0 + exp(-x));
    return tanh(x);
}

void forward(double* in, double* out, Mat w, Mat b, int layer) {
    for (int i = 0; i < w.rows; i++) {
        double summa = 0;
        for (int j = 0; j < w.cols; j++) {
            summa += w.data[i * w.cols + j] * in[j];
        }
        out[i] = activate(summa + b.data[i], layer);
    }
}

int main() {
    srand(time(NULL));

    Mat w1 = mat_init(16, 4), b1 = mat_init(16, 1);
    Mat w2 = mat_init(16, 16), b2 = mat_init(16, 1);
    Mat w3 = mat_init(3, 16), b3 = mat_init(3, 1);

    mat_rand(w1); mat_rand(b1);
    mat_rand(w2); mat_rand(b2);
    mat_rand(w3); mat_rand(b3);

    unsigned char* img = malloc(WIDTH * HEIGHT * 3);
    double h1[16], h2[16], out[3];

    for (int f = 0; f < FRAMES; f++) {
        double t = (double)f / (FRAMES - 1);

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                double nx = (double)x / WIDTH * 2.0 - 1.0;
                double ny = (double)y / HEIGHT * 2.0 - 1.0;
                double nr = sqrt(nx * nx + ny * ny);
                double in[4] = {nx, ny, t, nr};

                forward(in, h1,  w1, b1, 0);
                forward(h1, h2,  w2, b2, 1);
                forward(h2, out, w3, b3, 2);

                int idx = (y * WIDTH + x) * 3;
                img[idx + 0] = (unsigned char)((out[0] * 0.5 + 0.5) * 255);
                img[idx + 1] = (unsigned char)((out[1] * 0.5 + 0.5) * 255);
                img[idx + 2] = (unsigned char)((out[2] * 0.5 + 0.5) * 255);
            }
        }

        char path[64];
        sprintf(path, "frames/%04d.ppm", f);
        FILE* fp = fopen(path, "wb");
        if (fp) {
            fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
            fwrite(img, 1, WIDTH * HEIGHT * 3, fp);
            fclose(fp);
        }
        printf("Frame %d/%d\r", f + 1, FRAMES);
        fflush(stdout);
    }

    free(img);
    return 0;
}
