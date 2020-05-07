#include "project3.h"
//Chris Durand
//N00810837
//Project 3
//Inventory System: Inventory is given by standard input. Multiple orders can be processed.
//#define MAXLINE 1000
#define MAXLINE 1000  //Max number of lines from input
#define MAXSTRING 35 //Max size for a single line


int main(int argc, char *argv[]){
  itemNode *inventory = NULL;       //pointer to Linked list
  // head=ialloc();
  // head->itemName = (char *)malloc(sizeof(char));
  char string[MAXSTRING];         //string to hold the inputed string
  int lineLength = 0;

//main inventory input, this loop will read into inventory
  while(lineLength = myGetLine(string, MAXSTRING)){
    itemNode *newItem = ialloc();
    newItem->itemName = (char *)malloc(sizeof(char));
    newItem->skuNum = 0;
    newItem->price = 0;
    newItem->quantity = 1;
    newItem->next = NULL;

    int input;
    double price;
    char *name = malloc(10 * sizeof(char));
    char *longName = malloc(30 * sizeof(char));

    //printf("Line length: %d\n", lineLength);
    if(sscanf(string, "%d %s %lf", &input, name, &price) == 3){
      //printf("3 things\n");
      newItem->skuNum = input;
      newItem->itemName = name;
      newItem->price = price;
    }
    else if(sscanf(string, "%d %s %s %lf", &input, name, longName, &price) == 4){
      //printf("sku, longName, and price\n");
      sprintf(name, "%s%s%s", name, " ", longName);
      newItem->itemName = name;
      newItem->skuNum = input;
      newItem->price = price;
    }
    else if(sscanf(string, "%d %s %s", &input, name, longName) == 3){
      //printf("sku and longName\n");
      sprintf(name, "%s%s%s", name, " ", longName);
      newItem->itemName = name;
      newItem->skuNum = input;
    }
    else if(sscanf(string, "%s %s %lf", name, longName, &price) == 3){
      //printf("sku and longName\n");
      sprintf(name, "%s%s%s", name, " ", longName);
      newItem->itemName = name;
      newItem->price = price;
    }
    else if(sscanf(string, "%d %lf", &input, &price) == 2 && isDigit(input)){
      //printf("Sku and Price\n");
      newItem->skuNum = input;
      newItem->price = price;
    }
    else if(sscanf(string, "%s %lf", name, &price) == 2){
      //printf("description and price\n");
      newItem->itemName = name;
      newItem->price = price;
    }
    else if(sscanf(string, "%d %s", &input, name) == 2){
      //printf("sku and description\n");
      newItem->skuNum = input;
      newItem->itemName = name;
    }
    else if(sscanf(string, "%s %s", name, longName) == 2){
      //printf("Just Long name\n");
      sprintf(name, "%s%s%s", name, " ", longName);
      newItem->itemName = name;
      }
    else if(sscanf(string, "%d", &input) == 1){
      //printf("just the sku\n");
      newItem->skuNum = input;
    }
    else if(sscanf(string, "%s", name) == 1){
      //printf("just the description\n");
      newItem->itemName = name;
      }
    else{
      printf("Invalid Input\n");
      continue;
    }
    inventory = addItem(inventory, newItem);
  }
  printInventory(inventory);


  double salesTax = .0825;
  double finalPrice;
  char *nameBuf = (char *)malloc(sizeof(char));
  char *desc = (char *)malloc(sizeof(char));
  char *longdesc = (char *)malloc(sizeof(char));

//Order Processing Starts Here. This will loop through each argv file you pass
//in the cmd line
  for (int i = 1; i < argc; ++i){
    FILE  *orderFile;
    char *order = (char *)malloc(sizeof(char));
    itemNode *newItem = ialloc();
    newItem->itemName = (char *)malloc(sizeof(char));
    int input;
    int amount;
    double totalSale = 0.0;
    char *salesName = (char *)malloc(sizeof(char));
    char *customerName = (char *)malloc(sizeof(char));


    orderFile = fopen(argv[i], "r");
    // printf("testing");
    while(fgets(order, 20, orderFile) != NULL){
      if(sscanf(order, "%d %d", &input, &amount) == 2){
          newItem->skuNum = input;
          newItem->quantity = amount;
          totalSale += checkInventory(inventory, newItem, amount);
      }
      else if(sscanf(order, "%s %d", desc, &amount) == 2){
        newItem->itemName = desc;
        newItem->quantity = amount;
        totalSale += checkInventory(inventory, newItem, amount);
      }
      else if(sscanf(order, "%s %s %d", desc, longdesc, &amount) == 3){
        sprintf(desc, "%s%s%s", desc, " ", longdesc);
        newItem->itemName = desc;
        newItem->quantity = amount;
        totalSale += checkInventory(inventory, newItem, amount);
      }
      else if((sscanf(order, "%s", nameBuf) == 1) && strlen(salesName) == 0){
        strcpy(salesName, nameBuf);
      }
      else if(strlen(customerName) == 0){
          strcpy(customerName, nameBuf);
          printf("%s%s%s", "Thank you, ", customerName, " for choosing this General Store!\n");
      }
  }
  fclose(orderFile);
  printf("%s%.2f%s", "Total sales: $", totalSale, "\n");
  printf("%s%.2f%s", "Sales tax (8.25%): $", (totalSale * salesTax), "\n");
  printf("%s%.2f%s", "Final Price: $", (totalSale + (totalSale*salesTax)), "\n");
  if(strlen(salesName) != 0)
    printf("%s%s%s", "Your salesperson: ", salesName, "\n\n");
  printInventory(inventory);
  }
  // printf("%s%.2f%s", "Total sales: $", totalSale, "\n");
  // printf("%s%.2f%s", "Sales tax (8.25%): $", (totalSale * salesTax), "\n");
  // printf("%s%.2f%s", "Final Price: $", (totalSale + (totalSale*salesTax)), "\n");
  // if(strlen(salesName) != 0)
  //   printf("%s%s", "Your salesperson: ", salesName);
  // printInventory(inventory);
}

//addItem function: add an item node to a Linked list
itemNode *addItem(itemNode *head, itemNode *newItem){
  if(head == NULL){
    //printf("head added");
    head = ialloc();
    head = newItem;
  }else if((itemCompareTo(head, newItem))){
    incrementItem(head);
    fillIn(head, newItem);
  }
  else{
    head->next = addItem(head->next, newItem);
  }
  return head;

}



/* getLineSize: read a line into s, return length
/ this is the standard getline function from the book
*/
int myGetLine(char s[], int lim){
  int c, i;

  for(i=0; i <lim-1 && (c=getchar()) !=EOF && c!='\n'; ++i)
    s[i]=c;
  if(c == '\n'){
    s[i] = c;
    ++i;
    }
  s[i] = '\0';
  return i;
  }


/* copy: copy 'from' into 'to'
/this is the standard copy function from the book
*/
void copy(char to[], char from[]){
  int i;

  i = 0;
  while((to[i] = from[i]) != '\0')
      ++i;
}

//isDigit function: tests to see if the input is a digit, returns 0 if it is not
//a digit
//(I got the idea from http://pubs.opengroup.org/onlinepubs/009695399/functions/isdigit.html)
int isDigit(int c){
  if(c == 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58){
    return 1;
  }
    return 0;
}

//printInventory function: prints the inventory
void printInventory(itemNode *p){
  while(p != NULL){
    if(p->quantity == 0){
      p = p->next;
    }
    else{
      printf("%d %s %s%.2f %s%d %s", p->skuNum, p->itemName, "$", p->price, ": ", p->quantity, " in stock\n");
      p = p->next;
    }
  }
  printf("\n");
}


//checkInventory function: checks the inventory to see if there are enough available items for an order
double checkInventory(itemNode *inventory, itemNode *item, int amount){
  itemNode *currentNode = ialloc();
  currentNode = inventory;
  double totalPrice;
  double totalSale=0;
  double salesTax=.0825;


  while(currentNode != NULL){
    if(itemCompareTo(currentNode, item)){
        if(currentNode->quantity < amount){
          printf("%s %d %s %s %d %s", "Requested ", amount, currentNode->itemName, "; only", currentNode->quantity, "in stock\n");
          totalPrice = currentNode->quantity * currentNode->price;
          printf("%d %s %s %s %.2f %s %s %.2f %s", currentNode->quantity, " x ", currentNode->itemName, " @ $", currentNode->price, ":", "$", totalPrice, "\n");
          currentNode->quantity = 0;
          return totalPrice;
          break;
        }
        else{
          currentNode->quantity -= amount;
          totalPrice = amount * currentNode->price;
          printf("%d %s %s %s %.2f %s %s %.2f %s", amount, " x ", currentNode->itemName, " @ $", currentNode->price, ":", "$", totalPrice, "\n");
          return totalPrice;
          break;
      }

    }
    currentNode = currentNode->next;

  }
  if(currentNode == NULL){
    printf("%s %d %s", "SKU", item->skuNum, "not in stock\n");
    return 0;
  }
}
