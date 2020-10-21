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


#### How can I interract with the program.
Either the program run with input either without input , it has implemented a command interface that allows user to interract and do querries on it.

