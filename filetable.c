#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



#define BLOCKDATA_SIZE 512		// max amount of file data bytes 

#define FILENAME_SIZE 32		// max filename size

#define MAX_BLOCKS 90 			// max amount of blocks in the filesystem



// Defines a Block type as a struct with the following fields:
typedef struct Block {
	char* filename;
	char* filedata; 
} Block;



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


// populates the list with memory addresses(indecies)
// that are unused and returns the number of unused 
// memory addresses in the unused list
int get_used(int* used, int* freemap) {

	// stores the number of unavailable addresses
	int used_cnt = 0;

	// check the block availability of each address
	// within the free table and update accordingly
	for(int i = 0; i < MAX_BLOCKS; i++) {
		if(freemap[i] == 1) {
			used[used_cnt] = i;
			used_cnt++;		
		}
	}

	// return the number of unavailable addresses found
	return used_cnt; 
}


// same as get_used(int* fre...) however, it 
// checks for unused memory addreses 
int get_unused(int* unused, int* freemap) {

	int unused_cnt = 0;

	// Search through the freemap to 
	for(int i = 0; i < MAX_BLOCKS; i++) {
		if(freemap[i] == 0) {
			unused[unused_cnt] = i;
			unused_cnt++;		
		}
	}

	// return the number of available addresses found
	return unused_cnt;
}



// gets the index of the file
int get_address(char* filename, Block** filetable, int* freemap) {
	int used[MAX_BLOCKS];
	int size = get_used(used, freemap);

	// loop through all of the used memory addresses
	for(int i = 0; i < size; i++) {

		// address of the next used Block in the filetable
		int address = used[i];

	
		// compare the corresponding block's filename with the parameter
		if(strcmp(filetable[address]->filename, filename) == 0) {
			return address;
		}
	}

	// returns -1 if the file isnt found in the filetable
	return -1;
}


// returns true if a filename is already in 
bool in_filetable(char* filename, Block** filetable, int* freemap) {
	int block_address = get_address(filename, filetable, freemap);
	
	if(block_address != -1) {
		return true;
	} else {
		return false;
	}
}


// Adds a new file to the filetable and returns false if the filename is in the filetable already
bool add_file(char* filename, char* filedata, Block** filetable, int* freemap) {

	// check if the file is already in the file system
	if(in_filetable(filename, filetable, freemap)) {
		return false;
	}

	// create and allocate memory for the new Block
	Block* new_block = malloc(sizeof(Block));
	new_block->filename = malloc(sizeof(char) * FILENAME_SIZE);
	new_block->filedata = malloc(sizeof(char) * BLOCKDATA_SIZE);
	
	// uninitialized list for unused addresses
	int addresses[MAX_BLOCKS];

	// opulates the supplied list with addresses that are available from free map
	int size = get_unused(addresses, freemap);
	
	// you can use any algorithm you choose to get next address 
	// but im going to just choose the first for simplicity
	int next_address = addresses[0];

	// debug msg
	// printf("adding block to address %d", next_address);
	
	// edit the following filename and filedata of the Block 
	strcpy(new_block->filename, filename);
	strcpy(new_block->filedata, filedata);

	// add the new block to the filetable and 
	filetable[next_address] = new_block;

	// mark the address to used in the freemap
	freemap[next_address] = 1;

	return true;
}


// de-allocates memory resources and removes the file's 
// Block from the filetable and the freemap
bool remove_file(char* filename, Block** filetable, int* freemap) {

	// get the address of the filename
	int address = get_address(filename, filetable, freemap);

	// check and return false if the filename wasnt found
	if(address == -1) {
		return false;
	}
	
	//  get the corresponding block
	Block* block = filetable[address];

	// free assosiated data from the block and filetable
	free(block->filedata);
	free(block->filename);
	free(filetable[address]);

	// mark address as unavailable
	freemap[address] = 0;

	return true;
}


// prints a representation of the filesystem to the terminal
void print_summary(Block** filetable, int* freemap) {

	// uninitialized list for unused addresses
	int addresses[MAX_BLOCKS];

	// opulates the supplied list with addresses that are available from free map
	int size = get_used(addresses, freemap);

	// for each used address print the Block from the filetable 
	for(int i = 0; i < size; i++) {
		int addr = addresses[i];

		Block* blk = filetable[addr];
		
		printf("\n-----------\nAddress: %d, Filename: %s\n\t%s\n", addr, blk->filename, blk->filedata);
	}

	printf("-----------\n\n");
}

