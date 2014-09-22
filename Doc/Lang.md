				
	Raven v0.1 语法
	stmt     -> var loc;  
			  | var loc := bool;
			  | loc := bool;
			  | if bool do stmt;
			  | while bool do stmt;
			  | block;
			  | break;
	block    -> begin stmt end
	loc      -> id
	bool     -> bool or join
			  | join
	join     -> join and equality
			  | equality
	equality -> equality = rel
			  | equality <> rel
			  | rel
	rel      -> expr < expr
			  | expr <= expr
			  | expr > expr
			  | expr >= expr
			  | expr
	expr     -> expr + term
			  | expr - term
			  | term
	term     -> term * unary
			  | term / unary
			  | unary
	unary    -> not unary
			  | - unary
			  | factor
	factor   -> ( bool )
			  | loc
			  | num
			  | real
			  | true
			  | false
				