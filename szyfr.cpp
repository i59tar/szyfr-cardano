#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
//**           Wyrzuca Warningi z powodu:
//** deprecated conversion fron string const to char*
//**               mozna zignorowac
using namespace std;
//*********************FUNKCJE GLOBALNE********************************//
string cryptoPrep(string src){
        for (size_t i = 0;i<src.length();i++) if (src[i]<97 ||src[i]>122) src=src.erase(i--,1);
	return src;
} //preparuje tresc tak, aby zawieral tylko male litery alfabetu

string generate(){
	string key;
	int singular;
	string alphanum="abcdefghijklmnopqrstuvwxyz";
	for(int i=0;i<26;i++){
		singular=rand()%alphanum.length();
		key+=alphanum[singular];
		alphanum.erase(singular,1);
	}
	return key;
}//funkcja generujaca klucz


string load(char *filename){
	fstream file;
	file.open(filename);
	if(!file.is_open()){
		cout<<"Nie powiodlo sie ladowanie pliku "<<filename<<endl;
		return "";
	}
	string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	content=cryptoPrep(content);
	file.close();
	return content;
} //funkcja ladujaca zawartosc pliku 'filename' do zmiennej. Zwraca "" w razie niepowodzenia

void overwrite(char *filename, string text){
	fstream file;
	file.open(filename, std::fstream::out | std::fstream::trunc);
	file<<text;
	file.close();
} //Tworzy/Nadpisuje plik o nazwie 'filename' i zapelnia go trescia 'text'

bool alphacheck(string a){
	int tab[26]={0};
	for(int i=0;i<26;i++){
		tab[a[i]-97]++;
		if(tab[a[i]-97]==2)return false;
	}
	return true;	
} //test klucza - czy zawiera 26 roznych malych liter alfabetu

//*******************KONIEC FUNKCJE GLOBALNE*************************//
//**********************Klasa Cardano *******************************//
class Cardano{
public:

//----------------- KONSTRUKTORY I FUNKCJE -------------------------//
Cardano(string _text=""):text(_text){}

void encrypt(string &text, string &key){
	for(size_t i=0;i<text.length()-1;i++) text[i]=key[text[i]-97];
} //szyfrowanie

void decrypt(string &text, string &key){
	for(size_t i=0;i<text.length()-1;i++){
		for (int j=0;j<26;j++){
			if (text[i]==key[j]){
				text[i]=j+97;
				break;
			}
		}
	}
} //rozszyfrowanie

void Run(){
	if (text=="") return;
	if(mode[0]=='e' || mode[0]=='s' || mode[0]=='z'){
		key=generate();
		encrypt(text,key);
		overwrite("klucz.txt",key);
		}
	else if(mode[0]=='d' ||mode[0]=='o' || mode[0]=='r'){
		key=load("klucz.txt");
		if(key=="" || key.length()!=26 || !alphacheck(key))return;
		decrypt(text,key);
		overwrite("klucz.txt","");
		}
} //glowna funkcja szyfrujaca - obsluga trybow, modyfikacja plikow, zapis (przy szyfrowaniu) i usuwanie (przy rozszyfrowaniu) klucza

string text; //tresc pliku
string key; //klucz
string mode; //tryb
};



int main(int argc, char *argv[]){
if(argc>2)return 1;
srand(time(NULL));
Cardano A(load(argv[1]));
cout<<"Ustaw tryb dzialania (encr/decr): ";
cin>>A.mode;

A.Run();
	cout<<A.text<<endl;
	overwrite(argv[1],A.text);
return 0;
};
