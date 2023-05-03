#include <stdlib.h>
#include <string.h>

char Data_Type[50];

int noOfIdentifiers = 0;

struct IdentifierStructure
{
    int i;
    char c;
    double d;
    char *s;
    char*   data_type;
    char*  value;
}identifiers[1000];

double lastNumber=0.0;
char* lastid;

char* IdentifierArray[20]; 
extern int yylineno;
extern char* yytext; 


void showIdentifiers(){
    int i;
    for(i=0;i<noOfIdentifiers;i++){
        printf("%s\n",identifiers[i].value);
    }
}



void storeDataType(char* data_type){
    int i=0;
    while(data_type[i] != '\0'){
        Data_Type[i] = data_type[i];
        i++;
    }
}

char* retrieveDataType(){
    return Data_Type;
}

int isDuplicate(char* identifier,char* identifier_data_type){
    int i;
    for(i=0;i<noOfIdentifiers;i++){
        if(strcmp(identifier,identifiers[i].value) == 0){
            return 1;
        }
    }
    return 0;
}



char* extractIdentifier(char* arrayIdentifier){
    char extractedIdentifier[50];
    static char copied[50];

    int i=0;

    while(arrayIdentifier[i] != '['){
        extractedIdentifier[i] = arrayIdentifier[i];
        i++;
    }
    extractedIdentifier[i] = '\0';

    i=0;
    while(extractedIdentifier[i] != '\0'){
        copied[i] = extractedIdentifier[i];
        i++;
    }
    copied[i] = '\0';
    return copied;
    
}

// to store all identifiers and check for duplicates
void storeIdentifier(char* identifier, char* identifier_data_type){
    identifiers[noOfIdentifiers].value = identifier;
    identifiers[noOfIdentifiers].data_type = identifier_data_type;
    noOfIdentifiers++;
}

void assignInteger(int value){
    int i;
    for(i=0;i<noOfIdentifiers;i++){
        if(strcmp(lastid,identifiers[i].value) == 0){
            return;
            identifiers[i].i = value;
        }
    }
    printf("Undeclared identifier '%s' found.\n",lastid);
    exit(0);
}

void assignString(char* value){
    int i;
    for(i=0;i<noOfIdentifiers;i++){
        if(strcmp(lastid,identifiers[i].value) == 0){
            identifiers[i].s = value;
        }
    }
}

void assignCharacter(char value){
    int i;
    for(i=0;i<noOfIdentifiers;i++){
        if(strcmp(lastid,identifiers[i].value) == 0){
            identifiers[i].c = value;
        }
    }
}

void assignDouble(double value){
    int i;
    for(i=0;i<noOfIdentifiers;i++){
        if(strcmp(lastid,identifiers[i].value) == 0){
            identifiers[i].d = value;
        }
    }
}




void AssignmentError(char* data_type){
    printf("\nERROR ON LINE %d : \nInvalid assignment! Expected '%s', but found %s \n",yylineno,Data_Type, data_type);
    exit(0);
}

void DuplicateIdentifierError(char* identifier){
    printf("\nERROR ON LINE %d : \nDuplicate identifier '%s' found.\n",yylineno,identifier);
    exit(0);
}

char* UndeclaredIdentifierError(char* identifier){
    printf("\nERROR ON LINE %d : \nUndeclared identifier '%s' found.\n",yylineno,identifier);
    exit(0);
    return "Undeclared identifier";
    
}

void ArrayIndexError(char* identifier){
    printf("\nERROR ON LINE %d : \nArray index out of bounds for '%s'.\n",yylineno,identifier);
    exit(0);
}
char str[100];



// int isIFELSECon[1000];
// int topIFELSECon = -1;

double stackarray[100];
int isIDentifier[100]={};
int stackIFELSE[100]={};
int top = -1;
int topIFELSE = 0;
char* stringstack[1000];
int topstring = -1;

void pushString(char* value){

    topstring++;
    stringstack[topstring] = value;
}

char* popString(){
    topstring--;
    return stringstack[topstring+1];
}

char* getTopString(){
    return stringstack[topstring];
}


// void pushIFELSECon(int value){
//     topIFELSECon++;
//     isIFELSECon[topIFELSECon] = value;

// }

// void popIFELSECon(){
//     topIFELSECon--;
// }

// int getTopIFELSECon(){
//     return isIFELSECon[topIFELSECon];
// }





struct ICG
{
    char *value;
    double value1;
    char*   funName;
     char*  condition; // if else  while
     int conditioncode; //for nested if else and while
     int startend;
    

}ICGstack[10000];

int ICGTOP = -1;

int ifelse=0;
int whileloop=0;



void pushICG(char* value,double value1,char* funName,char* condition,int startend){

   
    ICGTOP++;
    ICGstack[ICGTOP].value = value;
    ICGstack[ICGTOP].value1 = value1;

    ICGstack[ICGTOP].funName = funName;
    ICGstack[ICGTOP].condition = condition; // if else  while
    ICGstack[ICGTOP].startend = startend;

if(strcmp(condition,"ifelse")==0){
          ICGstack[ICGTOP].conditioncode = ifelse;
          ifelse--; 
}

if(strcmp(condition,"if")==0){
     ifelse++;
    ICGstack[ICGTOP].conditioncode = ifelse;
}
if(strcmp(condition,"if-start")==0){
    //  ifelse++;
    ICGstack[ICGTOP].conditioncode = ifelse;
}

if(strcmp(condition,"else-start")==0){
     
    ICGstack[ICGTOP].conditioncode = ifelse;
//    ifelse--;
}



 if(strcmp(condition,"while")==0){

    whileloop++;
    ICGstack[ICGTOP].conditioncode = whileloop;
   
}

 if(strcmp(condition,"while-start")==0){

    // whileloop++;
    ICGstack[ICGTOP].conditioncode = whileloop;
   
}

 if(strcmp(condition,"while-end")==0){

    // whileloop++;
    ICGstack[ICGTOP].conditioncode = whileloop;
    whileloop--;
   
}


//  printf("%s %lf %s %s %d %d\n\n",value,value1,funName,condition,ICGstack[ICGTOP].conditioncode,startend);
}



double getTop(){
    return stackarray[top];
}

void push(double value){
  
    
    top++;
    isIDentifier[top] = 0;
    stackarray[top] = value;
}

double pop(){

  

if(top == -1){
    printf("STACK UNDERFLOW ERROR");
    exit(1);
}
    double value = stackarray[top];
    top--;
    return value;
}


int getTopIFELSE(){
    return stackIFELSE[topIFELSE];
}

void pushIFELSE(int value){
//  if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
//       return ;
//     }
//     if(getTopIFELSECon() == 2 && (int)getTopIFELSE()==1 ){
//       return ;
//     }

// printf("push if lese\n");

    topIFELSE++;
    // isIDentifier[topIFELSE] = 0;
    stackIFELSE[topIFELSE] = value;
}

int popIFELSE(){

//  if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
//       return 0;
//     }
//     if(getTopIFELSECon()== 2 && (int)getTopIFELSE()==1 ){
//       return 0;
//     }
   
if(topIFELSE == -1){
    printf("STACK UNDERFLOW ERROR IFELSE");
    exit(1);
}
    int value = stackIFELSE[topIFELSE];

    topIFELSE--;
    return value;
}






double getIdentiferValue(int i){
    //  if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
    //   return 0;
    // }
    // if(getTopIFELSECon() == 2 && (int)getTopIFELSE()==1 ){
    //   return 0;
    // }
    if(strcmp(identifiers[i].data_type,"int") == 0){
        return (double)identifiers[i].i;
    }
    else if(strcmp(identifiers[i].data_type,"char") == 0){
        return (double)identifiers[i].c;
    }
    else if(strcmp(identifiers[i].data_type,"double") == 0){
        return (double)identifiers[i].d;
    }
    
}


void mod(){
     double a = pop();

    if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }

    double b = pop();
 if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }


    push( (int)b%(int)a);
}
void power(){
     double a = pop();

    if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }

    double b = pop();
 if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }


// printf("power %d^ %d \n",(int)b,(int)a);

double c = 1;
    for(int i=0;i<a;i++){
         c*=b;
    }

// printf("power %d \n",(int)c);

    push(c );
}

void add(){

   
    double a = pop();

    if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }



    double b = pop();
 if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }


    push(a+b);
}

void subtract(){
    //  if( getTopIFELSECon()== 1 && (int)getTopIFELSE()==0 ){
    //   return ;
    // }
    // if(getTopIFELSECon() == 2 && (int)getTopIFELSE()==1 ){
    //   return ;
    // }
       double a = pop();

    if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }



    double b = pop();
 if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }
      push(b-a);
}

void multiply(){
    //  if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
    //   return ;
    // }
    // if(getTopIFELSECon()== 2 && (int)getTopIFELSE()==1 ){
    //   return ;
    // }
        double a = pop();

    if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }



    double b = pop();
 if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }
    push(a*b);
}

void divide(){

    //  if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
    //   return ;
    // }
    // if(getTopIFELSECon()== 2 && (int)getTopIFELSE()==1 ){
    //   return ;
    // }
       double a = pop();

    if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }



    double b = pop();
 if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }
    push( b/a);
}



void lastIdentifier(char* id){
    //   printf("la %d %d  %d\n",isI`FELSE,(int)getTop(),top);
    //  if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
    //   return;
    // }
    // if(getTopIFELSECon() == 2 && (int)getTopIFELSE()==1 ){
    //   return;
    // }
    for(int i=0;i<noOfIdentifiers;i++){
        if(strcmp(id,identifiers[i].value) == 0){
        //   push(i);

             top++;
    isIDentifier[top] = 1;
    stackarray[top] = i;
           return;
           
        }
    }

   UndeclaredIdentifierError(id);
}

void assignIdentifierValue(){
    
lastNumber = pop();
int i = (int)pop();

// printf("%s    assignidentifier\n",identifiers[i].value);
            if(strcmp(identifiers[i].data_type,"int") == 0){
                identifiers[i].i = (int)lastNumber;
            }
            else if(strcmp(identifiers[i].data_type,"char") == 0){
                identifiers[i].c = (char)lastNumber;
            }
            else if(strcmp(identifiers[i].data_type,"double") == 0){
                identifiers[i].d = lastNumber;
            }else if (strcmp(identifiers[i].data_type,"string") == 0){
                identifiers[i].s = popString();
            }

           
        
    
}



char* printIdentifier(char *identifier){
    // printf("%d %d  %d  %d\n",getTopIFELSECon(),(int)getTopIFELSE(),topIFELSE,top);
    //  if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
    //   return "";
    // }
    // if(getTopIFELSECon()== 2 && (int)getTopIFELSE()==1 ){
    //     // printf("k");
    //   return "";
    // }
    
    int i = (int)pop();
    char *temp;
    
            // return identifiers[i].data_type;
            if(strcmp(identifiers[i].data_type,"int") == 0){
                
                 sprintf(str, "%d", identifiers[i].i);
                 temp= str;

                 printf("%s",temp);
                 return temp;
            }
            else if(strcmp(identifiers[i].data_type,"char") == 0){
                 sprintf(str, "%c", identifiers[i].c);
                 temp= str;
                 printf("%s",temp);
                 return temp;
            }
            else if(strcmp(identifiers[i].data_type,"double") == 0){
            //    char str[100];
                 sprintf(str, "%lf", identifiers[i].d);
                 temp= str;
                 printf("%s",temp);
                 return temp;
            }
            else if(strcmp(identifiers[i].data_type,"string") == 0){
                temp= identifiers[i].s;
                printf("%s",temp);
                 return temp;
            }
            

 temp =UndeclaredIdentifierError(identifier);
 printf("\n%s\n",temp);
 exit(0);
                 return temp;
}


void emptyStack(){
//    top=-1;
}


void clearBuffers(){
    //  if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
    //   return;
    // }
    // if(getTopIFELSECon() == 2 && (int)getTopIFELSE()==1 ){
    //   return;
    // }
    int i=0;
    while(Data_Type[i] != '\0'){
        Data_Type[i] = '\0';
        i++;
    }
    //  emptyStack();


}


void setIFELSE(int value){

//  if(getTopIFELSECon() == 1 && getTopIFELSE()==0 ){
//       return ;
//     }
//     if(getTopIFELSECon()== 2 && getTopIFELSE()==1 ){
//         // printf("k");
//       return;
//     }
    
  


    // if(value == 1){
    //     pushIFELSECon(1);
    // }
    // else if(value == 2){
    //     popIFELSECon();
    //     pushIFELSECon(2);
    // }
    // else{
    //     popIFELSECon();
    // }
}

void equalequal(){

        // if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
        // return;
        // }
        // if( getTopIFELSECon() == 2 && (int)getTopIFELSE()==1 ){
        // return;
        // }
        double a = pop();
         if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }

        double b = pop();

         if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }

        if(a == b){
            // printf("true -==\n");
            pushIFELSE(1);
        }
        else{
            //  printf("false ==\n");
            pushIFELSE(0);
        }
}

void notequal(){
        // if( getTopIFELSECon()== 1 && (int)getTopIFELSE()==0 ){
        // return;
        // }
        // if(getTopIFELSECon() == 2 && (int)getTopIFELSE()==1 ){
        // return;
        // }
        double a = pop();
         if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }

        double b = pop();

         if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }

        if(a != b){
            // printf("true");
            pushIFELSE(1);
        }
        else{
            //  printf("false");
            pushIFELSE(0);
        }
}

void GreaterEqual(){
        // if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
        // return;
        // }
        // if(getTopIFELSECon() == 2 && (int)getTopIFELSE()==1 ){
        // return;
        // }
        double a = pop();
         if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }

        double b = pop();

         if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }

        if(a <= b){
            // printf("true");
            pushIFELSE(1);
        }
        else{
            //  printf("false");
            pushIFELSE(0);
        }
}


void Lessequal(){
        // if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
        // return;
        // }
        // if(getTopIFELSECon() == 2 && (int)getTopIFELSE()==1 ){
        // return;
        // }
        double a = pop();
         if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }

        double b = pop();

         if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }

        if(a >= b){
            // printf("true");
            pushIFELSE(1);
        }
        else{
            //  printf("false");
            pushIFELSE(0);
        }
}


void GreaterThan(){
        // if(getTopIFELSECon()== 1 && (int)getTopIFELSE()==0 ){
        // return;
        // }
        // if(getTopIFELSECon() == 2 && (int)getTopIFELSE()==1 ){
        // return;
        // }
        double a = pop();
         if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }

        double b = pop();

         if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }

        if(a < b){
            // printf("true");
            pushIFELSE(1);
        }
        else{
            //  printf("false");
            pushIFELSE(0);
        }
}

void LessThan(){
        // if(getTopIFELSECon() == 1 && (int)getTopIFELSE()==0 ){
        // return;
        // }
        // if(getTopIFELSECon()== 2 && (int)getTopIFELSE()==1 ){
        // return;
        // }
        double a = pop();
         if(isIDentifier[top+1] == 1){
        a = getIdentiferValue((int)a);
    }

        double b = pop();

         if(isIDentifier[top+1] == 1){
        b = getIdentiferValue((int)b);
    }

        if(a > b){
            // printf("true\n");
            pushIFELSE(1);
        }
        else{
            //  printf("false\n");
            pushIFELSE(0);
        }
}



void execute(){

int i =0;

for(int i=0;i<=ICGTOP;i++){

    // printf("%s\n",ICGstack[i].funName);
    // printf("%s\n",ICGstack[i].condition);
    if(strcmp(ICGstack[i].funName,"lastIdentifier")==0){
           lastIdentifier(ICGstack[i].value);
    }
    if(strcmp(ICGstack[i].funName,"equalequal")==0){
           equalequal();
    }
    if(strcmp(ICGstack[i].funName,"notequal")==0){
           notequal();
    }
    if(strcmp(ICGstack[i].funName,"GreaterThan")==0){
           GreaterThan();
    }
    if(strcmp(ICGstack[i].funName,"LessThan")==0){
           LessThan();
    }
    if(strcmp(ICGstack[i].funName,"GreaterEqual")==0){
           GreaterEqual();
    }
    if(strcmp(ICGstack[i].funName,"Lessequal")==0){
           Lessequal();
    }
    if(strcmp(ICGstack[i].funName,"assignIdentifierValue")==0){
              assignIdentifierValue();
         
    }
    if(strcmp(ICGstack[i].funName,"add")==0){
              add();    
    }
     if(strcmp(ICGstack[i].funName,"mod")==0){
              mod();    
    }
      if(strcmp(ICGstack[i].funName,"power")==0){
              power();    
    }
    if(strcmp(ICGstack[i].funName,"subtract")==0){
              subtract();    
    }
    if(strcmp(ICGstack[i].funName,"multiply")==0){
              multiply();    
    }
    if(strcmp(ICGstack[i].funName,"divide")==0){
              divide();    
    }
    if(strcmp(ICGstack[i].funName,"push")==0){
              push(ICGstack[i].value1);  
    }
    if(strcmp(ICGstack[i].funName,"printIdentifier")==0){
              printIdentifier(ICGstack[i].value);  
    }
    if(strcmp(ICGstack[i].funName,"pushString")==0){
        push(ICGstack[i].value1);
              pushString(ICGstack[i].value);
    }
    if(strcmp(ICGstack[i].funName,"println")==0){
              printf("\n");
    }
    if(strcmp(ICGstack[i].condition,"if-start")==0){
            //  printf("if-start  %d\n",getTopIFELSE());
             if(getTopIFELSE()==0){
                for(int j=i;j<=ICGTOP;j++){
                    if( (strcmp(ICGstack[j].condition,"ifelse")==0 || strcmp(ICGstack[j].condition,"else-start")==0) && ICGstack[j].conditioncode == ICGstack[i].conditioncode){
                       i=j;
                    //    printf("if-end || else strt foind  \n");
                        break;
                    }
                }
             }
             continue;

    }

    if(strcmp(ICGstack[i].condition,"else-start")==0){
        // printf("else-start  %d\n",getTopIFELSE());
             if(getTopIFELSE()==1){
                for(int j=i;j<=ICGTOP;j++){
                    // printf("searching after else start  %s  %d %d %d\n",ICGstack[j].condition,strcmp(ICGstack[j].condition,"ifelse"), ICGstack[j].conditioncode, ICGstack[i].conditioncode);
                    if( (strcmp(ICGstack[j].condition,"ifelse")==0) && ICGstack[j].conditioncode == ICGstack[i].conditioncode){
                       i=j;
                        // printf("if-end  \n");
                        break;
                    }
                }
             }
             continue;

    }

    if(strcmp(ICGstack[i].condition,"ifelse")==0){
             popIFELSE();
             continue;
    }

    if(strcmp(ICGstack[i].condition,"while-start")==0){
        // printf("while-start  %d\n",getTopIFELSE());
             if(getTopIFELSE()==0){
                for(int j=i;j<=ICGTOP;j++){
                    if( (strcmp(ICGstack[j].condition,"while-end")==0) && ICGstack[j].conditioncode == ICGstack[i].conditioncode){
                       i=j;
                        // printf("while-end  \n");
                        break;
                    }
                }
             }
             continue;

    }

    if(strcmp(ICGstack[i].condition,"while-end")==0){
        // printf("while-end  %d\n",getTopIFELSE());
             
                for(int j=i;j>=0;j--){
                    if( (strcmp(ICGstack[j].condition,"while")==0) && ICGstack[j].conditioncode == ICGstack[i].conditioncode){
                       i=j;
                        // printf("while-start  \n");
                        break;
                    }
                }
             
             continue;

    }




}


}

