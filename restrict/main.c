#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void __attribute__((noinline))
restrist_test(float *restrict a, float *restrict b, float *restrict c, int n) {
  for (int i = 0; i < n; i++)
    c[i] = a[i] + b[i];
}

void __attribute__((noinline))
no_restrict_test(float *a, float *b, float *c, int n) {
  for (int i = 0; i < n; i++)
    c[i] = a[i] + b[i];
}

int main() {

  struct timespec start, end;
  clockid_t id;

  long max_n = 1e7;
  float *a = malloc(max_n * sizeof(float));
  float *b = malloc(max_n * sizeof(float));
  float *c = malloc(max_n * sizeof(float));

  FILE *file = fopen("restrict.csv", "w");
  double nano_seconds;

  fprintf(file, "n,res,no_res\n");
  for (double n = 1.2; n < max_n; n = n*1.2) {
    fprintf(file, "%ld,", (long)n);
    clock_gettime(id, &start);
    restrist_test(a, b, c, n);
    clock_gettime(id, &end);

    nano_seconds = (double)end.tv_nsec - start.tv_nsec;
    fprintf(file, "%lf,", nano_seconds);

    clock_gettime(id, &start);
    restrist_test(a, b, c, n);
    clock_gettime(id, &end);

    nano_seconds = (double)end.tv_nsec - start.tv_nsec;
    fprintf(file, "%lf\n", nano_seconds);
  }

  fclose(file);
  free(a);
  free(b);
  free(c);
}
