# IntrusiveList

A minimal **intrusive doubly-linked list** library in C.

## What is an Intrusive List?

In a standard linked list, each node is a separate heap allocation that wraps your data. In an intrusive list, the link pointers (`left`/`right`) are embedded **directly inside your own struct**. This means:

- **No extra allocations** per element — the node is part of your data
- **O(1) removal** of any element
- **Better cache performance** — data and links are co-located in memory

## Project Structure

```
IntrusiveList/
├── libIntrusiveList/
│   ├── libIntrusive.h   # Types, macros, and function declarations
│   └── libIntrusive.c   # List implementation
├── main.c               # Usage example
└── CMakeLists.txt
```

## Building

```bash
git clone https://github.com/milutin2002/IntrusiveList.git
cd IntrusiveList
mkdir build && cd build
cmake ..
cmake --build .
```

## Usage

### 1. Embed `intrusiveNode` in your struct

```c
#include "libIntrusiveList/libIntrusive.h"

typedef struct {
    char name[20];
    int value;
    intrusiveNode node;  // intrusive link — embedded directly in your struct
} MyItem;
```

### 2. Create and initialize a list

```c
doubleLinkedList *list = calloc(1, sizeof(doubleLinkedList));
list->offset = OFFSET(MyItem, node);  // tells the list where the node lives in your struct
```

The `OFFSET` macro computes the byte offset of the `intrusiveNode` field within your struct, so the library can recover a pointer to your data from any node pointer.

### 3. Add nodes

```c
MyItem *a = calloc(1, sizeof(MyItem));
strcpy(a->name, "Alice");
a->value = 1;

MyItem *b = calloc(1, sizeof(MyItem));
strcpy(b->name, "Bob");
b->value = 2;

addNode(list, &a->node);
addNode(list, &b->node);
```

Nodes are inserted at the **head** of the list.

### 4. Iterate

```c
void print_item(intrusiveNode *n, int offset) {
    MyItem *item = (MyItem *)((char *)n - offset);
    printf("%s: %d\n", item->name, item->value);
}

iterateList(list, print_item);
```

The callback receives the `intrusiveNode *` and the offset, from which you recover the original struct using a pointer cast.

### 5. Remove a node

```c
removeNode(list, &a->node);
```

## API Reference

### Types

```c
typedef struct intrusiveNode {
    struct intrusiveNode *left, *right;
} intrusiveNode;

typedef struct doubleLinkedList {
    intrusiveNode *head;
    int (*key)(void *, void *);          // optional: for keyed lookups
    int (*comparison)(void *, void *);   // optional: for comparisons
    unsigned int offset;                 // byte offset of intrusiveNode in your struct
} doubleLinkedList;
```

### Macro

```c
OFFSET(structName, fieldName)
```
Returns the byte offset of `fieldName` within `structName`. Set `list->offset` to this value before using the list.

### Functions

| Function | Description |
|---|---|
| `addNode(list, node)` | Insert a node at the head of the list |
| `removeNode(list, node)` | Unlink a node from the list |
| `iterateList(list, callback)` | Walk the list, calling `callback(node, offset)` for each element |

## Example Output

From `main.c`, inserting three items and removing the middle one:

```
cddcdc 7
efdfdd 5
efff 4

cddcdc 7
efff 4
```

## Author

[milutin2002](https://github.com/milutin2002)

