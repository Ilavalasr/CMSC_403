/* Suraj Ilavala
 * CMSC 403: Assignment 4
 * Tokenizer.h
 *
 *
 *
 */
#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "Givens.h"
#include "Analyzer.h"
#include <stdio.h>
_Bool bodyStructure(struct lexics * allLex, struct lexics * current, int * index);
_Bool statementStructure(struct lexics * allLex, struct lexics * current, int * index);
_Bool statement_list(struct lexics * allLex, struct lexics * current, int * index);
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);
#endif
