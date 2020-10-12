// #pragma once
// #include "common_types.h"
 
// // dummy nodes - just for error detection 
// #define LIST_BOF (ListNode)0 // node before the first (;)
// #define LIST_EOF (ListNode)0 // node after the last (;)

// typedef struct linked_list* LinkedList;
// typedef struct list_node* ListNode;


// // Liked List functionality 

// // 1. This function is used to make a dummy list, just to allocate the 
// // necessary memory to hold an [empty] list.

// LinkedList list_create();


// // 2. Thus function is used to insert elements in the list, after the 
// // node "node" or at the top of the list if the node is LIST_BOF with 
// // value == value .

// void list_insert(LinkedList list, ListNode node, Pointer value);

//////////////////////////////////////////////////////////////////
//
// ADT List
//
// Abstract λίστα. Παρέχει σειριακή πρόσβαση στα στοιχεία, και
// προσθήκη/αφαίρεση σε οποιοδήποτε σημείο της λίστας.
//
///////////////////////////////////////////////////////////////////

#pragma once // #include το πολύ μία φορά

#include "common_types.h"

// Οι σταθερές αυτές συμβολίζουν εικονικούς κόμβους _πριν_ τον πρώτο και _μετά_ τον τελευταίο
#define LIST_BOF (ListNode)0
#define LIST_EOF (ListNode)0


// Λίστες και κόμβοι αναπαριστώνται από τους τύπους List και ListNode. Ο χρήστης δε χρειάζεται να γνωρίζει το περιεχόμενο
// των τύπων αυτών, απλά χρησιμοποιεί τις συναρτήσεις list_<foo> που δέχονται και επιστρέφουν List / ListNode.
//
// Οι τύποι αυτοί ορίζινται ως pointers στα "struct list" και "struct list_node" των οποίων το
// περιεχόμενο είναι άγνωστο (incomplete structs), και εξαρτάται από την υλοποίηση του ADT List.
//
typedef struct list* List;
typedef struct list_node* ListNode;



// Δημιουργεί και επιστρέφει μια νέα λίστα.
// Αν destroy_value != NULL, τότε καλείται destroy_value(value) κάθε φορά που αφαιρείται ένα στοιχείο.

List list_create(DestroyFunc destroy_value);

// Επιστρέφει τον αριθμό στοιχείων που περιέχει η λίστα.

int list_size(List list);

// Προσθέτει έναν νέο κόμβο __μετά__ τον node, ή στην αρχή αν node == LIST_BOF, με περιεχόμενο value.

void list_insert_next(List list, ListNode node, Pointer value);

// Αφαιρεί τον __επόμενο__ κόμβο από τον node, ή τον πρώτο κόμβο αν node == LIST_BOF.

void list_remove_next(List list, ListNode node);

// Επιστρέφει την πρώτη τιμή που είναι ισοδύναμη με value
// (με βάση τη συνάρτηση compare), ή NULL αν δεν υπάρχει

Pointer list_find(List list, Pointer value, CompareFunc compare);

// Αλλάζει τη συνάρτηση που καλείται σε κάθε αφαίρεση/αντικατάσταση στοιχείου σε
// destroy_value. Επιστρέφει την προηγούμενη τιμή της συνάρτησης.

DestroyFunc list_set_destroy_value(List list, DestroyFunc destroy_value);

// Ελευθερώνει όλη τη μνήμη που δεσμεύει η λίστα list.
// Οποιαδήποτε λειτουργία πάνω στη λίστα μετά το destroy είναι μη ορισμένη.

void list_destroy(List list);


// Διάσχιση της λίστας /////////////////////////////////////////////
//
// Επιστρέφουν τον πρώτο και τον τελευταίο κομβο της λίστας, ή LIST_BOF / LIST_EOF αντίστοιχα αν η λίστα είναι κενή

ListNode list_first(List list);
ListNode list_last(List list);

// Επιστρέφει τον κόμβο μετά από τον node, ή LIST_EOF αν ο node είναι ο τελευταίος

ListNode list_next(List list, ListNode node);

// Επιστρέφει το περιεχόμενο του κόμβου node

Pointer list_node_value(List list, ListNode node);

// Βρίσκει τo πρώτo στοιχείο που είναι ισοδύναμο με value (με βάση τη συνάρτηση compare).
// Επιστρέφει τον κόμβο του στοιχείου, ή LIST_EOF αν δεν βρεθεί.

ListNode list_find_node(List list, Pointer value, CompareFunc compare);


// Deletes the node node of the list.
void list_remove(List list, ListNode node);