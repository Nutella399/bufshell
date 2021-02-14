#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

//DO THIS MYSELF 
/*
char** parsestring(char string[100]) {
  char** args = malloc(10*sizeof(char*));
  int i = 0; 
  char* token; 
  token = strtok(string, " "); 
  while(token != NULL) {
    args[i] = token; 
    i++;
    token = strtok(NULL, "\0"); 
  }
  return args; 
}
*/


char** parsestring(char* string) {
  char** args = malloc(10*sizeof(char*));
  for(int l = 0; l < 2; l++) {
    args[l] = malloc(10*sizeof(char));
    //args[l]= 0; 
  }
  
  int i = 0; 
  int j = 0;
  int k = 0;   
  while(string[k] != 0) {
    if(string[k] == 32 && string[k-1] != 32 && k-1 >= 0) {
     i++;
     j = 0; 
    }else if(string[k] != 32) {
      args[i][j] = string[k]; 
      j++;
    } 
    k++;
  }
  printf("%d", i); 
  //args[i++][0] = '\0';
  return args; 
}

char* getinput() {
  char* string = NULL;
	size_t length = 0; 
	int trueLength = getline(&string, &length, stdin);
	string[trueLength-1] = 0; 
	return string; 
}

char** seperateargs(char** string) {
  char** args = malloc(10*sizeof(char*)); 
  int i = 0; 
  while(string[i+1] != 0) {
    printf("here"); 
    args[i] = string[i+1]; 
    i++; 
  }
  args[i] = 0; 
  return args; 
}

//autocomplete function

//history functions 

int main() {
  printf("\e[1;1H\e[2J");
	char cmd[100];
	char s[100]; 
  pid_t cpid; 
	while (1) {
	  char* string;
	  printf("$>");
	  string =  getinput(); 
	  char** cmd = parsestring(string);
	  if(strncmp("exit",cmd[0], 5) == 0) {
	    break;
	  } else if(strncmp("cd",cmd[0], 3) == 0) {
	    chdir(cmd[1]); 
	  } else if(strncmp("pwd",cmd[0],4) == 0) {
	    printf("%s \n", getcwd(s,100)); 
	  } else {
	    char** args = seperateargs(cmd);   
	    cpid = fork();
	    if(cpid == 0) {
	      execvp(cmd[0], args); 
	    }else {
	      wait(NULL); 
	    } 
	  }
	  
 	}
	return 0; 
}

