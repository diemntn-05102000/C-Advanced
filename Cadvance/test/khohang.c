#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "graph_muahang.h"

// Lưu tên và id sản phẩm
JRB input_SP(char* file_name, int* m)
{
    JRB tree = make_jrb();
    FILE* f = fopen(file_name, "r");
    char name[20];
    int id;

    fscanf(f, "%d\n", m);
    for (int i = 0; i < *m; ++i)
    {
        fscanf(f, "%s %d\n", name, &id);
        jrb_insert_int(tree, id, new_jval_s(strdup(name)));
    }
    return tree;
}

// Nhập tên, id và số lượng sản phẩm của kho hàng
Graph intput_KH(char* file_name, int m)
{
    Graph G = createGraph();
    FILE* f = fopen(file_name, "r");
    int n;
    char name[30];
    int id1, id2, sl;
    double d;

    fscanf(f, "%d\n", &n); // Số lượng kho hàng
    for (int i = 0; i < n; ++i)
    {
        fscanf(f, "%s %d\n", name, &id1); // Tên và id kho hàng
        addVertex(G, id1, name);
        JRB tree = make_jrb();
        jrb_insert_int(G.SP, id1, new_jval_v(tree));
        for (int i = 0; i < m; ++i)
        {
            fscanf(f, "%d %d\n", &id1, &sl); // Id và số lượng sản phẩm trong kho hàng
            jrb_insert_int(tree, id1, new_jval_i(sl));
        }
    }

    fscanf(f, "%d\n", &n); // Số lượng liên kết
    for (int i = 0; i < n; ++i)
    {
        fscanf(f, "%d %d %lf\n", &id1, &id2, &d);
        addEdge(G, id1, id2, d);
        addEdge(G, id2, id1, d);
    }
    return G;
}

// Lấy số lượng của 1 sản phẩm trong 1 kho hàng
int getSL(Graph G, int id_kh, int id_sp)
{
    JRB tree = (JRB) jval_v(jrb_find_int(G.SP, id_kh)->val);
    JRB node = jrb_find_int(tree, id_sp);
    return jval_i(node->val);
}

int main(int argc, char* argv[])
{
    if (argc == 1)
        return 0;
    
    if (strcmp(argv[1], "-t") == 0)
    {
        printf("C-Advanced, HK20182\n");
        return 0;
    }

    if (strcmp(argv[1], "-s") == 0)
    {
        int m;
        JRB SP = input_SP(argv[2], &m);
        JRB iter;
        jrb_traverse(iter, SP)
        {
            printf("%s %d\n", jval_s(iter->val), jval_i(iter->key));
        }
        jrb_free_tree(SP);
        return 0;
    }

    if (strcmp(argv[1], "-w") == 0)
    {
        int m;
        JRB SP = input_SP(argv[3], &m);
        Graph KH = intput_KH(argv[2], m);
        int id1 = atoi(argv[4]);
        int id2 = atoi(argv[5]);
        double d;

        if (!jrb_find_int(KH.vertices, id1) || !jrb_find_int(KH.vertices, id2))
            printf("-1\n");
        else
        {
            d = getEdgeValue(KH, id1, id2);
            if (d == INFINITIVE_VALUE)
                printf("-1\n");
            else
                printf("%.0lfkm\n", d);
        }
        jrb_free_tree(SP);
        dropGraph(KH);
        return 0;
    }

    if (strcmp(argv[1], "-a") == 0)
    {
        int m;
        JRB SP = input_SP(argv[3], &m);
        Graph KH = intput_KH(argv[2], m);
        JRB iter1, iter2, tree;
        jrb_traverse(iter1, KH.SP)
        {
	  printf("%s \n", getVertex(KH, jval_i(iter1->key)));
            tree = (JRB) jval_v(iter1->val);
            jrb_traverse(iter2, tree)
            {
                printf("%s %d\n", jval_s(jrb_find_int(SP, jval_i(iter2->key))->val), jval_i(iter2->val));
            }
            if (jrb_next(iter1) != jrb_nil(KH.SP))
                printf("-----\n");
        }
        jrb_free_tree(SP);
        dropGraph(KH);
        return 0;
    }

    if (strcmp(argv[1], "-h") == 0)
    {
        int m;
        JRB SP = input_SP(argv[3], &m);
        Graph KH = intput_KH(argv[2], m);
        int id_sp = atoi(argv[4]);
        int id_kh = atoi(argv[5]);
        JRB node, tree;

        printf("%s\n", getVertex(KH, id_kh));
        tree = (JRB) jval_v(jrb_find_int(KH.SP, id_kh)->val);
        node = jrb_find_int(tree, id_sp);
        printf("%s %d\n", jval_s(jrb_find_int(SP, id_sp)->val), jval_i(node->val));

        int n, output[100];
        n = outdegree(KH, id_kh, output);
        if (n > 0)
        {
            printf("---- Cac kho ke la: \n");
            for (int i = 0; i < n; ++i)
            {
                printf("%s\n", getVertex(KH, output[i]));
                tree = (JRB) jval_v(jrb_find_int(KH.SP, output[i])->val);
                node = jrb_find_int(tree, id_sp);
                printf("%s %d\n", jval_s(jrb_find_int(SP, id_sp)->val), jval_i(node->val));
            }
        }
        jrb_free_tree(SP);
        dropGraph(KH);
        return 0;
    }

    if (strcmp(argv[1], "-g") == 0)
    {
        int m;
        JRB SP = input_SP(argv[3], &m);
        Graph KH = intput_KH(argv[2], m);
        double time = 0; // Tính theo giờ
        int id_sp = atoi(argv[4]);
        int sl = atoi(argv[5]);
        int id_kh1 = atoi(argv[6]);
        int id_kh2 = atoi(argv[7]);
	int path[1000],length;
        // if (getSL(KH, id_kh1, id_sp) >= sl)
        //     time += 0.5;
        //     // printf("Dat hang thanh cong. Thoi gian giao hang la 30 phut\n");
        // else
        // {
        //     // int path[100], length;
        //     // double d = shortestPath(KH, id_kh1, id_kh2, path, &length);
        //     // printf("%.0lf\n", d);
        // }
        if (getSL(KH, id_kh1, id_sp) >= sl)
            printf("Dat hang thanh cong. Thoi gian giao hang la 30 phut\n");
        if (getSL(KH, id_kh1, id_sp) + getSL(KH, id_kh2, id_sp) < sl)
            printf("Dat hang khong thanh cong\n");
        if (getSL(KH, id_kh1, id_sp) + getSL(KH, id_kh2, id_sp)>= sl)
	  {
            double d = shortestPath(KH, id_kh1, id_kh2, path, &length);
            printf("%.0lf\n", d);
	  }
        jrb_free_tree(SP);
        dropGraph(KH);
        return 0;
    }  
}
