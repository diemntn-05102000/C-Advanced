#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
#include"dllist.h"
#include"jval.h"
#define INFINITIVE_VALUE 1000000
typedef JRB Graph;
Graph createGraph()
{
  return make_jrb();
}
double adjacent(Graph graph, int v1, int v2)
{
  JRB node, tree;
  node = jrb_find_int(graph, v1);
  if(node==NULL)
    return INFINITIVE_VALUE;
  tree = (JRB)jval_v(node->val);
  node = jrb_find_int(tree,v2);
  if(node==NULL)
    return INFINITIVE_VALUE;
  else
    return jval_d(node->val);
}
void addEdge(Graph graph, int v1, int v2,double weight)
{
  JRB node, tree;
  if(adjacent(graph, v1, v2) == INFINITIVE_VALUE)
    {
      node = jrb_find_int(graph, v1);
      if(node==NULL)
	{
	  tree = make_jrb();
	  jrb_insert_int(graph, v1, new_jval_v(tree));
	}else
	{
	  tree = (JRB)jval_v(node->val);
	}
      jrb_insert_int(tree, v2, new_jval_d(weight));
    }
  if(adjacent(graph, v2, v1)== INFINITIVE_VALUE)
    {
      node = jrb_find_int(graph, v2);
      if(node==NULL)
	{
	  tree = make_jrb();
	  jrb_insert_int(graph, v2, new_jval_v(tree));
	}else
	{
	  tree = (JRB)jval_v(node->val);
	}
      jrb_insert_int(tree, v1, new_jval_d(weight));
    }
}

int getAdjacentVertices(Graph graph, int v, int *output)
{
  JRB tree, node;
  int total;
  node = jrb_find_int(graph, v);
  if(node == NULL)
    return 0;
  tree = (JRB)jval_v(node->val);
  total = 0;
  jrb_traverse(node, tree)
    {
      output[total] = jval_i(node->key);
      total++;
    }
  return total;
}
/*double shortestPath(Graph g,int s,int t,int* path,int* length)
{
    double distance[1000],min,w,total;
    int previous[1000], tmp[1000];
    int n,output[1000],i,u,v,start;
    Dllist ptr,queue,node;

    for(i=0;i<1000;i++)
        distance[i]= INFINITIVE_VALUE;
        distance[s]=0;
        previous[s]=s;
        queue = new_dllist();
        dll_append(queue,new_jval_i(s));
        while(!dll_empty(queue))
        {
            min = INFINITIVE_VALUE;
            dll_traverse(ptr,queue)
            {
                u = jval_i(ptr->val);
                if(min>distance[u])
                {
                    min = distance[u];
                    node = ptr;
                }
            }
	    
            dll_delete_node(node);
            if(u==t) break;
            n = getAdjacentVertices(g,u,output);
            for(i=0;i<n;i++)
            {
 
                v = output[i];
                w = adjacent(g,u,v);
                if(distance[v]>distance[u]+w);
                {
                    distance[v]= distance[u]+w;
                    previous[v]=u;
                }
             dll_append(queue,new_jval_i(v));
            }
        }
        total = distance[t];
       
        if(total!=INFINITIVE_VALUE)
        {
	  
            tmp[0] = t;
            n = 1;
	    u=t;
            while(u!=s)
            {
	     
                u = previous[u];
                tmp[n]= u;
	      n++;
            }
	    
            for(i=n-1;i>=0;i--)
            {
	      
                path[n-i-1]=tmp[i];
	       
            }
            *length = n;
        }
    free_dllist(queue);
    return total;
    }*/
double shortestPath(Graph G, int s, int t, int* path, int* length)
{
    int previous[100]; // Lưu các node trước đó, dùng để tìm đường đi (path)
    double distance[100]; // Khoảng cách ngắn nhất giữa S đến các đỉnh
    int add[100]; // Kiểm tra node đã visited
    Dllist queue = new_dllist();
    Dllist iter;
    Dllist node;
    int u;
    printf("S = %d - T = %d\n", s, t);
    for (int i = 0; i < 100; ++i)
        distance[i] = INFINITIVE_VALUE;
    distance[s] = 0;
    previous[s]=s;
     memset(add, 0, sizeof(int)*100);
    dll_append(queue, new_jval_i(s));
    add[s] = 1;

    while (!dll_empty(queue))
    {
        // Lấy ra đỉnh có khoảng cách gần s nhất trong queue
        double min = INFINITIVE_VALUE;
        printf("QUEUE: ");
        dll_traverse(iter, queue)
        {
            u = jval_i(iter->val);
            printf("%d - %.0lf | ", u, distance[u]);
            if (min > distance[u])
            {
                min = distance[u];
                node = iter;
            }
        }
        u = jval_i(node->val);
        printf("min = %.0lf | POP: %d\n", min, u);
        dll_delete_node(node);

        if (u == t)
	  {
	   
            break;
	  } 
        // Cập nhật lại khoảng cách của các đỉnh kề u so với s
        // So khoảng cách d[u] và d[v] + c(u, v)
        int n, v, w, output[100];
        n = getAdjacentVertices(G, u, output);
        for (int i = 0; i < n; ++i)
        {
            v = output[i];
            w = adjacent(G, u, v);
            if (distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                previous[v] = u;
            }

            if (!add[v])
            {
                add[v] = 1;
                dll_append(queue, new_jval_i(v));
            }    
        }
    }
    // Tìm đường đi (path), số đỉnh đi qua (length) và tổng quãng đường (return) (từ previous)
    int n, tmp[100];
    if(distance[t] != INFINITIVE_VALUE)
    {
        // Path
        tmp[0] = t;
        n = 1;
        u = t;
   
        while(u != s)
        {
	  
            u = previous[u];
            tmp[n] = u;
            n++;
        }
        *length = n;
        // Reverse

	for(int a = n-1 ; a >= 0 ; a--)
	  path[n-a-1] = tmp[a];
    }
    free_dllist(queue);
    return distance[t];

    }


void dropGraph(Graph graph)
{
  JRB node, tree;
  jrb_traverse(node, graph)
    {
      tree = (JRB)jval_v(node->val);
      jrb_free_tree(tree);
    }
  jrb_free_tree(graph);
}
int main()
{
  int path[100],length;
  double d;
  int i, n, output[100];
  Graph g = createGraph();
  addEdge(g, 0, 1,10);
  addEdge(g, 1, 2,20);
  addEdge(g, 1, 3,15);
  addEdge(g, 2, 3,25);
  addEdge(g, 2, 4,5);
  addEdge(g, 4, 5,30);
  /* n = getAdjacentVertices(g, 1, output);
  if(n == 0)
    printf("No adjacent vertices of node 1\n");
  else
    {
      printf("Adjacent vertices of node 1 : ");
      for(i=0; i<n; i++)
	{
	  printf("%5d",output[i]);
	}
      printf("\n");
      }
  printf("\nBFS: start from node 1 to 5:");
  BFS(g, 1, 4, printVertex);
  printf("\nBFS: start from node 1 to all:");
  BFS(g, 1, -1, printVertex);
  printf("\nDFS: start from node 2 to 5:");
  DFS(g, 1, 4, printVertex);
  printf("\nDFS: start from node 1 to all:");
  DFS(g, 1, -1, printVertex);*/
 
  d = shortestPath(g, 1, 5, path, &length);
  printf("%.2lf",d);
  printf("\n");
  dropGraph(g);
  return 0;
}
  
