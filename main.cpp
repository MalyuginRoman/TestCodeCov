#include "include/config.h"

int main() {
  bool success = true;
#ifdef testEquationSolution
  root x = solve(1, 2, 1);
  double result = 1.;
  success &= ((x.x1 - result) < e);
#endif
#ifdef correctA
  double a = 0.;
  double b = 0.;
  double c = 0.;
  x = solve(a, b, c);
  success &= (a < e);
#endif
#ifdef noRoot
  a = 1.;
  b = 0.;
  c = 1.;
  d = discr(a, b, c);
  x = solve(a, b, c);
  success &= (d < 0);
#endif
#ifdef oneRoot
  a = 1.;
  b = 2.;
  c = 1.;
  d = discr(a, b, c);
  x = solve(a, b, c);
  success &= (abs(d) < e);
#endif
#ifdef twoRoot
  a = 1.;
  b = 0.;
  c = -1.;
  d = discr(a, b, c);
  x = solve(a, b, c);
  success &= (abs(d) > e);
#endif
  return success ? 0 : 1;
}
