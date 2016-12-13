# szyfr-cardano
Szyfr Cardano. Język - C/C++

Version 0.2
-	Zastosowano klasy i pogrupowano kod w bardziej przejrzyste funkcje


Schemat działania:
- 	W terminalu przyjmuje 1 argument: plik z tekstem do zaszyfrowania/odszyfrowania
- 	Wybieramy, czy chcemy zaszyfrować, czy odszyfrować
-	W wypadku szyfrowania: program generuje klucz i zapisuje go w pliku "klucz.txt"
-	Szyfr Cardano podmienia litery alfabetu w tekście szyfrowanym na litery w kluczu wg zasady: 'a'-1.litera klucza, 'b'-druga litera klucza itp.
-	Rozszyfrowanie: program ładuje klucz zapisany w pliku "klucz.txt" i porównuje każdą literę tekstu z kluczem
-	Jeżeli pozycje liter w tekście i kluczu są zgodne, szyfr korzysta z pozycji litery w kluczu aby zamienić tekst z powrotem

Wytyczne:
-	Aby rozszyfrowanie się udało, w folderze musi się znajdować plik tekstowy "klucz.txt".
-	plik 'klucz.txt' musi się składać z dokładnie 26 znaków - małych liter, każda różna od siebie


	
