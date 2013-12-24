select count(ModelName) SuburbanCount, avg(costvalue) AverageSuburbanCost
from vehicle
where ModelName = 'Suburban';