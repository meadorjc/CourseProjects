use MyGuitarShop;

select CardNumber, len(cardnumber) as NumberLength, 
					right(cardnumber, 4) as CardEnd, 
					concat('XXXX-XXXX-XXXX-', right(cardnumber, 4)) as SecretCardEnd
from Orders