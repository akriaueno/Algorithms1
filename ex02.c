/*  ヘッダを使い、循環させる場合の連結リストのプログラム
 *  L => Head => Cell(1) => Cell(2) => ... => Cell(n) => Head => ...
 */
#include<stdlib.h>
#include<stdio.h>

typedef int elemtype;
typedef struct Lcell *List;

struct Lcell {
  elemtype element;
  struct Lcell *next;
};

struct Lcell *GetNewCell() {
  struct Lcell *cell;
  cell = (struct Lcell *)malloc(sizeof(struct Lcell));
  return cell;
}

List LCreate() {
  List head;
  head = GetNewCell();
  head->next = head;  // 循環させる
  return head;
}

List Tail(List L) {
  List p = L;
  while(p->next != L) {
    p = p->next; 
  }
  return p;
}

int Length(List L) {
  int len = 0;
  List p = L->next;
  while(p != L) {  // Lはヘッダ
     len++;
     p = p->next;
  }
  return len;
}

void Insert(elemtype x, List p) {  // pの直後に挿入する
  struct Lcell *newcell;
  newcell = GetNewCell();
  newcell->element = x;
  newcell->next = p->next;
  p->next = newcell;
}

List Merge(List L1, List L2) {
  List head = LCreate(),  p1 = L1->next, p2 = L2->next;
  // p1とp2を比較しながら末尾にインサートする
  while (p1 != L1 && p2 != L2) {  // L1とL2はヘッダ
    if (p1->element < p2->element) {
      Insert(p1->element, Tail(head));
      p1 = p1->next;
    } else {
      Insert(p2->element, Tail(head));
      p2 = p2->next;
    }
  }
  // p1かp2の要素がまだ残っている場合はマージした後に付け加える
  while (p1 != L1) {
    Insert(p1->element, Tail(head));
    p1 = p1->next;
  }
  while (p2 != L2) {
    Insert(p2->element, Tail(head));
    p2 = p2->next;
  }
  return head;
}

void Show(List L) {
  List p = L->next;
  while(p != L) {
    printf("%d ", p->element);
    p = p->next;
  }
  printf("\n");
}

void Delete(List L) {
  List p = Tail(L);
  while (p != L) {
    printf("ただいまのリスト"); Show(L);
    Tail(Tail(L))->next = L;  // Tail(Tail(L))は末尾から2番目なのでこれをヘッダにつなぐ
    free(p);
    p = Tail(L);
  }
}

int main() {
  List L1, L2;
  int buf;
  L1 = LCreate();
  L2 = LCreate();
  printf("要素をリストL1, L2の末尾に追加します\n");
  printf("L1の要素を入力\n");
  while(scanf("%d", &buf) != EOF) {
    Insert(buf, Tail(L1));
  }
  printf("L2の要素を入力\n");
  while(scanf("%d", &buf) != EOF) {
    Insert(buf, Tail(L2));
  }
  printf("L1の長さは %d\n", Length(L1));
  printf("L2の長さは %d\n", Length(L2));
  printf("L1の要素は "); Show(L1);
  printf("L2の要素は "); Show(L2);
  printf("L1とL2をマージしたリストの要素は "); Show(Merge(L1, L2));
  Delete(L1);
  Delete(L2);
  return 0;
}
