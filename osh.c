
//Requested file system command interceptor- Bertin Simeon 4/30/26 3:48 PM
if (strcmp(args[0], "format") == 0) {//Function intializes disk and clears freemap and filetable
    format(filetable, freemap);
    continue;
} else if (strcmp(args[0], "create") == 0) {//Sets aside a free block and associates a filename to refer to affermentioned free block
    create(args[1], filetable, freemap);
    continue;
} else if (strcmp(args[0], "read") == 0) {//Finds requested block and displays content within block
    read_file(args[1], filetable, freemap);
    continue;
} else if (strcmp(args[0], "write") == 0) {//Changes contents of the content within the requested block
    // Assuming args[2] holds the string of data to write
    write_file(args[1], args[2], filetable, freemap); 
    continue;
} else if (strcmp(args[0], "delete") == 0) {//Sets a block free and removes it from the table 
    delete_file(args[1], filetable, freemap);
    continue;
} else if (strcmp(args[0], "ls") == 0) {// Acts as the lister of all existing files
    ls(filetable, freemap);
    continue;
}
