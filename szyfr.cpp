#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
//A is ASCII 65, Z is 90
//a is ascii 97, z is 122
// spacebar is 32
using namespace std;

string szyfr(string text, string mode, string cipher);
string crypto_prep(string src);
string generate();
bool alphacheck(string a);

int main(int argc, char *argv[]){
srand(time(NULL));
if (argc<2) cout<<"Nieprawidlowa ilosc argumentow"<<endl;
else{
	string tryb;
	fstream klucz;
	fstream tekst;
	
	tekst.open(argv[1]);
	if (tekst.is_open()){
		string tresc ((istreambuf_iterator<char>(tekst)), istreambuf_iterator<char>());
		tresc = crypto_prep(tresc);
//wczytywanie tekstu
		if (argc==2){
			cout<<"Czy chcesz zaszyfrowac czy rozszyfrowac tekst? 'encr'/'decr'"<<endl;
			cin>>tryb;
		}
//opcja recznego wybierania trybu dzialania 'encr'/'decr'
		else tryb=argv[2];
		tekst.close();
		tekst.open(argv[1], std::fstream::out | std::fstream::trunc);
		if(tryb[0]=='e' || tryb[0]=='s' || tryb[0]=='z'){
			//pierwsze litery slow "encrypt" || "szyfruj" || "zaszyfruj"
			string cardano;
			cardano = generate();			
			tresc = szyfr(tresc,"encr",cardano);
 			cout<<"Tekst zostal zaszyfrowany. Oto efekt: "<<endl<<tresc<<endl;
			tekst<<tresc;	
			klucz.open("klucz.txt", std::fstream::out | std::fstream::trunc);
			klucz<<cardano;
			cout<<"Wygenerowany klucz: "<<endl<<cardano<<endl;
			tekst.close();
			klucz.close();
			}
		else if(tryb[0]=='d' ||tryb[0]=='o' || tryb[0]=='r'){
			//pierwsze litery slow "decrypt" || "odszyfruj" || "rozszyfruj"
			klucz.open("klucz.txt");
			if(!klucz.is_open()){
				cout<<"Nie znaleziono klucza."<<endl;
				tekst<<tresc;
				tekst.close();
				return 1;
			}
			string cardano ((istreambuf_iterator<char>(klucz)), istreambuf_iterator<char>());
			cardano=crypto_prep(cardano);
			if(!alphacheck(cardano) || cardano.length()!=26){
				cout<<"Plik 'klucz.txt' nie jest kluczem"<<endl;
				tekst<<tresc;
				tekst.close();
				return 1;
			}
			tresc = szyfr(tresc, "decr",cardano);
 			cout<<"Tekst zostal rozszyfrowany. Oto efekt: "<<endl<<tresc<<endl;			
			tekst<<tresc;
			cout<<"Zastosowany klucz: "<<endl<<cardano<<endl;
			klucz.close();
			tekst.close();
			}
		else cout<<"Nie rozpoznano trybu."<<endl;
		}
		
else cout<<"Nie powiodlo sie wczytywanie tekstu"<<endl;
}
return 0;
}

string szyfr(string text, string mode, string cipher){
	if (mode=="encr")for(size_t i=0;i<text.length()-1;i++) text[i]=cipher[text[i]-97];
	else if(mode=="decr"){
		for(size_t i=0;i<text.length()-1;i++){
			for (int j=0;j<26;j++){
				if (text[i]==cipher[j]){
					text[i]=j+97;
					break;
				}
			}
		}
	}
	return text;
}

string crypto_prep(string src)
{
    if (src.length() == 0) {
        return src;
    }

    for (size_t idx = 0;idx<src.length();idx++){
	if (src[idx]<97 ||src[idx]>122) src=src.erase(idx--,1);

    }

    return src;
}
//**************FUNKCJA GENERUJACA KLUCZ *******************//
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
}
bool alphacheck(string a){
	int tab[26]={0};
	for(int i=0;i<26;i++){
		tab[a[i]-97]++;
		if(tab[a[i]-97]==2)return false;
	}
	return true;	
}	
