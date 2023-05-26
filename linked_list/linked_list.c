#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
};

struct node *generate_nodes();
int count_of_nodes(struct node *head);
void print_data(struct node *head);
struct node *add1(struct node *head, int data);
struct node *add2(struct node *head, int data);
struct node *add3(struct node *ptr, int data, int count);
struct node *delete1(struct node *head);
void delet2(struct node *head, int count);

int main()
{
    struct node *head = NULL;
    head = generate_nodes();
    printf("%p\n", head);
    int count;
    count = count_of_nodes(head);
    print_data(head);
    head = add1(head, 4);
    head = add2(head, 0);
    print_data(head);
    count = count_of_nodes(head);
    head = add3(head, 110110001, count);
    /* while (head != NULL)
    {
        head = delete1(head);
    }*/
    head = delete1(head);
    count = count_of_nodes(head);
    delet2(head, count);
    return 0;
}

// function to generate a linked list
struct node *generate_nodes()
{
    static struct node *head;
    head = NULL;
    struct node *current;
    current = NULL;

    for (size_t i = 0; i < 3; i++)
    {
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        if (new_node == NULL)
        {
            printf("No available memory.");
            exit(1);
        }
        if (head == NULL)
        {
            head = new_node;
            current = new_node;
        }
        else
        {
            current->link = new_node;
        }

        printf("data[%ld]: ", i + 1);
        scanf("%d", &new_node->data);
        current = new_node;
    }
    return head;
}

// function to count the number of nodes of a list
int count_of_nodes(struct node *head)
{
    int count = 0;
    if (head == NULL)
    {
        printf("No available memory.");
        exit(1);
    }
    struct node *ptr = NULL;
    ptr = head;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->link;
    }
    printf("number of nodes = %d\n", count);
    return count;
}

// function to print all the data in the list
void print_data(struct node *head)
{
    if (head == NULL)
    {
        printf("No available memory.");
        exit(1);
    }
    struct node *ptr = NULL;
    ptr = head;
    while (ptr != NULL)
    {
        printf("%d\n", ptr->data);
        ptr = ptr->link;
    }
    printf("--------------------------------------------------------------------------\n");
}

// function to add a node at the end of the list with traversing the list
struct node *add1(struct node *head, int data)
{

    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        printf("No available memory.");
        exit(1);
    }
    new_node->data = data;
    new_node->link = NULL;

    struct node *temp;
    temp = head;

    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    temp->link = new_node;

    print_data(head);
    return head;
}

// function to add a node at the end of the lsit without traversing the list(needs a special list generation)
/*void add(struct node *head, int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->link = NULL;

    head->link = new_node;
    print_data(head);
}*/

// function to add a node at the beginning of the list

struct node *add2(struct node *head, int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        printf("No available memory.");
        exit(1);
    }

    new_node->data = data;
    new_node->link = head;
    head = new_node;
    return head;
}

// function to add a node at a certain postion in the list
struct node *add3(struct node *ptr, int data, int count)
{
    int position = 0;
    printf("Enter Position: ");
    scanf("%d", &position);
    if (position <= count && position > 0)
    {
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        if (new_node == NULL)
        {
            printf("No available memory.");
            exit(1);
        }
        struct node *current = (struct node *)malloc(sizeof(struct node));
        if (current == NULL)
        {
            printf("No available memory.");
            exit(1);
        }
        current = ptr;
        if (position > 1)
        {
            for (size_t i = 0; i < position - 2; i++)
            {
                current = current->link;
            }
            new_node->data = data;
            new_node->link = current->link;
            current->link = new_node;
            print_data(ptr);
            return ptr;
        }
        else if (position == 1)
        {
            ptr = add2(ptr, data);
            print_data(ptr);
            return ptr;
        }
    }
    else if (position == count + 1)
    {
        ptr = add1(ptr, data);
        return ptr;
    }

    else
    {
        printf("Out of Range.\n");
        add3(ptr, data, count);
    }
}

// function to delete the first node of a linked list
struct node *delete1(struct node *head)
{
    if (head == NULL)
    {
        printf("List is already empty!");
        exit(1);
    }

    else
    {
        struct node *temp = head;
        head = head->link;
        free(temp);
        print_data(head);
        return head;
    }
}

// function to delete the last node of a linked list
void delet2(struct node *head, int count)
{
    if (head == NULL)
        printf("List is already empty!");
    else
    {
        struct node *temp = head;
        for (size_t i = 1; i <= count; i++)
        {
            if (i == count - 1)
            {
                temp->link = NULL;
            }
            else
            {
                temp = temp->link;
            }
        }
        free(temp);
        print_data(head);
    }
}