![run-tests](../../workflows/run-tests/badge.svg)


**NOTE :** *This repo , is a part of the 1st Programming assignment that we had to implement for the course of Operating Systems - Fall 2020.*


<p align="center"> 
 <h1>Student Management using Data Structures </h1> 
</p> 

This is a **Data Structures** based project , that is implemented by a Hash Table and and Inverted Index as you can see at the following picture .

<p align="center"> 
 <img width="800" height="500" src="images/structures.png">
</p>


### General Info About **Student Management** 


#### What does the Structures contain ?
Both stuctures contain students' information as a struct named record and for each Student contains its :
* Student ID
* Registation Year
* First Name
* Last Name
* GPA

#### How does these Structures hold data ?
Data are stored in the Hash table with key their **StudentID**
Data are stored in the Inverted Index by their **Registration Year**

#### How can I run the program ? 
For this question I have 2 answers.
If you want to run the program with input files that are stored in **tst** folder , either interract without input files.

For the first choice : just clone the repo and type :
``` 
make run
```
 and 
 
``` 
make valgrind
```
 Either if you want run with the current input file (input300000) type:
```
make run_no_args
```
and 
```
make valgrind_no_args
```
All the above commands compile and run the main program.
The commands that contain *valgrind* , use the [valgrind](https://valgrind.org/) debugger.


#### How can I interract with the program ?
Either the program run with input either without input , it has implemented a command interface that allows user to interract and do querries on it.

#### Acceptable Commands and their use

 1. i(nsert) studentid lastname firstname zip year gpa: εισήγαγε στην δομή ένα φοιτητή με κλειδί
studentid που έχει εισαχθεί το έτος year, έχει μόνιμη κατοικία στον Τ.Κ. zip και έχει μέσο όρο μέχρι
στιγμής gpa. Επανάληψη εισαγωγής εγγραφής με υπάρχον κλειδί studentid στην δομή δεν είναι εφικτή
και σχετική ένδειξη λάθους εμφανίζεται στην έξοδο.

2. l(ook-up) studentid: ανάκτησε και τύπωσε στην εγγραφή του εν λόγω φοιτητή στο tty. Αν δεν
υπάρχει, τύπωσε σχετικό μήνυμα.

3. d(elete) studentid: διέγραψε από την δομή την/τον φοιτήτρια/φοιτητή με αριθμό studentid. Αν δεν
υπάρχει τέτοια εγγραφή, τύπωσε σχετικό μήνυμα.

4. n(umber) year: για την ακαδημαϊκή χρονιά year βρες πόσοι παραμένουν εγγεγραμμένοι. Στο ΕΚΠΑ
εγγεγραμμένος μπορεί να παραμείνει κάποιος χωρίς περιορισμό. Η εντολή αυτή βρίσκει πόσοι φοιτητές
συνεχίζουν να δραστηριοποιούνται πχ. στο 6ο χρόνο, κλπ.

5. t(op) num year: για την ακαδημαϊκή χρονιά year βρες τους num φοιτητές με την καλύτερη απόδοση.
6. a(verage) year: για την ακαδημαϊκή χρονιά year βρες τους τον μέσο όρο.

7. m(inimum) year: για την ακαδημαϊκή χρονιά year βρες την/τον φοιτήτρια/φοιτητή με το μικρότερο μέσο
όρο.

8. c(ount): για κάθε έτος φοίτησης βρες τον αριθμό των φοιτητών που υπάρχουν στην δομή.


9. exit: το πρόγραμμα τερματίζει αφού απελευθερώσει με συγκροτημένο τρόπο όλο το χώρο που έχει
καταλάβει στην μνήμη.
