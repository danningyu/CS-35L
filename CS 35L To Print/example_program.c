#include <stdio.h>
#include <stdlib.h>

// Macro
#define BUFFER_SIZE 1024
#define min(X, Y) ((X) < (Y) ? (X) : (Y))

void f ( int ** a , int ** b);
int f1 (int a);
int f2 (int a);



int main(int argc, char *argv[]) {
  int a = 10;
  int b = 15;
  
  // Pointer to pointer
  int * a_p = &a;
  int * b_p = &b;

  printf("before f: a_p points to %d\n", *a_p);
  printf("%p\n", (void *) a_p);

  // Pass pointer to pointer to function
  f(&a_p, &b_p);
  printf("%p\n", (char *) a_p);

  printf("after f: a_p points to %d\n", *a_p);
  // printf ("Number of arguments %d, the first argument is %s\n", argc, argv[1]);
  int arr1[10];
  // printf("%lu \n", sizeof(arr1)); 


  // Put int i outside the loop for some older version of C
  // int i;
  // for ( i =0; i<5; i+=1) {
  //   printf("%d", i);
  // }


  // Function Pointer
  int (*fn_ptr)(int);
  fn_ptr = f2;
  printf("Return is: %d \n",(*fn_ptr)(1));

  char * p_c;
  printf("pointer: %p\n", p_c);
  p_c = malloc(1);
  printf("pointer: %p\n", p_c);
  *p_c = 'a';
  // Don't try this!! You only allocate 1 bytes but trying to access 2 bytes 
  // This might work on your computer, but actually undefined behavior
  *(p_c+1) = 'b';
  printf("charactor is %c \n", *p_c);
  free(p_c);
  // Don't try this!! You free the memory but try to access again
  // This might work on your computer, but actually undefined behavior
  printf("charactor is %c \n", *p_c);
  return 0;
}

void f ( int ** a_ptr , int ** b_ptr) {
  printf("%p\n", *a_ptr);
  // printf("%p\n", a_ptr);
  *a_ptr = *b_ptr;      
}

int f1 (int a) {
  return a+1;
}

int f2 (int a) {
  return a-1;
}