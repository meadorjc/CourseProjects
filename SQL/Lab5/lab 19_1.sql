use myguitarshop;

select firstname, lastname, line1, line2, city, state, zipcode
from customers c
join Addresses a
on c.customerid = a.CustomerID
for XML auto, root('CustomerAddresses'), elements;

go
create xml schema collection customeraddress.xml_schema_name
as xml_schema_expression;

go
create xml schema collection customeraddresses
as
'<?xml version="1.0" encoding="utf-8"?>
<xs:schema attributeFormDefault="unqualified" elementFormDefault="qualified" xmlns:xs="http://www.w3.org/2001/XMLSchema">
	<xs:element name="customeraddresses">
		<xs:complexType>
			<xs:sequence>
				<xs:element maxOccurs="unbounded" name="customer">
					<xs:complexType>
						<xs:sequence>
							<xs:element name="firstname" type="xs:string" />
								<xs:element name="lastname" type="xs:string" />
									<xs:element name="address">
										<xs:complexType>
											<xs:sequence>
												<xs:element name="line1" type="xs:string" />
												<xs:element name="line2" type="xs:string" />
												<xs:element name="city" type="xs:string" />
												<xs:element name="state" type="xs:string" />
												<xs:element name="zipcode" type="xs:unsignedInt" />
									</xs:sequence>
								</xs:complexType>
							</xs:element>
						</xs:sequence>
					</xs:complexType>
				</xs:element>
			</xs:sequence>
		</xs:complexType>
	</xs:element>
</xs:schema>';