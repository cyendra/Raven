#pragma once

namespace RavenInternal {

	class Token {
	public:
		static 	enum Tag {
			VAR, LOC, IF, THEN, ELSE, DO, WHILE, BEGIN, END,
			SET,
		};
		Token();
		virtual ~Token();
	};

}
