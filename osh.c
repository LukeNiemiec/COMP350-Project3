#include "filetable.c"


// removes all files from the filesystem by getting 
// all of the used blocks and 
void format(Block** filetable, int* freemap) {
	// create an empty list for addresses in the filetable with blocks in them
	int used_addresses[MAX_BLOCKS];

	// fill the list with addresses and get the size of it 
	int size = get_used(used_addresses, freemap);

	// get each used block by looping through results
	// and remove the block from the filetable
	for(int i = 0; i < size; i++) {
	
		// get the block's filetable address
		int file_address = used_addresses[i];
		
		// get the block from the filetable
		Block* file = filetable[file_address];

		// get the filename from the block
		char* filename = file->filename;

		// remove the block from the filetable and freemap
		remove_file(filename, filetable, freemap);
		
	}

	printf("[+] Successfully formated the disk\n");
}




//	before creating, reading, deleting and writing files from 
//	user, you must check whether a file exists first.block
	
/*	EXAMPLE CODE:



	bool in_files = in_filetable(filename, filetable, freemap)

	if(in_files) {
		// can proceed for: read_file(), delete_file(), write_file()

		int address = get_address(filename, filetable, freemap);

		Block* file = filetable[address];


		// write data to the file:
		strcpy(file->filedata, "some file")
		
		
		
	} else {
		// can proceed for: create
		// TODO: error handling for this condition
	}

	
*/ 



// write data to a file

/*
	. get the address of the filename from the filetable using: 	get_address()
	. get the block from the filetree using the address:			filetable[address
	. use strcpy() to add data to block->filedata:					strcpy(block)

*/
void write_file(char* fileame, char* filedata, Block** filetable, int* freemap) {}

void create(char* filename, Block** filetable, int* freemap) {}

void read_file(char* filename, Block** filetable, int* freemap) {}

void delete_file(char* filename, Block** filetable, int* freemap) {}

// list all files in the filetable:
void ls(Block** filetable, int* freemap) {}



// FOR COMMAND TESTING PUTPOSES:
// gets a command from the user input
int get_input(char* out) {
	int size = 20;
	fflush(stdin);
	printf("\n> ");
	fgets(out, size, stdin);
	return size;
}

void main(int argc, char* argv[]) {

	/* FREEMAP: A list of 90 ones and zeros
	
	Each element represents the block availability 
	at the element's index(memory address).
	Block availability could be 1 or 0 */
	int freemap[MAX_BLOCKS];

	/* FILETABLE: A list of 90 Block pointers
	Each block is null at first but will fill up 
	when we add new files to the filetable. We keep
	track of what addresses have blocks using the freemap*/
	Block* filetable[MAX_BLOCKS];

	
	// looped to keep the filesystem running 
	while(true) {

		// FOR COMMAND TESTING PURPOSES:
		// collecting user input
		char in[30];

				
		// get user input
		int size = get_input(in);

		// creates an array of args
		char* args[3];
		char* arg = strtok(in, " ");
		int cnt = 0;
		

		// loop through matches from strtok
		while(arg != NULL) {
		
			// allocate and copy arg to the Command struct
			args[cnt] = malloc(sizeof(char) * (strlen(arg)+1));
			strcpy(args[cnt], arg);
			
			arg = strtok(NULL, " ");
			cnt++;
		}

		args[cnt] = NULL;

		
		// Created from user input:
		// 	.	args   - array of strings
		// 	. 	cnt	   - number of arguments in args
		// -------------------------------
		// now we can have commands without restarting the command
		// and test commands with the filesystem on the same file
		// -------------------------------

		
		//Requested file system command interceptor- Bertin Simeon 4/30/26 3:48 PM
		if (strcmp(args[0], "format\n") == 0) {//Function intializes disk and clears freemap and filetable
		    format(filetable, freemap);
		    
		} else if (strcmp(args[0], "create\n") == 0) {//Sets aside a free block and associates a filename to refer to affermentioned free block
		    create(args[1], filetable, freemap);
		    
		} else if (strcmp(args[0], "read\n") == 0) {//Finds requested block and displays content within block
		    read_file(args[1], filetable, freemap);
		    
		} else if (strcmp(args[0], "write\n") == 0) {//Changes contents of the content within the requested block
		
			/*TODO:
				. check the output for prompting for filedata after we confirmed that 
				the file is in the system or treat all remaining arguments until argc arguments
				
			*/
			
		
		    // Assuming args[2] holds the string of data to write
		    write_file(args[1], args[2], filetable, freemap); 
		    
		} else if (strcmp(args[0], "delete\n") == 0) {//Sets a block free and removes it from the table 
		    delete_file(args[1], filetable, freemap);
		    
		} else if (strcmp(args[0], "ls\n") == 0) {// Acts as the lister of all existing files
		    ls(filetable, freemap);
		    
		}
	}	
}
