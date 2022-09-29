//
// Created by tholz on 27.08.2022.
//

#include "derive_transform.h"

pattern_registry_t derive_registry_gen1 = { .name = "DERIVE_PRE" };
pattern_registry_t derive_registry_gen2 = { .name = "DERIVE" };

void derive_transform_init() {
	pattern_registry_add_rule(&derive_registry_gen1, "CONST_ADD", "ADD,(NUM),(ANY) > $2");
	pattern_registry_add_rule(&derive_registry_gen1, "CONST_SUB", "SUB,(NUM),(ANY) > $2");

	pattern_registry_add_rule(&derive_registry_gen2, "PRODUCT", "@MUL,(FUNC),(FUNC) > ADD,MUL,MUL,$1,*$2,*$1,$2");
	pattern_registry_add_rule(&derive_registry_gen2, "CHAIN", "@(FUNC),(FUNC) > MUL,*$1,*$2");
	pattern_registry_add_rule(&derive_registry_gen2, "CHAIN_2", "@(FUNC),(!NUM),(FUNC) > MUL,*$1,*$3");

	pattern_registry_add_rule(&derive_registry_gen2, "VAR", "VAR > [NUM=1]");
	pattern_registry_add_rule(&derive_registry_gen2, "CONST", "NUM > [NUM=0]");
	pattern_registry_add_rule(&derive_registry_gen2, "POWER", "~POW,(FUNC),(NUM) > MUL,$2,POW,-,-,$1,[SUB,$2,NUM=1]");
	pattern_registry_add_rule(&derive_registry_gen2, "SIN", "~SIN,(FUNC) > COS,$1,-");
	pattern_registry_add_rule(&derive_registry_gen2, "COS", "~COS,(FUNC) > SUB,[NUM=0],SIN,-,-,$1,-");
	pattern_registry_add_rule(&derive_registry_gen2, "LOG", "~LOG,(FUNC) > DIV,[NUM=1],$1");
	pattern_registry_add_rule(&derive_registry_gen2, "LN", "~LN,(FUNC) > DIV,[NUM=1],$1");
	pattern_registry_add_rule(&derive_registry_gen2, "E", "~POW,E,(FUNC) > POW,E,$1");
	pattern_registry_add_rule(&derive_registry_gen2, "SQRT", "~SQRT,(FUNC) > DIV,[NUM=1],MUL,-,-,[NUM=2],SQRT,-,-,-,-,-,-,$1");

	pattern_registry_add_rule(&derive_registry_gen2, "VAR_MUL_CONST", "MUL,VAR,(NUM) > $1");
}
