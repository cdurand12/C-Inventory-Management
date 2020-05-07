#ifndef ITEM_H
#define ITEM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
  int skuNum;       //SKU# of the item
  char *itemName;   //Description of the item
  double price;    //Price of the item
  int quantity;    //amount of item in inventory
  struct item *next; //next item in inventory
}itemNode;

struct item *ialloc(void);
int itemCompareTo(struct item *item1, struct item *item2);
void changeItemName(struct item *ipt, char *newName);
void changeItemSku(struct item *ipt, int newSku);
void changeItemPrice(struct item *ipt, double newPrice);
void incrementItem(struct item *ipt);
void fillIn(struct item *ipt1, struct item *ipt2);




#endif
