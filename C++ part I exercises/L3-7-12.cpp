/*****************
    Caleb Meador
    COSC 1436
    Programming Lab 3
    L3-7-12.cpp
    Grade Book Modification
*******************/


#include <iostream>
#include <iomanip> //include to format output
#include <cstring> //include to use strings
using namespace std;

const int A = 0;    //For array letterGrade, A = 0
const int B = 1;    //For array letterGrade, B = 1
const int C = 2;    //For array letterGrade, C = 2
const int D = 3;    //For array letterGrade, D = 3
const int F = 4;    //For array letterGrade, F = 4

//Total number of students; only 5
const int NUM_STUD = 5;

//Students only had 4 tests each.
const int NUM_GRADE = 4;

//There are only 5 letter grades that can be assigned to each test.
const int LETTER_GRADE = 5;

//Function input() prototype - used to get input on student's name, and grade
//for each test.
void input(string studentName[], 
           double studentGrade[][NUM_GRADE], int students);

//Function calcDisplay() prototype - used to calculate the lowest score of the
//4 tests and average the highest 3 tests, and display the results. 
void calcDisplay(string studentName[], 
            double studentGrade[][NUM_GRADE],
            char letterGrade[], int students, int letter);

int main()
{
    //String array holds students names of size [NUM_STUD}.
    string studentName[NUM_STUD];
    
    //Char array initialized to the 5 possible letter grades that a test score
    //represents
    char letterGrade [LETTER_GRADE] = {'A', 'B', 'C', 'D', 'F',};
    
    //double array of size 3X4 is initialized to -1 to prime memory locations.
    double studentGrade[NUM_STUD][NUM_GRADE] = {{-1,-1,-1,-1},
                                                {-1,-1,-1,-1},
                                                {-1,-1,-1,-1},
                                                {-1,-1,-1,-1},
                                                {-1,-1,-1,-1}};
       
    //output display message
    cout << "\n\n--===Student Grade Report Program===--\n\n";
    
    //function call input(), passing studentName, studentGrade, and NUM_STUD
    //in order to get name, and 4 students grades from user.
    input(studentName, studentGrade, NUM_STUD);
    
    //calcDisplay() call; finds the lowest grade and drops it; calculates the 
    //average of the three highest scores; outputs report.
    calcDisplay(studentName, studentGrade, letterGrade, NUM_STUD, LETTER_GRADE);
    
    cout << endl << endl;
    
    //Pause system before ending program
    system("Pause");

    return 0;

}

//Function input() definition: gets user input to assign string to studentName
//array, assign grades to studentGrade
void input(string studentName[], 
     double studentGrade[][NUM_GRADE], int students)
{
    //Output prompt to user to ask for input.
    cout << "Please input the student's name and four test scores.\n";
    
    //For-loop iterates through each row of the array as many times as there 
    //are students.
    for (int i = 0; i < students; ++i)
    {
        //Output prompt for input of student name
        cout << "\nStudent[" << i+1 << "] ";
        
        //getline() called to get string and input to studentName[i]
        getline(cin, studentName[i]);
        
        cout << endl;
        
        //Nested loop runs iterates through a double-type array to accept the 
        //test grade and assigns it to the same row as the student's string 
        //array; iterating through the column values, j, the individual test
        //grades are assigned to the appropriate number. 
        for(int j = 0; j < NUM_GRADE; ++j)
        {
            
            //While-loop validates input; the grade entered must be greater than
            // zero and less than 100, 
            while(studentGrade[i][j] < 0 || studentGrade[i][j] > 100)
            {
                //Output input prompt
                cout << "\n\tGrade[" << j+1 << "] (0-100):";
                
                //input grade to array
                cin >> studentGrade[i][j];
                
                //Ignore the white-space after using cin
                cin.ignore();
            
                //Output error message is the input falls below 0 or greater
                //than 100
                if (studentGrade[i][j] < 0 || studentGrade[i][j] > 100)
                {
                    cout << "\n\t*Must be between 0 and 100: ";
            
                }
            }
        }
    }           
}    
    

//Function calcDisplay() finds and drops the lowest grade, averaging only the 
//top three scores, then displays the grade report for each student and assigns
//them each a letter grade based on the average.
void calcDisplay(string studentName[], double studentGrade[][NUM_GRADE],
                char letterGrade[], int students,int letter)

{
    //Declare and initialize sumCount as 0; this integer variable sums the 
    //grades in order to average them.
    int sumCount = 0;
    
    //Declare lowestScore array; this stores the value of the lowest score for 
    //each student and stores it as a double in this array.
    double lowestScore[NUM_STUD];
    
    //Declare sumHighest array and initialize to 0; this stores the sum of the 
    //highest scores for each student for use in calculating the average score.
    double sumHighest[NUM_STUD] = {0,0,0,0,0};
    
    //Declare studentAvg array and initialize to 0; this stores the student's
    //calculated final average for use in displaying the report.
    double studentAvg[NUM_STUD] = {0,0,0,0,0};
    
    //Output grade report title
    cout << "\n--==Student Grade Report Summary==--\n";
    
    //For loop finds the lowestScore out of the array of studentGrade
    //Outer loop i represents the student
    for (int i = 0; i < students; ++i)
        {
            //Assign the first student grade to lowestScore[i] array location
            lowestScore[i] = studentGrade[i][0];
            
            //Nested loop iterates through the grades of the student (i), and if
            //-statement within test to see if the current grade is less than
            //lowestScore; it if is, then that score will be assigned to 
            //lowestScore.
            for(int j = 0; j < NUM_GRADE; ++j)
            {
                if (studentGrade[i][j] < lowestScore[i])
                {
                    lowestScore[i] = studentGrade[i][j];
                }
            }
        }     
    
    //For-loop iterates through the grades of a student and drops only 1 score
    //that is found to be the lowest
    for (int i = 0; i < students; ++i)
        {
            //integer variable serves as a sentinal; when one grade has been 
            //dropped, don't drop any more. Initialized to zero at each new
            //iteration (for each student).
            sumCount = 0;
           
            
            //Nested loop cycles through the grades of the student.
            for(int j = 0; j < NUM_GRADE; ++j)
            {
                
                //If the student's grade the lowest score
                //and another grade hasn't already been dropped, then increase
                //sumCount by one to signal that a grade has been dropped
				if (studentGrade[i][j] == lowestScore[i] && sumCount < 1)
                {
                     sumCount++;
				}
                //If a grade hasn't been dropped yet, then add the value in
                //studentGrade to the array sumHighest to add up the total value
                //of the three highest grades.
                else
                {
                    sumHighest[i] += studentGrade[i][j];
                }
            }
        
            //Store the value of total of the 3 highest grades, divided by 3, in
            //the array studentAvg.
            studentAvg[i] = sumHighest[i] / (NUM_GRADE-1.0);
        
        }     

    //For loop cycles through each student's average test score and outputs a 
    //report that displays the student's name, average grade, and assigns a 
    //letter grade.
    for (int i = 0; i < students; ++i)
    {
        //If the student's average is 90 or higher, or 100 or lower, then the
        //letter grade is A.
        if(studentAvg[i] >= 90 && studentAvg[i] <= 100)
            cout << "\n Student: \t" << studentName[i] << "\n Average: \t"  
                 << fixed << setprecision(2) << studentAvg[i] 
                 << "\n Letter Grade: \t"<< letterGrade[A] << endl << endl;
        
        //Otherwise, If the student's average is 80 or higher, or lower than 90
        //then the letter grade is B. 
        else if(studentAvg[i] >= 80 && studentAvg[i] < 90)
            cout << "\n Student: \t" << studentName[i] << "\n Average: \t"   
                 << fixed << setprecision(2) << studentAvg[i] 
                 << "\n Letter Grade: \t"<< letterGrade[B] << endl << endl;
        
        //Otherwise, If the student's average is 70 or higher, or lower than 80
        //then the letter grade is C.
        else if(studentAvg[i] >= 70 && studentAvg[i] < 80)
            cout << "\n Student: \t" << studentName[i] << "\n Average: \t"   
                 << fixed << setprecision(2) << studentAvg[i] 
                 << "\n Letter Grade: \t"<< letterGrade[C] << endl << endl;
        
        //Otherwise, If the student's average is 60 or higher, or lower than 70
        //then the letter grade is D.
        else if(studentAvg[i] >= 60 && studentAvg[i] < 70)
            cout << "\n Student: \t" << studentName[i] << "\n Average: \t"   
                 << fixed << setprecision(2) << studentAvg[i] 
                 << "\n Letter Grade: \t"<< letterGrade[D] << endl << endl;
        
        //Otherwise, If the student's average is 0 or higher, or lower than 60
        //then the letter grade is F.
        else if(studentAvg[i] >= 0 && studentAvg[i] < 60)
            cout << "\n Student: \t" << studentName[i] << "\n Average: \t"  
                 << fixed << setprecision(2) << studentAvg[i] 
                 << "\n Letter Grade: \t"<< letterGrade[F] << endl << endl;
            
    }

}


