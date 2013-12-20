Caleb Meador 12/19/2013 - meadorjc at gmail.com

NameDirectory (Ge2 part II)	
	
	Batch-File Usage: NameDirectory.exe can be from command-line only due to 
        required command-line arguments. Furthermore, the program is meant to 
        write specifically formatted data to a new file through indirection 
        operators (as per program requirements), so that an output file may also
        be used as an input file. Thus, outputting characters to the console was
        prohibited. Using a batch-file to run the program gives the user more 
        information about the processing, but doesn't interfer with the programs
        use of indirection operators.
        
		NameDirectoryAscending.bat
			Display file data before and after sort; creates a new file with data
			sorted in ascending order.
		NameDirectoryDescending.bat
			Display file data before and after sort; creates a new file with data
			sorted in descending order.	
            
    Command-line Usage: NameDirectory {asc | desc} < InputFile.txt > OutputFile.txt
	
	Purpose: To better understand the use of file i/o streams, command-line 
    arguments, various levels of pointers and pointer indirection, and dynamic 
    memory allocation, and text parsing.
    
	Program: This program reads in a list of names and sorts them in ascending 
    or descending order.
    
		Input File Format:  [Number of entries]				2
							LastName, FirstName				Smith, John J.
							...		, ...					Adams, Susan Ann
	
	Procedure:
	For more detailed specifications, see NameDirectorySortSpecs.pdf
    
        Read, process, and save command-line arguments.
		
		Read number of data items from file.
		
		Dynamically allocate an array of pointers on the heap, each element 
        containing the address of a dynamically allocated string object.
		
		Loop through data in file:
			Read in data
			Copy to temp string
			Copy temp string to dynamically allocated string pointer.
			Place string pointer address in array of pointers.
		End loop
		
		Sort array of pointers so that the names in the dynamically allocated 
        strings are in ASCENDING or DESCENDING order, as per user's command-line
        argument.
        
		Output results.
		
		Free dynamically allocated memory.
		