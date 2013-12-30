/*Caleb Meador meadorjc at gmail.com*/
use MyGuitarShop;

go
create table productdescriptions (
	descriptionsId  int not null identity primary key,
	productid int not null ,
	[description] xml not null
);
SET IDENTITY_INSERT productdescriptions  ON;
go 




insert into productdescriptions (descriptionsid, productid, description)
values (1, 1, '<div>
  <h1>Tradition Redesigned</h1>
  <p>The Fender Stratocaster Electric Guitar is a Fender icon. Upgrades include a richer, deeper neck tint for a more elegant and expensive appearance; glossed neck front for improved looks with satin back for smooth playability; and bent steel Fender saddles with classic look and great tone. String spacing is narrowed for modern playability, saddle height screws are resized to reduce rough feel, and string slot on saddle is elongated to reduce string friction or breakage.</p>
  <p>The return of the American Standard Series Strat continues Fender''s tradition of commitment to the people who play Fender instruments out there in the real world. Today''s American Standard Stratocaster guitars are worthy heirs of their revered ancestors�mindful of player needs and taking full advantage of modern advances, yet remaining completely true to the elements and spirit that made these instruments popular in the first place. Improvements include redesigned bridges, neck and body finishes, and a Fender-exclusive high-tech molded case. Still on board for the American Standard Strat are the beloved hand-rolled fingerboard edges, Alnico V pickups, the Delta system that includes a high-output bridge pickup and a special no-load tone control, providing more gain, more high end, and a little more "raw" tone, and staggered tuning machines for tone and stability guaranteed to last a lifetime (with its limited lifetime warranty)!</p>
  <h2>Redesigned American Standard Strat Bridge</h2>
  <p>Gives sought-after tone with modern smooth trem travel. Block retains the mass and tone of a vintage bridge block, but is chamfered for access to deeper dives. Saddles have the classic look and tone, but with modern improvements (spacing, slot elongation, height, screw length).</p>
  <h3>Features</h3>
  <ul>
    <li>Solid alder body (urethane finish)</li>
    <li>3 hot American Strat single-coil pickups</li>
    <li>Rosewood or maple fretboard</li>
    <li>Fender SKB hardshell case, cable, strap, and polishing cloth</li>
    </ul>
</div>');

go
select *
from productdescriptions;