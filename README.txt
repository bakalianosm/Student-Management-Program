﻿Λειτουργικά Συστήματα - Προγραμματιστική Άσκηση 1
Μιχαήλ Μπακαλιάνος 
ΑΜ: 1115201700269




Σημείωση: το πρόγραμμα μου αν λάβει από τον χρήση κάποιο αρχείο εισόδου , αναμένει να λάβει και configuration  file, το οποίο εξηγώ παρακάτω τι περιέχει και θεωρείται απαραίτητο για την ορθή λειτουργία του προγράμματος.Όλες οι εντολές τρέχουν εφόσον βρισκόμαστε μέσα στο directory της εργασίας και όχι σε κάποιον εμφωλευμένο φάκελο.




Για την ορθή εκτέλεση του προγράμματος :
1. Με χρήση ορισμάτων γραμμής εντολών :  Μέσα στο Makefile έχω βάλει μία μεταβλητή που λέγεται ARGS και είναι formatted για να ανοίγει το αρχείο input30000.txt που δόθηκε καθώς και το [απαραίτητο] σύμφωνα με την υλοποίηση μου configfile/
1. Για να τρέξει με χρήση ορισμάτων το πρόγραμμα πληκτρολογήστε την εντολή make run.
2. Για να τρέξει με χρήση ορισμάτων το πρόγραμμα καθώς και να κληθεί το valgrind, πληκτρολογήστε την εντολή make valgrind
      2.  Χωρίς χρήση ορισμάτων γραμμής εντολών :
1. Για να τρέξει χωρίς ορίσματα γραμμής εντολών το πρόγραμμα πληκτρολογήστε την εντολή make run_no_args
2. Για να τρέξει χωρίς ορίσματα γραμμής εντολών το πρόγραμμα πληκτρολογήστε την εντολή make valgrind_no_args        


Γενικά για την εργασία :
Στην εργασία αυτή , όπως θα δείτε έχω χωρισμένο τον κώδικα σε modules , και κάθε δομή την έχω υλοποιημένη σε διαφορετικά αρχεία.  Οι δομές που έχω χρησιμοποιήσει είναι 3 : ένας πίνακας κατακερματισμού ο οποίος είναι υλοποιημένος με λίστες ,ένα inverted Index και τέλος , μια (απλά συνδεδεμένη) λίστα .
Σχετικά με τη δομή της εργασίας , μέσα στο directory περιέχεται ένα και μοναδικό Makefile με οδηγίες για την μεταγλώττιση και σύνδεση του προγράμματος , και 5 ακόμα φάκελοι : 
1. configs : όπου είναι κάποια config files που έχω φτιάξει και τα διαχειρίζεται το πρόγραμμα κατα την εκτέλεσή του 
2. include : φάκελος που περιέχει τα header files 
3. modules : ο πηγαίος κώδικας των δομών και κάποιων συναρτήσεων που χρησιμοποιεί το πρόγραμμα
4. src : πηγαία των προγραμμάτων που συνδέονται με τα modules
5. tst : τα αρχεία που έχει δώσει ο διδάσκον για Testing . 
Η δομή του πίνακα κατακερματισμού είναι στο αρχείο hash_table και είναι ΑΥΣΤΗΡΑ ΔΙΚΗ μου υλοποίηση για το μάθημα Κ08 - Δομές Δεδομένων ,και την χρησιμοποίησα στην εργασία αυτή, με μόνη διαφορά ,ότι το interface παρουσιάζει τον πίνακα κατακερματισμού ως Map  , αλλά λειτουργικά είναι το ίδιο πράγμα.
        Για την λίστα έχω εμπνευστεί από το μάθημα  Κ08 - Δομές Δεδομένων , μιας και το πέρασα το προηγούμενο εξάμηνο και έχω διασαφηνισει όλες τις έννοιες ως προς τις δομές δεδομένων που έχω διδαχθεί.
        Το invertertedIndex το έχω υλοποιήσει με λίστες και αυτό , ουσιαστικά έχω βάλει μία λίστα η οποία περιέχει για κόμβους της indexNodes οι οποίοι αναπαρίστανται από μία δομή που περιλαμβάνει μία ακέραια μεταβλητή year και μία λίστα indexList η οποία κρατάει τα  records με έτος εγγραφής year. 
        Το αρχείο common_types έχει δηλωμένους κάποιους τύπους όπως δομές και συναρτήσεις που χρησιμοποιούνται σχεδόν από όλα τα modules της εργασίας.
Η άσκηση έχει υλοποιηθεί στο VIsual Studio Code σε Λειτουργικό σύστημα Ubuntu 18.04 και έχει δοκιμαστεί με επιτυχία στη μηχανή Linux 04 του εργαστηρίου και στο συγκεκριμένο μηχάνημα έχει τρέξει επιτυχώς και χωρίς Memory Leaks ή Erros κατά την εκτέλεση του valgrind.


Λεπτομέρειες hash_table:
        Για την δομή αυτή, χρησιμοποιώ λίστες ως buckets Τον αρχικό αριθμό των buckets τον καθορίζουμε κατά την δημιουργία . Για κάθε στοιχείο προς εισαγωγή, το bucket επιλέγεται μέσω της hash_function που έχουμε δώσει και ορίσει εμείς στο πρόγραμμα , η οποία στη προκειμένη περίπτωση είναι μια πολύ απλη συνάρτηση.Επίσης επειδή οι τιμές key,value είναι ορισμένες ως δείκτες (void*) αυτό μας δίνει τη δυνατότητα να είναι οποιουδήποτε τύπου δείκτη θέλουμε και έτσι έχουμε ευελιξία ως προς τα δεδομένα που κρατάει. Αυτός είναι ο λόγος που έχω φτιάξει και τις destroy functions οι οποίες είναι προσαρμοσμένες έτσι ώστε να αποδεσμεύουν κατάλληλα τον χώρο που δέσμευσε το hash_table και στη προκειμένη περίπτωση καταστρέφουν ένα record και τα περιεχόμενα του.


Λεπτομερειες για το invertedIndex:
         Όπως ζητείται από την εκφώνηση αλλά και παρουσιάζεται στο σχήμα, έχω φτιάξει μια λίστα με κόμβους που έχω δημιουργήσει εγώ indexNodes και στη συνέχεια έχω υλοποιήσει το interface ώστε να αποθηκεύονται σωστα τα  records μέσα στη δομή. Για τα records  μέσα στην δομή κρατάω pointer προς αυτά και η αποδέσμευση γίνεται μία φορά και γίνεται κατά την καταστροφή του hash_table , όχι εδώ. 
Σε αυτή τη δομή καταστρέφω μόνο τους κόμβους με χρήση της συνάρτησης καταστροφής που έχω φτιάξει και έπειτα καταστρέφω και την κύρια δομή (ή αλλιώς τη λίστα που αποθηκεύονται οι indexNodes). 


Λεπτομέρειες για την linked_list:
        Επίσης όπως στο map / hash_table έχω υλοποιήσει την λίστα με την ιδιαιτερότητα να αποθηκεύει pointers ώστε να επιτευχθεί ευελιξία και επίσης έχω υλοποιήσει τη λίστα να περιέχει dummy κόμβους για διευκόλυνση σε άλλες λειτουργίες της λιστας. Επίσης, υπάρχει συνάρτηση καταστροφής που αποδεσμεύει τον χώρο που πιάνει ένας κόμβος λίστας.


Σχετικά με το mnstd:
        Αρχικά , η υλοποίηση που έχω επιλέξει , αρχικα ανοίγει τα αρχεία που έχουν δωθεί ώς ορίσματα  , εαν έχουν δοθεί και τα δύο ορίσματα με οποιαδήποτε σειρά και στη συνέχεια απο το αρχείο input διαβάζει τα δεδομένα προς εισαγωγή στη δομή μας και εισάγει τις εγγραφές στις δομές. Από το αρχείο config έχει διαβάσει έναν αριθμό , ο οποίος συμβολίζει το αρχικό μέγεθος του hash table , δηλαδή τον αριθμό των buckets που θα περιέχει.Είναι προφανές ότι, ανάλογα με το αρχείο που δίνουμε ως είσοδο , χρειάζεται και το αντίστοιχο hash size , αλλά και κατάλληλο ώστε να μην υπάρχουν καθυστερήσεις στη δομή και τις λειτουργίες της.Προφανώς, για 300 μαθητές στη προκειμένη περίπτωση δεν μπορούμε να έχουμε ίδιο αριθμό buckets με αυτόν που θα έχουμε για 300.000 μαθητές. Αν βάλουμε τον αριθμό αυτό ίδιο , τότε για 300.000 μαθητές μάλλον το πρόγραμμα θα γίνει αρκετά αργό . Για αυτό η τιμή αυτή επιλέγεται κατά την αρχικοποίηση της δομής.
Κατόπιν,εμφανίζεται έναν μήνυμα στην οθόνη για τον αριθμό των διπλότυπων που υπάρχουν στη δομή.
Στη συνέχεια εφόσον το πρόγραμμα έχει διαχειριστεί με επιτυχία τα ορίσματα της γραμμής εντολών αν αυτά υπάρχουν, προχωράει στο κομμάτι της αλληλεπίδρασης του με τον χρήστη.  
Με την χρήση της fgets δίνω τη δυνατότητα στον χρήστη να κάνει πολλαπλά ερωτήματα συνεχόμενα, το ένα μετά το άλλο και το πρόγραμμα απαντάει με την κατάλληλη έξοδο.Όταν όμως, ο χρήτης πληκτρολογήσει την λέξη exit  , τότε όπως ζητείται και από την εκφώνηση , το πρόγραμμα ήρθε η ώρα να τερματίσει. Αποδεσμεύεται η μνήμη που έχει δεσμευτεί ώς εκείνη τη στιγμή από τις δομές και το κυρίως πρόγραμμα και τερματίζεται επιτυχώς το πρόγραμμα.Σε κάθε άλλη περίπτωση το πρόγραμμα δεν έχει τερματίσει επιτυχώς.


Λεπτομέρειες υλοποίησης του Interface:
        Μία κοινή λειτουργία για όλες τις επιλογές που δίνονται στο interface είναι η χρήση της συνάρτησης checkString η οποία παίρνει όρισμα μια συμβολοσειρά και έναν αριθμό και επιστρέφει true αν ο αριθμός των ορισμάτων είναι ίσος με n . Για παράδειγμα στο insert, για να είναι σωστή η λειτουργία χρειάζονται 7 ορίσματα. Αν δεν δοθούν 7 ορίσματα το πρόγραμμα θα εκτυπώσει μήνυμα λάθους και θα περιμένει για την επόμενη εντολή. 


1. insert  studentid lastname firstname zip year gpa: διαβάζονται τα δεδομένα της εγγραφής προς εισαγωγή, αποδίδονται με σωστή σειρά σε μεταβλητές και έπειτα αποδίδονται οι μεταβλητές αυτές σε μια εγγραφή και τέλος προστίθενται στη δομή μας , με χρήση των συναρτήσεων εισαγωγής για το map/hash_table και invertedIndex. Εκτυπώνεται το κατάλληλο μήνυμα


2. look-up studentid : για τη συνάρτηση αυτή ψάχνω μέσα στο map/hashtable για κόμβο με key ίσο με student id. Εκτυπώνεται το κατάλληλο μήνυμα.
 
3. delete studentid : διαγράφεται η εγγραφή και από τις δυό δομές , αν υπάρχει και στη συνέχεια εκτυπώνεται αντίστοιχο μήνυμα .
4. number year  : καλείται η συνάρτηση   invertedIndex_yearCount η οποία απλά βρίσκει σε ποιον κόμβο υπάρχει η λίστα με το έτος year και επιστρέφει το μέγεθος της λίστας που περιέχει τις εγγραφές με έτος year. Εκτυπώνεται το κατάλληλο μήνυμα.


5. top  num year : καλείται η συνάρτηση   invertedIndex_topNstudents η οποία φτιάχνει μια αντιγραφή της λίστας με εγγραφές έτους year και για n φορές βρίσκει το max της νέας λίστας και στη συνέχεια το αφαιρεί. [χρησιμοποιείται η συνάρτηση findMax] Εκτυπώνεται το κατάλληλο μήνυμα.


6. average year :   καλείται η συνάρτηση invertedIndex_averageYear και η οποία , εφόσον βρεί σε ποια λίστα υπάρχουν εγγραφές με έτος year , βρίσκει τον ΜΟ τους.Εκτυπώνεται το κατάλληλο μήνυμα.


7. minimum year :  καλείται η συνάρτηση  invertedIndex_minimumYear η οποία βρίσκει ποιος είναι ο μικρότερος Μ.Ο. με έτος εγγραφής year και στη συνέχεια επιστρέφει τις εγγραφές που έχουν αυτό το ΜΟ(μπορεί να είναι πάνω από 1). Εκτυπώνεται το κατάλληλο μήνυμα.


8. postal code rank 


9. exit  : αποδεσμεύεται η μνήμη και τερματίζει επιτυχώς το πρόγραμμα.