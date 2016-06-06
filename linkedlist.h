typedef struct Node Node;
typedef struct LinkedList LinkedList;

struct Node
{
	char name[30];
	double data;
	struct Node *next;
	struct Node *prev;
};

Node *head, *tail;

struct LinkedList
{
	Node *head;
	Node *tail;
};

void init(LinkedList *list);
int get_size(LinkedList *list);
int Get_ListCount();

Node *add_before(Node *node, char *name, double data);
Node *add_last(LinkedList *list, char *name, double data);

void remove_node(Node *node);

Node *Find_Node_By_Index(LinkedList *list, int i);
Node *get_node_by_name(LinkedList *list, char *name);
int Get_NodeIndex(LinkedList *list, Node *node);

void printList(LinkedList *list);

	
void init(LinkedList *list)

{

    list->head = (Node *)malloc(sizeof(Node));
    list->tail = (Node *)malloc(sizeof(Node));
	list->head->prev=NULL;
    list->head->next = list->tail;
    list->tail->prev = list->head;
	list->tail->next=NULL;   

}


int get_size(LinkedList *list)
{ 
     int size = 0; 
     Node *temp = list -> head -> next; 
     while(temp != list -> tail)
	 { 
         size ++; 
         temp = temp -> next; 
     } 
     return size; 
 } 

int Get_ListCount()
{
     Node *NewNode;
     int count=0;

     for (NewNode = head->next; NewNode; NewNode = NewNode->next)
	 {
          count++;
     }
     return count;
}

Node *add_before(Node *node, char *name, double data){ 
     Node *newNode = (Node *)malloc(sizeof(Node)); 
	 strcpy(newNode -> name, name);
     newNode -> data = data;
     newNode -> prev = node -> prev; 
     newNode -> next = node; 
      
     node -> prev -> next = newNode; 
     node -> prev = newNode; 
     return newNode; 
 } 

Node *add_last(LinkedList *list, char *name, double data)
{ 
     return add_before(list -> tail, name, data); 
 } 

void remove_node(Node *node)
{
	if(node == head || node ==tail)
		return;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
}

Node *Find_Node_By_Index(LinkedList *list, int i)
{
	Node *NewNode = list -> head -> next;
	int index = 0;

	//for(NewNode; NewNode != list ->tail; NewNode = NewNode -> next)
	while(NewNode != list-> tail)
	{
		if(index == i)
		{
			return NewNode;
		}
		index++;
		NewNode = NewNode->next;
	}
	return NULL;
}

Node *get_node_by_name(LinkedList *list, char *name)
{
	Node *temp = list -> head -> next;
	while(temp != list -> tail)
	{
		if(strcmp(temp -> name, name) == 0)
			return temp;
		temp = temp -> next;
	}
	return NULL;
}

int Get_NodeIndex(LinkedList *list, Node *node)
{
	Node *NewNode = list -> head-> next;
	int index = 0;

	//for(NewNode = head->next; NewNode != list ->tail; NewNode = NewNode->next)
	while(NewNode != list -> tail)
	{
		if(NewNode == node)
		{
			return index;
		}
		index++;
		NewNode = NewNode->next;
	}
	return -1;
}

Node *find_node(LinkedList *list, char *name)
{
	Node *temp;
	temp = head->next;
	while(temp != tail && strcmp(temp -> name, name) != 0)
	{
		temp = temp->next;
	}
	return temp;
}

void printList(LinkedList *list)
{
	Node *NewNode = list->head->next;

	while(NewNode != list ->tail)
	{
		printf("%lf ", NewNode->data);
		NewNode = NewNode -> next;
	}
}
