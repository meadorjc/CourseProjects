Imports VBClassLibrary

Public Class frmAddVehicle

    Private Sub btnExit_Click(sender As System.Object, e As System.Windows.RoutedEventArgs)
        Me.Close()
    End Sub

    Private Sub btnClear_Click(sender As System.Object, e As System.Windows.RoutedEventArgs)
        txtCostValue.Clear()
        txtInventoryID.Clear()
        txtManufacturer.Clear()
        txtModelName.Clear()
        txtModelYear.Clear()
        txtVehicleID.Clear()
        txtMessage.Text = ""
        txtInventoryID.Focus()
    End Sub

    Private Sub btnInsert_Click(sender As System.Object, e As System.Windows.RoutedEventArgs)
        If IsValidData() Then
            Dim inventoryID As Int32 = Convert.ToInt32(txtInventoryID.Text)
            Dim manufacturer As String = txtManufacturer.Text
            Dim modelname As String = txtModelName.Text
            Dim year As Int32 = Convert.ToInt32(txtModelYear.Text)
            Dim vehicleid As String = txtVehicleID.Text
            Dim costvalue As Decimal = Convert.ToDecimal(txtCostValue.Text)
            Dim vehicle1 As New Vehicle(inventoryID, manufacturer, modelname, year, vehicleid, costvalue)
            If VehicleDB.InsertVehicle(vehicle1) Then
                txtMessage.Text = "The above vehicle was added to the database."
            Else
                txtMessage.Text = "The above vehicle was not added to the database."
            End If
        End If
    End Sub

    Private Function IsValidData() As Boolean
        Return WPFValidator.IsPresent(txtInventoryID) AndAlso _
                   WPFValidator.IsInt32(txtInventoryID) AndAlso _
                   WPFValidator.IsPresent(txtManufacturer) AndAlso _
                   WPFValidator.IsPresent(txtModelName) AndAlso _
                   WPFValidator.IsPresent(txtModelYear) AndAlso _
                   WPFValidator.IsInt32(txtModelYear) AndAlso _
                   WPFValidator.IsPresent(txtVehicleID) AndAlso _
                   WPFValidator.IsPresent(txtCostValue) AndAlso _
                   WPFValidator.IsDecimal(txtCostValue) AndAlso _
                   WPFValidator.IsDecimal(txtCostValue, 0D)
    End Function
End Class
