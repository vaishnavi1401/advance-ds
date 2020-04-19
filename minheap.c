#include<stdio.h>
void minheapinsertion(int heap[],int n)
{
   int now,element,i;
      for(i=0;i<n;i++)
            printf("%d  ",heap[i]);
            printf("\n");
     heap[0]=-99;
        now=n;
        element=heap[n-1];
        printf("%d \n",element);
        while(heap[now/2]>element)
        {

            heap[now]=heap[now/2];
            now=now/2;
        }
        heap[now]=element;


}
void minheapdeletion(int heap[],int n)
{
 int now=1,child=now*2;
 printf("%d",heap[now]);
 int ele=heap[n];
 n--;
 while(heap[child]<ele&&child<n)
 {
     if(heap[child]>heap[child+1])
     child =child+1;
     heap[now]=heap[child];
     now=child;
     child=now*2;
 }
 heap[now]=heap[child];
}
int main()
{
    int n,i;
    printf("enter nodes");
    scanf("%d",&n);
int heap[n+1];
    for(i=1;i<=n;i++)
        scanf("%d",&heap[i]);
        minheapinsertion(&heap,n+1);
                        for(i=0;i<n;i++)
            printf("%d  ",heap[i]);
            printf("\n");
        minheapdeletion(&heap,n);
for(i=0;i<n;i++)
            printf("%d  ",heap[i]);
            printf("\n");


}

