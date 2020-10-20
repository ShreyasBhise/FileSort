# SystemsAsst0

TL;DR: Insertion sort and quicksort on files full of strings of ASCII characters and files full of integers.


Project Description:

You will write some code to read in data from a file, sort it and output the sorted values. In this case while the 
representation will be the same for all files, the data may be different. This is to say all files will be ASCII character 
files, however some will hold numeric data and some will hold strings. Your code will need to decide which type of information 
it is dealing with and select an appropriately-typed sorting function for the task. Keep in mind that the sorting function is 
not the same as the sorthing algorithm - one is an implementation, the other is a theoretical ordering of operations and 
partitioning of information. The user is allowed to select which sorting algorithm to use at runtime, so you will need to 
implement as the first parameter to your code a flag in order to select which sorting algorithm's implementation (function) 
your code should apply. Your code must also take in as your second command line parameter a single file name, open it, read in 
all tokens from it and determine whether the data is representing integers or strings. You are guaranteed that the tokens will 
be ASCII character data and that they all will be comma-separated. You should however ignore all other separations (newlines, 
spaces, tabs, etc.). Once all data has been sorted, your code should output the entire sorted contents to STDOUT with each 
value on its own line in increasing order (you might find it beneficial then to sort tokens in the same manner).

You can segment this work in to a series of modules, which in the end may ease the developement path considerably. You can 
break the code in to the following functional elements:
- read from a file
			- open it (and error states)
			- read in one char, up to a comma, multiple comma-separated tokens, multiple tokens with interspersed noise (spaces, newlines..)
			- read on char at a time (optionally, read in n chars and extract tokens from the buffer)
- sorts
			- code linked lists
			- code insertion sort first (it is simple)
			- write sorts on linked lists of numbers
			- duplicate code and change type/functions to work on linked lists of numbers
- function pointers
			- write an integer and a string comparator
			- generalize the input types to be void*, but cast them inside the function
			- copy/paste sort code and modify it to accept your comparators
