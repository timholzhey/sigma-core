//
// Created by tholz on 22.10.2022.
//

#include "integrate_transform.h"

pattern_registry_t integrate_registry = { .name = "INTEGRATE" };
pattern_registry_t integrate_add_c_registry = { .name = "INTEGRATE_ADD_C" };

void integrate_transform_init() {
	pattern_registry_add_rule(&integrate_registry, "VAR", "VAR > MUL,DIV,POW,[NUM=1],[NUM=2],VAR,[NUM=2]");
	pattern_registry_add_rule(&integrate_registry, "VAR_POWER", "POW,VAR,(NUM) > MUL,DIV,POW,[NUM=1],ADD,VAR,ADD,-,-,$1,[NUM=1],-,-,$1,[NUM=1]");
	pattern_registry_add_rule(&integrate_registry, "CONST", "(CONST) > MUL,$1,VAR");

	pattern_registry_add_rule(&integrate_add_c_registry, "ANY", "(ANY) > ADD,$1,CONST");
}
