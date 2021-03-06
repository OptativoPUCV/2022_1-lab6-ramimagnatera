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
  int f = 0;
  int c = 0;
  
  //filas
  for(f = 0 ; f < 9 ; f++){
    int fila[10] = {0};
    for(c = 0 ; c < 9 ; c++){
      if(fila[n->sudo[f][c]] != 0) return 0;
      if(fila[n->sudo[f][c]] == 0 && n->sudo[f][c] != 0){
        fila[n->sudo[f][c]] = 1;
      }
    }
  }
  
  //columna
  for(f = 0 ; f < 9 ; f++){
    int columna[10] = {0};
    for(c = 0 ; c < 9 ; c++){
      if(columna[n->sudo[c][f]] != 0) return 0;
      if(columna[n->sudo[c][f]] == 0 && n->sudo[c][f] != 0){
        columna[n->sudo[c][f]] = 1;
      }
    }
  }
  
  for (f = 0; f < 9; f++){
    int aux = f;
    int matriz[10] = {0};
    for (c = 0; c < 9 ; c++){
      int a = 3*(aux/3) + (c/3);
      int b = 3*(aux%3) + (c%3);
      if (matriz[n->sudo[a][b]] != 0) return 0;
      if(matriz[n->sudo[a][b]] == 0 && n->sudo[a][b] != 0){
      matriz[n->sudo[a][b]]=1;
      }
    }
  }    
  return 1;
}

List* get_adj_nodes(Node* n){
  List* list=createList();
  int cont = 9;
  for(int i = 0 ; i < 9 ; i++){
    for(int j = 0 ; j < 9 ; j++){
      if (n->sudo[i][j] == 0){
        while(cont > 0){
          Node * new = copy(n);
          new->sudo[i][j] = cont;
          if (is_valid(new)) pushFront(list,new);
          cont--;
        }
        return list; 
      }
    }
  }  
  return list;       
}


int is_final(Node* n){
    for(int i = 0 ; i < 9 ; i++){
      for(int j = 0 ; j < 9 ; j++){
        if (n->sudo[i][j] == 0){
          return 0;
        }
      }
    }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  
  Stack* st = createStack();
  push(st, initial);

  while(get_size(st) != 0){
    Node* n = top(st);
    pop(st);
    if(is_final(n)) return n;
    
    List* list = get_adj_nodes(n);
    Node* aux = first(list);
    
    while(aux != NULL){
      push(st,aux);
      aux = next(list);
    }
    
    (*cont)++;
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