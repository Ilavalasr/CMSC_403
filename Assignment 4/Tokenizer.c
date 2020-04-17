/* Suraj Ilavala
 * CMSC 403: Assignment 4
 * Tokenizer.c
 *
 * Tokenizes the file from input and addes it to universal list that can be used by other files.
 * After the the file is parsed or is parsable it sends to parser to check
 */

#include <stdlib.h>
#include <string.h>
#include "Tokenizer.h"

//adds any new lexical found and adds to the universal lexeme
void combineLexics(struct lexics * aLex, int * numLex, char * lexeme, int token){
  struct lexics temp;//creates a temp file
  strcpy(temp.lexeme, lexeme);//sets a temp file to the given lexeme
  temp.token = token;//sets temp token to the given token
  aLex[*numLex] = temp;//adds token to the lexics
  (*numLex)++;
}
//makes adding the characters to the lexics easier
char * singleLexAdd(char lex){
  char * one = malloc(2 * sizeof(char));
  one[0] = lex;
  one[1] = '\0';
  return one;
}
//Gets all letters until white space and special characters are detected
char * getIdent(char * cLine, int * pos){
  char * ident = malloc(MY_CHAR_MAX * sizeof(char));
  int place = 0;
  //checks until white space and special characters.
  while(!((cLine[*pos]=='\n')||(cLine[*pos]=='\t')|| (cLine[*pos]==' ')) && !((cLine[*pos]=='{')||(cLine[*pos]=='}')||(cLine[*pos]=='(')||(cLine[*pos]==')')||(cLine[*pos]=='=')||(cLine[*pos]=='*')||(cLine[*pos]=='+')||(cLine[*pos]=='!')||(cLine[*pos]==';')||(cLine[*pos]==','))){
    ident[place] = cLine[*pos];
    place++;
    (*pos)++;
  }
  ident[place] = '\0';
  (*pos)--;
  place = 0;
  return ident;
}

_Bool lineParseing(struct lexics * aLex, char * cLine, int * numLex){
  for(int i = 0; i < strlen(cLine); i++){
    //checks if its letters, '_' is said to be a letter because it is a part of the method name.
    if((('a' <= cLine[i]) && ('z' >= cLine[i])) || (('A' <= cLine[i]) && ('Z' >= cLine[i])) || (cLine[i] == '_')){
      char * word = getIdent(cLine, &i);
      int variableType = IDENTIFIER;
      if(!strcmp(word, "int") || !strcmp(word, "void")){
        variableType = VARTYPE;
      }
      else if(!strcmp(word, "while")){
        variableType = WHILE_KEYWORD;
      }
      else if(!strcmp(word, "return")){
        variableType = RETURN_KEYWORD;
      }
      combineLexics(aLex, numLex, word, variableType);
    }
    //checks for numbers
    else if(cLine[i] <= '9' && cLine[i] >= '0'){
      combineLexics(aLex, numLex, singleLexAdd(cLine[i]), NUMBER);
    }
    //checks for '{}();,' and  adds it accordingly
    else if(cLine[i] == '{'){
      combineLexics(aLex, numLex, singleLexAdd('{'), LEFT_BRACKET);
    }
    else if(cLine[i] == '}'){
      combineLexics(aLex, numLex, singleLexAdd('}'), RIGHT_BRACKET);
    }
    else if(cLine[i] == '('){
      combineLexics(aLex, numLex, singleLexAdd('('), LEFT_PARENTHESIS);
    }
    else if(cLine[i] == ')'){
      combineLexics(aLex, numLex, singleLexAdd(')'), RIGHT_PARENTHESIS);
    }
    else if(cLine[i] == ';'){
      combineLexics(aLex, numLex, singleLexAdd(';'), EOL);
    }
    else if(cLine[i] == ','){
      combineLexics(aLex, numLex, singleLexAdd(','), COMMA);
    }
    //checks mathmatematical symbols
    else if(cLine[i] == '+' || cLine[i] == '-' || cLine[i] == '*' || cLine[i] == '/' || cLine[i] == '%'){
      combineLexics(aLex, numLex, singleLexAdd(cLine[i]), BINOP);
    }
    //checks the expressions '!', '!=', '=', '==' and act accordingly
    else if(cLine[i] == '!'){
      if(cLine[i+1] == '='){
        combineLexics(aLex, numLex, "!=", BINOP);
        i++;
      }
      else{
        combineLexics(aLex, numLex, "!", BINOP);
      }
    }
    else if(cLine[i] == '='){
      if(cLine[i+1] == '='){
        combineLexics(aLex, numLex, "==", BINOP);
        i++;
      }
      else{
        combineLexics(aLex, numLex, "=", BINOP);
      }
    }
    //if the cline[i] is space it continues without failing
    else if(cLine[i]=='\n'||cLine[i]=='\t'|| cLine[i]==' '){
      continue;
    }
    else{
      return FALSE;
    }
  }
  //somehow makes it all the way down here it returns true
  return TRUE;
}
//gets the file contents and set it to string, after that it does the lineParseing and returns true or false
_Bool tokenizer(struct lexics * aLex, int * numLex, FILE *inf){
  char str[MY_CHAR_MAX];
  while(fgets(str, MY_CHAR_MAX, inf) != NULL){
    if(lineParseing(aLex, str, numLex) == FALSE){
      return FALSE;
    }
  }
  return TRUE;
}
