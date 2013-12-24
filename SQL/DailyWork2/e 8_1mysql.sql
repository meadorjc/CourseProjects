select invoice_total, format(invoice_total,1) as format_total,
convert(invoice_total,unsigned) as convert_total,
cast(invoice_total as unsigned) as cast_total
from invoices