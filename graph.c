#include <stdio.h>
typedef struct graph
{
  int dest;
  struct graph *next;

} graph_type;
int visited[10];
graph_type source[10];
void addedge(int s, int d)
{
  graph_type *t;
  t = (graph_type *)malloc(sizeof(graph_type));
  if (t != NULL)
  {
    t->next = source[s].next;
    t->dest = d;
    source[s].next = t;
  }
}
void printgraph(int v)
{

  for (int i = 0; i < v; i++)
  {
    printf("%d", i);
    graph_type *p = source[i].next;
    while (p != NULL)
    {
      printf("-->%d ", p->dest);
      p = p->next;
    }
    printf("\n");
  }
}

int main()
{
  int s, d, v, e, i;
  printf("enter no of vertices");
  scanf("%d", &v);
  printf("enter no of edges");
  scanf("%d", &e);
  for (i = 0; i < e; i++)
  {
    printf("enter source and destination");
    scanf("%d%d", &s, &d);
    addedge(s, d);
  }
  printgraph(v);
  
}
