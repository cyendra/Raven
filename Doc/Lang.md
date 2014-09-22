				
	Raven v0.1 语法
	stmts	 -> stmts stmt
	stmt     -> decls;
			  | if bool then stmt;
			  | if bool then stmt else stmt;
			  | while bool do stmt;
			  | block;
			  | break;
			  | continue;
	decls	 -> var decl;
	decl	 -> set
			  | decl, set
	set		 -> loc
			  | loc := bool
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
	integer  -> [1-9][0-9]*
			  | 0
	real	 -> [0-9]+\.[0-9]+