#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
  int somma;
  int chiave;
}grafo;

void costruisci_max_heap(grafo top[],int k);
void max_heapify(grafo top[],int i,int k);
int scan_number();
int AggiungiGrafo(int n,int*matrix);
void TopK(grafo top[],int k);
int dijkstra(int vet[],int n);


int main()
{
  int k,n,chiave=0,*matrix,somma,cont,i; //k migliori grafi, n numero nodi,matrice salva il grafo corrente,somma è la somma dei cammini,cont aiuta nel contare i caratteri letti
  grafo *top;// salva chiave e somma dei cammini minimi
  char c,input[14];//per non usare scanf
  n=scan_number();
  k=scan_number();
  matrix = (int *)malloc((n * n) * sizeof(int));
  top=(grafo*)malloc(k*sizeof(grafo));
  for(i=0;i<k;i++)
    top[i].chiave=-1;
  while(1)
  {
    c=getchar_unlocked();
    cont=0;
    if(c==EOF)
      break;
    while(c!='\n')
    {
      input[cont]=c;
      cont++;
      c=getchar_unlocked();
    }
    input[cont]='\0';
    if(strcmp(input,"AggiungiGrafo")==0)
    {
      somma=AggiungiGrafo(n,matrix);
      if(chiave<k-1)//se ci sono meno di k grafi lo inserisco tranquillamente nel vettore
      {
        top[chiave].chiave=chiave;
        top[chiave].somma=somma;
      }
      else if(chiave==k-1)//creo maxHeap
      {
        top[chiave].chiave=chiave;
        top[chiave].somma=somma;
        costruisci_max_heap(top,k);
      }
      else if(top[0].somma>somma)//sostituisco il valore più alto e modifico l'albero per farlo ridiventare un MaxHeap
      {
        top[0].chiave=chiave;
        top[0].somma=somma;
        max_heapify(top,0,k);
      }
      chiave++;
    }
    else if(strcmp(input,"TopK")==0)
      TopK(top,k);
    input[0]='\0';//resetto ingresso per utilizzare getchar in modo corretto
  }
  free(top);
  free(matrix);
  return 0;
}
void costruisci_max_heap(grafo top[],int k)
{
  int i,max=(k/2)-1;
  for(i=max;i>=0;i--)
    max_heapify(top,i,k);
  return;
}

void max_heapify(grafo top[],int i,int k)
{
  int l=2*i+1,r=2*i+2,posmax;
  grafo appoggio;
  if(l<k && top[l].somma>top[i].somma)
    posmax=l;
  else
    posmax=i;
  if(r<k && top[r].somma>top[posmax].somma)
    posmax=r;
  if(posmax!=i)
  {
    appoggio=top[i];
    top[i]=top[posmax];
    top[posmax]=appoggio;
    max_heapify(top,posmax,k);
  }
  return;
}

int AggiungiGrafo(int n,int*matrix)//salvo il grafo eritorno la somma dei cammni
{
  int somma_cammini;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      matrix[i*n+j]=scan_number();
    }
  }
  somma_cammini = dijkstra(matrix,n);
  return somma_cammini;
}

void TopK(grafo top[],int k)//stampa MaxHeap
{
  int i;
  for(i=0;i<k;i++)
  {
    if(top[i].chiave==-1)
      break;
    if(i==k-1 || top[i+1].chiave==-1)
      printf("%d",top[i].chiave);
    else
      printf("%d ",top[i].chiave);
  }
  printf("\n");
  return;
}


int dijkstra(int vet[],int n)
{
  int i,nodo=0,j,min,*cammini,*completati,ris=0;
  cammini =malloc(sizeof(int)*n);
  completati= malloc(sizeof(int)*n);
  for(i=0;i<n;i++)
  {
    completati[i]=0;
    cammini[i]=0;
  }
  for(i=0;i<n-1;i++)
  {
    min=0;
    if(i!=0)
    {
      for(j=1;j<n;j++)// scelta nuovo nodo
      {
        if(((min>cammini[j] && min!=0) || min==0) && completati[j]==0 && cammini[j]!=0)
        {
          min=cammini[j];
          nodo=j;
        }
      }
      if(min==0)//esci dal ciclo se gli altri nodi non sono connessi
        break;
    }
    completati[nodo]=1;
    for(j=1;j<n;j++)
    {
      if(nodo!=j && vet[n*nodo+j]!=0 && (vet[n*nodo+j]+cammini[nodo]<cammini[j] || cammini[j]==0 ))
        cammini[j]=vet[n*nodo+j]+cammini[nodo];
    }
  }
  for(i=0;i<n;i++)
    ris+=cammini[i];
  free(cammini);
  free(completati);
  return ris;
}

int scan_number()//uso getchar per salvare del tempo
{
  char c;
  int a=0;
  c=getchar_unlocked();
  while(c<'0' || c>'9')
    c=getchar_unlocked();
  while(c>='0' && c<='9')
  {
    a=a*10+c-48;
    c=getchar_unlocked();
  }
  return a;
}
