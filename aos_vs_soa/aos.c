#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  float *x;
  float *y;
  float *z;
  long n;
} setup_data_t;

setup_data_t setup(long n) {
  setup_data_t data;
  data.x = malloc(n * sizeof(float));
  data.y = malloc(n * sizeof(float));
  data.y = malloc(n * sizeof(float));
  data.n = n;
  return data;
}

void finish(setup_data_t data) {
  free(data.x);
  free(data.y);
  free(data.z);
}

float __attribute__((noinline)) performance_test(setup_data_t data) {
  float sum = 0;
  for (long i = 0; i < data.n; i++)
    sum += data.x[i];

  for (int i = 0; i < data.n; i++)
    sum += data.y[i];

  for (int i = 0; i < data.n; i++)
    sum += data.z[i];
  return sum;
}

int main() {
  setup_data_t data;
  struct timespec start, end;
  clockid_t id;

  FILE *file = fopen("aos.csv", "w");

  fprintf(file, "n,time\n");
  for (long n = 0; n < 1e5; n += 1e1) {
    data = setup(n);
    double nano_seconnds;
    for (int i = 0; i < 100; i++) {

      clock_gettime(id, &start);
      performance_test(data);
      clock_gettime(id, &end);
      nano_seconnds += (double)end.tv_nsec - start.tv_nsec;
    }
    nano_seconnds /= 100;
    fprintf(file, "%ld,%lf\n", n, nano_seconnds);
    finish(data);
  }
}