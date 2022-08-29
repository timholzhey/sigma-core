//
// Created by tholz on 27.08.2022.
//

#include "derive_transform.h"

pattern_registry_t derive_registry_gen1 = { .name = "DERIVE_PRE" };
pattern_registry_t derive_registry_gen2 = { .name = "DERIVE" };

void derive_transform_init() {
	pattern_registry_add_rule(&derive_registry_gen1, "CONST_ADD", "ADD,(NUM),(ANY) > $2");
	pattern_registry_add_rule(&derive_registry_gen1, "CONST_SUB", "SUB,(NUM),(ANY) > $2");

	pattern_registry_add_rule(&derive_registry_gen2, "VAR", "VAR > [NUM=1]");
	pattern_registry_add_rule(&derive_registry_gen2, "CONST", "NUM > [NUM=0]");
	pattern_registry_add_rule(&derive_registry_gen2, "POWER", "~POW,VAR,(NUM) > MUL,$1,POW,-,-,VAR,[SUB,$1,NUM=1]");
	pattern_registry_add_rule(&derive_registry_gen2, "SIN", "SIN,VAR > COS,VAR,-");
	pattern_registry_add_rule(&derive_registry_gen2, "COS", "COS,VAR > SUB,[NUM=0],SIN,-,-,VAR,-");
	pattern_registry_add_rule(&derive_registry_gen2, "LOG", "LOG,VAR > DIV,[NUM=1],VAR");
	pattern_registry_add_rule(&derive_registry_gen2, "E", "~POW,E,VAR > POW,E,VAR");
}
