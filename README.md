![run-tests](../../workflows/run-tests/badge.svg)


**NOTE :** *This repo , is a part of the 1st Programming assignment that we had to implement for the course of Operating Systems - Fall 2020.*


<p align="center"> 
 <h1>Student Management using Data Structures </h1> 
</p> 

This is a **Data Structures** based project , that is implemented by a **Hash Table** and and **Inverted Index** as you can see in the following picture .

<p align="center"> 
 <img width="800" height="500" src="images/structures.png">
</p>


### General Info About **Student Management** 


#### What does this repository contains ?
* **configs** folder : configuration files. Files that in this project set the size of buckets that the Hash Table contains.
* **include"** folder : contains header files 
* **modules** folder : contains data structures source files
* **src** folder : contains the main programs mnstd and mnstd_only_args ( *this file is used to run only with CL arguments* )
* **tst** folder : contains input files.

#### What does the Structures contain ?
Both stuctures contain students' information as a struct named record and for each Student contains its :
* Student ID
* Registation Year
* First Name
* Last Name
* ZIP number 
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

 1. **i**(nsert) studentid lastname firstname zip year gpa: this command inserts a record to the structures.

2. **l**(ook-up) studentid: this command searches for a student with "studentid" StudentID.

3. **d**(elete) studentid: this command deletes both of the structures the student with "studentid" StudentID , if exists.

4. **n**(umber) year: for the academic year "year" find how many students are enrolled .

5. **t**(op) num year: this command finds the top "num" students for "year" year , based on their GPA.

6. **a**(verage) year: this command finds the average GPA for "year" year.

7. **m**(inimum) year: this command finds the student with the smallest GPA for "year" year.

8. **c**(ount): for each year find how many students are enrolled.

9. **exit**: terminates the main program and deallocate all the memory that allocated dynamically.



