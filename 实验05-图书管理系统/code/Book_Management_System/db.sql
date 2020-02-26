create schema booksystemmanager;
	use booksystemmanager;
	set autocommit = 0;

create table card
(
	cno		char(10),
    password char(16),
	name	varchar(10),
	department	varchar(40),
	type		char(1),
    primary key(cno)
);

create table admin
(
	ID varchar(10), 
	password varchar(16), 
	name varchar(10),
	contact varchar(20),
    primary key(ID)
);

create table book
(
	bno char(8) ,
	category 	char(10),
	title 		varchar(40),
	press		varchar(30),
	year		int,
	author		varchar(20),
	price		decimal(7,2),
	total		int,
	stock		int,
    primary key(bno)
);

create table borrow
(
	cno	char(10),
	bno char(8) ,
    ID varchar(10),
	borrow_date char(20),
	return_date char(20),
	primary key(cno, bno, ID),
	foreign key(cno) references card(cno),
	foreign key(bno) references book(bno),
    foreign key(ID) references admin(ID)

);

