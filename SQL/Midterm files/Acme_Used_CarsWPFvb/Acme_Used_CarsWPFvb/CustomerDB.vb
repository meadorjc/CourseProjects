Imports System.Data
Imports System.Data.SqlClient

Public Class CustomerDB

    Public Shared Function InsertCustomer(customer1 As Customer) As Boolean
        Dim rows As Integer = 0
        Dim con As SqlConnection = Acme_Used_CarsDB.GetConnection()
        Dim cmd As New SqlCommand()
        cmd.CommandText = "insert into Customer values (@number,@name,@inventoryid)"
        cmd.CommandType = CommandType.Text
        cmd.Connection = con
        cmd.Parameters.AddWithValue("@number", customer1.Number)
        cmd.Parameters.AddWithValue("@name", customer1.Name)
        cmd.Parameters.AddWithValue("@inventoryid", customer1.InventoryID)
        Try
            con.Open()
            rows = cmd.ExecuteNonQuery()
        Catch err As SqlException
            MessageBox.Show(err.Message, "Database Error")
        Finally
            con.Close()
        End Try
        If rows = 1 Then
            Return True
        Else
            Return False
        End If
    End Function

End Class
