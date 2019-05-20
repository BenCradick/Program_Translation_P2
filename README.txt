<<<<<<< HEAD

=======
P4:
Globally scoped variables are used again.
=======================================================================================================================
>>>>>>> P4
P3:
Globally scoped variables used.



=======================================================================================================================
P2:
Parser with binary tree works, prints the name of the node and tokens if applicable.
Fixed the issue with P1 where it was delimiting by whitespaces, should no longer generate errors for valid syntax.






<<<<<<< HEAD
#################################################################################################################
=======
=======================================================================================================================
>>>>>>> P4
P1:
Attempt at option 3 was made.

The FSA table is implemented modularly over a few functions, c++ makes it not_fun++ to store functions in an array, and
access them.
Each function listed corresponds to a function in the attached .png.
Scanner::routeToken() serves as f0.
Scanner::verifyId() serves to handle f1 and the check for leading uppercase for f0, wasn't a great way to just shove the
uppercase check on routeToken().
Scanner::verifyInt() serves to handle int in the graph.
It was suggested in the project instructions that a second filter should identify keywords, because keywords would
be initially categorized as belonging to the type id_tk all id_tk's were run through Scanner::getKeyWordToken().
The driver function is TestScanner::test().
