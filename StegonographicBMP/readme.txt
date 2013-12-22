/*****************************************************
*    Caleb Meador
*    COSC1437 GE#6 , Fall, 2013
*    Filename:readme.txt
*    12/05/2013
*       Update 12/19/2013
********************************************************/
Stegonography literally means "concealed writing," and describes encoding hidden
messages or data within other data.  For more information, 
see: http://en.wikipedia.org/wiki/Steganography

StegonographicBitmap is a program that allows for bitmap files to be created, 
edited, and hidden within other bitmap files. It is based off a previous project, 
PixBlockBMP, to generate bitmaps from a preset template of 10 by 10 pixel-blocks, 
which are 50px by 50px squares.  The user can insert and delete rows and 
columns, modify the color of a single block, write the bitmap to a new file, 
and quit the program through a series of text file commands. 


A sample command-file is included:
    
    CommandFile.txt

Batch-File Usage:   
    
    runStegoBMP.bat
    
    This batch file opens the command-prompt and runs the StegoBMP with 
    "CommandFile.txt" as an argument. From the commands given in the text file,
    the program creates 7 bitmap files to demonstrate the various commands that
    are available.
        default.bmp 
            - standard generated bitmap
        default1.bmp 
            - standard bitmap file after insertions
        default2.bmp 
            - standard bitmap file after new default color and modifications
        stegoDefault.bmp 
            - default stegonographic file (same as default.bmp)
        fileToHide.bmp 
            - small bitmap which will be hidden inside another file.
        default2withHiddenFile.bmp 
            - same as default2.bmp, only with binary data
                altered in order to store fileToHide.bmp inside of the image.
        foundFile.bmp 
            - File after it has been decoded from binary data inside 
                the bitmap file.

Command-Line Commands: 
    
    StegoBMP takes one arguments, the name of the text-file containing commands.
    
    StegoBMP [command-file-name].txt

Command-File commands:
    
    CREATE NEW FILE OBJECT - creates default file to edit with red block-letter C
    
        createDefaultBitmapObject
    
    CREATE NEW FILE OBJECT FROM EXISTING FILE - creates a file object from GE5 
    compatible bitmap
    
        createBitmapObjectFromBMPFile [filename].bmp
    
    CREATE NEW STEGONOGRAPHY FILE OBJECT
    
        createDefaultStegoBitmapObject
    
    CREATE NEW STEGONOGRAPHY FILE OBJECT FROM EXISTING FILE
    
        createStegoBitmapObjectFromBMPFile [filename].bmp
    
        SPECIAL STEGONOGRAPHIC COMMANDS: 
        These may only be used with steganography objects
        
        HIDE BITMAP WITHIN ANOTHER BITMAP
        
            hideFileinBMPFile [fileWithHiddenData].bmp [fileToHide].bmp
        
        GET HIDDEN BITMAP FROM ENCODED FILE
            
            retrieveFileFromBMPFile [fileWithHiddenData].bmp [fileToReveal].bmp
    
    
    GENERAL COMMANDS:
    These commands may be used with both normal bitmap and stenographic bitmap objects
    
        CREATE NEW DEFAULT COLOR:
        
            default r [0-255] g [0-255] b [0-255] a [0-255] (use ALL)
        
        INSERT ROW OR COLUMN with/without COLOR
        
            insert { row | col } [#] r [0-255] g [0-255] b [0-255] a [0-255]
            
            NOTE: colors optional. If omitted, replaced by default values.
        
        DELETE ROW OR COLUMN:
        
            delete {row | col} [#] 
        
        MODIFY ROW OR COLUMN with COLOR
        
            mod [row] [#] [col] [#] r [0-255] g [0-255] b [0-255] a [0-255]
            
            NOTE: colors optional. If omitted, replaced by value of 255 
            (default color)
        
        WRITE CURRENT FILE to FILESYSTEM
        
            write [user bmp file-name].bmp
        
        QUIT PROGRAM
        
            quit
            
            
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
        9       R    R    R    R    R    R    R    R    R    R
        8       R    R    R    R    R    R    R    R    R    R
        7       R    R    .    .    .    .    .    .    .    .
        6       R    R    .    .    .    .    .    .    .    .
        5       R    R    .    .    .    .    .    .    .    .
        4       R    R    .    .    .    .    .    .    .    .
        3       R    R    .    .    .    .    .    .    .    .
        2       R    R    .    .    .    .    .    .    .    .
        1       R    R    R    R    R    R    R    R    R    R
        0       R    R    R    R    R    R    R    R    R    R

                0    1    2    3    4    5    6    7    8    9
                COL

        NOTE: rows and columns are numbered to represent the order in which 
        bitmap files are displayed, from bottom to top, left to right; (0, 0) to 
        (9,9).
        
        The significance of this is that bitmaps are stored in file horizontally
        flipped, and this must be taken into consideration when storing them 
        in program memory for editing. For ease of editing and processing, the 
        representative images are stored in program memory as below. 
        
        ROW    
        0       R    R    R    R    R    R    R    R    R    R
        1       R    R    R    R    R    R    R    R    R    R
        2       R    R    .    .    .    .    .    .    .    .
        3       R    R    .    .    .    .    .    .    .    .
        4       R    R    .    .    .    .    .    .    .    .
        5       R    R    .    .    .    .    .    .    .    .
        6       R    R    .    .    .    .    .    .    .    .
        7       R    R    .    .    .    .    .    .    .    .
        8       R    R    R    R    R    R    R    R    R    R
        9       R    R    R    R    R    R    R    R    R    R

                0    1    2    3    4    5    6    7    8    9

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
            