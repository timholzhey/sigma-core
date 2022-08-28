//
// Created by tholz on 27.08.2022.
//

#include "derive_transform.h"

pattern_registry_t derive_registry = { .name = "Derive" };

void derive_transform_init() {
	pattern_registry_add_rule(&derive_registry, "DERIVE_CONST_ADD", "ADD,(NUM),(ANY) > $2"); // TODO: Replace ANY with FUNC (has VAR as some child)
	pattern_registry_add_rule(&derive_registry, "DERIVE_CONST_SUB", "SUB,(NUM),(ANY) > $2");
	//pattern_registry_add_rule(&derive_registry, "DERIVE_VAR", "VAR > [NUM=1]"); // TODO: Define is top level of function split by ADD or SUB
	pattern_registry_add_rule(&derive_registry, "DERIVE_POWER", "POW,VAR,(NUM) > MUL,$1,POW,-,-,VAR,[SUB,$1,NUM=1]");
	pattern_registry_add_rule(&derive_registry, "DERIVE_SIN", "SIN,VAR > COS,VAR,-");
}
