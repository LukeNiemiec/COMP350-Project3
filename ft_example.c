// include the file table file
#include "filetable.c"	

/*
MACROS:

	NAME				VALUE
	
	BLOCKDATA_SIZE		52
	FILENAME_SIZE		32
	MAX_BLOCKS			90


TABLE OF FUNCTIONS:
	RETURNS			NAME																DESCRIPTION

	bool			in_filetable(char* filename, Block** filetable, int* freemap)		checks if a filename is already in the filetable
	
*	int				get_address(char* filename, Block** filetable, int* freemap)		returns the address of the Block with the corresponding filename 
	
	int 			get_used(int* used, int* freemap)									populates the supplied list with addresses for used blocks and returns the size of the list
	
	int				get_unused(int* unused, int* freemap)								populates the supplied list with addresses that dont contain any blocks and returns the size of the list

*	bool			add_file(char* filename, Block** filetable, int* freemap)			allocates memory for the block, must be done before adding filename or filedata

*	bool 			remove_file(char* filename, Block** filetable, int* freemap)		removes all traces of the file from the specified file system

	void 			print_summary()														prints a summary of the filesystem contents
	
*/


// Example usage of the freemap and filetable using functions above
int main(int argc, char* argv[]) {


	
	/* FREEMAP: A list of 90 ones and zeros
	
	Each element represents the block availability 
	at the element's index(memory address).
	Block availability could be 1 or 0 */
	int freemap[MAX_BLOCKS];

	/* FILETABLE: A list of 90 Block pointers
	Each block is defined above*/
	Block* filetable[MAX_BLOCKS];

	

	// Example: creating files with data and put them in the filetable and freemap
	add_file("classes", "COMP350, COMP430, SOCI102, MATH200, COMP405", filetable, freemap);
	
	add_file("TODO","your moma", filetable, freemap);

	add_file("notes", "boomshakalaka", filetable, freemap);


	// prints debug message with filesystem contents and 
	print_summary(filetable, freemap);

	
	// Example: removing file with name "TODO" from the filetable and freemap 
	remove_file("classes", filetable, freemap);

	print_summary(filetable, freemap);
}
