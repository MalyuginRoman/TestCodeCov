#include "include/config.h"

int main() {
  bool success = true;
#ifdef testEquationSolution
  root x = solve(1, 2, 1);
  double result = 1.;
  success &= ((x.x1 - result) < e);
#endif
#ifdef correctA()
  root x = solve(0, 0, 0);
  success &= (a < 0);
#endif
#ifdef noRoot
  double d = discr(1, 0, 1);
  success &= (d < 0);
#endif
#ifdef oneRoot
  double d = discr(1, 2, 1);
  success &= (abs(d) < e);
#endif
#ifdef twoRoot
  double d = discr(1, 0, -1);
  success &= (abs(d) > e);
#endif
  return success ? 0 : 1;
}
