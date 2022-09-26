# Sigma core
Algebra engine in C (WIP)

## Functions:
- [x] Constant (simplify)
- [x] Derive
- [ ] Integrate

## REPL example

```shell
~ % sigma
Sigma algebra engine v0.0.1.
Type "help" for more information and "q" to quit.
> 10^3
1000
> 'x^2
2x
> derive[sin(y),y]
cos(y)
> 
```

## Library Example

```c
#include <stdio.h>
#include "math_core.h"

int main() {
    printf("The derivative of x^2+sin(2x) is %s", derive("x^2+sin(2x)", 'x'));
    return 0;
}
```
