				
	Raven v0.1 语法
	stmts	 -> stmts stmt
	stmt     -> var decls;
			  | if bool then stmt
			  | if bool then stmt else stmt
			  | while bool do stmt;
			  | block
			  | break;
			  | continue;
			  | Assign;
	decls	 -> decl
			  | decl, decls
	decl	 -> loc
	Assign	 -> loc := bool
	block    -> begin stmts end
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
			  | term % unary
			  | unary
	unary    -> not unary
			  | - unary
			  | factor
	factor   -> ( bool )
			  | loc
			  | integer
			  | real
			  | true
			  | false
	integer  -> [0-9]+
	real	 -> [0-9]+\.[0-9]+


	关键字与符号
	var if then else while do begin end break return continue
	true false and or not
	+ - * / %
	:= = > < >= <= <>
	( ) { }
	; . ,
	


