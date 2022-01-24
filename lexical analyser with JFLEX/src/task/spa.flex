
%%

%class Lexical
%standalone


keywords= "abstract"|"assert"|"boolean"|"break"|"byte"|"case"|"catch"|"char"|"class"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extends"|"final"|"finally"|"float"|"for"|"if"|"goto"|"implements"|"import"|"instanceof"|"int"|"interface"|"long"|"native"|"new"|"package"|"private"|"protected"|"public"|"return"|"short"|"static"|"strictfp"|"super"|"switch"|"synchronized"|"this"|"throw"|"throws"|"transient"|"try"|"void"|"volatile"|"while"

OctalDigit= [0-7]
OctalDigits= {OctalDigit}+
OctalNumeral= "0"{OctalDigits}
OctalIntegerLiteral= {OctalNumeral}{IntgerTypeSuffix}


words= [a-zA-Z]
IntgerTypeSuffix= ["l" | "L"]?
SingelCotation= [']
DoubleCotation = "\"" 
space= "\f"|"\t"|"\r"|" "|"\n"|"\r"|"\r\n"

EscapeSequences =\\b|\\t|\\n|\\f|\\r|\\\\|\\\'|\\\"



Char= "("|")"|"{"|"}"|"["|"]"|";"|","|"."|"@"|"="|">"|"<"|"!"|"~"|"?"|":"|"+"|"-"|"*"|"/"|"&"|"|"|"^"|"%"  
Separators= "("|")"|"{"|"}"|"["|"]"|";"|","|"."|"..."|"@"|"::"
Operators= "="|">"|"<"|"!"|"~"|"?"|":"|"->"|"=="|">="|"<="|"!="|"&&"|"||"|"++"|"--"|"+"|"-"|"*"|"/"|"&"|"|"|"^"|"%"|"<<"|">>"|"+="|"-="|"*="|"/="|"&="|"|="|"^="|"%="
NullLiteral= "null"


CommentSign= "//"
Startcomm= "/*"
Endcomm= "*/"
Comment ={CommentSign}[^\n\r]*
multicomm ={Startcomm}~{Endcomm}


NonZeroDigits= [1-9]
Digit =[0-9]
Digits ={Digit}+
DecimalIntegerLiteral= {NonZeroDigits}{Digits}*{IntgerTypeSuffix}


HexDigit= [0-9a-fA-F]
HexDigits= {HexDigit}+
HexNumeral= "0x"{HexDigits}
HexIntegerLiteral ={HexNumeral}{IntgerTypeSuffix} 


BinaryDigit= [0-1]
BinaryDigits= {BinaryDigit}+ 
BinaryNumeral= "0b"{BinaryDigits}|"0B"{BinaryDigits}
BinaryIntegerLiteral= {BinaryNumeral}{IntgerTypeSuffix}



FloatTypeSuffix=  "d"|"D"|"f"|"F"
Sign= [+-]
ExponentIndicator= "e"|"E"
ExponentPart= {ExponentIndicator}{Sign}{Digits}
FloatingPointLiteral= ({Digits}[.]{Digits}?{ExponentPart}?{FloatTypeSuffix}?)|[.]{Digits}{ExponentPart}?{FloatTypeSuffix}?|{Digits}{ExponentPart}{FloatTypeSuffix}?|{Digits}{ExponentPart}?{FloatTypeSuffix}

BooleanLiteral= ("true"|"false")
hexa = "\\u"
CharacterLiteral= {SingelCotation}(([^\'\\])|({hexa}{HexDigit}{4})|{EscapeSequences}|("\\"[0-7]+)){SingelCotation}
StringLiteral= {DoubleCotation}([^\"\n\\]*|({hexa}{HexDigit}{4})|{EscapeSequences}|("\\"[0-7]+))*{DoubleCotation}
Identifier= ("_"|{words})({words}|{Digits}|"_")*


TextBlock= {DoubleCotation}{DoubleCotation}{DoubleCotation} [^\\]* {DoubleCotation}{DoubleCotation}{DoubleCotation}





%%


{keywords} {System.out.printf(" \n(%s)=============> keywords \n" ,yytext());}
{space} {System.out.printf(" \n =============>space \n" ,yytext());}
{Separators} {System.out.printf(" \n(%s)=============> Separators \n" ,yytext());}
{Operators} {System.out.printf(" \n(%s) =============>Operators \n" ,yytext());}
{NullLiteral} {System.out.printf("\n (%s) =============>NullLiteral \n" ,yytext());}
{Comment} {System.out.printf(" \n(%s)=============> Comment \n" ,yytext());}
{multicomm} {System.out.printf(" \n(%s) =============>multicomm \n" ,yytext());}
{OctalIntegerLiteral} {System.out.printf(" \n(%s)=============> OctalIntegerLiteral \n" ,yytext());}
{DecimalIntegerLiteral} {System.out.printf(" \n(%s)=============> DecimalIntegerLiteral \n" ,yytext());}
{HexIntegerLiteral} {System.out.printf(" \n(%s) =============>HexIntegerLiteral \n" ,yytext());}
{BinaryIntegerLiteral} {System.out.printf(" \n(%s)=============> BinaryIntegerLiteral \n" ,yytext());}
{FloatingPointLiteral} {System.out.printf(" \n(%s)=============> FloatingPointLiteral \n" ,yytext());}
{BooleanLiteral} {System.out.printf(" \n (%s) =============>BooleanLiteral \n" ,yytext());}
{CharacterLiteral} {System.out.printf(" \n (%s)=============> CharacterLiteral \n" ,yytext());}
{StringLiteral} {System.out.printf(" \n(%s) =============>StringLiteral \n" ,yytext());}
{Identifier} {System.out.printf(" \n (%s)=============> Identifier \n" ,yytext());}
{TextBlock} {System.out.printf("\n (%s)=============> TextBlock \n" ,yytext());}

