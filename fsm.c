#include <stdio.h>
int main(int argc, char* argv[]){
  FILE *def; //definition of the fsm
  FILE *inp; //input stream
  
  def = fopen(argv[1],"r");
  inp = fopen(arv[2],"r");

  char line[200];

  while (fgets(line, sizeof(line),def)){
    printf("%s",line);
  }
  fclose(def);
  return 0;
}

  
