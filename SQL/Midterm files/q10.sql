select Name, Manufacturer, ModelName, CostValue
from vehicle v
left join Customer c
on v.InventoryID = c.InventoryID
where c.Number is not null
