
Public Class Customer
    Private cNumber As String
    Private cName As String
    Private cInventoryID As Integer

    Sub New()
        cNumber = ""
        cName = ""
        cInventoryID = 0
    End Sub

    Sub New(number As String, name As String, inventoryid As Integer)
        cNumber = number
        cName = name
        cInventoryID = inventoryid
    End Sub

    Public Property Number As String
        Get
            Return cNumber
        End Get
        Set(value As String)
            cNumber = value
        End Set
    End Property

    Public Property Name As String
        Get
            Return cName
        End Get
        Set(value As String)
            cName = value
        End Set
    End Property

    Public Property InventoryID As Integer
        Get
            Return cInventoryID
        End Get
        Set(value As Integer)
            cInventoryID = value
        End Set
    End Property

End Class
