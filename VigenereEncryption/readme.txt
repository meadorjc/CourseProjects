Caleb Meador 12/17/2013 - meadorjc at gmail.com

StudentGradeDataSorter (GE4)
 - For detailed program specifications, see VigenereEncryptionSpecifications.pdf

    Purpose: The purpose of this program is to utilize multi-dimensional arrays, enumerated
        data-types, structs, pointers to structs, dynamically allocated struct data, 
        command-line arguments, and flexible input-file data processing to encrypt and decrypt 
        text using a Vigenere cypher. See: http://en.wikipedia.org/wiki/Vigenere_cipher
        
        Definitions
        Plaintext:  Alphabetic characeters, either upper or lower-case (preserved),
                    ignoring whitespace and numeric characters.
        Key:        Any sequence of upper-case alphabetic characters (1024 max) 
                    repeated over extent of plaintext.
        Ciphertext: Upper and lower-case encoded from plaintext.
        
        Encryption method: For each plaintext character (i.e. A), find its position
            along the top-most row (x-axis) of the Vigenere table.  Once located, 
            mark this column. Next, search down the left-most (y-axis) column 
            until the corresponding key character is found (i.e. L). Mark this row.
            The intersection of (A, L) in the table contains the letter L, which is the encoded character.
        
        Example
        Plaintext:      ATTACKATDAWN
        Key:            LEMONLEMONLE
        Ciphertext:     LXFOPVEFRNHR
        
        Vigenere Cipher Table:
        A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
        B C D E F G H I J K L M N O P Q R S T U V W X Y Z A
        C D E F G H I J K L M N O P Q R S T U V W X Y Z A B
        D E F G H I J K L M N O P Q R S T U V W X Y Z A B C
        E F G H I J K L M N O P Q R S T U V W X Y Z A B C D
        F G H I J K L M N O P Q R S T U V W X Y Z A B C D E
        G H I J K L M N O P Q R S T U V W X Y Z A B C D E F
        H I J K L M N O P Q R S T U V W X Y Z A B C D E F G
        I J K L M N O P Q R S T U V W X Y Z A B C D E F G H
        J K L M N O P Q R S T U V W X Y Z A B C D E F G H I
        K L M N O P Q R S T U V W X Y Z A B C D E F G H I J
        L M N O P Q R S T U V W X Y Z A B C D E F G H I J K
        M N O P Q R S T U V W X Y Z A B C D E F G H I J K L
        N O P Q R S T U V W X Y Z A B C D E F G H I J K L M
        O P Q R S T U V W X Y Z A B C D E F G H I J K L M N
        P Q R S T U V W X Y Z A B C D E F G H I J K L M N O
        Q R S T U V W X Y Z A B C D E F G H I J K L M N O P
        R S T U V W X Y Z A B C D E F G H I J K L M N O P Q
        S T U V W X Y Z A B C D E F G H I J K L M N O P Q R
        T U V W X Y Z A B C D E F G H I J K L M N O P Q R S
        U V W X Y Z A B C D E F G H I J K L M N O P Q R S T
        V W X Y Z A B C D E F G H I J K L M N O P Q R S T U
        W X Y Z A B C D E F G H I J K L M N O P Q R S T U V
        X Y Z A B C D E F G H I J K L M N O P Q R S T U V W
        Y Z A B C D E F G H I J K L M N O P Q R S T U V W X
        Z A B C D E F G H I J K L M N O P Q R S T U V W X Y
        
    Procedure:
        Process command-line arguments and save for later use.

        Open appropriate files for encryption and decryption.

        Create 2-dimensional array of Vigenere Table to serve as a cipher.
        
        Create 1-dimensional array to serve as the key for the cipher.
        
        While there is information in file:
            Depending on ENCRYPT or DECRYPT mode, get a character from appropriate file to encode or decode.
        
            Get the corresponding cipher character.
            
            Translate from source to encoded/decoded character.
            
            Write to output file.
        
        Close all files.
        
        Free all dynamically allocated memory.
        
        End program.
        
        
    Command-Line Usage: Commands may be entered in any order.
        
        ENCRYPT (– e) 
            Argument indicates the program should encrypt the file indicated by the (–p) 
            argument and save the cipher text in a file specified by the (–c) argument.
        
        DECRYPT (– d) 
            Argument indicates the program should decrypt the file indicated by the (–c) 
            argument and save the plain text in a file specified by the (–p) argument.
        
        KEY-FILE (–k) 
            Argument specifies the name of the file containing the password.
        
        The -e, -d, -p, -c, and -k arguments can occur in any order on the command line. 
        
        Exactly one of the arguments e or d must occur on the command line. All other arguments are
        optional. 
        
        If either the –c or –p arguments is not specified, the plaintext file is assumed to 
        be plaintext.txt and the cipher text file is assumed to be ciphertext.txt. 
        
        If the –k argument is not specified, it is assumed that a file named password.txt 
        will be used. 
        
        All default files are assumed to be in the current directory.
        
        Example:
        GE4  –e –p PlainText.txt –c CipherText.txt –k password.txt
        GE4  -d -p PlainText.txt –c CipherText.txt –k password.txt
        GE4  -e
        GE4  -d
        
    Batch-File Usage:
        The following batch-files insert corresponding command-line arguments to the command-prompt on Windows machines.
        
        VigenereEncryptInputFile.bat
            VigenereEncryption -e -p  PlainText.txt -c EncryptedFile.txt -k password.txt
            
            Encrypt characters from PlainText.txt into new file
            DecryptedFile.txt.
        
        VigenereDecryptOutputFile.bat
            VigenereEncryption -d -c EncryptedFile.txt -p DecryptedFile.txt -k password.txt
        
            Decrypt characters from DecryptedFile.txt into a new
            file DecryptedFile