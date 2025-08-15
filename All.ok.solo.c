#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct
{
int id;
char name[50];
int quantity;
float price;
}Product;

typedef struct Shipment
{
int id;
int productid;
char destination[50];
struct Shipment*next;
}Shipment;


typedef struct
{
int id;
char customer[50];
int productid;
int quantity;
}Order;


typedef struct History
{
char action[30];
Product product;
struct History*next;
}History;

Product inventory[100];
int productcount=0;

Shipment*shipments=NULL;

Order orders[100];
int front=-1;int rear=-1;

History*history=NULL;

void addhistory(const char*action,Product p)
{
History*newitem=(History*)malloc(sizeof(History));
strcpy(newitem->action,action);
newitem->product=p;
newitem->next=history;history=newitem;
}
void clearscreen(){
system("clear||cls");
}

void addproduct(){
Product p;
printf("\nEnter product ID: ");
scanf("%d",&p.id);
int i;
for(i=0;i<productcount;i++)
{if(inventory[i].id==p.id){
printf("ID  exists!\n");
return;
}
}
printf("Enter name:");
scanf("%s",p.name);
printf("Enter quantity:");
scanf("%d",&p.quantity);
printf("Enter price:");
scanf("%f",&p.price);

inventory[productcount]=p;productcount++;
addhistory("ADDED PRODUCT",p);
printf("Product added!\n");
}

void addshipment()
{Shipment*newship=(Shipment*)malloc(sizeof(Shipment));
printf("\nEnter shipment ID:");
scanf("%d",&newship->id);
printf("Enter product ID:");
scanf("%d",&newship->productid);
printf("Enter destination:");
scanf("%s",newship->destination);
newship->next=shipments;
shipments=newship;
printf("Shipment added!\n");
}

void placeorder()
{if(rear==99){printf("Order queue full!\n");
return;
}
if(front==-1)front = 0;
Order o;

printf("\nEnter order ID:");
scanf("%d",&o.id);
printf("Enter customer name:");
scanf("%s",o.customer);
printf("Enter product ID:");
scanf("%d",&o.productid);
printf("Enter quantity:");
scanf("%d",&o.quantity);
orders[++rear]=o;
printf("Order placed!\n");
}

void undo()
{if(history==NULL)
{printf("Nothing to undo!\n");
return;
}
History*lastaction=history;
history=history->next;

printf("Undid: %s (Product %d)\n", lastaction->action, lastaction->product.id);
free(lastaction);
}

void showproducts()
{printf("\n%-5s\t%-20s\t%-10s\t%s\n","ID","NAME","QUANTITY", "PRICE");
for(int i=0;i<productcount;i++)
{printf("%-5d\t%-20s\t%-10d\t%.2f\n",
inventory[i].id,
inventory[i].name,
inventory[i].quantity,
inventory[i].price);
}
}
void showshipments()
{
Shipment*current=shipments;
printf("\n%-5s\t%-10s\t%-20s","ID","PRODUCTID","DESTINATION");
while(current!=NULL)
{
printf("\n%-5d\t%-10d\t%-20s\n",
current->id,
current->productid,
current->destination);
current=current->next;
}
}
void showorders()
{
if(front==-1)
{printf("\nNo orders available.\n");
return;
}
printf("\n%-5s\t%-20s\t%-10s\t%-10s\n","ID","CUSTOMER","PRODUCTID","QUANTITY");
int i;
for(i=front;i<=rear;i++)
{printf("%-5d\t%-20s\t%-10d\t%-10d\n",
orders[i].id,
orders[i].customer,
orders[i].productid,
orders[i].quantity);
}
}
int main()
{
int choice;

while(1)
{
printf("\n     WAREHOUSE MANAGEMENT SYSTEM    \n");
printf("1. Product Management\n");
printf("2. Shipment Management\n");
printf("3. Order Management\n");
printf("4. Undo Last Action\n");
printf("5. View All Data\n");
printf("0. Exit\n");
printf("Choose: ");
scanf("%d",&choice);

switch(choice)
{
case 1:
addproduct();break;
case 2:
addshipment();break;
case 3:
placeorder();break;
case 4
undo();break;
case 5:
printf("\nPRODUCTS:\n");
showproducts();

printf("\nSHIPMENTS:\n");
showshipments();

printf("\nORDERS:\n");
showorders();
break;

case 0:
return 0;
default:
printf("Invalid choice\n");
printf("\nPress enter to continue...");
getchar(); getchar();
break;
}
}
}
