#include<stdio.h>
int main(){
  FILE *fp;
  int n;
  fp=fopen("file1.data","r");
  if(fp==NULL){
    printf("Cannot open file file1.data\n");
  }
  while(1){
    n=fgetc(fp);
    if(n==EOF) break;
    putchar(n);
  }
  printf("\n");
  fclose(fp);
  return 0;
}
