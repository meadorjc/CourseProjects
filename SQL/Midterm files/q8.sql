select avg(CostValue) as AvgCostValue, Manufacturer
from Vehicle
group by Manufacturer;