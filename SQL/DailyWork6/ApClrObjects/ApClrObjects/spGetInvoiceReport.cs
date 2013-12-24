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
    public static void spGetInvoiceReport ()
    {
        // Open the Connection object for the context
        SqlConnection con = new SqlConnection("Context connection=true");
        con.Open();
        //create a string
        string selectStatement = "select VendorName, InvoiceNumber, InvoiceDate, InvoiceTotal " +
            "from Vendors join Invoices on Vendors.VendorID = Invoices.VendorID " +
            "where InvoiceTotal - CreditTotal - PaymentTotal > 0";

        //create a Command Object
        SqlCommand selectCommand = new SqlCommand(selectStatement, con); //con is a connection
        //Use the SqlPipe
        SqlPipe pipe = SqlContext.Pipe;

        pipe.ExecuteAndSend(selectCommand);

        con.Close();

    }
}
