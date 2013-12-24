select InventoryID, Manufacturer, ModelName
from Vehicle
where inventoryId not in (select InventoryID
						from Customer c)