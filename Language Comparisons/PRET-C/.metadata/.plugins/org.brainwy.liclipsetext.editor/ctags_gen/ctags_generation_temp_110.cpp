#include <stdio.h>

int X = 0;
int Y = 0;

int main() {
  X = 0; Y = 0;
  if (X == 1) { /* Nothing */ } else { X = 1; }
  printf("X = %d Y = %d\n", X, Y);
  
  EOT;
  X = 0; Y = 0;
  PAR(t0, t1);
  printf("X = %d Y = %d\n", X, Y);
  
  return 0;
}

thread t0() {
  if (X == 1) { /* Nothing */ } else { Y = 1; }
}
thread t1() {
  if (Y == 1) { X = 1; }
}