%{
    #include <string.h>
    #include <stdlib.h>
    #include "y.tab.h"
    void extern yyerror(char*);
    void InvalidToken();

%}

whitespace      [ \t\r\v\f]
linefeed        \n

%%
"void"  |
"int"   |
"string"  |
"float" |
"unsigned int"  |
"unsigned char" |
"void*"         |
"int*"          |
"char*"         |
"float*"                                        {yylval.dataType = strdup(yytext);return DATA_TYPE;}

"struct"                                        {yylval.dataType = strdup(yytext);return STRUCT;}

"println"                                       {return PRINTLN;}
"'"                                             {return SINGLE_QUOTES;}
","                                             {return COMMA;}
";"                                             {return SEMI_COLON;}
"="                                             {return EQUALS;}
"("                                             {return BRACKET_OPEN;}
")"                                             {return BRACKET_CLOSE;}
"{"                                             {return CURLY_BRACE_OPEN;}
"^"                                             {return CARET;}
"}"                                             {return CURLY_BRACE_CLOSE;}
"["                                             {return BIG_BRACKET_OPEN;}
"]"                                             {return BIG_BRACKET_CLOSE;}
"print"                                          {return PRINT;}
">=" return GE; 
"<=" return LE; 
"==" return EQ; 
"!=" return NE; 
"while" return WHILE; 
"if" return IF; 
"else" return ELSE;
"+" return PLUS;
"-" return MINUS;
"*" return MUL;
"/" return DIV;
"%" return MOD;
">" return GT;
"<" return LT;


[\'][a-zA-Z][\']                                {yylval.charVal = yytext[1];    return CHARACTER_VALUE;}
[-+]?[0-9]+                                     {yylval.intVal = atoi(yytext);  return INTEGER_VALUE;}
[-+]?[0-9]*\.?[0-9]+                            {yylval.floatVal = atof(yytext); return FLOAT_VALUE;}

[a-zA-Z][_a-zA-Z0-9]*(\[[0-9]+\])+              {yylval.strVal = strdup(yytext); return ARRAY_IDENTIFIER;}
[a-zA-Z][_a-zA-Z0-9]*                           {yylval.dataType = strdup(yytext); return IDENTIFIER;}


\"(\\.|[^"])*\"                                 {yylval.strVal = strdup(yytext); return STRING_VALUE;}


{linefeed}                                      {yylineno++;}
{whitespace}                                    ;
.                                               {InvalidToken();}


%%

int yywrap(void){
    return 1;
}

void yyerror(char *s) {
    fprintf(stderr, "\nERROR ON LINE %d : \n %s\n", yylineno, s);
    exit(0);
}

void InvalidToken(){
    printf("ERROR ON LINE %d : \n Invalid Token %s\n", yylineno,yytext);
    exit(0);
}
