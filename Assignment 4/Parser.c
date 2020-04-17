/* Suraj Ilavala
 * CMSC 403: Assignment 4
 * Parser.c
 *
 * Parses and makes sure the structure of the entire expression is valid
 *
 */

#include <stdlib.h>
#include <assert.h>
#include "Parser.h"

int numLex = 0;
//checks to see if the next token is expected if not it returns false causing it to not add it
//but if it is expected then it adds the current lexics and says true
_Bool checkNextLex(struct lexics * allLex, struct lexics * current, int * index, int expected){
  assert(*index < numLex);
  if(current->token != expected){
    return FALSE;
  }
  (*index)++;
  *current = allLex[*index];
  return TRUE;
}
//This is the argument structure that is given then it is set up 'void int(char n)'
_Bool arg_decl(struct lexics * allLex, struct lexics * current, int *index){
  if(current->token == RIGHT_PARENTHESIS){
    return TRUE;
  }
  //this sets up the how the expression should be set up
  while(1){
    if(checkNextLex(allLex, current, index, LEFT_BRACKET) == FALSE){
      return FALSE;
    }
    if((checkNextLex(allLex, current, index, VARTYPE) == FALSE) || (checkNextLex(allLex, current, index, IDENTIFIER) == FALSE)){
      return FALSE;
    }
    if(!checkNextLex(allLex, current, index, COMMA)){
      break;
    }
  }
  return TRUE;
}
//header structure and sets up to make sure there is valid elements to display header 'void int()'
_Bool headerStructure(struct lexics * allLex, struct lexics * current, int * index){
  if((checkNextLex(allLex, current, index, VARTYPE) == FALSE) || (checkNextLex(allLex, current, index, IDENTIFIER) == FALSE) || (checkNextLex(allLex, current, index, LEFT_PARENTHESIS) == FALSE) || (checkNextLex(allLex, current, index, RIGHT_PARENTHESIS) == FALSE)){
    return FALSE;
  }
  if(!arg_decl(allLex, current, index)){
    return FALSE;
  }
  return TRUE;
}
//makes sure the term is structred with the necessary elements to display the terms consistly like this 'int 5'
_Bool termStructure(struct lexics * allLex, struct lexics * current, int * index){
  return checkNextLex(allLex, current, index, IDENTIFIER) || checkNextLex(allLex, current, index, NUMBER);
}
//the actual expression structure something like this (expression)
_Bool expressionStructure(struct lexics * allLex, struct lexics * current, int * index){
  if(termStructure(allLex, current, index)){
    while(checkNextLex(allLex, current, index, BINOP)){
      if(!termStructure(allLex, current, index)){
        return FALSE;
      }
    }
    return TRUE;
  }
  else{
      return checkNextLex(allLex, current, index, LEFT_PARENTHESIS) && expressionStructure(allLex, current, index) && checkNextLex(allLex, current, index, RIGHT_PARENTHESIS);
  }
}
//structure that comes after the =: '= d + 10;'
_Bool equalStructure(struct lexics * allLex, struct lexics * current, int * index){
  return checkNextLex(allLex, current, index, EQUAL) && expressionStructure(allLex, current, index) && checkNextLex(allLex, current, index, EOL);
}
//Return statement structure return 'expression;'
_Bool returnStructure(struct lexics * allLex, struct lexics * current, int * index){
  return expressionStructure(allLex, current, index) && checkNextLex(allLex, current, index, EOL);
}
//while loop structure 'while(expression == false)'
_Bool whileStructure(struct lexics * allLex, struct lexics * current, int * index){
  if((checkNextLex(allLex, current, index, LEFT_PARENTHESIS) == FALSE) || (checkNextLex(allLex, current, index, RIGHT_PARENTHESIS) == FALSE) || (expressionStructure(allLex, current, index) == FALSE) || (statementStructure(allLex, current, index) == FALSE)){
    return FALSE;
  }
  return TRUE;
}
//body structure of the expression: while (...) '{statement_list}'
_Bool bodyStructure(struct lexics * allLex, struct lexics * current, int * index){
  if((checkNextLex(allLex, current, index, LEFT_BRACKET) == FALSE) || (checkNextLex(allLex, current, index, RIGHT_BRACKET) == FALSE) || (statement_list(allLex, current, index) == FALSE)){
    return FALSE;
  }
  return TRUE;
}
//goes through and checks each keyword and identifier to check the statement structure
_Bool statementStructure(struct lexics * allLex, struct lexics * current, int * index){
  if(checkNextLex(allLex, current, index, WHILE_KEYWORD)){
    return whileStructure(allLex, current, index);
  }
  else if(checkNextLex(allLex, current, index, IDENTIFIER)){
    return equalStructure(allLex, current, index);
  }
  else if(current->token == LEFT_BRACKET){
    return bodyStructure(allLex, current, index);
  }
  else if(checkNextLex(allLex, current, index, RETURN_KEYWORD)){
    return returnStructure(allLex, current, index);
  }
  else{
    return FALSE;
  }
}
//has a list of all assignments and checks it
_Bool statement_list(struct lexics * allLex, struct lexics * current, int * index){
  if(current->token == RIGHT_BRACKET){
    return TRUE;
  }
  while(1){
    if(!statementStructure(allLex, current, index)){
      return FALSE;
    }
    else if(current->token == RIGHT_BRACKET){
      return TRUE;
    }
  }
  return TRUE;
}
//actual parser and calls headerStructure and bodyStructure and starts checking the structure
_Bool parser(struct lexics * allLex, int numberOfLexics){
  int index = 0;
  struct lexics current = allLex[index];
  numLex = numberOfLexics;
  return headerStructure(allLex, &current, &index) && bodyStructure(allLex, &current, &index) && (index == numberOfLexics);
}
