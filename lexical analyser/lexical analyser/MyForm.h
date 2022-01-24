#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <msclr\marshal_cppstd.h>
#include<bits/stdc++.h>
#include <unordered_map>
#include <regex>
//#include"testlib.h"
#define endl '\n'
#define all(v) v.begin(),v.end()
#define allr(s) s.rbegin(),s.rend()
#define RT(s) return cout<<s,0
#define sz(s)    (int)(s.size())
//#define PI acos(-1)
#define EPS 1e-8
#define watch(x) cout << (#x)<<" = "<<x<<endl
#define mk(x, y) make_pair(x, y)
using namespace std;
using namespace System;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
int dy[] = { 1, -1, 0, 0, -1, 1, 1, -1 };
int dx[] = { 0, 0, 1, -1, 1, -1, 1, -1 };


#pragma region arrays_of_data
vector<string> keywords{ "abstract","continue","for","new","switch","assert","default","if","package","synchronized","boolean","do","goto","private","this","break","double","implements","protected","throw","byte","else","import","public","throws","case","enum","instanceof","return","transient","catch","extends","int","short","try","char","final","interface","static","void","class","finally","long","strictfp","volatile","const","float","native","super","while" };
vector<string> operators{ "=", ">", "<", "!", "~", "?", ":", "->", "==", ">=", "<=", "!=", "&&", "||", "++", "--", "+", "-", "*", "/", "&", "|", "^", "%", "<<", ">>", "+=", "-=", "*=", "/=", "&=", ",=", "^=", "%=" };
vector<string> sperators{ "(", ")", "{", "}", "[", "]", ";", ",", ".", "...", "@", "::" };
vector<string> Escapesequance{ "\\b" , "\\t" , "\\n" , "\\f" , "\\r" , "\\\\"  ,"\\\'","\\\"" };
vector<char> flsuf{ 'f', 'F', 'd', 'D' };
map<string, string> symbolTable;
#pragma endregion

#pragma region helpful_funcs
bool is_digit(char ch) {
	return ch >= '0' && ch <= '9';
}
bool is_digit(string str) {
	for (auto& ch : str)
		if (!is_digit(ch))
			return false;
	return true;
}
bool is_alpha_digit(char ch) { // check wheter ch is letter or digit
	return isalpha(ch) || is_digit(ch);
}
bool is_alpha_digit_und(char ch) {
	return isalpha(ch) || is_digit(ch) || ch == '_';
}
bool is_alpha(string str) {
	for (auto& ch : str)
		if (!isalpha(ch))
			return false;
	return true;
}
bool is_alpha_digit(string str) {
	for (auto& ch : str)
		if (!is_alpha_digit(ch))
			return false;
	return true;
}
bool is_alpha_digit_und(string str) {
	for (auto& ch : str)
		if (!is_alpha_digit_und(ch))
			return false;
	return true;
}
bool is_hex_digit(char ch) {
	return is_digit(ch) || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f');
}
bool is_hex_digit(string str) {
	for (auto& ch : str)
		if (!is_hex_digit(ch))
			return false;
	return true;
}
bool is_signed_int(string str) {
	if (sz(str) == 0) return false;
	if (str[0] == '-' || str[0] == '+')
		str.erase(str.begin(), str.begin() + 1);
	if (sz(str) == 0) return false; // string was just sign
	return is_digit(str);
}
int read_digit(string & str, int idx) {
	// return first index greater than or equal to idx that not digit
	while (idx < sz(str) && is_digit(str[idx]))
		idx++;
	return idx;
}
bool is_exponent_part(string str) {
	if (sz(str) < 2) return false; // e{signed intger} e3 || e+3
	if (tolower(str[0]) != 'e') return false; // check e exist
	str.erase(str.begin(), str.begin() + 1); // erase e
	return is_signed_int(str); // check remain string is signed intger (+3)
}
bool is_float_f1(string str) {
	// Digits . [Digits] [ExponentPart] [FloatTypeSuffix]
	if (sz(str) == 0) return false;
	if (count(all(flsuf), str.back()) > 0) // check FloatTypeSuffix optional
		str.pop_back();
	int idx = read_digit(str, 0); // must read digits until stop
	if (!idx || idx == sz(str)) // idx == 0 means no digits in the string prefix
		return false;           // idx == sz(str) means the whole string is digits
	if (str[idx] != '.') return false; // check dot
	idx++; // skip dot
	idx = read_digit(str, idx); // optional digits
	if (idx == sz(str)) return true; // Digits .Digits [FloatTypeSuffix]
	return is_exponent_part(str.substr(idx)); // Digits . [Digits] ExponentPart [FloatTypeSuffix]
}
bool is_float_f2(string str) {
	// . Digits [ExponentPart] [FloatTypeSuffix]
	if (sz(str) == 0) return false;
	if (str[0] != '.') return false; // must begin with dot
	if (count(all(flsuf), str.back()) > 0) // check FloatTypeSuffix optional
		str.pop_back();
	int idx = read_digit(str, 1); // must read digits after dot
	if (idx == 1) return false; // means that there exist not digits after dot
	if (idx == sz(str)) return true; // . Digits [FloatTypeSuffix]
	return is_exponent_part(str.substr(idx)); // . Digits [ExponentPart] [FloatTypeSuffix]
}
bool is_float_f3(string str) {
	// Digits ExponentPart [FloatTypeSuffix]
	if (sz(str) == 0) return false;
	if (count(all(flsuf), str.back()) > 0) // check FloatTypeSuffix optional
		str.pop_back();
	int idx = read_digit(str, 0); // must begin with digits
	if (idx == 0) return false; // not contains digits in the begening
	return is_exponent_part(str.substr(idx)); // Digits ExponentPart [FloatTypeSuffix]
}
bool is_float_f4(string str) {
	// Digits [ExponentPart] FloatTypeSuffix
	if (sz(str) == 0) return false;
	if (count(all(flsuf), str.back()) == 0) // must end with FloatTypeSuffix
		return false;
	str.pop_back(); // erase float suffix
	int idx = read_digit(str, 0); // must begin with digits
	if (idx == 0) return false; // not begin with digits
	if (idx == sz(str)) return true; // Digits FloatTypeSuffix
	return is_exponent_part(str.substr(idx)); // Digits [ExponentPart] FloatTypeSuffix
}
bool is_half_float_f1(string str) {
	// Digits . [Digits] e|E;
	int idx = read_digit(str, 0); // must begin with digits
	if (idx == 0 || idx == sz(str)) return false; // idx == 0 str doesn't begin with digits
	// idx == sz(str) str contains only digits
	if (str[idx] != '.') return false; // check dot
	idx++; // skip dot
	idx = read_digit(str, idx); // Digits . [Digits]
	if (idx != sz(str) - 1) return false; // must end with e|E
	return tolower(str.back()) == 'e'; // Digits . [Digits] e|E;
}
bool is_half_float_f2(string str) {
	// .  Digits e|E
	if (sz(str) == 0) return false;
	if (str[0] != '.') return false; // begin with dot
	int idx = read_digit(str, 1); // check digit after dot
	if (idx == 1 || idx != sz(str) - 1) return false;
	// idx == 1 then no digits after dot
	// idx != sz(str) - 1  str must end with e|E
	return tolower(str.back()) == 'e';
}
bool is_half_float_f3(string str) {
	// Digits e|E;
	int idx = read_digit(str, 0); // must begin digits
	if (idx == 0 || idx != sz(str) - 1) // idx == 0  str not begin with digits 
		return false;
	// idx != sz(str) - 1   str must end with e|E
	return tolower(str.back()) == 'e';
}
#pragma endregion 

#pragma region regular_express_funcs
bool is_decimal(string str) {
	if (sz(str) == 0) return false; // if string is empty
	if (tolower(str.back()) == 'l') // check IntegerTypeSuffix
		str.pop_back();
	if (sz(str) == 0)return false; // check if string is only IntegerTypeSuffix
	if (str == "0")
		return  true;
	if (str[0] == '0') // may be octal but not decimal
		return  false;
	return is_digit(str);
}
bool is_hex(string str) {
	if (sz(str) == 0)return false;
	if (tolower(str.back()) == 'l')
		str.pop_back();
	if (sz(str) == 0)return false;
	if (sz(str) < 3)return false; // str = 0x not valid it must be 0x{at least one hex digit}
	if (str[0] != '0' || tolower(str[1]) != 'x') return false;
	return is_hex_digit(str.substr(2)); // check from index 2 to end of string is hex or not
}
bool is_octal(string str) {
	if (sz(str) == 0)return false;
	if (tolower(str.back() == 'l'))
		str.pop_back();
	if (sz(str) == 0)return false;
	if (str[0] != '0') return false; // octal must begin with 0
	if (sz(str) < 2)return false; // // str = 0 not valid it must be 0{at least one octal digit}

	for (int i = 1; i < sz(str); i++)
		if (str[i] < '0' || str[i] > '7') // check octal range
			return false;
	return true;
}
bool is_binary(string str) {
	if (sz(str) == 0)return false;
	if (tolower(str.back()) == 'l')
		str.pop_back();
	if (sz(str) == 0)return false;
	if (sz(str) < 3)return false; // 0b{at least one binary digit}
	if (str[0] != '0' || tolower(str[1]) != 'b')
		return false;
	for (int i = 2; i < sz(str); i++)
		if (str[i] < '0' || str[i] > '1')
			return false;
	return true;
}
bool is_bool(string str) {
	return str == "true" || str == "false";
}
bool is_identifier(string str) {
	if (!sz(str)) return false;
	if (str[0] != '_' && !isalpha(str[0])) // must begin with _ or letter
		return false;
	return is_alpha_digit_und(str);
}
bool is_float(string str) {
	// check four cases
	return is_float_f1(str) || is_float_f2(str) || is_float_f3(str)
		|| is_float_f4(str);
}
bool is_half_float(string str) {
	return is_half_float_f1(str) || is_half_float_f2(str) || is_half_float_f3(str);
	/*string digits = "([0-9])";

	string fl_1 = "(" + digits + "+" + "\\." + digits + "*" + "[eE]" + ")";

	string fl_2 = "(\\." + digits + "+" + "[eE]" + ")";

	string fl_3 = "(" + digits + "+" + "[eE]" + ")";

	string fl_last = fl_1 + "|" + fl_2 + "|" + fl_3;
	regex fl(fl_last);*/
}
bool is_keyword(string str) {
	return count(all(keywords), str) > 0;
}
bool is_operator(string str) {
	return count(all(operators), str) > 0;
}
bool is_sperator(string str) {
	return count(all(sperators), str) > 0;
}
bool is_CharacterLiteral(string str) {
#pragma region first case
	// [^\'\\]
	if (sz(str) <= 2) return false; // ''
	if (str[0] != '\'' || str.back() != '\'') // check first and last single quatation
		return false;
	if (str[1] != '\'' && str[1] != '\\' && sz(str) == 3) // frist case
		return true;
#pragma endregion
#pragma region second case
	// {\u}{HexDigit}{4}
	bool flag = false;
	// '\uabcd'

	if (sz(str) == 2 + 2 + 4 && str[1] == '\\' && str[2] == 'u'
		&& is_hex_digit(str.substr(3, 4)))
		return true;
#pragma endregion 
#pragma region third case
	// {EscapeSequences}
	string strwithoutqutes = "";
	for (int i = 1; i < sz(str) - 1; i++)
		strwithoutqutes += str[i];
	if (count(all(Escapesequance), strwithoutqutes) > 0)
		return true;
#pragma endregion 
#pragma region fourth case
	// ("\"[0-7]+)
	int num = 0;
	for (int i = 2; i < sz(str) - 1; i++) {
		if (str[1] == '\\' && str[i] >= '0' && str[i] <= '7') {
			flag = true;
			num *= 10;
			num += (str[i] - '0');
		}
		else flag = false;
	}
	// max value 377
	if (flag && sz(str) <= 6 && num <= 377)
		return true;
#pragma endregion 
	return false;
}
bool is_StringLiteral(string str) {
	if (sz(str) < 2) return false; // "
	if (str[0] != '\"' || str.back() != '\"') // check first and last double quatoes
		return false;
	str.erase(str.begin(), str.begin() + 1); // erase double first quoate
	str.pop_back(); // erase last double quoate
	if (count(all(str), '\n') > 0) // string contains end line
		return false;
	int cnt_bslash = 0;
	for (auto& ch : str) {
		if (ch == '\\') {
			cnt_bslash++;
			continue;
		}
		// "asdf\\"sdf" not valid
		// "asdf\\\"sdf" valid
		if ((ch == '\"' || ch == '\'') && cnt_bslash % 2 == 0)
			return false; // double quate has even back slash as prefix
		cnt_bslash = 0;
	}
	if (cnt_bslash & 1) // string end with odd back slahes
		return false;
	return true;
}
bool is_text_block(string str) {
	if (sz(str) <= 6) return false;
	string tx = "\"\"\"";
	if (str.substr(0, sz(tx)) != tx) return false; // check first tx
	if (str.substr(sz(str) - sz(tx), sz(tx)) != tx) return false; // check last tx
	int idx = sz(tx);
	// read white spaces
	while (idx < sz(str) && (str[idx] == ' ' || str[idx] == '\t' || str[idx] == '\f'))
		idx++;
	if (idx == sz(str)) return false;
	if (str[idx] != '\n' && str[idx] != '\r')
		return false;
	return true;
}
bool is_null(string str) {
	return str == "null";
}
#pragma endregion


#pragma region main_funcs
string print(string up, string dow) {
	string ret = "( "+dow+" )   :" +"( " + up+" )" + "\n";
	return ret;
}
string get_input() {
	string ret = "", str;
	// use cin.ignore() if you use cin
	//cin.ignore(); 
	while (getline(cin, str))
		ret += " " + str + "\n";
	return ret;
}
int get_idx(string& inp, int st, char ch, bool ty) {
	int idx = st, cnt_bslash = 0;
	while (idx < sz(inp)) {
		if (inp[idx] == '\\') {
			cnt_bslash++;
			idx++;
			continue;
		}
		if (inp[idx] == ch && (!ty || cnt_bslash % 2 == 0))
			return idx;
		idx++;
		cnt_bslash = 0;
	}
	return -1;
}
int get_idx(string& inp, int st, string str) {
	int idx = st;
	while (idx < sz(inp)) {
		if (sz(inp) - idx >= sz(str) && inp.substr(idx, sz(str)) == str)
			return idx;
		idx++;
	}
	return -1;
}

string lastPrinted = "";
string check_print(string str) {
	if (str == "") return "";
	string tmp_lastPrinted = lastPrinted;
	lastPrinted = str;
	if (is_text_block(str))
		return print("text block", str);
	else if (is_null(str))
		return print("NullLiteral", str);
	else if (is_bool(str))
		return print("boolen", str);
	else if (is_keyword(str))
		return print("keyword", str);
	else if (is_identifier(str)) {
		if (symbolTable.find(str) == symbolTable.end())
			symbolTable[str] = tmp_lastPrinted;
		return print("identifier", str);
	}
	else if (is_decimal(str))
		return print("decimal", str);
	else if (is_float(str))
		return print("float", str);
	else if (is_hex(str))
		return print("hexdecimal", str);
	else if (is_octal(str))
		return print("octal", str);
	else if (is_binary(str))
		return print("binary", str);
	else if (is_operator(str))
		return print("operator", str);
	else if (is_sperator(str))
		return print("sperator", str);
	else if (is_StringLiteral(str))
		return print("string", str);
	else if (is_CharacterLiteral(str))
		return print("char", str);
	else return print("not detected", str);
}
#pragma endregion

string extract_file(string inp) {
	string ret = "";
	vector<char> whitespaces{ ' ', '\t', '\f', '\n', '\r' };
	vector<string> spli;
	for (auto& it : operators)
		if (it != "." && it != "+" && it != "-")
			spli.push_back(it);
	for (auto& it : sperators)
		if (it != "." && it != "+" && it != "-")
			spli.push_back(it);
	sort(all(spli), [](string a, string b) {return sz(a) > sz(b); });
	string cur = "";
	int idx = 0;
	while (idx < sz(inp)) {
		// check by white spaces
		if (count(all(whitespaces), inp[idx]) > 0) {
			ret += check_print(cur) + "\n";
			cur = "";
			idx++;
			continue;
		}
		string tx = "\"\"\"";
		// check text block
		if (sz(inp) - idx >= sz(tx) && inp.substr(idx, sz(tx)) == tx) {
			ret += check_print(cur) += "\n";
			cur = "";
			int g = get_idx(inp, idx + sz(tx), tx);
			int to = (g == -1 ? sz(inp) : g + sz(tx));
			string p = inp.substr(idx, to - idx);
			ret += check_print(p) + "\n";
			idx = to;
			continue;
		}
		// check single comment
		if (inp[idx] == '/' && idx + 1 < sz(inp) && inp[idx + 1] == '/') {
			ret += check_print(cur) += "\n";
			cur = "";
			int g = get_idx(inp, idx + 2, '\n', 0);
			string p = inp.substr(idx, g - idx + 1);
			ret += print("single comment", p) + "\n";
			idx = g + 1;
			continue;
		}
		// check multi comment
		if (inp[idx] == '/' && idx + 1 < sz(inp) && inp[idx + 1] == '*') {
			ret += check_print(cur) += "\n";
			cur = "";
			string p = "*/";
			int g = get_idx(inp, idx, p);
			int to = (g == -1 ? sz(inp) : g + sz(p));
			p = inp.substr(idx, to - idx);
			ret += print((g == -1 ? "opened multi comment" : "multi comment"), p) + "\n";
			idx = to;
			continue;
		}
		// check string or char 
		if (inp[idx] == '\"' || inp[idx] == '\'') {
			ret += check_print(cur) += "\n";
			cur = "";
			int g = get_idx(inp, idx + 1, inp[idx], 1);
			int to = (g == -1 ? sz(inp) : g + 1);
			string p = inp.substr(idx, to - idx);
			ret += check_print(p) + "\n";
			idx = to;
			continue;
		}
		
		// spilit by operators, sperators (spli)
		string opsp = "-1";
		for (auto& it : spli) {
			if (sz(inp) - idx >= sz(it) && inp.substr(idx, sz(it)) == it) {
				opsp = it;
				break;
			}
		}
		if (opsp != "-1") {
			ret += check_print(cur) += "\n";
			cur = "";
			idx += sz(opsp);
			ret += check_print(opsp) + "\n";
			continue;
		}
		// check dot and float
		if (inp[idx] == '.' && !((sz(cur) && is_digit(cur)) || (idx + 1 < sz(inp) && is_digit(inp[idx + 1])))) {
			ret += check_print(cur) += "\n";
			cur = "";
			ret += check_print(".") + "\n";
			idx += 1;
			continue;
		}
		if ((inp[idx] == '+' || inp[idx] == '-') && !is_half_float(cur)) {
			ret += check_print(cur) += "\n";
			cur = "";
			ret += check_print(string(1, inp[idx])) + "\n";
			idx += 1;
			continue;
		}
		cur.push_back(inp[idx]);
		idx++;
	}
	ret += check_print(cur) += "\n";
	return ret;
}




namespace lexicalanalyser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	protected:

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::RichTextBox^ richTextBox2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Cambria", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(41, 35);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(1096, 320);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox1_TextChanged);
			// 
			// button1
			// 
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 26.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(1169, 169);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(169, 72);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Analyze";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// richTextBox2
			// 
			this->richTextBox2->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->richTextBox2->Font = (gcnew System::Drawing::Font(L"Cambria", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->richTextBox2->Location = System::Drawing::Point(41, 448);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->ReadOnly = true;
			this->richTextBox2->Size = System::Drawing::Size(1096, 378);
			this->richTextBox2->TabIndex = 4;
			this->richTextBox2->Text = L"";
			this->richTextBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox2_TextChanged);
			// 
			// button2
			// 
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 26.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(1169, 495);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(169, 51);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Remove";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::Control;
			this->label1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label1.Image")));
			this->label1->Location = System::Drawing::Point(45, 3);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(187, 29);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Input your code...";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label2.Image")));
			this->label2->Location = System::Drawing::Point(45, 406);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(87, 29);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Result..";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1350, 858);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {

		
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		msclr::interop::marshal_context context;
		//convert from manged string to unmanged string
		string mystring = context.marshal_as<std::string>(richTextBox1->Text);
		string s12 = extract_file(mystring);
		String^ newstring = gcnew String(s12.data()); //convert from unmanged string to manged string
		richTextBox2->Text = newstring;
		
		
	}
	
private: System::Void richTextBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	richTextBox2->Text = "";
	richTextBox1->Text = "";
	
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
