use AP;

create table Instructions (
	InstructionID int not null identity primary key,
	instructions xml not null);

	set @instructionXML = '
	<Instructions>
		<Step>
			<Description>This is the first step.<Description>
			<SubStep>This is the first step.</Substep>
			<SubStep>This is the seconds step.</Substep>
		</Step>
		<Step>
			<Description>This is the second step.<Description>
		</Step>
		<Step>
			<Description>This is the third step.<Description>
		</Step>
	</Instructions>
'
;

insert into instructions values (@InstructionXML);

select * from instructions;
