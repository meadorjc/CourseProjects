Caleb Meador 12/19/2013 - meadorjc at gmail.com

StudentGradeDataSorter (GE3)
    
    Command-Line Usage:
    
      StudentGradeDataSort {name | score} {asc | des} < [InputFile].txt > [OutputFile].txt

        {name | score} 
        
            Choose whether to sort data by name or score.
            
        {asc | des} 
        
            Choose whether to sort name or score in ascending or descending
            order. 
     
        [InputFile].txt
            
            Text-file that holds student names and grades in a specified format.
            The text-file information is inserted into the program through the 
            use of the redirection operator (<).
               
               N 
               "Lastname0, Firstname0" S
               "Lastname2, Firstname2" S
               
            where N represents the number of names in the file, and S is the 
            student's score.
    
        [OutputFile].txt
            
            Text-file that holds the sorted output of student names and grades 
            in a specified format. The text-file information is inserted into 
            the program through the use of the redirection operator (>).
        
        Examples:
        
        StudentGradeDataSort name  asc < TestFile1.txt > NameAsc.txt
        StudentGradeDataSort score asc < TestFile1.txt > ScoreAsc.txt
        StudentGradeDataSort name  des < TestFile1.txt > NameDes.txt
        StudentGradeDataSort score des < TestFile1.txt > ScoreDes.txt
        StudentGradeDataSort asc name  < TestFile1.txt > NameAsc.txt
        StudentGradeDataSort asc score < TestFile1.txt > ScoreAsc.txt
        StudentGradeDataSort des name  < TestFile1.txt > NameDes.txt
        StudentGradeDataSort des score < TestFile1.txt > ScoreDes.txt

        Commands may be entered in any order.
        
    Batch-File Usage:
        The following batch-files insert corresponding command-line arguments
        to the command-prompt on Windows machines.
        
        SortNameAscending.bat :
        StudentGradeDataSort name asc < InputExample.txt > SortNameAscendingOutput.txt

        SortNameDescending.bat :
        StudentGradeDataSort name des < InputExample.txt > SortNameDescendingOutput.txt
        
        SortNameAscending.bat :
        StudentGradeDataSort score asc < InputExample.txt > SortScoreAscendingOutput.txt
        
        SortNameAscending.bat :
        StudentGradeDataSort score des < InputExample.txt > SortScoreDescendingOutput.txt

    Purpose: The purpose of this program was to utilize structs, pointers
        to structs, dynamically allocated struct data, command-line arguments,
        and flexible input-file data processing to sort information in 
        alphabetic, numeric, ascending, or descending orders as per user 
        arguments.
    
        Input File Example: 
        
            [number of entries]                  2
            ["name0"][score0]                    "Frost, Jack" 87
            ["name1"][score1]                    "Kent, Clark" 120
            ...          ...                     ...
            
    Procedure:
    For detailed program specifications, see ProgramSpecifications.pdf
    
    Process command-line arguments and save for later use.
        
        Read the number of data items from the file.
        
        Dynamically allocate array of struct pointers that
            contains the addresses of structs that have a nested
            char pointer to the student's name and an unsigned 
            integer containing the student's score.
        
        While there is data being read from the file:
            Read and parse a data line, separating the name
            and score and storing them.
            
            Dynamically allocate memory for a student struct
            and place its address in the array of struct pointers.
            
            Dynamically allocate memory to store the name of the student
            and store in the struct's pointer to an array of chars.
        
        Sort the list based on the command line arguments.
        
        Free all dynamically allocated memory.
    