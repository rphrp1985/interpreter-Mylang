%{
  #include <stdio.h>
  #include <string.h>

  #include "HeaderFiles/langFunctions.h"
  #include "HeaderFiles/validators.h"

  extern char Data_Type[50];

  extern void yyerror();
  extern int yylex();
  extern char* yytext;
  extern int yylineno;

  void storeDataType(char*);
  int isDuplicate(char*, char*);
  void storeIdentifier(char*,char*);
  void DuplicateIdentifierError(char*);
  char* retrieveDataType();
  void clearBuffers();
  int isValidAssignment(char*);
  void AssignmentError(char*);
  char* extractIdentifier(char[]);
  void assignInteger(int);
  void lastIdentifier(char*);
  void assignDouble(double);
  void assignCharacter(char);
  void assignString(char*);
  char* printIdentifier(char*);
  void push(double);
  double pop();
  void add();
  void subtract();
  void multiply();
  void divide();
  void assignIdentifierValue();
  void setIFELSE(int);
  void equalequal();
  int popIFELSE();
  void notequal();
  void GreaterEqual();
  void Lessequal();
  void GreaterThan();
  void LessThan();
  void pushICG(char*,double,char*,char*,int);

  //For Array Identifiers
  int noOfArrayIdentifiers=0;
  char extractedIdentifier[50][50];

%}


%define parse.lac full
%define parse.error verbose


%union {
  int intVal;
  char* dataType;
  char* strVal;
  float floatVal;
  char charVal;
}



%token  COMMA   SINGLE_QUOTES   SEMI_COLON   EQUALS 
%token  BRACKET_OPEN  BRACKET_CLOSE   CURLY_BRACE_OPEN  CURLY_BRACE_CLOSE BIG_BRACKET_OPEN  BIG_BRACKET_CLOSE

%token <charVal>  CHARACTER_VALUE
%token <intVal>   INTEGER_VALUE
%token <floatVal> FLOAT_VALUE
%token <strVal> STRING_VALUE

%token <intVal> INT
%token <floatVal> FLOAT
%token <strVal> STRING
%token <dataType> DATA_TYPE
%token <strVal> IDENTIFIER   ARRAY_IDENTIFIER
%token <strVal> STRUCT
%token PRINT CARET

%token WHILE IF PLUS MINUS MUL DIV GE LE EQ NE GT LT MOD PRINTLN
%nonassoc IFX 
%nonassoc ELSE 
%left MOD GE LE EQ NE '>' '<' 
%left  PLUS MINUS 
%left  MUL DIV
%right left
%left CARET



%type <strVal> DECLARATION
%type <strVal> EXPRESSION


%%
  
DECLARATION : EXPRESSION  SEMI_COLON                              { clearBuffers(); }
      | DECLARATION EXPRESSION  SEMI_COLON                        { clearBuffers(); }
      | error '>'                     {/* ' > ' stops execution all together */}
      ;

EXPRESSION  : DATA_TYPE IDENTIFIER              {
                                  if(!isDuplicate($2,retrieveDataType())){
                                    storeIdentifier($2,$1);
                                    storeDataType($1);
                                  }else{
                                    DuplicateIdentifierError($2);
                                  } 
                                 // lastIdentifier($2);
                             
                             pushICG($2,0.0,"lastIdentifier","",0);

                              //   printf("%s\n",$2);
                                }


      | PRINT EXPRESSION  {
                          //  printf("%s %d %s",$2.type,$2.value,$2);
                           // printf("printing identfier %s",$2);
                           // printf("%s",printIdentifier($2));

                            pushICG($2,0.0,"printIdentifier","",0);    


                            }
      | PRINTLN  { pushICG("",0.0,"println","",0);  }

      | IFGRAMMAR CURLY_BRACE_OPEN DECLARATION CURLY_BRACE_CLOSE { pushICG("",0.0,"","ifelse",1); }
      | IFGRAMMAR CURLY_BRACE_OPEN DECLARATION CURLY_BRACE_CLOSE ELSEGRAMMAR CURLY_BRACE_OPEN DECLARATION CURLY_BRACE_CLOSE { pushICG("",0.0,"","ifelse",1); }
      | EXPRESSION EQ EXPRESSION {  pushICG("",0.0,"equalequal","",0);  }   
      |EXPRESSION NE EXPRESSION {  pushICG("",0.0,"notequal","",1);  }
      |EXPRESSION GT EXPRESSION { pushICG("",0.0,"GreaterThan","",1);  }
      |EXPRESSION LT EXPRESSION { pushICG("",0.0,"LessThan","",1);  }
      |EXPRESSION GE EXPRESSION {  pushICG("",0.0,"ifelse","",1);  }
      |EXPRESSION LE EXPRESSION { pushICG("",0.0,"Lessequal","",1);  }
      |EXPRESSION MOD EXPRESSION {  pushICG("",0.0,"mod","",1); }
      | WHILEGRAMMAR CURLY_BRACE_OPEN DECLARATION CURLY_BRACE_CLOSE { pushICG("",0.0,"","while-end",1); }  
      | IDENTIFIER   {  pushICG($1,0.0,"lastIdentifier","",0);  }


      | EXPRESSION  EQUALS  EXPRESSION            { pushICG("",0.0,"assignIdentifierValue","",1);  }

      | EXPRESSION  COMMA IDENTIFIER         {
                                  if(!isDuplicate($3,retrieveDataType())){
                                    storeIdentifier($3,retrieveDataType());
                                  }else{
                                    DuplicateIdentifierError($3);
                                  }
                                }


    


      | DATA_TYPE   ARRAY_IDENTIFIER            {
                                    
                                  strcpy(extractedIdentifier[noOfArrayIdentifiers],extractIdentifier($2));
                                  if(!isDuplicate(extractedIdentifier[noOfArrayIdentifiers],retrieveDataType())){
                                    storeIdentifier(extractedIdentifier[noOfArrayIdentifiers],retrieveDataType());
                                    storeDataType($1);
                                  }else{
                                    DuplicateIdentifierError(extractedIdentifier[noOfArrayIdentifiers]);
                                  } 
                                  noOfArrayIdentifiers++;
                                }

      | EXPRESSION  EQUALS  CURLY_BRACE_OPEN  PARAMETER_LIST  CURLY_BRACE_CLOSE  

      | EXPRESSION COMMA ARRAY_IDENTIFIER             {
                                    strcpy(extractedIdentifier[noOfArrayIdentifiers],extractIdentifier($3));
                                    if(!isDuplicate(extractedIdentifier[noOfArrayIdentifiers],retrieveDataType())){
                                      storeIdentifier(extractedIdentifier[noOfArrayIdentifiers],retrieveDataType());
                                    }else{
                                      DuplicateIdentifierError(extractedIdentifier[noOfArrayIdentifiers]);
                                    } 
                                    noOfArrayIdentifiers++;
                                  }

      | EXPRESSION PLUS EXPRESSION { pushICG("",0.0,"add","",1);   }
      | EXPRESSION CARET EXPRESSION { pushICG("",0.0,"power","",1);}
      | EXPRESSION MINUS EXPRESSION { pushICG("",0.0,"subtract","",1);   }
      | EXPRESSION MUL EXPRESSION {  pushICG("",0.0,"multiply","",1);   }
      | EXPRESSION DIV EXPRESSION {pushICG("",0.0,"divide","",1);   }
      |NUMBER {}
      
      
      

      | error '>'                   {/* no need to call yyerror cuz of line 1570 of y.tab.c*/}
      ;

IFGRAMMAR  : IFTOKRN EXPRESSION { pushICG("",0.0,"","if-start",0);};

IFTOKRN : IF { pushICG("",0.0,"","if",0);};
WHILEGRAMMAR : WHILET EXPRESSION { pushICG("",0.0,"","while-start",0);};
WHILET : WHILE { pushICG("",0.0,"","while",0);};

ELSEGRAMMAR  : ELSE { pushICG("",0.0,"","else-start",0); } ;


          

NUMBER    : INTEGER_VALUE                 {
                                            if(!isValidAssignment("int")){ AssignmentError(itoa($1));}
                                            else{
                                              
                                              pushICG("",$1,"push","",1);
                                            }


                                                    }
      | FLOAT_VALUE                   {if(!isValidAssignment("float")){ AssignmentError(ftoa($1));}
                                          else{
                                           // assignDouble($1);
                                           // push($1);
                                            pushICG("",$1,"push","",1);
                                          }
                                      }
      | CHARACTER_VALUE                 {if(!isValidAssignment("char")){ AssignmentError(ctoa($1));}else {  pushICG("",$1,"push","",1); }   }
      | STRING_VALUE              {if(!isValidAssignment("char*")){ AssignmentError($1);} else{  pushICG($1,0.0,"pushString","",1); }  }
      ;


PARAMETER_LIST  : NUMBER
        | PARAMETER_LIST  COMMA   NUMBER
          |   NUMBER EQUALS NUMBER                        { yyerror("Two or more equal signs are not allowed in C");} 
          |   error '>'
        ;


%%


int main(){

  yyparse();
  execute();
  //printf("No Errors!!\n");
  return 0;
}