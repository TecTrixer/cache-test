#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void output_image(const void *image_buffer, int rows, int columns) {
  FILE *fptr = fopen("out.ppm", "w");
  if (fptr == NULL) {
    printf("Error when opening file!");
    exit(1);
  }
  int out = fprintf(fptr, "P6 %d %d 255 ", rows, columns);
  int out2 = fwrite(image_buffer, 1, rows * columns * 3, fptr);
  fclose(fptr);
  printf("successfully written %d + %d bytes\n", out, out2);
}

double simul(int array_size, int stride) {
  int * x = (int *)malloc(sizeof(int) * array_size);
  if (!x) {
    printf("Malloc was not successfull");
    exit(1);
  }
  int i;
  for (i = 0; i < array_size; i += stride) {
    x[i] = i + stride;
  }
  x[i - stride] = 0;

  double steps = 0.0;
  int nextstep = 0;
  time_t start_time = time(NULL);
  time_t end_time;
  double diff;
  do {
    nextstep = 0;
    do {
      nextstep = x[nextstep];
    } while (nextstep != 0);

    steps = steps + 1.0;
    end_time = time(NULL);
    diff = difftime(end_time, start_time);
  } while (diff < 5.0);
  double load_time_ns = diff / (steps * (array_size / stride)) * 1e9;
  printf("Average access latency for stride %d and array size %d with %f steps: %f\n", stride,
         array_size, steps, load_time_ns);
  fflush(NULL);
  free(x);
  return load_time_ns;
}

int main() {
  // char x[255][255][3];
  // for (int i = 0; i < 255; i++) {
  //   for (int j = 0; j < 255; j++) {
  //     x[i][j][0] = i;
  //     x[i][j][1] = j;
  //     x[i][j][2] = j;
  //   }
  // }
  // output_image((const void *)&x, 255, 255);
  // double results[24][26];
  FILE *fptr = fopen("results.csv", "w");
  if (fptr == NULL) {
    printf("Error when opening file!");
    exit(1);
  }
  int out = fprintf(fptr, "Stride, Size, Result\n");
  for (int size = 12; size <= 26; size += 2) {
    for (int stride = 2; stride <= 24; stride += 2) {
      if (stride >= size) {
        continue;
      }
      double res = simul(1 << size, 1 << stride);
      out += fprintf(fptr, "%d, %d, %f\n", 1 << stride, 1 << size, res);
    }
    printf("\n");
  }
  fclose(fptr);
  printf("successfully written %d bytes\n", out);
  return 0;
}
