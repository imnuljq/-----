//
//  main.cpp
//  二叉搜索树操作集
//
//  Created by s20181105883 on 2019/12/24.
//  Copyright © 2019 s20181105883. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
//∂˛≤Ê ˜Ω⁄µ„ ˝æ›Ω·ππ∂®“Â
typedef struct _node{
    int value;
    struct _node *Left;
    struct _node *Right;
}Node;
typedef struct _tree{
    Node *root;
}Tree;
//∂˛≤Ê ˜ª˘±æ≤Ÿ◊˜
void Buildbt(Node **bt);                //∂˛≤Ê ˜Ω®¡¢
void Buildbst(Tree *tree,int n);        //∂˛≤ÊÀ—À˜ ˜Ω®¡¢
int  Getheight(Node *tree);                //∏ﬂ∂»
void Afterprint(Node *tree);            //«∞–Ú±È¿˙
void Medianprint(Node *tree);            //÷––Ú±È¿˙
void Beforeprint(Node *tree);            //∫Û–¯±È¿˙
void Levelprint(Node *tree);            //≤„¥Œ±È¿˙
void Searchmin(Node *tree);                //≤È’“◊Ó–°÷µ
void Searchmax(Node *tree);                //≤È’“◊Ó¥Û÷µ
bool IsBST(Node *T);                    //≈–∂œ «∑ÒŒ™∂˛≤ÊÀ—À˜ ˜
Node *Delete(Node *tree,int x);            //…æ≥˝
Node *Insert(Node *tree,int x);            //≤Â»Î
void Free(Node *tree);                    //«Â≥˝
void Print(Node *tree,int layer);        //¥Ú”° ˜–Œ
void basic(Node *tree);                 //∏ﬂ∂»+±È¿˙+◊Ó÷µ+ ˜–Œ≤Ÿ◊˜ºØ∫œ
void pre_inconstruct(int *pre,int *in,int n,Node **root);            //«∞÷––Ú÷ÿΩ®
void in_postconstruct(int *in,int *post,int n,Node **root);            //÷–∫Û–Ú÷ÿΩ®
int main()
{
    Tree tree;
    tree.root = NULL;
    Node *bt = NULL;
    int n,number;
    printf("«Î ‰»ÎΩ⁄µ„÷µ:\n");
    Buildbt(&bt);
//    while(cin>>n){
//        if(n==-1){
//            break;
//        }
//        Buildbst(&tree,n);
//    }
    tree.root = bt;
    basic(tree.root);
    printf("«Î ‰»Î≤Ÿ◊˜–Ú∫≈(1-2):\n");
    while(cin>>n){
        if(n==1){
            //≤Â»Î
            printf("«Î ‰»Îƒ„“™≤Â»Îµƒ÷µ:\n");
            cin>>number;
            tree.root = Insert(tree.root,number);
            basic(tree.root);
        }
        else if(n==2){
            //…æ≥˝
            printf("«Î ‰»Îƒ„“™…æ≥˝µƒ÷µ:\n");
            cin>>number;
            tree.root = Delete(tree.root,number);
            basic(tree.root);
        }
        else{
            Free(tree.root);
            printf("∂˛≤Ê ˜“—æ≠ Õ∑≈\n");
            break;
        }
        printf("«Î ‰»Î≤Ÿ◊˜–Ú∫≈(1-2):\n");
    }
    printf("«ÎºÃ–¯ ‰»Î≤Ÿ◊˜–Ú∫≈(1-2):\n");
    while(cin>>n){
        int s,preorder[100],inorder[100],postorder[100];
        if(n==1){
            printf("«Î ‰»Î¥˝÷ÿΩ®∂˛≤Ê ˜µƒΩ⁄µ„ ˝ƒø:");
            cin>>s;
            printf("«Î ‰»Î«∞–Ú±È¿˙–Ú¡–:");
            for(int i = 0;i < s;i++){
                cin>>preorder[i];
            }
            printf("«Î ‰»Î÷––Ú±È¿˙–Ú¡–:");
            for(int i = 0;i < s;i++){
                cin>>inorder[i];
            }
            Node *root = NULL;
            pre_inconstruct(preorder,inorder,s,&root);
            basic(root);
            Free(root);
        }
        else if(n==2){
            printf("«Î ‰»Î¥˝÷ÿΩ®∂˛≤Ê ˜µƒΩ⁄µ„ ˝ƒø:");
            cin>>s;
            printf("«Î ‰»Î÷––Ú±È¿˙–Ú¡–:");
            for(int i = 0;i < s;i++){
                cin>>inorder[i];
            }
            printf("«Î ‰»Î∫Û–Ú±È¿˙–Ú¡–:");
            for(int i = 0;i < s;i++){
                cin>>postorder[i];
            }
            Node *root = NULL;
            in_postconstruct(inorder,postorder,s,&root);
            basic(root);
            Free(root);
        }
        else{
            break;
        }
        printf("«ÎºÃ–¯ ‰»Î≤Ÿ◊˜–Ú∫≈(1-2):\n");
    }
    return 0;
}
void Buildbt(Node **bt)
{
      int n;
      cin>>n;
      if(n == -1)
          *bt = NULL;
      else{
        *bt=(Node *)malloc(sizeof(Node));
          (*bt)->value = n;
          Buildbt(&((*bt)->Left));
          Buildbt(&((*bt)->Right));
    }
}

void Buildbst(Tree *tree,int n)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->value = n;
    p->Left = NULL;
    p->Right = NULL;
    if(tree->root==NULL){
        tree->root = p;
    }
    else{
        Node *q = tree->root;
        while(q!=NULL){
            if(n<q->value){
                if(q->Left==NULL){
                    q->Left = p;
                    return ;
                }
                else{
                    q = q->Left;
                }
            }
            else{
                if(q->Right==NULL){
                    q->Right = p;
                    return ;
                }
                else{
                    q = q->Right;
                }
            }
        }
    }
    return ;
}
void basic(Node *tree)
{
    Print(tree,1);
    cout<<endl<<endl<<endl;
    printf(" ˜µƒ∏ﬂ∂»:%d\n",Getheight(tree));
    printf("«∞–Ú±È¿˙:\n");
    Afterprint(tree);
    printf("\n÷––Ú±È¿˙:\n");
    Medianprint(tree);
    printf("\n∫Û–Ú±È¿˙:\n");
    Beforeprint(tree);
    printf("\n≤„¥Œ±È¿˙:\n");
    Levelprint(tree);
    Searchmin(tree);
    Searchmax(tree);
    bool ans = IsBST(tree);
    printf(" «∑ÒŒ™“ªø√∂˛≤ÊÀ—À˜ ˜:");
    if(ans == true){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
}
int Getheight(Node *tree)
{
    int HL,HR,MaxH;
    if(tree){
        HL = Getheight(tree->Left);
        HR = Getheight(tree->Right);
        MaxH = HL > HR ? HL : HR;
        return MaxH+1;
    }
    else{
        return 0;
    }
}
void Afterprint(Node *tree)
{
    if(tree!=NULL){
        printf("%d ",tree->value);
        Afterprint(tree->Left);
        Afterprint(tree->Right);
    }
}
void Medianprint(Node *tree)
{
    if(tree!=NULL){
        Medianprint(tree->Left);
        printf("%d ",tree->value);
        Medianprint(tree->Right);
    }
}
void Beforeprint(Node *tree)
{
    if(tree!=NULL){
        Beforeprint(tree->Left);
        Beforeprint(tree->Right);
        printf("%d ",tree->value);
    }
}
void Levelprint(Node *tree)
{
    queue<Node *>q;
    while(!q.empty()){
        q.pop();
    }
    if(tree!=NULL){
        q.push(tree);
    }
    while(!q.empty()){
        Node *p = q.front();
        cout<<p->value<<" ";
        if(p->Left!=NULL){
            q.push(p->Left);
        }
        if(p->Right!=NULL){
            q.push(p->Right);
        }
        q.pop();
    }
    cout<<endl;
}
void Searchmin(Node *tree)
{
    if(tree==NULL){
        printf("∂˛≤Ê ˜Œ™ø’,Œﬁ∑®≤È’“◊Ó–°÷µ!\n");
    }
    else{
        while(tree->Left!=NULL){
            tree = tree->Left;
        }
        printf("Minvalue = %d\n",tree->value);
    }
}
void Searchmax(Node *tree)
{
    if(tree==NULL){
        printf("∂˛≤Ê ˜Œ™ø’,Œﬁ∑®≤È’“◊Ó¥Û÷µ!\n");
    }
    else{
        while(tree->Right!=NULL){
            tree = tree->Right;
        }
        printf("Maxvalue = %d\n",tree->value);
    }
}
Node *Insert(Node *tree,int x)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->value = x;
    p->Left = p->Right = NULL;
    if(tree==NULL){
        tree = p;
        return tree;
    }
    Node *q = NULL,*root = tree;
    while(tree!=NULL){
        q = tree;
        if(tree->value > x){
            tree = tree->Left;
        }
        else{
            tree = tree->Right;
        }
    }
    if(q->value > x){
        q->Left = p;
    }
    else{
        q->Right = p;
    }
    return root;
}
Node *Delete(Node *root,int x)
{
    int Found = 0;
    if(root==NULL){
        printf(" ˜Œ™ø’ ˜,Œﬁ∑®Ω¯––…æ≥˝≤Ÿ◊˜!\n");
        return NULL;
    }
    Node *q = NULL,*p = root;
    while(p){
        if(p->value > x){
            q = p;
            p = p->Left;
        }
        else if(p->value <x){
            q = p;
            p = p->Right;
        }
        else if(p->value == x){
            Found = 1;
            if(p->Left == NULL && p->Right == NULL){                //…æ≥˝“∂Ω·µ„
                if(q == NULL){
                    root = NULL;
                }
                else{
                    if(q->Left == p){
                        q->Left = NULL;
                    }
                    else if(q->Right == p){
                        q->Right = NULL;
                    }
                }
                free(p);
                return root;
            }
            else if(p->Left !=NULL && p->Right != NULL){
                Node *t = p->Left,*s = NULL;
                while(t->Right){                                    //—∞’“◊Û◊” ˜µƒ”“◊” ˜÷–µƒ◊Ó¥ÛΩ·µ„
                    s = t;
                    t = t->Right;                                    //“ª∂® «“∂Ω·µ„ªÚ’ﬂµ•∫¢◊”Ω·µ„
                }
                p->value = t->value;
                if(s == NULL){                                        //◊Û◊” ˜ «“ª∏ˆ–±∂˛≤Ê ˜
                    p->Left = t->Left;
                }
                else{                                                //◊Û◊” ˜≤ª «“ª∏ˆ–±∂˛≤Ê ˜
                    s->Right = t->Left;
                }
                free(t);
                return root;
            }
            else if(p->Left!=NULL||p->Right!=NULL){                    //”–“ª∏ˆ∫¢◊”
                if(q == NULL){
                    if(p->Left == NULL){
                        root = p->Right;
                    }
                    if(p->Right == NULL){
                        root = p->Left;
                    }
                }
                else if(q != NULL){
                    if(q->Left == p){
                        if(p->Left == NULL){
                            q->Left = p->Right;
                        }
                        else if(p->Right == NULL){
                            q->Left = p->Left;
                        }
                    }
                    else if(q->Right == p){
                        if(p->Left == NULL){
                            q->Right = p->Right;
                        }
                        else if(p->Right == NULL){
                            q->Right = p->Left;
                        }
                    }
                }
                free(p);
                return root;
            }
        }
    }
    if(Found == 0){
        cout<<"√ª”–’“µΩ–Ë“™…æ≥˝µƒΩ·µ„!"<<endl;
        return root;
    }
    return root;
}
bool IsBST(Node *T)
{
    Node *p;
    if(!T)
        return true;
    if(!T->Left&&!T->Right)
        return true;
    p=T->Left;
    if(p)
    {
        while(p->Right)//◊Û◊” ˜µƒ◊Ó¥Û÷µ‘⁄”“œ¬Ω«
            p=p->Right;
        if(p->value>T->value)
            return false;
    }
    p=T->Right;
    if(p)
    {
        while(p->Left)//”“◊” ˜µƒ◊Ó–°÷µ‘⁄◊Ûœ¬Ω«
            p=p->Left;
        if(p->value < T->value)
            return false;
    }
    return IsBST(T->Left)&&IsBST(T->Right);
}
void Free(Node *tree)
{
    if(tree->Left)  Free(tree->Left);
    if(tree->Right) Free(tree->Right);
    free(tree);
}
void Print(Node *tree,int layer)
{
    if(tree == NULL){
        return ;
    }
    Print(tree->Right,layer+1);
    for(int i = 0;i < layer;i++){
        printf("    ");
    }
    printf("%d\n",tree->value);
    Print(tree->Left,layer+1);
}
void pre_inconstruct(int *pre,int *in,int n,Node **root)
{
    if(!pre ||!in || n <= 0){
        return ;
    }
    int i;
    for(i = 0;i < n;i++){
        if(pre[0] == in[i]){
            break;
        }
    }
    if(i >= n){
        return ;
    }
    *root = (Node *)malloc(sizeof(Node));
    if(root == NULL){
        return ;
    }
    (*root)->value = pre[0];
    (*root)->Left = (*root)->Right = NULL;
    pre_inconstruct(pre+1,in,i,&(*root)->Left);
    pre_inconstruct(pre+i+1,in+i+1,n-i-1,&(*root)->Right);
}
void in_postconstruct(int *in,int *post,int n,Node **root)
{
    if(!in ||!post||n <= 0){
        return ;
    }
    int i;
    for(i = 0;i < n;i++){
        if(post[n-1] == in[i]){
            break;
        }
    }
    if(i >= n){
        return ;
    }
    *root = (Node *)malloc(sizeof(Node));
    if(root == NULL){
        return ;
    }
    (*root)->value = post[n-1];
    (*root)->Left = (*root)->Right = NULL;
    in_postconstruct(in,post,i,&(*root)->Left);
    in_postconstruct(in+i+1,post+i,n-i-1,&(*root)->Right);
}
/*
30 15 -1 -1 41 33 -1 35  -1 -1  50 -1 -1
1
32
1
16
1
11
2
41
2
33
2
50
2
30
2
16
3
1
7
1 2 4 3 5 7 6
2 4 1 5 7 3 6
2
7
15 30 32 33 35 41 50
15 32 35 33 50 41 30
*/
