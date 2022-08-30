//
// Created by tholz on 27.08.2022.
//

#include "const_transform.h"

pattern_registry_t const_registry = { .name = "CONST" };

void const_transform_init() {
	pattern_registry_add_rule(&const_registry, "COMMUT_MULT", "MUL,MUL,(ANY),(NUM),(NUM),-,- > MUL,[MUL,$2,$3],$1");
	pattern_registry_add_rule(&const_registry, "COMMUT_MULT", "MUL,MUL,(NUM),(NUM),(ANY),-,- > MUL,[MUL,$1,$2],$3");
	pattern_registry_add_rule(&const_registry, "COMMUT_ADD", "ADD,ADD,(ANY),(NUM),(NUM),-,- > ADD,[ADD,$2,$3],$1");
	pattern_registry_add_rule(&const_registry, "COMMUT_ADD", "ADD,ADD,(NUM),(NUM),(ANY),-,- > ADD,[ADD,$1,$2],$3");
	pattern_registry_add_rule(&const_registry, "POWER_1", "~POW,(ANY),(NUM=1) > $1");
	pattern_registry_add_rule(&const_registry, "POWER_0", "~POW,ANY,(NUM=0) > [NUM=1]");
	pattern_registry_add_rule(&const_registry, "1_POWER", "~POW,(NUM=1),ANY > [NUM=1]");
	pattern_registry_add_rule(&const_registry, "ADD_0", "ADD,(ANY),(NUM=0) > $1");
	pattern_registry_add_rule(&const_registry, "MUL_0", "MUL,(ANY),(NUM=0) > [NUM=0]");
	pattern_registry_add_rule(&const_registry, "MUL_1", "MUL,(ANY),(NUM=1) > $1");
	pattern_registry_add_rule(&const_registry, "DIV_BY_1", "~DIV,(ANY),(NUM=1) > $1");
	pattern_registry_add_rule(&const_registry, "DIV_BY_0", "~DIV,(ANY),(NUM=0) > ERR: Division by zero");
	pattern_registry_add_rule(&const_registry, "VAR_MUL", "MUL,VAR,VAR > POW,VAR,[NUM=2]");
	pattern_registry_add_rule(&const_registry, "VAR_ADD", "ADD,VAR,VAR > MUL,[NUM=2],VAR");
	pattern_registry_add_rule(&const_registry, "VAR_SUB", "SUB,VAR,VAR > [NUM=0]");
	pattern_registry_add_rule(&const_registry, "VAR_DIV", "DIV,VAR,VAR > [NUM=1]");
	pattern_registry_add_rule(&const_registry, "VAR_MUL_POWERS", "MUL,POW,POW,VAR,(NUM),VAR,(NUM) > POW,VAR,[ADD,$1,$2]");
	pattern_registry_add_rule(&const_registry, "ADD_NEGATIVE", "ADD,(ANY),SUB,-,-,(NUM=0),(ANY) > SUB,$1,$3");

	pattern_registry_add_rule(&const_registry, "BINOM_1", "~POW,ADD,(NUM=2),(ANY),(ANY) > "
														  "ADD,"
														  "POW,ADD,"
														  "$2,[NUM=2],MUL,POW,"
														  "-,-,-,-,MUL,$3,$3,[NUM=2],"
														  "-,-,-,-,-,-,-,-,[NUM=2],$2");
	pattern_registry_add_rule(&const_registry, "BINOM_2", "~POW,SUB,(NUM=2),(ANY),(ANY) > "
														  "ADD,"
														  "POW,ADD,"
														  "$2,[NUM=2],SUB,POW,"
														  "-,-,-,-,[NUM=0],MUL,$3,[NUM=2],"
														  "-,-,-,-,-,-,-,-,-,-,MUL,$3,-,-,-,-,"
														  "-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,[NUM=2],$2");

	pattern_registry_add_rule(&const_registry, "ORDER_ADD_NUM", "~ADD,(NUM),(!NUM) > ADD,$2,$1"); // move constants to the right
	pattern_registry_add_rule(&const_registry, "ORDER_MUL_NUM", "~MUL,(!NUM),(NUM) > MUL,$2,$1"); // move factors to the left
}
