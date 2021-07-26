#include "graph_jrb.h"
#include "fields.h"
#include "jrb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n;
int main() {
  int choose;
  char *filename = "pageConnections.txt";
  char *file2 = "webpages.txt";
  Graph g = createGraph();
  Graph h = createGraph();
  readFile(g, filename);
  ReadFile2(g, file2);
  readFile(h, filename);
  ReadFile2(h, file2);
  do {
    printf("\n\n-------------MENU-------------\n");
    printf("1.In so luong web va URL\n");
    printf("2.Web co nhieu lien ket nhat\n");
    printf("3.PageRank\n");
    printf("4.spam and lien ket\n");
    printf("5.Min\n");
    printf("6.Thoat\n");
    printf("Lua chon cua ban la:");
    scanf("%d%*c", &choose);
    switch (choose) {
    case 1: {
      JRB NODE;
      printf("Tong cong ID ban co la:%d\n", n);
      printf("Danh sach:");
      printf("\n");
      jrb_traverse(NODE, g.vertices) {
        printf("%d %s", NODE->key, NODE->val);
        printf("\n");
      }
      printf("\n");
      maxmin(g);
      printf("\n");
      break;
    }
    case 2: {
      khoitao(g);
      TinhToan(g);
      JRB node;
      jrb_traverse(node, g.vertices) {
        printf("%d %.2lf\n", node->key, node->val.d);
      }
      sosanhcotrongso(g, h);
      break;
    }
    case 3: {
      printf("So lan lap ban mong muon:");
      int m;
      scanf("%d%*c", &m);
      for (int i = 0; i < m; i++) {
        TinhToan(g);
      }
      opt3(g, h);
      break;
    }
    case 4: {
      option4(g);
      break;
    }
    case 5: {
      opt5(h);
      break;
    }
    case 6: {
      break;
    }
    }
  } while (choose != 6);
}

//a b c
void readFile(Graph g, char *filename) {
  IS is = new_inputstruct(filename);
  if (is == NULL) {
    printf("Error: File Fail!\n");
    exit(1);
  }
  get_line(is);
  n = atoi(is->fields[0]);
  while (get_line(is) > 0) {
    int id1 = atoi(is->fields[0]);
    for (int i = 1; i < is->NF; i++) {
      int id2 = atoi(is->fields[i]);
      addEdge(g, id1, id2, 1);
    }
  }
}
void maxmin(Graph g) {
  int max, min;
  max = -1000;
  min = 1000;
  int nowmax;
  int nowmin;
  JRB node;
  jrb_traverse(node, g.vertices) {
    int m;
    int output[100];
    m = indegree(g, jval_i(node->key), output);
    if (m > max) {
      max = m;
      nowmax = jval_i(node->key);
    }
    if (m < min) {
      min = m;
      nowmin = jval_i(node->key);
    }
  }
  node = jrb_find_int(g.vertices, nowmax);
  printf("Webpage  co nhieu lien ket toi nhat:%s\n", jval_s(node->val));
  node = jrb_find_int(g.vertices, nowmin);
  printf("Webpage co it lien ket toi nhat:%s\n", jval_s(node->val));
}
void option4(Graph g) {
  JRB node;
  int output[100];
  int den = 0;
  int vao = 0;
  jrb_traverse(node, g.vertices) {
    int in = indegree(g, jval_i(node->key), output);
    int out = outdegree(g, jval_i(node->key), output);
    if (in == 0) {
      den++;
    }
    if (out == 0) {
      vao++;
    }
  }
  printf("So web chi co lien ket den khong co lien ket di:%d\n", den);
  printf("So web chi co lien ket di khong co lien ket den:%d\n", vao);
}
void ReadFile2(Graph g, char *filename) {
  IS is = new_inputstruct(filename);
  if (is == NULL) {
    printf("Error: File Fail!\n");
    exit(1);
  }
  get_line(is);
  int m = atoi(is->fields[0]);
  while (get_line(is) > 0) {
    int id = atoi(is->fields[1]);
    addVertex(g, id, is->fields[0]);
  }
}
void khoitao(Graph g) {
  JRB node;
  double x = 1;
  jrb_traverse(node, g.vertices) { node->val.d = x; }
}
void TinhToan(Graph g) {
  JRB node;
  int out1, out2;
  int output1[100], output2[100];
  jrb_traverse(node, g.vertices) {
    int id = jval_i(node->key);
    out1 = outdegree(g, id, output1);
    for (int i = 0; i < out1; i++) {
      JRB node1 = jrb_find_int(g.vertices, output1[i]);
      int h = outdegree(g, output1[i], output2);
      if (h != 0) {
        node->val.d += (node1->val.d) / h;
      } else {
        node->val.d += node1->val.d;
      }
    }
  }
}
void sosanhcotrongso(Graph g, Graph h) {
  double max, min;
  max = -1000;
  min = 1000;
  int nowmax;
  int nowmin;
  JRB node;
  jrb_traverse(node, g.vertices) {
    double m;
    m = node->val.d;
    if (m > max) {
      max = m;
      nowmax = jval_i(node->key);
    }
    if (m < min) {
      min = m;
      nowmin = jval_i(node->key);
    }
  }

  printf("%d\n", nowmax);
  JRB NODE1 = jrb_find_int(h.vertices, nowmax);
  printf("URL cua page co trong so lon nhat:%s\n\n", jval_s(NODE1->val));
  //   printf("1.\n");
  NODE1 = jrb_find_int(h.vertices, nowmin);
  printf("URL cua page co trong so nho nhat:%s\n", jval_s(NODE1->val));

  //   printf("Webpage  co nhieu lien ket toi nhat:%d\n", jval_s(node->val));
  //   node = jrb_find_int(g.vertices, nowmin);
  //   printf("Webpage co it lien ket toi nhat:%%d\n", jval_s(node->val));
}
void opt3(Graph g, Graph h) {
  JRB node1, node2;
  jrb_traverse(node1, g.vertices) {
    double m = jval_d(node1->key);
    printf("%lf\n", m);
    // jrb_insert_dbl(node2, node1->val.d, );
    // printf("1\n");
  }

  jrb_traverse(node1, node2) {
    int i = 0;
    if (i == 3) {
      break;
    }
    JRB FINAL = jrb_find_int(h.vertices, node1->val.i);
    printf("%s\n", jval_s(FINAL->val));
    i++;
  }
}
void opt5(Graph g) {
  int id1, id2;
  printf("Nhap id1:");
  scanf("%d%*c", &id1);
  printf("Nhap id2:");
  scanf("%d%*c", &id2);
  if (id1 == id2) {
    printf("-1\n");
    exit(3);
  }
  JRB node = jrb_find_int(g.vertices, id1);
  if (node == NULL) {
    printf("-1\n");
    exit(3);
  }
  node = jrb_find_int(g.vertices, id2);
  if (node == NULL) {
    printf("-1\n");
    exit(3);
  }
  int output[100];
  int ketqua = shortest_noWeight_path(g, id1, id2, output);
  if (ketqua == INFINITIVE_VALUE) {
    printf("-1\n");
    exit(1);
  }

  printf("Ket qua cuoi cung la:%d\n", ketqua - 1);
}
