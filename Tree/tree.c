#include "tree.h"

size_t gdcounter = 0;

Node* PlantTree (tree_t push)
{
    Node* tree = (Node*) calloc (1, sizeof (Node));
    tree->data = push;
    return tree;
}
Node* CpyTree (Node* tree)
{
    return RecCpyTree (tree);
}

Node* RecCpyTree (Node* tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    Node* newtree = PlantTree (tree->data);
    if (tree->left)
    {
        newtree->left = RecCpyTree (tree->left);
        if (!newtree->left)
        {
            return NULL;
        }
    }
    if (tree->right)
    {
        newtree->right = RecCpyTree (tree->right);
        if (!newtree->left)
        {
            return NULL;
        }
    }
    return newtree;
}


int ChopDown (Node* tree)
{
    if (tree == NULL)
    {
        return 1;
    }
    if (tree->left != NULL)
    {
        ChopDown (tree->left);
    }
    if (tree->right != NULL)
    {
        ChopDown (tree->right);
    }
    free (tree);
    return 0;
}

Node* SetLBranch (Node* leaf, tree_t push)
{
    if (leaf == NULL)
    {
        return NULL;
    }
    if (leaf->left != NULL)
    {
        return NULL;
    }
    leaf->left = (Node*) calloc (1, sizeof (Node));
    leaf->left->data = push;
    return leaf->left;
}

Node* SetRBranch (Node* leaf, tree_t push)
{
    if (leaf == NULL)
    {
        return NULL;
    }
    if (leaf->right != NULL)
    {
        return NULL;
    }
    leaf->right = (Node*) calloc (1, sizeof (Node));
    leaf->right->data = push;
    return leaf->right;
}

void PrintTree (const Node* const node, FILE* f)
{
    fprintf (f, "\tNODE_%p[label = \"{ <_node_> node:\\n%p | data:\\n ", node, node);
    fprintelem (f, node->data);
    fprintf (f, " | { <left> left:\\n%p | <right> right:\\n%p} }\"];\n", node->left, node->right);
    if (node->left)
    {
        PrintTree (node->left, f);
        fprintf (f, "\tNODE_%p:left:s -> NODE_%p:_node_:n [style = bold, dir = both, arrowhead = crow, arrowtail = dot, color = chocolate4];\n", node, node->left);
    }
    if (node->right)
    {
        PrintTree (node->right, f);
        fprintf (f, "\tNODE_%p:right:s -> NODE_%p:_node_:n [style = bold, dir = both, arrowhead = crow, arrowtail = dot, color = chocolate4];\n", node, node->right);
    }
}

int TreeDbgDump (const Node* const tree)
{
    assert (tree != NULL);
    FILE* graph = fopen ("logs/graph_dump.dot", "w");
    if (graph == NULL)
    {
        system ("mkdir logs/");
        graph = fopen ("logs/graph_dump.dot", "w");
    }
    fprintf (graph, "digraph G{\n");
    fprintf (graph, "\trankdir=TB;\n");
    fprintf (graph, "\tnode[color = forestgreen,shape=record, penwidth=3.0, style = filled, fillcolor = green];\n");
    PrintTree (tree, graph);
    fprintf (graph, "}\n");
    fclose (graph);
    char* cmd_mes = (char*) calloc (LEN0, sizeof (char));
    sprintf (cmd_mes, "dot -Tpng logs/graph_dump.dot -o logs/Graph_Dump%zd.png", gdcounter);
    system (cmd_mes);
    free (cmd_mes);
    system ("rm logs/graph_dump.dot");
    gdcounter++;
    return 0;
}
