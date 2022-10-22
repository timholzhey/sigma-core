# Sigma core
Algebra engine in C (WIP!)

## Functions:
- [x] Constant
- [x] Derive
- [x] Integrate
- [x] Plot

## REPL example

```shell
~ % sigma
Sigma algebra engine v0.1.0. (4.33 ms)
Type "help" for more information and "q" to quit.
> 10^3
1000
> der x^2
2x
> int 3x^2
x^3+c
> func_derive[sin(y),y]
cos(y)
> 
```

## Command line example

```shell
~ % sigma -c "der sin(x^2)"
cos(x^2)*2x
```

Usage: `sigma [options]`

Options:
```shell
   -v               Verbose output
   --version        Print version
   -c <input>       Compile input
   -h               Print this help
```

## Library Example

```c
#include <stdio.h>
#include "math_core.h"

int main() {
    printf("The derivative of x^2+sin(2x) is %s", math_derive("x^2+sin(2x)", 'x'));
    return 0;
}
```
