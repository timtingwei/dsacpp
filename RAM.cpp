/*  ------------------------------
    Copyright <2017> [Tim Hu]
    email: timtingwei@hotamail.com    
   ------------------------------
   File:RAM:Floor
   Date:Tue 26 Dec 2017
   -----------------------------
*/

#include <iostream>

void print_ram(const int* c, const int* d, const int* x, const int* a);

int f() {
  int c = 12;           // 0, R[0] <- c
  int d = 5;            // 1, R[1] <- d
  int x = 0;            // 2, R[2] <- 0
  int a = 0;            //
  print_ram(&c, &d, &x, &a);
  a = 1;                // 3, R[3] <- 1
  while (c > 0) {       // 8, IF R[0] > 0 GOTO 4
    c += a;             // 4, R[0] <- R[0] + R[2]
    c -= d;             // 5, R[0] <- R[0] - R[1]
    x += a;             // 6, R[2] <- R[2] + R[3]
    print_ram(&c, &d, &x, &a);
  }
  x--;                  // 7, R[0] <- R[2] - R[3]
  print_ram(&c, &d, &x, &a);
  return x;             // 9, STOP
}

void print_ram(const int* c, const int* d, const int* x, const int* a) {
  std::cout << " R[0] = " << *c << " R[1] = " << *d
            << " R[2] = " << *x << " R[3] = " << *a
            << "\n -- ------------------- -- \n";
}

int main() {
  std::cout << "RETURN::count R[0] = " << f() << std::endl;
  return 0;
}


