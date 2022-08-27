//
// Created by tholz on 27.08.2022.
//

#include "const_transform.h"

pattern_registry_t const_registry;

void const_transform_init() {
	pattern_registry_add_rule(&const_registry, "MUL,MUL,(ANY),(NUM),(NUM),-,- > MUL,[MUL,$2,$3],$1");
}
