Caleb Meador 12/19/2013 - meadorjc at gmail.com

PixelBlockBitmapGenerator (GE4)
    
    PixBlockBMP generates bitmaps from a preset template of 10 by 10 pixel-
    blocks, which are 50px by 50px squares.  The user can insert and delete
    rows and columns, modify the color of a single block, write the bitmap to 
    a new file, and quit the program through a text file. 
    
    Batch-File Usage:
        
        RunPixBlockBMP.bat 

            This batch file runs PixBlockBMP.exe with CommandFile.txt as the
            command-line argument 
            
            The example command-file that is included creates four bitmap files:
                default1.bmp
                defaultAfterInsert.bmp
                newDefaultColor.bmp, and
                tinyBitmap.bmp. 
                
            These four files demonstrate the default image, as well as the 
            default image after using various commands to edit the image.
    
    Command-Line Usage: 
        
        PixBlockBMP takes one command-line argument, which is the name of a text-
        file that serves at the command-file.    
    
        PixBlockBMP [Command-File-Name].txt
    
    Command-File Usage: Commands may be entered in any order.

        NEW DEFAULT COLOR
            default r [0-255] g [0-255] b [0-255] a [0-255] (use ALL)
        
        INSERT ROW or COL
            insert {row | col} [#] r [0-255] g [0-255] b [0-255] a [0-255]
                NOTE: colors optional. 
                If omitted, replaced by default values.
        
        DELETE ROW or COL
            delete {row | col} [#] (use all)
        
        MODIFY BLOCK
            mod [row] [#] [col] [#] r [0-255] g [0-255] b [0-255] a [0-255]
                NOTE: colors optional. 
                If omitted, replaced by value of 255 (default color)
        
        WRITE TO FILE
            write [user bmp file-name].bmp
        
        QUIT PROGRAM
            quit
    
        Example:
            default r 255 g 128 b 80 a 255
            insert row 5 r 20 g 23 b 188 a 222
            delete col 9
            mod row 0 col 0 r 0 g 255 b 25 a 80
            write ExampleBitmap.bmp
            quit


    Purpose: The purpose of this program is to utilize and consolidate learning 
        for the following concepts:
            - multi-dimensional to one-dimensional vector translations 
            - bitwise operator and byte-order configuration for primitive datatypes
            - binary-mode file processing 
            - Understand and work with hexadecimal format 
            - Understand bitmap file formatting and header structures.
            - continue to develop skills of structs, pointers to structs, 
                dynamically allocated struct data, command-line arguments processing, 
                and flexible input-file data processing.
                
        Definitions:
        PixelBlock 
            A 50px by 50px block of uniform color stored as a single unsigned 
            integer in a 1-d vector array; color can be specified by user
            or be filled in by a preset default color.
        
        Default PixelBlock Image         
            The default vector of unsigned integers with 100 elements, representing
            the pixel-blocks in the stardard 10 pixel-block by 10 pixel-block image.
            The default image is initially populated by a block-letter 'C'.
        
            Representation:
            
            R = RED     (0xFFFF0000)
            . = WHITE   (0xFFFFFFFF)
            
        ROW    
        9       R	R	R	R	R	R	R	R	R	R
        8       R	R	R	R	R	R	R	R	R	R
        7       R	R	.	.	.	.	.	.	.	.
        6       R	R	.	.	.	.	.	.	.	.
        5       R	R	.	.	.	.	.	.	.	.
        4       R	R	.	.	.	.	.	.	.	.
        3       R	R	.	.	.	.	.	.	.	.
        2       R	R	.	.	.	.	.	.	.	.
        1       R	R	R	R	R	R	R	R	R	R
        0       R	R	R	R	R	R	R	R	R	R

                0   1   2   3   4   5   6   7   8   9
                COL
                
        NOTE: rows and columns are numbered to represent the order in which 
        bitmap files are displayed, from bottom to top, left to right; (0, 0) to 
        (9,9).
        
        The significance of this is that bitmaps are stored in file horizontally
        flipped, and this must be taken into consideration when storing them 
        in program memory for editing. For ease of editing and processing, the 
        representative images are stored in program memory as below. 
        
        ROW    
        0       R	R	R	R	R	R	R	R	R	R
        1       R	R	R	R	R	R	R	R	R	R
        2       R	R	.	.	.	.	.	.	.	.
        3       R	R	.	.	.	.	.	.	.	.
        4       R	R	.	.	.	.	.	.	.	.
        5       R	R	.	.	.	.	.	.	.	.
        6       R	R	.	.	.	.	.	.	.	.
        7       R	R	.	.	.	.	.	.	.	.
        8       R	R	R	R	R	R	R	R	R	R
        9       R	R	R	R	R	R	R	R	R	R

                0   1   2   3   4   5   6   7   8   9
                COL
        
        Commands to edit the pixel-block vector use the grid as above, such that
        users may enter a command to modify (0, 0) and the top row, left-most
        pixel-block will be edited.
        
        Commands are entered first into a command-file that is then read in
        sequential order by the program.
        
    Procedure:
    For detailed program specifications, see PixBlockBMPSpecifications.pdf

        Process command-line arguments and save for later use.
        
        Check file system for file existence and open if present.
        
        Create the default bitmap image and save in program memory to edit later.
        
        Get an initial line from input file.
        
        While the there is still information to process in the file:
            Parse line from command-file into commands.
            
            Process commands and set necessary flags for appropriate edit.
            
            Execute commands to edit bitmap, write to file, or quit.
            
            Display any error messages from invalid data and continue.

            Reset flags as necessary.
            
            Get the next line from the file.

        Free all dynamically allocated memory.
              
        Close all files.
       
        End program.
        
