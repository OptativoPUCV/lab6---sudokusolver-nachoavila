#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
 

    for(int f=0;f<9;f++){

      int arrayFila[10]={0};
      int arrayCol[10]={0};
      int arraySub[10]={0};

         for(int c=0;c<9;c++){

            if(n->sudo[f][c]!=0){
                if(arrayFila[n->sudo[f][c]]==1){
                    return 0;
                }else{
                    arrayFila[n->sudo[f][c]]=1;
                }
            }

             if(n->sudo[c][f]!=0){
                if(arrayCol[n->sudo[c][f]]==1){
                    return 0;
                }else{
                    arrayCol[n->sudo[c][f]]=1;
                }
            }
              int i=3*(f/3) + (c/3) ;
              int j=3*(f%3) + (c%3) ;
             if(n->sudo[i][j]!=0){
                 if(arraySub[n->sudo[i][j]]==1){
                     return 0;
                 }else{
                     arraySub[n->sudo[i][j]]=1;
                 }
             }
        }

    }


    return 1;
  
}

List* get_adj_nodes(Node* n){
  List* list=createList();

  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0 ){
        for(int aux = 1; aux < 10; aux++){
          n->sudo[i][j] = aux;
          Node* nuevoNodo = copy(n);
          if(is_valid(nuevoNodo) == 1){
            pushBack(list,nuevoNodo);
          }
        }
      }
    }
  }
  return list;
}


int is_final(Node* n){
  for(int i = 0 ; i < 9 ; i++){

    for(int j = 0 ; j < 9 ; j++){

      if(n->sudo[i][j] == 0) return 0;
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack * aux = createStack();
  push(aux, initial);

  while(is_empty(aux) != 1){

    Node * primero = top(aux);
    pop(aux);
    if(is_final(primero) == 1) return primero;
    List * lista = get_adj_nodes(primero);
    Node * nodos = first(lista);
    while(nodos != NULL){
      push(aux,nodos);
      nodos = next(lista);
    }
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/