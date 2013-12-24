//------------------------------------------------------------------------------
// <copyright file="CSSqlStoredProcedure.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------
using System;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;

public partial class StoredProcedures
{
    [Microsoft.SqlServer.Server.SqlProcedure]
    public static void SqlStoredProcedure1 ()
    {
        //Get the data from the database
        
        //Define two variables
        int numberOfGrades = 0;
        double totalNCredits = numberofGrades * 3.0;
        double weightTotal = 0.0;
        char letterGrade;
        //a lot of ifs
        if (letterGrade == "A")
            numberGrade = 4.0;
        else if (letterGrade == "B")
            numberGrade = 3.0;

        weightTotal = weightTotal + numberGrade + 3.0;

        //end of loop

        Gpa = weightTotal / totalNCredits;
        
        //output the result
        


        
    }
}
