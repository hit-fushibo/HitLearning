#ifndef DEFINE_H
#define DEFINE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct HuffmanTree
{
    float weight;
    char element;
    struct HuffmanTree *Lchild;
    struct HuffmanTree *Rchild;
}HuT;

typedef struct CharWeight
{
    char data;
    float weight;
}CW;

int codectn=0;

#endif