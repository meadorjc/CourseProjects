
Public Class Vehicle
    Private cInventoryID As Integer
    Private cManufacturer As String
    Private cModelName As String
    Private cYear As Integer
    Private cVehicleID As String
    Private cCostValue As Decimal

    Public Property InventoryID As Integer
        Get
            Return cInventoryID
        End Get
        Set(value As Integer)
            cInventoryID = value
        End Set
    End Property

    Public Property Manufacturer As String
        Get
            Return cManufacturer
        End Get
        Set(value As String)
            cManufacturer = value
        End Set
    End Property

    Public Property ModelName As String
        Get
            Return cModelName
        End Get
        Set(value As String)
            cModelName = value
        End Set
    End Property

    Public Property Year As Integer
        Get
            Return cYear
        End Get
        Set(value As Integer)
            cYear = value
        End Set
    End Property

    Public Property VehicleID As String
        Get
            Return cVehicleID
        End Get
        Set(value As String)
            cVehicleID = value
        End Set
    End Property

    Public Property CostValue As Decimal
        Get
            Return cCostValue
        End Get
        Set(value As Decimal)
            cCostValue = value
        End Set
    End Property

    Public Sub New()
        cInventoryID = 0
        cManufacturer = ""
        cModelName = ""
        cYear = DateTime.Today.Year
        cVehicleID = ""
        cCostValue = 0
    End Sub

    Public Sub New(inventoryid As Integer, manufacturer As String, modelname As String, year As Integer, vehicleid As String, costvalue As Decimal)
        cInventoryID = inventoryid
        cManufacturer = manufacturer
        cModelName = modelname
        cYear = year
        cVehicleID = vehicleid
        cCostValue = costvalue
    End Sub

End Class
