#include "stdio.h"
#include "stdlib.h"

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}Node;

typedef struct tree{
    Node* root;
}Tree;

int count = 0, sum[100] = {0}, max = 0;

/* Yeni düğüm döndüren fonksiyon */
Node* new_Node(void){
    Node* new_node=(Node*)malloc(sizeof(Node));
    printf("Enter new value: ");
    scanf("%d",&new_node->data);
    new_node->left=NULL;
    new_node->right=NULL;
    return new_node;
}

/* Yeni ağaç döndüren fonksiyon */
Tree* new_Tree(void){
    Tree* new_tree=(Tree*)malloc(sizeof(Tree));
    new_tree->root=NULL;
    return new_tree;
}

/* Ağaca düğüm ekleme fonksiyonu */
void insert(Node* new_node,Tree* tree){
    if(tree->root==NULL || new_node->data==tree->root->data){ /* Kök düğüme ekleme */
        tree->root=new_node;
        return;
    }
    Node* tmp=tree->root;
    while(1){
        if(tmp->data>new_node->data){
            if(tmp->left==NULL){ /* Sola ekleme */
                tmp->left=new_node;
                return;
            }
            tmp=tmp->left;
        }
        else if(tmp->data<new_node->data){ /* Sağa ekleme */
            if(tmp->right==NULL){
                tmp->right=new_node;
                return;
            }
            tmp=tmp->right;
        }
        else{ /* Eklenen sayinin agacta olma durumu */
            printf("The number you added is already there!\n");
            return;
        }
    }
}

/* Ağaçtaki düğümlerin toplamını veren fonksiyon */
int sum_Of_Nodes(Node* node){
    if(node==NULL){
        return 0;
    }
    return node->data+sum_Of_Nodes(node->left)+sum_Of_Nodes(node->right);
}

/* Aynı düzeydeki elemanların toplamını bulan fonksiyon */
void sum_Of_Same_Level_Nodes(Node* node){
    if(node->left!=NULL){
        count++;
        sum_Of_Same_Level_Nodes(node->left);
    }
    sum[count] = sum[count] + node->data;  /* Aynı düzeydeki elemanların toplanmasi */
    if(max < count){
        max = count;
    }
    if(node->right!=NULL){
        count++;
        sum_Of_Same_Level_Nodes(node->right);
    }
    count--;
}

/* Menu fonksiyonu */
void menu(Tree* tree){
    printf("Welcome");
    int x;
    while (1){
        printf("\n\nSelect action:\n\n1:Add a node to tree\n2:Show sum of nodes\n3:Show sum of same level nodes\n\n");
        printf("Choice: ");
        scanf("%d",&x);
        printf("\n");
        switch (x){
            case 1:
                insert(new_Node(),tree);
                break;
            case 2:
                printf("Sum: %d\n",sum_Of_Nodes(tree->root));
                break;
            case 3:
                sum_Of_Same_Level_Nodes(tree->root);
                printf("Sum of nodes : \n Level \t Sum ");
                for (int i = 0; i <= max; i++)
                    printf("\n %d \t: %d ", i, sum[i]);
                break;
            default:
                printf("Wrong choice!!");
                break;
        }
    }
}

int main(){
    Tree* tree=new_Tree();
    menu(tree);
    return 0;
}
