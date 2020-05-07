#include "item.h"

//itemExists function: checks to see if the item being compare compared
//are the same. Returns 1 if item is the same, 0 if its not.
int itemCompareTo(struct item *item1, struct item *item2){
  if(item1->skuNum == item2->skuNum && item1->skuNum != 0){
    return 1;
  }
  else if(strcmp(item1->itemName, item2->itemName) == 0 && strlen(item1->itemName) > 1){
    return 1;
  }
  else{
    return 0;
  }
}


//changeItemName function: updates the name of an item
void changeItemName(struct item *ipt, char *newName){
  strcpy(ipt->itemName, newName);
}

//changeItemSku function: updates the items sku
void changeItemSku(struct item *ipt, int newSku){
  ipt->skuNum = newSku;
}

//changeItemPrice function: updates the items Price
void changeItemPrice(struct item *ipt, double newPrice){
  ipt->price = newPrice;
}

//incrementItem function: increments the number of items in inventory
void incrementItem(struct item *ipt){
  ipt->quantity += 1;
}

//ialloc function: allocates memory for an item node
itemNode *ialloc(void){
  return (itemNode *)malloc(sizeof(itemNode));
}

//fillIn function: fills in any missing data
void fillIn(struct item *ipt1, struct item *ipt2){
  if(ipt1->skuNum == 0){
    ipt1->skuNum = ipt2->skuNum;
  }
  if(strlen(ipt1->itemName) == 0){
    strcpy(ipt1->itemName, ipt2->itemName);
  }
  if(ipt1->price == 0){
    ipt1->price = ipt2->price;
  }
}
