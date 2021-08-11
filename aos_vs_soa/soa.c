#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef float float3[3];
typedef struct {
  float3 *xyz;
  long n;
} setup_data_t;

setup_data_t setup(long n) {
  setup_data_t data;
  data.xyz = malloc(n * sizeof(float3));
  data.n = n;
  return data;
}

void finish(setup_data_t data) { free(data.xyz); }

float __attribute__((noinline)) performance_test(setup_data_t data) {
  float sum = 0;
  for (long i = 0; i < data.n; i++) {

    sum += data.xyz[i][0];
    sum += data.xyz[i][1];
    sum += data.xyz[i][2];
  }
  return sum;
}

int main() {
  setup_data_t data;
  struct timespec start, end;
  clockid_t id;

  FILE *file = fopen("soa.csv", "w");

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