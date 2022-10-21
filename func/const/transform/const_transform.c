//
// Created by tholz on 27.08.2022.
//

#include "const_transform.h"

pattern_registry_t const_registry = { .name = "CONST" };

void const_transform_init() {
	pattern_registry_add_rule(&const_registry, "COMMUT_MULT", "MUL,MUL,(ANY),(NUM),(NUM),-,- > MUL,[MUL,$2,$3],$1");
	pattern_registry_add_rule(&const_registry, "COMMUT_MULT2", "MUL,MUL,(NUM),(NUM),(ANY),-,- > MUL,[MUL,$1,$2],$3");
	pattern_registry_add_rule(&const_registry, "COMMUT_ADD", "ADD,ADD,(ANY),(NUM),(NUM),-,- > ADD,[ADD,$2,$3],$1");
	pattern_registry_add_rule(&const_registry, "COMMUT_ADD2", "ADD,ADD,(NUM),(NUM),(ANY),-,- > ADD,[ADD,$1,$2],$3");
	pattern_registry_add_rule(&const_registry, "MULT_NUM_FRAC", "~MUL,(NUM),DIV,-,-,(NUM),(ANY) > DIV,[MUL,$1,$2],$3");
	pattern_registry_add_rule(&const_registry, "POWER_1", "~POW,(ANY),(NUM=1) > $1");
	pattern_registry_add_rule(&const_registry, "POWER_0", "~POW,ANY,(NUM=0) > [NUM=1]");
	pattern_registry_add_rule(&const_registry, "1_POWER", "~POW,(NUM=1),ANY > [NUM=1]");
	pattern_registry_add_rule(&const_registry, "ADD_0", "ADD,(ANY),(NUM=0) > $1");
	pattern_registry_add_rule(&const_registry, "SUB_0", "~SUB,(ANY),(NUM=0) > $1");
	pattern_registry_add_rule(&const_registry, "MUL_0", "MUL,(ANY),(NUM=0) > [NUM=0]");
	pattern_registry_add_rule(&const_registry, "MUL_1", "MUL,(ANY),(NUM=1) > $1");
	pattern_registry_add_rule(&const_registry, "DIV_BY_1", "~DIV,(ANY),(NUM=1) > $1");
	pattern_registry_add_rule(&const_registry, "DIV_BY_0", "~DIV,(ANY),(NUM=0) > ERR: Division by zero");
	pattern_registry_add_rule(&const_registry, "ADD_NEGATIVE", "ADD,(ANY),SUB,-,-,(NUM=0),(ANY) > SUB,$1,$3");
	pattern_registry_add_rule(&const_registry, "SUB_NEG", "~SUB,(ANY),SUB,-,-,(NUM=0),(ANY) > ADD,$1,$3");
	pattern_registry_add_rule(&const_registry, "SQUARE_SQRT", "POW,SQRT,(NUM=2),(ANY) > $2");
	pattern_registry_add_rule(&const_registry, "LN_EXP", "LN,POW,-,E,(ANY) > $1");
	pattern_registry_add_rule(&const_registry, "LOG_EXP", "LOG,POW,-,E,(ANY) > $1");
	pattern_registry_add_rule(&const_registry, "EXP_LN", "POW,E,LN,-,-,(ANY) > $1");
	pattern_registry_add_rule(&const_registry, "EXP_LOG", "POW,E,LOG,-,-,(ANY) > $1");
	pattern_registry_add_rule(&const_registry, "POWER_POWER", "POW,POW,(NUM),(ANY),(NUM) > POW,$2,[MUL,$1,$3]");
	pattern_registry_add_rule(&const_registry, "MUL_NEG_POWER", "MUL,(ANY),POW,-,-,(ANY),(NUM=NEG) > DIV,$1,POW,-,-,$2,SUB,-,-,-,-,-,-,[NUM=0],$3");

	pattern_registry_add_rule(&const_registry, "ADD_SAME_MULTIPLES", "ADD,MUL,MUL,(NUM),(?ANY),(NUM),(?ANY) > MUL,[ADD,$1,$3],$2");
	pattern_registry_add_rule(&const_registry, "ADD_SAME", "ADD,(?ANY),(?ANY) > MUL,[NUM=2],$1");
	pattern_registry_add_rule(&const_registry, "SUB_SAME", "SUB,(?ANY),(?ANY) > [NUM=0]");
	pattern_registry_add_rule(&const_registry, "DIV_SAME", "~DIV,(?ANY),(?ANY) > [NUM=1]");
	pattern_registry_add_rule(&const_registry, "MUL_SAME_POWERS", "MUL,POW,POW,(?ANY),(NUM),(?ANY),(NUM) > POW,$1,[ADD,$2,$4]");
	pattern_registry_add_rule(&const_registry, "MUL_SAME_POWER", "MUL,POW,(?ANY),(?ANY),(NUM) > POW,$1,ADD,-,-,$3,[NUM=1]");
	pattern_registry_add_rule(&const_registry, "MUL_SAME", "MUL,(?ANY),(?ANY) > POW,$1,[NUM=2]");
	pattern_registry_add_rule(&const_registry, "ADD_SAME_PROD", "ADD,MUL,(?ANY),(NUM),(?ANY) > MUL,ADD,$1,$2,[NUM=1]");
	pattern_registry_add_rule(&const_registry, "ADD_SAME_PROD2", "ADD,(?ANY),MUL,ANY,ANY,(NUM),(?ANY) > MUL,ADD,$1,$2,[NUM=1]");
	pattern_registry_add_rule(&const_registry, "SUB_SAME_PROD", "~SUB,MUL,(?ANY),(NUM),(?ANY) > MUL,SUB,$1,$2,[NUM=1]");
	pattern_registry_add_rule(&const_registry, "SUB_SAME_PROD2", "~SUB,(?ANY),MUL,ANY,ANY,(NUM),(?ANY) > MUL,SUB,$1,[NUM=1],$2");
	pattern_registry_add_rule(&const_registry, "MUL_SAME_SQRT", "MUL,SQRT,SQRT,(?ANY),-,(?ANY),- > $1");

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
	pattern_registry_add_rule(&const_registry, "ORDER_MUL_USER_VAR", "~MUL,(!USER_VAR),(USER_VAR) > MUL,$2,$1"); // move user vars to the left
	pattern_registry_add_rule(&const_registry, "ORDER_MUL_NUM", "~MUL,(!NUM),(NUM) > MUL,$2,$1"); // move factors to the left
}
