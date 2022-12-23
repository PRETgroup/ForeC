int X = 0;
int Y = 0;

int main() {
  X = 0; Y = 0;
  if (X == 1) { /* Nothing */ } else { X = 1; }
  EOT;
  X = 0; Y = 0;
  PAR(t0, t1);
}

thread t0() {
  if (X == 1) { /* Nothing */ } else { Y = 1; }
}
thread t1() {
  if (Y == 1) { X = 1; }
}