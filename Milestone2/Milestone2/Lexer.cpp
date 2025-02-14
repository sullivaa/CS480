#include "Lexer.h"


Lexer::Lexer()
{
}
//finds the next token
Token Lexer::nextToken(int &offset) {
	Token next;
	next = scan(offset);
	return next;
}

Token Lexer::scan(int &offset) {
	ifstream testfile;
	testfile.open("testfile.txt");
	testfile.seekg(offset);

	Token token;

	while (!testfile.eof()) {
		offset++;
		while (testfile.get(c)) {
			if (c == ' ' || c == '\t' || c == '\n') {
				///offset = offset + 2;
				offset++;
				continue;
			}
			else {
				break;
			}
		}
		
		while (true) {
			//looking for operators or strings
			if (isalpha(c) || isdigit(c) || c == ' ' || c == '\t' || c == '\n') { //there is a prob here where we are not looking at this before nums and stuff. Need to rearrange loops.
				break;
			}
			else {		
				stringstream ss;
				string s;
				ss << c;
				ss >> s;

				//string
				if (c == '\"') {
					string st;
					testfile.get(c);
					offset++;
					while (testfile.peek() != '\"') {
						st += c;
						testfile.get(c);
						offset++;
					}
					st += c;
					offset++;

					token = Token(Tag::STRINGTYPE, st);
					return token;
				}


				switch (c) {
				case ';':
					break;
				case '(':
					token = Token(Tag::LPAR, s);
					return token;
				case ')':
					token = Token(Tag::RPAR, s);
					return token;
				case '&':
					token = Token(Tag::AND, s);
					return token;
				case '|':
					token = Token(Tag::OR, s);
					return token;
				case '+':
					token = Token(Tag::PLUS, s);
					return token;
				case '-':
					token = Token(Tag::MINUS, s);
					return token;
				case '*':
					token = Token(Tag::MULT, s);
					return token;
				case '/':
					token = Token(Tag::DIV, s);
					return token;
				case '^':
					token = Token(Tag::POW, s);
					return token;
				case '%':
					token = Token(Tag::MOD, s);
					return token;
				case '=':
					token = Token(Tag::EQUAL, s);
					return token;
				case '!':
					if (testfile.peek() != '=') {
						token = Token(Tag::NOT, s);
						return token;
					}
					else {
						s = c;
						testfile.get(c);
						s += c;

						offset = offset++;
						token = Token(Tag::NE, s);
						return token;
					}
				case '<':
					if (testfile.peek() != '=') {
						token = Token(Tag::LT, s);
						return token;
					}
					else {
						s = c;
						testfile.get(c);
						s += c;
						//cout << s;
						offset++;
						token = Token(Tag::LE, s);
						return token;
					}
				case '>':
					if (testfile.peek() != '=') {
						token = Token(Tag::GT, s);
						return token;
					}
					else {
						s = c;
						testfile.get(c);
						s += c;
						offset++;
						token = Token(Tag::GE, s);
						return token;
					}
				case ':':
					if (testfile.peek() != '=') {
						break;
					}
					else {
						s = c;
						testfile.get(c);
						s += c;
						offset++;
						token = Token(Tag::ASSIGN, s);
						return token;
					}

				default:
					break;
				}
				testfile.get(c);
				offset++;
			}
		} //out of loop; can look for nums, reals, keywords, or ids now



		int v = 0;
		float x = 0;
		string l;

		//numbers		
		if (isdigit(c)) {
			while (isdigit(c)) {
				l += c;
				testfile.get(c);
				offset++;
			}
			if (c == '.') {
				l += c; // add the decimal
				//cout << l;
				testfile.get(c);
				//cout << c;
				while (isdigit(c)) {
					l += c; 
					testfile.get(c);
					offset++;
				}
				//cout << l;
				x = stof(l);
				token = Token(Tag::REALTYPE, x);
				return token;
			}
			else {
					//return Num(v);
				v = stoi(l);
				offset--;

				token = Token(Tag::INTTYPE, v);
				return token;
			}
		}

		//letters
		if (isalpha(c)) {
			string b;

			do {
				b += c;
				testfile.get(c);
				offset++;
			} while (isalpha(c) || isdigit(c));

			//offset--;
			//cout << b;
			if (b.compare("and") == 0) {
				token = Token(Tag::AND, b);
				return token;
			}
			if (b.compare("or") == 0) {
				token = Token(Tag::OR, b);
				return token;
			}
			if (b.compare("not") == 0) {
				token = Token(Tag::NOT, b);
				return token;
			}
			if (b.compare("true") == 0) {
				token = Token(Tag::TRUE, b);
				return token;
			}
			if (b.compare("false") == 0) {
				token = Token(Tag::FALSE, b);
				return token;
			}
			if (b.compare("bool") == 0) {
				token = Token(Tag::BOOL, b);
				return token;
			}
			if (b.compare("int") == 0) {
				token = Token(Tag::INT, b);
				return token;
			}
			if (b.compare("real") == 0) {
				token = Token(Tag::REAL, b);
				return token;
			}
			if (b.compare("string") == 0) {
				token = Token(Tag::STRING, b);
				return token;
			}
			if (b.compare("sin") == 0) {
				token = Token(Tag::SIN, b);
				return token;
			}
			if (b.compare("cos") == 0) {
				token = Token(Tag::COS, b);
				return token;
			}
			if (b.compare("tan") == 0) {
				token = Token(Tag::TAN, b);
				return token;
			}
			if (b.compare("if") == 0) {
				token = Token(Tag::IF, b);
				return token;
			}
			if (b.compare("while") == 0) {
				token = Token(Tag::WHILE, b);
				return token;
			}
			if (b.compare("let") == 0) {
				token = Token(Tag::LET, b);
				return token;
			}
			if (b.compare("stdout") == 0) {
				token = Token(Tag::STDOUT, b);
				return token;
			}
			else { 
				//offset--;
				token = Token(Tag::ID, b);
				return token;
			}
		}

	}

	if (testfile.peek() < 0) {
	//cout << "Reached EOF\n";		
		return Token(Tag::END, "end");
	}
	testfile.close();
}
/*
Token Lexer::checkName(int &offset) {
	if (isalpha(c)) {
		string b;
		Word w;
		do {
			b += c;
			testfile.get(c);
			offset++;
		} while (isalpha(c) || isdigit(c));
		//offset--;

		w.lexeme = b;
		cout << b;
		if (b.compare("and") == 0) {
			w.tag = Tag::AND;
			w = Word(Tag::AND, b);
			return w;
		}
		if (b.compare("or") == 0) {
			w.tag = Tag::OR;
			return w;
		}
		if (b.compare("not") == 0) {
			w.tag = Tag::NOT;
			return w;
		}
		if (b.compare("true") == 0) {
			w.tag = Tag::TRUE;
			return w;
		}
		if (b.compare("false") == 0) {
			w.tag = Tag::FALSE;
			return w;
		}
		if (b.compare("bool") == 0) {
			w.tag = Tag::BOOL;
			return w;
		}
		if (b.compare("int") == 0) {
			w.tag = Tag::INT;
			return w;
		}
		if (b.compare("real") == 0) {
			w.tag = Tag::REAL;
			return w;
		}
		if (b.compare("string") == 0) {
			w.tag = Tag::STRING;
			return w;
		}
		if (b.compare("sin") == 0) {
			w.tag = Tag::SIN;
			return w;
		}
		if (b.compare("cos") == 0) {
			w.tag = Tag::COS;
			return w;
		}
		if (b.compare("tan") == 0) {
			w.tag = Tag::TAN;
			return w;
		}
		if (b.compare("if") == 0) {
			w.tag = Tag::IF;
			return w;
		}
		if (b.compare("while") == 0) {
			w.tag = Tag::WHILE;
			return w;
		}
		if (b.compare("let") == 0) {
			w.tag = Tag::LET;
			return w;
		}
		if (b.compare("stdout") == 0) {
			w.tag = Tag::STDOUT;
			return w;
		}
		else {
			//offset--;

			w.tag = Tag::ID;
			return w;
		}
	}
}
Token Lexer::checkNum(int &offset) {
	Num n;
	//Real r;
	int v = 0;
	float x = 0;
	string l;

	//numbers		
	if (isdigit(c)) {
		while (isdigit(c)) {
			l += c;
			testfile.get(c);
			offset++;
		}
		if (c == '.') {
			l += c; // add the decimal
			//cout << l;
			testfile.get(c);
			//cout << c;
			while (isdigit(c)) {
				l += c;
				testfile.get(c);
				offset++;
			}
			cout << l;
			x = stof(l);
			//cout << x;
			return Tag::REALTYPE;
		}
		else {
			//return Num(v);
			v = stoi(l);
			cout << v;
			n.tag = Tag::INTTYPE;
			n.value = v;
			offset--;
			return n;
		}
	}
}
Token Lexer::checkString(int &offset) {
	stringstream ss;
	string s;
	ss << c;
	ss >> s;

	Word op;
	op.lexeme = s;

	Word str;
	
	if (c == '\"') {
		string st;
		testfile.get(c);
		offset++;
		while (testfile.peek() != '\"') {
			st += c;
			testfile.get(c);
			offset++;
		}
		st += c;
		offset++;
		//cout << st << " ";
		str.tag = Tag::STRINGTYPE;
		str.lexeme = st;

		//str = Word(289, st);
		cout << str.lexeme;
		//cout << str.tag;

		return str;
	}
}

Token Lexer::checkOper(int &offset) {
	Word n;
	stringstream ss;
	string s;
	ss << c;
	ss >> s;

	Word op;
	op.lexeme = s;

	Word str;

	switch (c) {
	case ';':
		break;
	case '(':
		cout << c;
		op.tag = Tag::LPAR;
		return op;
	case ')':
		cout << c;
		op.tag = Tag::RPAR;
		return op;
	case '&':
		cout << c;
		//n = Word(Tag::AND, s);
		op.tag = Tag::AND;
		return op;
	case '|':
		cout << c;
		op.tag = Tag::OR;
		return op;
	case '+':
		cout << c;
		op.tag = Tag::PLUS;
		return op;
	case '-':
		cout << c;
		op.tag = Tag::MINUS;
		return op;
	case '*':
		cout << c;
		op.tag = Tag::MULT;
		return op;
	case '/':
		cout << c;
		op.tag = Tag::DIV;
		return op;
	case '^':
		cout << c;
		op.tag = Tag::POW;
		return op;
	case '%':
		cout << c;
		op.tag = Tag::MOD;
		return op;
	case '=':
		cout << c;
		op.tag = Tag::EQUAL;
		return op;
	case '!':
		if (testfile.peek() != '=') {
			cout << c;
			op.tag = Tag::NOT;
		}
		else {
			s = c;
			testfile.get(c);
			s += c;
			cout << s;
			offset = offset++;
			op.tag = Tag::NE;
		}
		return op;
	case '<':
		if (testfile.peek() != '=') {
			cout << c;
			op.tag = Tag::LT;
		}
		else {
			s = c;
			testfile.get(c);
			s += c;
			cout << s;
			offset++;
			op.tag = Tag::LE;
		}
		return op;
	case '>':
		if (testfile.peek() != '=') {
			cout << c;
			op.tag = Tag::GT;
		}
		else {
			s = c;
			testfile.get(c);
			s += c;
			cout << s;
			offset++;
			op.tag = Tag::GE;
		}
		return op;
	case ':':
		if (testfile.peek() != '=') {
			break;
		}
		else {
			s = c;
			testfile.get(c);
			s += c;
			cout << s;
			offset++;
			op.tag = Tag::ASSIGN;
		}
		return op;
	default:
		break;
	}
	testfile.get(c);
	offset++;
}

Token Lexer::scan2(int &offset) {
	testfile.open("testfile.txt");
	testfile.seekg(offset);

	Token t;

	while (!testfile.eof()) {
		offset++;
		while (testfile.get(c)) {
			//whitespace
			if (c == ' ' || c == '\t' || c == '\n') {
				offset++;
				//continue;
			}
			else {
				t = Lexer::checkName(offset);
				t = Lexer::checkNum(offset);
				t = Lexer::checkString(offset);
				t = Lexer::checkOper(offset);
			}
		}
	}
	if (testfile.peek() < 0) {
		cout << "Reached EOF\n";
		t = Tag::END;
	}
	return t;
}
*/