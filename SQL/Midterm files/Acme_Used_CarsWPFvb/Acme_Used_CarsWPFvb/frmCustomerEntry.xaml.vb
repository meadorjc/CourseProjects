Imports VBClassLibrary

Public Class frmCustomerEntry

    Private Sub btnInsert_Click(sender As System.Object, e As System.Windows.RoutedEventArgs)
        Dim number As String = txtNumber.Text
        Dim name As String = txtName.Text
        Dim invid As Integer = Convert.ToInt32(cboInventoryID.SelectedItem)
        Dim c As New Customer(number, name, invid)
        If CustomerDB.InsertCustomer(c) Then
            txtMessage.Text = "The above customer was entered into the database."
        Else
            txtMessage.Text = "The above customer was not entered into the database."
        End If
    End Sub

    Private Sub btnClear_Click(sender As System.Object, e As System.Windows.RoutedEventArgs)
        txtMessage.Text = ""
        txtName.Text = ""
        txtNumber.Text = ""
        cboInventoryID.SelectedIndex = -1
        txtNumber.Focus()
    End Sub

    Private Sub btnExit_Click(sender As System.Object, e As System.Windows.RoutedEventArgs)
        Me.Close()
    End Sub

    Private Sub Window_Loaded(sender As System.Object, e As System.Windows.RoutedEventArgs) Handles MyBase.Loaded
        Dim vehlist As List(Of Vehicle) = VehicleDB.GetVehicles()
        For Each v As Vehicle In vehlist
            cboInventoryID.Items.Add(v.InventoryID)
        Next
        cboInventoryID.SelectedIndex = -1
    End Sub
End Class
