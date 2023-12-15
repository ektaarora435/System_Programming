Objective
Write a Lex program to count the number of vowels and consonants from text file.
Code
%{
  int vowels = 0;
  int consonants = 0;
%}
%%
A|E|I|O|U|a|e|i|o|u { vowels++; };
[A-Za-z] { consonants++; };
[ |\n|\t] { ; }
. { ; }
%%
int main()
{
  yylex();
  printf("%i vowels, %i consonants\n", vowels, consonants);
  return 0;
}

int yywrap()
{
  return 1;
}

Output
  
PRACTICAL 2
Objective
Write a Lex program to identify a word entered by user is a verb or not.
Code
%%
is     |
am     |
are    |
were   |
was    |
be     |
being  |
been   |
do     |
does   |
did    |
will   |
would  |
should |
can    |
could  |
has    |
have   |
had    |
go        { printf("%s is a verb\n", yytext); }
[A-Za-z]+ { printf("%s is not a verb\n", yytext); }
[ |\t|\n] { ; }
. { ; }
%%
int main()
{
  yylex();
  return 0;
}

int yywrap()
{
  return 1;
}

Output
 
PRACTICAL 3
Objective
Write a Lex program to count the number of integers, floats, identifiers, operators, and comments in a C program.
Code
%{
  int integers = 0;
  int floats = 0;
  int identifiers = 0;
  int operators = 0;
  int comments = 0;
%}
%%
[#].* { printf("%s <- preprocessor directive\n", yytext); } // preprocessor directives
[ |\n|\t] { ; } // whitespaces
[,|;|"("|")"|"{"|"}"|"\["|"\]"] { ; } // brackets, delimiters
"//".* { comments++; printf("%s <- comment\n", yytext); } // single line comments
[0-9]+ { integers++; printf("%s <- integer\n", yytext); } // integers
[0-9]+("."[0-9]+) { floats++; printf("%s <- float\n", yytext); } // floats
void|int|main|char|for|while|continue|switch|case|break|if|else|return|true|false { printf("%s <- keyword\n", yytext); } // keywords
"<="|">="|"!="|"=="|"<"|">"|"&"|"|"|"^"|"<<"|">>"|"~"|"&&"|"||"|"!"|"++"|"--"|"="|"+"|"-“|"*"|"/"|"%" { operators++; printf("%s <- operator\n", yytext); } // operators
[']([^\\\']|\\.)?['] { ; } // characters
["]([^\\\"]|\\.)*["] { ; } // strings
[a-zA-Z_]+[a-zA-Z0-9_]* { identifiers++; printf("%s <- identifier\n", yytext); } // identifiers
%%
int main() {
  yyin = fopen("text.c", "r");
  yylex();
  printf("\n");
  printf("number of integers: %d\n", integers);
  printf("number of floats: %d\n", floats);
  printf("number of identifiers: %d\n", identifiers);
  printf("number of operators: %d\n", operators);
  printf("number of comments: %d", comments);
  return 0;
}

int yywrap() {
  return 1;
}

Input
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loop()
{
  int i, j = 5; // okay
  for (int i = 0; i < j; i++)
  {
    printf("%d. Hi\n", (i + 1));
  }
}

int main()
{
  double a = -3.14;
  char at = '@', tab = '\t';

  loop();

  return 0;
}



Output
 
 
  
PRACTICAL 4
Objective
Write a Lex program to count the number of words, characters, blank spaces, and lines in a text file.
Code
%{
  int words = 0;
  int lines = 0;
  int spaces = 0;
  int characters = 0;
%}
%%
[^ \t\n,\.:;]+ { words++; characters += yyleng; }
[\n] { lines++; characters += yyleng; }
[ |\t] { spaces++; characters += yyleng; }
. { characters++; }
%%
int main() {
  yyin = fopen("text.txt", "r");
  yylex();
  printf("number of words: %d\n", words);
  printf("number of blank spaces: %d\n", spaces);
  printf("number of lines: %d\n", lines);
  printf("number of characters: %d\n", characters);
  return 0;
}

int yywrap() {
  return 1;
}

Input
Sudipto Ghosh
College Roll Number 78003


Output
  
PRACTICAL 5
Objective
Write a Lex program that implements the Caesar cipher.
Code
%{
  int rot = 0;
%}
%%
[A-Z] { fprintf(yyout, "%c", (yytext[0] - 'A' + rot) % 26 + 'A'); }
[a-z] { fprintf(yyout, "%c", (yytext[0] - 'a' + rot) % 26 + 'a'); }
. { fprintf(yyout, "%s", yytext); }
%%
int main(void) {
  printf("Enter Key (ROT): ");
  scanf("%d", &rot);
  yyin = fopen("input.txt", "r");
  yyout = fopen("output.txt", "w");
  yylex();
  fclose(yyin);
  fclose(yyout);
  return 0;
}

int yywrap() {
  return 1;
}

Output


 
	
PRACTICAL 6
Objective
Write a program in Lex to recognize a valid arithmetic expression.
Code
%{
  #include <stdio.h>
  int brackets = 0,
      operators = 0,
      numbersOridentifiers = 0,
      flag = 0;
%}
%%
[a-zA-Z_]+[a-zA-Z0-9_]* { numbersOridentifiers++; }
-?[0-9]+("."[0-9]+)? { numbersOridentifiers++; }
[+|\-|*|/|=|\^|%] { operators++; }
"(" { brackets++; }
")" { brackets--; }
";" { flag = 1; }
.|\n { ; }
%%
int main() {
  yylex();
  if (
    (operators + 1) == numbersOridentifiers
      && brackets == 0 && flag == 0
  ) {
    printf("Valid Expression\n");
  } else {
    printf("Invalid Expression\n");
  }
  return 0;
}

int yywrap() {
  return 1;
}

Output
 
PRACTICAL 7
Objective
Write a Lex program that finds the longest word in the input.
Code
%{
  int length = 0;
  char *word = NULL;
%}
%%
[a-zA-Z]+ { 
  if (yyleng > length) {
    length = yyleng;
    word = yytext;
  }
}
[ |\n|\t] { ; }
. { ; }
%%
int main(void) {
  yyin = fopen("input.txt", "r");
  yylex();
  fclose(yyin);
  printf("Longest Word: %.*s\n", length, word);
  printf("Length of Longest Word: %d\n", length);
  return 0;
}

int yywrap() {
  return 1;
}

Output



PRACTICAL 1
Objective
A Program in YACC to evaluate an expression (simple calculator program for addition and subtraction, multiplication, division).
Code
/* yacc.y */
%{
  #include <stdio.h>
  #include <stdlib.h>
  extern int yylex();
  void yyerror(char *);
%}

%union { float f; }
%token <f> NUM
%type <f> E T F
%%
S : E { printf("%f\n", $1); }
  ;
E : E '+' T { $$ = $1 + $3; }
  | E '-' T { $$ = $1 - $3; }
  | T
  ;
T : T '*' F { $$ = $1 * $3; }
  | T '/' F { $$ = $1 / $3; }
  | F
  ;
F : '(' E ')' { $$ = $2; }
  | '-' F { $$  = -$2; }
  | NUM
  ;
%%
int main()
{
   yyparse();
   return 0;
}

void yyerror(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

/* lex.l */
%{
  #include <stdio.h>
  #include <stdlib.h>

  #if __has_include("y.tab.h")
    #include "y.tab.h"
  #endif
%}

%option noyywrap
%%
[0-9]+(\.[0-9]+)? { yylval.f = atof(yytext); return NUM; }
[\-+()*/] { return yytext[0]; }
[ \t\n]+ { ; }
%%

Output
  
PRACTICAL 2
Objective
Program in YACC to recognize the language (𝑎𝑛𝑏, n ≥ 10) (Output to say input is valid or not)
Code
/* yacc.y */
%{
  #include <stdio.h>
  #include <stdlib.h>
  extern int yylex();
  void yyerror(char *);
%}

%token A B
%%
S : X Y B '\n' { printf("VALID STRING\n"); exit(0); } 
  ;
X : A A A A A A A A A A
  ;
Y : A Y
  |
  ;
%%
int main()
{
   yyparse();
   return 0;
}

void yyerror(char *msg) {
  fprintf(stderr, "INVALID STRING\n");
  exit(1);
}

/* lex.l */
%{
  #include <stdio.h>
  #include <stdlib.h>

  #if __has_include("y.tab.h")
    #include "y.tab.h"
  #endif
%}

%option noyywrap
%%
[a] { return A; }
[b] { return B; }
[ |\n|\t] { return yytext[0]; }
. { return yytext[0]; }
%%

Output
 
 
PRACTICAL 3
Objective
A Program in YACC which recognizes a valid variable which starts with letter followed by a digit. The letter should be in lowercase only.
Code
/* yacc.y */
%{
  #include <stdio.h>
  #include <stdlib.h>
  extern int yylex();
  void yyerror(char *);
%}

%token D L
%%
S : L D { printf("VALID IDENTIFIER\n"); }
  ;
%%
int main()
{
    yyparse();
    return 0;
}

void yyerror(char *msg)
{
    fprintf(stderr, "INVALID IDENTIFIER\n");
    exit(1);
}

/* lex.l */
%{
  #include <stdio.h>
  #include <stdlib.h>

  #if __has_include("y.tab.h")
    #include "y.tab.h"
  #endif
%}
%option noyywrap
%%
[a-z] { return L; }
[0-9] { return D; }
[ \t\n]+ { ; }
. { return yytext[0]; }
%%

Output
 
 
PRACTICAL 4
Objective
Program in YACC to recognize the strings "ab", "aabb", "aaabbb", … of the language (𝑎𝑛 𝑏𝑛, n ≥ 1).
Code
/* yacc.y */
%{
  #include <stdio.h>
  #include <stdlib.h>
  extern int yylex();
  void yyerror(char *);
%}

%token A B

%%
S : E '\n' { printf("VALID STRING\n"); exit(0); }
  ;
E : A E B
  | A B
  ;
%%
int main()
{
   yyparse();
   return 0;
}

void yyerror(char *msg) {
  fprintf(stderr, "INVALID STRING\n");
  exit(1);
}

/* lex.l */
%{
  #include <stdio.h>
  #include <stdlib.h>

  #if __has_include("y.tab.h")
    #include "y.tab.h"
  #endif
%}

%option noyywrap
%%
[a] { return A; }
[b] { return B; }
[ |\n|\t] { return yytext[0]; }
. { return yytext[0]; }
%%

Output
 

