Class MainWindow 

    Private Sub btnExit_Click(sender As System.Object, e As System.Windows.RoutedEventArgs)
        Me.Close()
    End Sub

    Private Sub btnCustomerEntry_Click(sender As System.Object, e As System.Windows.RoutedEventArgs)
        Dim customerForm As New frmCustomerEntry()
        customerForm.Show()
    End Sub

    Private Sub btnVehicleEntry_Click(sender As System.Object, e As System.Windows.RoutedEventArgs)
        Dim addVehicleForm As New frmAddVehicle()
        addVehicleForm.Show()
    End Sub
End Class
