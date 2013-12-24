Imports System.Data
Imports System.Data.SqlClient

Public Class Acme_Used_CarsDB

    Public Shared Function GetConnection() As SqlConnection
        Dim con As New SqlConnection()
        con.ConnectionString = "Data Source=localhost\sqlexp2012;Initial Catalog='Acme Used Cars';Integrated Security=SSPI"
        Return con
    End Function

End Class
