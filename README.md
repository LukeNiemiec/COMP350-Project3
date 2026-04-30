Ive updated the code on `osh.c` to be a one off command so that we can simplify testing 
each indiviual command. Ive also created an example using the filetable and the freemap 
functions in `filetable.c` for the `format()` function aswell as outlined some more examples
that will help the function programmers with their functions. 

Please feel free to reach out with questions on the functionality of `filetable.c` or 
check out the reference at the top of the file.


**BUILD AND TEST FUNCTIONS**:

	. just update your functions and use the command line arguments to test it
	. this allows us to test the commands with the block-based filesystem after one 
	  another to test for bugs in the command's functionality
		
	
	TERMINAL EXAMPLE:
		```

		gcc osh.c -o osh
		
		./osh

		> format
		[+] Successfully formatted disk

		>
		```
