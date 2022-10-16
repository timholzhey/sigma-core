//
// Created by tholz on 27.08.2022.
//

#include "derive_transform.h"

pattern_registry_t derive_registry = { .name = "DERIVE" };

void derive_transform_init() {
	pattern_registry_add_rule(&derive_registry, "DIV_FUNC_CONST", "~@DIV,(FUNC),(CONST) > DIV,*$1,$2");
	pattern_registry_add_rule(&derive_registry, "DIV_CONST_FUNC", "~@DIV,(CONST),(FUNC) > MUL,$1,*POW,-,-,$2,[NUM=-1]");
	pattern_registry_add_rule(&derive_registry, "FUNC_PRODUCT", "@MUL,(FUNC),(FUNC) > ADD,MUL,MUL,$1,*$2,*$1,$2");
	pattern_registry_add_rule(&derive_registry, "FUNC_QUOTIENT", "~@DIV,(FUNC),(FUNC) > DIV,SUB,POW,MUL,MUL,$2,[NUM=2],$2,*$1,$1,*$2");
	pattern_registry_add_rule(&derive_registry, "FUNC_CHAIN_1", "@(FUNC),(FUNC) > MUL,*$1,*$2");
	pattern_registry_add_rule(&derive_registry, "FUNC_CHAIN_2", "@(FUNC),(!NUM),(FUNC) > MUL,*$1,*$3");

	pattern_registry_add_rule(&derive_registry, "VAR", "VAR > [NUM=1]");
	pattern_registry_add_rule(&derive_registry, "CONST", "CONST > [NUM=0]");
	pattern_registry_add_rule(&derive_registry, "POWER", "~POW,(FUNC),(NUM) > MUL,$2,POW,-,-,$1,[SUB,$2,NUM=1]");
	pattern_registry_add_rule(&derive_registry, "SIN", "~SIN,(FUNC) > COS,$1,-");
	pattern_registry_add_rule(&derive_registry, "COS", "~COS,(FUNC) > SUB,[NUM=0],SIN,-,-,$1,-");
	pattern_registry_add_rule(&derive_registry, "LOG", "~LOG,(FUNC) > DIV,[NUM=1],$1");
	pattern_registry_add_rule(&derive_registry, "LN", "~LN,(FUNC) > DIV,[NUM=1],$1");
	pattern_registry_add_rule(&derive_registry, "E_POWER", "~POW,E,(FUNC) > POW,E,$1");
	pattern_registry_add_rule(&derive_registry, "SQRT", "~SQRT,(FUNC) > DIV,[NUM=1],MUL,-,-,[NUM=2],SQRT,-,-,-,-,-,-,$1");

	pattern_registry_add_rule(&derive_registry, "VAR_MUL_CONST1", "MUL,VAR,(NUM) > $1");
	pattern_registry_add_rule(&derive_registry, "VAR_MUL_CONST2", "MUL,VAR,(USER_VAR) > $1");
}
