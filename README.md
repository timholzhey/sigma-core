# Sigma core
Algebra engine in C (WIP)

## Functions:
- [x] Constant (simplify)
- [x] Derive
- [ ] Integrate

## Example

```c
#include <stdio.h>
#include "sigma.h"

int main() {
    printf("The derivative of x^2+sin(2x) is %s", derive("x^2+sin(2x)", 'x'));
    return 0;
}
```

## Derivative solver flow
- Lex string
- Preprocess tokens
- Parse tokens
- Eval AST
  - Const eval
    - Transform constant rules
    - Evaluate constant operations
    - Transform constant rules
  - Transform derivative rules set 1
  - Transform derivative rules set 2
  - Const eval
    - Transform constant rules
    - Evaluate constant operations
    - Transform constant rules
- Stringify
