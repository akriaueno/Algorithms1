#include<stdio.h>
#include<stdlib.h>
#include<err.h>

typedef int elmtype;
typedef struct Lcell *LcellP;
typedef struct Stack *StackP;

struct Lcell {
  elmtype element;
  struct Lcell *next;
};

struct Stack {
  LcellP top;
  LcellP elements;
};

StackP initstack() {
  StackP s = (StackP)malloc(sizeof(struct Stack));
  LcellP l = (LcellP)malloc(sizeof(struct Lcell));  //ダミーヘッド
  l->next = NULL;
  s->top = NULL;
  s->elements = l;
  return s;
}

void StPush(elmtype x, StackP st) {
  LcellP n = (LcellP)malloc(sizeof(struct Lcell));
  LcellP p = st->elements;  // st->elementsの末尾を示すためのポインタ
  n->element = x;
  n->next = NULL;
  while(p->next != NULL) p = p->next;  // 末尾を見つける
  p->next = n;
  st->top = n;
}

elmtype StPop(StackP st) {
  if (st->top == st->elements) err(EXIT_FAILURE, "Stack is empty");
  elmtype x = st->top->element;
  LcellP garbage = st->top;
  LcellP new_top = st->elements;
  while(new_top->next != garbage) new_top = new_top->next;
  st->top = new_top;
  new_top->next = NULL;
  free(garbage);
  return x;
}

int main() {
  int x;
  char buf[128];
  StackP s = initstack();
  while(fgets(buf,sizeof(buf),stdin) != NULL) {
    if(buf[0] == 'p') {
      printf("POP! %d\n", StPop(s));
    } else {
      sscanf(buf,"%d", &x);
      StPush(x, s);
    }
  }
}
