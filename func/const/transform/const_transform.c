//
// Created by tholz on 27.08.2022.
//

#include "const_transform.h"

pattern_registry_t const_registry = { .name = "Constant" };

void const_transform_init() {
	pattern_registry_add_rule(&const_registry, "CONST_COMMUT_MULT", "MUL,MUL,(ANY),(NUM),(NUM),-,- > MUL,[MUL,$2,$3],$1");
	pattern_registry_add_rule(&const_registry, "CONST_COMMUT_MULT", "MUL,MUL,(NUM),(NUM),(ANY),-,- > MUL,[MUL,$1,$2],$3");
	pattern_registry_add_rule(&const_registry, "CONST_POWER_1", "POW,(ANY),(NUM=1) > $1");
	pattern_registry_add_rule(&const_registry, "CONST_POWER_0", "POW,(ANY),(NUM=0) > [NUM=1]");
	pattern_registry_add_rule(&const_registry, "ADD_0", "ADD,(ANY),(NUM=0) > $1");
	pattern_registry_add_rule(&const_registry, "MUL_0", "MUL,(ANY),(NUM=0) > [NUM=0]");
	pattern_registry_add_rule(&const_registry, "MUL_1", "MUL,(ANY),(NUM=1) > $1");
}
