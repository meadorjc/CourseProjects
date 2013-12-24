Imports System.Data
Imports System.Data.SqlClient

Public Class VehicleDB

    Public Shared Function GetVehicles() As List(Of Vehicle)
        Dim con As SqlConnection = Acme_Used_CarsDB.GetConnection()
        Dim vehList As New List(Of Vehicle)()
        Dim command As New SqlCommand()
        command.CommandText = "select * from Vehicle"
        command.CommandType = CommandType.Text
        command.Connection = con
        Try
            con.Open()
            Dim reader As SqlDataReader = command.ExecuteReader()
            While reader.Read()
                Dim v As New Vehicle()
                v.InventoryID = Convert.ToInt32(reader(0))
                v.Manufacturer = reader(1).ToString()
                v.ModelName = reader(2).ToString()
                v.Year = Convert.ToInt32(reader(3))
                v.VehicleID = reader(4).ToString()
                v.CostValue = Convert.ToDecimal(reader(5))
                vehList.Add(v)
            End While
            reader.Close()
        Catch err As SqlException
            MessageBox.Show(err.Message, "Database Error")
        Finally
            con.Close()
        End Try
        Return vehList
    End Function

    Public Shared Function InsertVehicle(vehicle1 As Vehicle) As Boolean
        Dim rows As Integer = 0
        Dim con As SqlConnection = Acme_Used_CarsDB.GetConnection()
        Dim command As New SqlCommand()
        command.CommandText = "insert into Vehicle values (@inventoryid,@manufacturer,@ModelName,@year,@vehicleid,@costvalue)"
        command.CommandType = CommandType.Text
        command.Connection = con
        command.Parameters.AddWithValue("@inventoryid", vehicle1.InventoryID)
        command.Parameters.AddWithValue("@manufacturer", vehicle1.Manufacturer)
        command.Parameters.AddWithValue("@ModelName", vehicle1.ModelName)
        command.Parameters.AddWithValue("@year", vehicle1.Year)
        command.Parameters.AddWithValue("@vehicleid", vehicle1.VehicleID)
        command.Parameters.AddWithValue("@costvalue", vehicle1.CostValue)
        Try
            con.Open()
            rows = command.ExecuteNonQuery()
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
