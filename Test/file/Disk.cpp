#include "../file/Disk.hpp"
#include <iomanip>

Disk::Disk()
{
	for (int i = 0; i < 1024; i++)
	{
		this->HDD[i] = -1;
	}
	this->root = Directory();
	this->root.setName("root");
}


Disk::~Disk()
{
	////("Usunieto dysk :C");
	std::cout << "Usunieto dysk :C" << std::endl;
}

// NIE UZYTKOWNIK
void Disk::pobierzBlok(int index)
{
	////("Odczytuje zawartosc bloku o indeksie: " + to_string(index));
	//std::cout << "Odczytuje zawartosc bloku o indeksie: " + to_string(index) << std::endl;

	std::string zawartosc;
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		if (this->HDD[i] != -1)
		{
			if (this->HDD[i] < 32)
			{
				zawartosc += '[' + to_string(static_cast<int>(this->HDD[i])) + ']';
			}
			else
			{
				zawartosc += this->HDD[i];
			}
		}
		else
		{
			zawartosc += char(176);
		}
	}
	std::cout << zawartosc;
}

void Disk::wypiszPlik(int index)
{
	std::string zawartosc;
	////("Wypisuje plik o podanym numerze bloku indeksowego: " + to_string(index));
	std::cout << "Wypisuje plik o podanym numerze bloku indeksowego: " + to_string(index) << std::endl;
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		if (this->HDD[i] != -1)
		{
			////("Przechodze do bloku danych numer: " + HDD[i]);
			std::cout << "Przechodze do bloku danych numer: " + to_string(HDD[i]) << std::endl;
			for (int j = this->HDD[i] * 32; j < (this->HDD[i] * 32) + 32; j++)
			{
				if (this->HDD[j] != -1)
				{
					zawartosc += this->HDD[j];
				}
			}
		}
	}
	std::cout << zawartosc << std::endl;
}

bool Disk::czyZaj(int index)
{
	////("Sprawdzam czy blok o indeksie " + to_string(index) + " jest wolny.");
	std::cout << "Sprawdzam czy blok o indeksie " + to_string(index) + " jest wolny." << std::endl;
	return zajeBloki[index];
}

int Disk::znajdzWolny(int index)
{
	////("Szukam pierwszego wolnego bloku od podanego indeksu " + to_string(index));
	std::cout << "Szukam pierwszego wolnego bloku od podanego indeksu " + to_string(index) << std::endl;
	for (int i = index; i < 32; i++)
	{
		if (!czyZaj(i))
		{
			////("Znaleziono wolny blok o numerze " + to_string(i));
			std::cout << "Znaleziono wolny blok o numerze " + to_string(i) << std::endl;
			return i;
		}
	}
	for (int i = 0; i < index; i++)
	{
		if (!czyZaj(i))
		{
			////("Znaleziono wolny blok o numerze " + to_string(i));
			std::cout << "Znaleziono wolny blok o numerze " + to_string(i) << std::endl;
			return i;
		}
	}
	////("Nie znaleziono wolnego bloku.");
	std::cout << "Nie znaleziono wolnego bloku." << std::endl;
	return -1;
}

bool Disk::open(std::string name)
{
	////("Otwieram plik o podanej nazwie " + name);
	std::cout << "Otwieram plik o podanej nazwie " + name << std::endl;
	if (root.f.fileExists(name) != -1)
	{
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				////("Plik "+ name +" juz jest otwarty");
				std::cout << "Plik " + name + " juz jest otwarty" << std::endl;
				return false;
			}
		}
		root.f.openFiles.push_back(name);
		////("Pomyslnie otworzono plik " + name);
		std::cout << "Pomyslnie otworzono plik " + name << std::endl;
		return true;
	}
	////("Brak pliku o podanej nazwie " + name);
	std::cout << "Brak pliku o podanej nazwie " + name << std::endl;
	return false;
}

bool Disk::close(std::string name)
{
	////("Zamykam plik " + name);
	std::cout << "Zamykam plik " + name << std::endl;
	if (root.f.fileExists(name) != -1)
	{
		int pos = 0;
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				root.f.openFiles.erase(root.f.openFiles.begin() + pos);
				////("Zamknieto plik " + name);
				std::cout << "Zamknieto plik" + name << std::endl;
				return true;
			}
			pos++;
		}
		////("Plik "+ name +" nawet nie byl otwarty.");
		std::cout << "Plik " + name + " nawet nie byl otwarty." << std::endl;
		return false;
	}
	////("Brak pliku o podanej nazwie " + name);
	std::cout << "Brak pliku o podanej nazwie " + name << std::endl;
	return false;
}

bool Disk::status(std::string name)
{
	if (root.f.fileExists(name) != -1)
	{
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				////("Plik "+ name +" jest juz otwarty.")
				std::cout << "Plik " + name + " jest juz otwarty." << std::endl;
				return true;
			}
		}
		////("Plik "+name+" nie jest otwarty.")
		std::cout << "Plik " + name + " nie jest otwarty." << std::endl;
		return false;
	}
	////("Plik o podanej nazwie nie istnieje.");
	std::cout << "Plik o podanej nazwie nie istnieje " + name << std::endl;
	return false;
}

bool Disk::czyMozna(std::string fname)
{
	std::string comp;
	if (root.f.fileExists(fname) != -1)
	{
		for (auto e : root.f.files)
		{
			comp += e.getName() + "." + e.getExt();
			if (comp == fname)

			{
				auto a = new Acl();
				int pom = a->readPermissions(fname);
				if (pom < e.getAccessLevel())
				{
					////("Obecny uzytkownik nie ma wystarczajacych uprawnien do pliku " + fname);
					std::cout << "Obecny uzytkownik nie ma wystarczajacych uprawnien do pliku " + fname +
						" poziom dostepu " + to_string(pom) << std::endl;
					return false;
				}
				////("Obecny uzytkownik posiada wystarczajace uprawnienia do pliku " + fname);
				std::cout << "Obecny uzytkownik posiada wystarczajace uprawnienia do pliku " + fname << std::endl;
				return true;
			}
			comp = "";
		}
		return false;
	}
	////("Plik o podanej nazwie nie istnieje " + fname);
	std::cout << "Plik o podanej nazwie nie istnieje " + fname << std::endl;
	return false;
}

bool Disk::czyMoznaCZ(std::string fname)
{
	std::string comp;
	if (root.f.fileExists(fname) != -1)
	{
		for (auto e : root.f.files)
		{
			comp += e.getName() + "." + e.getExt();
			if (comp == fname)

			{
				Acl* a = new Acl();
				int pom = a->readPermissions(fname);
				if (pom < e.getAccessLevel() - 1)
				{
					////("Obecny uzytkownik nie ma wystarczajacych uprawnien do pliku " + fname);
					std::cout << "Obecny uzytkownik nie ma wystarczajacych uprawnien do pliku " + fname +
						" poziom dostepu " + to_string(pom) << std::endl;
					return false;
				}
				////("Obecny uzytkownik posiada wystarczajace uprawnienia do pliku " + fname);
				std::cout << "Obecny uzytkownik posiada wystarczajace uprawnienia do pliku " + fname << std::endl;
				return true;
			}
			comp = "";
		}
		return false;
	}
	////("Plik o podanej nazwie nie istnieje " + fname);
	std::cout << "Plik o podanej nazwie nie istnieje " + fname << std::endl;
	return false;
}

/*
void Disk::wypiszBlok(int index)
{
	////("Wypisuje blok o podanym indeksie " + to_string(index));
	//std::cout << "Wypisuje blok o podanym indeksie " + to_string(index) << std::endl;
	std::string temp;
	if (index != -1) {
		for (int i = index * 32; i < (index * 32) + 32; i++)
		{
			if (this->HDD[i] == -1) temp += '-';
			else
			{
				temp += this->HDD[i];
			}
		}
		std::cout << temp;
	}
}

//


// Metoda przeciazona dla interpretera nie dla interfejsu

void Disk::dodajpPlik(std::string name)
{
	if (root.f.fileExists(name) == -1)
	{
		int blokI = znajdzWolny(0);
		if (blokI == -1)
		{
			//DisplayLog("Brak wolnych blokow!");
			return;
		}
		zajeBloki[blokI] = true;
		root.mkfile(name, blokI);
		//DisplayLog("Stworzono plik o podanej nazwie " + name + " z blokiem indeksowym o numerze " + to_string(blokI));
		return;
	}
	//DisplayLog("Plik o podanej nazwie juz istnieje" + name);
	return;
}

void Disk::nadpiszPlik(std::string name, std::string dane)
{
	int blokI = root.f.fileExists(name);
	if (!czyMozna(name)) return;
	if (blokI == -1)
	{
		////("Plik o podanej nazwie nie istnieje " + name);
		std::cout << "Plik o podanej nazwie nie istnieje " + name << std::endl;
		return;
	}
	int pos = 0;
	bool koniec = false;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (koniec == false)
		{
			for (int j = this->HDD[i] * 32; j < (this->HDD[j] * 32) + 32; j++)
			{
				if (pos < dane.length())
				{
					this->HDD[j] = dane.at(pos);
					pos++;
				}
				else
				{
					this->HDD[j] = -1;
					koniec = true;
				}
			}
		}
		else
		{
			for (int j = this->HDD[i] * 32; j < (this->HDD[j] * 32) + 32; j++)
			{
				this->HDD[j] = -1;
			}
			zajeBloki[i] = false;
			this->HDD[i] = -1;
		}
	}
}

void Disk::dopiszDoPliku(std::string name, std::string dane)
{

	////("Dopisuje do pliku " + name);
	std::cout << "Dopisuje do pliku " + name << std::endl;

	int blokI = root.f.fileExists(name);
	if (blokI == -1)
	{
		////("Podany plik "+name+" nie istnieje");
		std::cout << "Podany plik " + name + " nie istnieje" << std::endl;
		return;
	}
	if (!czyMozna(name)) return;
	std::vector<int> wolne;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (this->HDD[i] == -1)
		{
			wolne.push_back(i);
		}
	}
	if (wolne.empty())
	{
		////("Plik "+ name +" osiagnal maksymalny rozmiar.");
		std::cout << "Plik " + name + " osiagnal maksymalny rozmiar." << std::endl;
		return;
	}
	if (sizeof(wolne) * 32 < dane.length())
	{
		////("Dane zbyt duze.");
		std::cout << "Dane zbyt duze." << std::endl;
		return;
	}
	int pos = 0;
	////("Sprawdzamy czy mozemy dopisac do zajetego bloku danych, ktory moze nie byc pelny");
	std::cout << "Sprawdzamy czy mozemy dopisac do zajetego bloku danych, ktory moze nie byc pelny" << std::endl;
	if (wolne.size() != 32)
	{
		int temp = this->HDD[wolne[0] - 1];
		for (int i = temp * 32; i < (temp * 32) + 32; i++)
		{
			if (this->HDD[i] == -1)
			{
				if (pos >= dane.length()) return;
				this->HDD[i] = dane.at(pos);
				pos++;
			}
		}
	}
	////("Dopisujemy do pliku " + name);
	std::cout << "Dopisujemy do pliku " + name << std::endl;
	for (auto e : wolne)
	{
		int blokD = znajdzWolny(0);
		if (blokD == -1)
		{
			////("Brak wolnych blokow.");
			std::cout << "Brak wolnych blokow!" << std::endl;
			return;
		}
		zajeBloki[blokD] = true;
		this->HDD[e] = blokD;

		for (int e = blokD * 32; e < blokD * 32 + 32; e++)
		{
			if (pos < dane.length())
			{
				this->HDD[e] = dane[pos];
				pos++;
			}
			else
			{
				this->HDD[e] = -1;
				return;
			}
		}
	}
}

void Disk::wypiszPlik(std::string name)
{
	////("Wypisuje plik " + name);
	std::cout << "Wypisuje plik " + name << std::endl;
	int i = root.f.fileExists(name);
	if (i != -1)
	{
		//Brak pliku o podanej nazwie
	}
	if (!czyMozna(name)) return; // nie mozna;
	wypiszPlik(i);
}

void Disk::usunPlik(std::string name)
{
	////("Usuwam plik " + name);
	int blokI = root.f.fileExists(name);

	if (blokI == -1)
	{
		std::cout << "Brak pliku o podanej nazwie " + name << std::endl;
	}
	if (!czyMozna(name)) return;
	std::cout << "Usuwam plik " + name << std::endl;

	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{

		if (this->HDD[i] != -1)
		{
			zajeBloki[this->HDD[i]] = false;

			for (int j = this->HDD[i] * 32; j < (this->HDD[i] * 32) + 32; j++)
			{
				this->HDD[j] = -1;
			}
			this->HDD[i] = -1;
		}
	}
	zajeBloki[blokI] = false;
	root.f.rmfile(name);
	int pos = 0;
	for (auto e : root.f.openFiles)
	{
		if (e == name)
		{
			root.f.openFiles.erase(root.f.openFiles.begin() + pos);
			////("Usunieto plik "+ name +" z tablicy otwartosci.");
			std::cout << "Usunieto plik " + name + " z tablicy otwartosci." << std::endl;
			break;
		}
		pos++;
	}

	////("Plik o podanej nazwie nie istnieje " + name);
	std::cout << "Plik o podanej nazwie juz nie istnieje " + name << std::endl;
}

*/
//////
// FUNKCJE INTERFEJSU

void Disk::dodajDane()
{
	std::string name;
	std::string dane;
	//std::cout << "Prosze podac nazwe pliku: ";
	std::cin >> name;
	std::cout << std::endl;
	//std::cout << "Prosze podac dane: ";
	std::getline(std::cin, dane);
	dane = dane.substr(1, dane.length());
	/*
	if (vec.size() == 3)
	{

		int index = stoi(vec[2]);
		if (name.length() == 0)
		{
			////("Nie podano nazwy pliku!");
			std::cout << "Nie podano nazwy pliku!" << std::endl;
			return;
		}
		if (root.f.fileExists(name) == -1)
		{
			std::string temp = dane;
			if (temp.length() > 32 * 31)
			{
				////("Rozmiar pliku przekracza maksymalna wartosc.");
				std::cout << "Rozmiar pliku przekracza maksymalna wartosc." << std::endl;
				return;
			}
			int blokI = znajdzWolny(index);
			//std::cout << blokI << std::endl;
			if (blokI == -1)
			{
				////("Brak wolnych blokow!");
				std::cout << "Brak wolnych blokow!" << std::endl;
				return;
			}
			unsigned int pos = 0;
			int rozm = ceil(temp.length() / 32.0);
			zajeBloki[blokI] = true;
			for (int i = blokI * 32; i < blokI * 32 + rozm * 32; i++)
			{
				if (pos < temp.length())
				{
					int blokD = znajdzWolny(blokI);
					if (blokD == -1)
					{
						////("Brak wolnego miejsca na dysku!");
						std::cout << "Brak wolnego miejsca na dysku!" << std::endl;
						return;
					}
					this->HDD[i] = blokD;
					zajeBloki[blokD] = true;
					for (int e = blokD * 32; e < blokD * 32 + 32; e++)
					{
						if (pos < temp.length())
						{
							this->HDD[e] = temp.at(pos);
							pos++;
						}
						else
						{
							this->HDD[e] = -1;
						}
					}
				}
				else
				{
					break;
				}
			}
			root.f.mkfile(name, blokI);
			////("Utworzono plik o podanej nazwie z podanymi danymi o bloku indeksowym " + to_string(blokI) );
			std::cout << "Utworzono plik o podanej nazwie " + name + " z podanymi danymi o bloku indeksowym " + to_string(blokI) << std::endl;
			return;
		}
		////("Plik o podanej nazwie ju¿ istnieje! " + name);
		std::cout << "Plik o podanej nazwie ju¿ istnieje! " + name << std::endl;
		return;
	}
	*/

	if (name.length() == 0)
	{
		////("Nie podano nazwy pliku!");
		std::cout << "Nie podano nazwy pliku!" << std::endl;
		return;
	}
	if (root.f.fileExists(name) == -1)
	{
		std::string temp = dane;
		if (temp.length() > 32 * 31)
		{
			////("Rozmiar pliku przekracza maksymalna wartosc.");
			std::cout << "Rozmiar pliku przekracza maksymalna wartosc." << std::endl;
			return;
		}
		int blokI = znajdzWolny(0);
		//std::cout << blokI << std::endl;
		if (blokI == -1)
		{
			////("Brak wolnych blokow!");
			std::cout << "Brak wolnych blokow!" << std::endl;
			return;
		}
		unsigned int pos = 0;
		int rozm = ceil(temp.length() / 32.00);
		zajeBloki[blokI] = true;
		for (int i = blokI * 32; i < blokI * 32 + rozm * 32; i++)
		{
			if (pos < temp.length())
			{
				int blokD = znajdzWolny(blokI);
				if (blokD == -1)
				{
					////("Brak wolnego miejsca na dysku!");
					std::cout << "Brak wolnego miejsca na dysku!" << std::endl;
					return;
				}
				this->HDD[i] = blokD;
				zajeBloki[blokD] = true;
				for (int e = blokD * 32; e < blokD * 32 + 32; e++)
				{
					if (pos < temp.length())
					{
						this->HDD[e] = temp.at(pos);
						pos++;
					}
					else
					{
						this->HDD[e] = -1;
					}
				}
			}
			else
			{
				break;
			}
		}
		root.f.mkfile(name, blokI, temp.length() + 32);
		////("Utworzono plik o podanej nazwie z podanymi danymi o bloku indeksowym " + to_string(blokI) );
		std::cout << "Utworzono plik o podanej nazwie " + name + " z podanymi danymi o bloku indeksowym " +
			to_string(blokI) << std::endl;
		return;
	}
	////("Plik o podanej nazwie ju¿ istnieje! " + name);
	std::cout << "Plik o podanej nazwie juz istnieje! " + name << std::endl;
}

void Disk::dodajpPlik()
{
	std::string name;
	//std::cout << "Prosze podac nazwe pliku: ";
	std::cin >> name;
	//std::cout << std::endl;
	if (root.f.fileExists(name) == -1)
	{
		int blokI = znajdzWolny(0);
		if (blokI == -1)
		{
			////("Brak wolnych blokow!");
			std::cout << "Brak wolnych blokow!" << std::endl;
			return;
		}
		zajeBloki[blokI] = true;
		root.f.mkfile(name, blokI, 32);
		////("Stworzono plik o podanej nazwie " + name + " z blokiem indeksowym o numerze " + to_string(blokI));
		std::cout << "Utworzono plik o podanej nazwie " + name + " z blokiem indeksowym o numerze " + to_string(blokI)
			<< std::endl;
		return;
	}
	////("Plik o podanej nazwie juz istnieje" + name);

	std::cout << "Plik o podanej nazwie juz istnieje" + name << std::endl;
}

void Disk::wypiszBlok()
{
	int index;
	//std::cout << "Prosze podac numer bloku: ";
	std::cin >> index;
	//std::cout << std::endl;

	////("Wypisuje blok o podanym indeksie " + to_string(index));
	//std::cout << "Wypisuje blok o podanym indeksie " + to_string(index) << std::endl;
	std::string temp;
	if (index != -1)
	{
		for (int i = index * 32; i < (index * 32) + 32; i++)
		{
			if (this->HDD[i] == -1) temp += '-';
			else
			{
				temp += this->HDD[i];
			}
		}
		std::cout << temp << std::endl;
	}
}

void Disk::wypiszDysk()
{
	////("Wypisuje zawartosc calego dysku.");
	std::cout << "Wypisuje zawartosc calego dysku." << std::endl;

	for (int j = 0; j < 32; j++)
	{
		pobierzBlok(j); // U mnie dziala
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void Disk::wypiszPlik()
{
	std::string name;
	//std::cout << "Prosze podac nazwe pliku: ";
	std::cin >> name;
	////("Wypisuje plik " + name);

	int i = root.f.fileExists(name);
	if (i == -1)
	{
		std::cout << std::endl << "Brak pliku " + name << std::endl;
	}
	if (!czyMoznaCZ(name)) return; // nie mozna;
	std::cout << std::endl << "Wypisuje plik " + name << std::endl;
	wypiszPlik(i);
}

void Disk::dopiszDoPliku()
{
	std::string name;
	//std::cout << "Prosze podac nazwe pliku: ";
	std::cin >> name;
	//std::cout << std::endl;
	std::string dane;
	//std::cout << "Prosze podac dane do dopisania: ";
	std::getline(std::cin, dane);
	dane = dane.substr(1, dane.length());
	//std::cout << std::endl;
	////("Dopisuje do pliku " + name);


	int blokI = root.f.fileExists(name);
	if (blokI == -1)
	{
		////("Podany plik "+name+" nie istnieje");
		std::cout << "Podany plik " + name + " nie istnieje" << std::endl;
		return;
	}
	if (!czyMozna(name)) return;
	std::cout << "Dopisuje do pliku " + name << std::endl;
	std::vector<int> wolne;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (this->HDD[i] == -1)
		{
			wolne.push_back(i);
		}
	}
	if (wolne.empty())
	{
		////("Plik "+ name +" osiagnal maksymalny rozmiar.");
		std::cout << "Plik " + name + " osiagnal maksymalny rozmiar." << std::endl;
		return;
	}
	if (sizeof(wolne) * 32 < dane.length())
	{
		////("Dane zbyt duze.");
		std::cout << "Dane zbyt duze." << std::endl;
		return;
	}
	int pos = 0;

	////("Sprawdzamy czy mozemy dopisac do zajetego bloku danych, ktory moze nie byc pelny");
	std::cout << "Sprawdzamy czy mozemy dopisac do zajetego bloku danych, ktory moze nie byc pelny" << std::endl;
	if (wolne.size() != 32)
	{
		int temp = this->HDD[wolne[0] - 1];
		for (int i = temp * 32; i < (temp * 32) + 32; i++)
		{
			if (this->HDD[i] == -1)
			{
				if (pos >= dane.length())
				{
					for (auto& b : root.f.files)
					{
						if (b.getName() + "." + b.getExt() == name)
						{
							std::cout << "Poprzedni rozmiar: " << b.getRozmiar() << std::endl;
							b.setRozmiar(b.getRozmiar() + dane.length());
							std::cout << "Obecny rozmiar: " << b.getRozmiar() << std::endl;
							break;
						}
					}
					return;
				}
				this->HDD[i] = dane.at(pos);
				pos++;
			}
		}
	}
	////("Dopisujemy do pliku " + name);
	std::cout << "Dopisujemy do pliku " + name << std::endl;
	for (auto e : wolne)
	{
		int blokD = znajdzWolny(0);
		if (blokD == -1)
		{
			////("Brak wolnych blokow.");
			std::cout << "Brak wolnych blokow!" << std::endl;
			return;
		}
		zajeBloki[blokD] = true;
		this->HDD[e] = blokD;
		for (int z = blokD * 32; z < blokD * 32 + 32; z++)
		{
			if (pos < dane.length())
			{
				this->HDD[z] = dane[pos];
				pos++;
			}
			else
			{
				this->HDD[z] = -1;
			}
		}
		if (pos >= dane.length())
		{
			for (auto& b : root.f.files)
			{
				if (b.getName() + "." + b.getExt() == name)
				{
					std::cout << "Poprzedni rozmiar: " << b.getRozmiar() << std::endl;
					b.setRozmiar(b.getRozmiar() + dane.length());
					std::cout << "Obecny rozmiar: " << b.getRozmiar() << std::endl;
					break;
				}
			}
			return;
		}
	}
}

void Disk::usunPlik()
{
	std::string name;
	//std::cout << "Prosze podac nazwe pliku: ";
	std::cin >> name;
	//std::cout << std::endl;
	////("Usuwam plik " + name);
	int blokI = root.f.fileExists(name);

	if (blokI == -1)
	{
		std::cout << "Brak pliku o podanej nazwie " + name << std::endl;
	}
	if (!czyMozna(name)) return;
	std::cout << "Usuwam plik " + name << std::endl;

	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (this->HDD[i] != -1)
		{
			zajeBloki[this->HDD[i]] = false;

			for (int j = this->HDD[i] * 32; j < (this->HDD[i] * 32) + 32; j++)
			{
				this->HDD[j] = -1;
			}
			this->HDD[i] = -1;
		}
	}
	zajeBloki[blokI] = false;
	root.f.rmfile(name);
	int pos = 0;
	for (const auto& e : root.f.openFiles)
	{
		if (e == name)
		{
			root.f.openFiles.erase(root.f.openFiles.begin() + pos);
			////("Usunieto plik "+ name +" z tablicy otwartosci.");
			std::cout << "Usunieto plik " + name + " z tablicy otwartosci." << std::endl;
			break;
		}
		pos++;
	}

	////("Plik o podanej nazwie nie istnieje " + name);
	std::cout << "Plik o podanej nazwie juz nie istnieje " + name << std::endl;
}


/*
 
void Disk::nadpiszPlik(std::string name, std::string dane)
{
	int blokI = root.f.fileExists(name);
	if (!czyMozna(name)) return;
	if (blokI == -1)
	{
		////("Plik o podanej nazwie nie istnieje " + name);
		std::cout << "Plik o podanej nazwie nie istnieje " + name << std::endl;
		return;
	}
	int pos = 0;
	bool koniec = false;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (koniec == false)
		{
			for (int j = this->HDD[i] * 32; j < (this->HDD[j] * 32) + 32; j++)
			{
				if (pos < dane.length())
				{
					this->HDD[j] = dane.at(pos);
					pos++;
				}
				else
				{
					this->HDD[j] = -1;
					koniec = true;
				}
			}
		}
		else
		{
			for (int j = this->HDD[i] * 32; j < (this->HDD[j] * 32) + 32; j++)
			{
				this->HDD[j] = -1;
			}
			zajeBloki[i] = false;
			this->HDD[i] = -1;
		}
	}
}

 */


void Disk::nadpiszPlik()
{
	std::string name;
	//std::cout << "Prosze podac nazwe pliku: ";
	std::cin >> name;
	//std::cout << std::endl;
	std::string dane;
	//std::cout << "Prosze podac dane do nadpisania pliku: ";
	std::getline(std::cin, dane);
	dane = dane.substr(1, dane.length());
	//std::cout << std::endl;
	int blokI = root.f.fileExists(name);
	if (!czyMozna(name)) return;
	if (blokI == -1)
	{
		////("Plik o podanej nazwie nie istnieje " + name);
		std::cout << "Plik o podanej nazwie nie istnieje " + name << std::endl;
		return;
	}
	int pos = 0;
	bool koniec = false;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (!koniec)
		{
			for (int j = this->HDD[i] * 32; j < (this->HDD[j] * 32) + 32; j++)
			{
				if (pos < dane.length())
				{
					this->HDD[j] = dane.at(pos);
					pos++;
				}
				else
				{
					this->HDD[j] = -1;
					koniec = true;
				}
			}
			if (i == 31) break;
			i++;
		}
		else
		{
			for (int j = this->HDD[i] * 32; j < (this->HDD[j] * 32) + 32; j++)
			{
				this->HDD[j] = -1;
			}
			zajeBloki[i] = false;
			this->HDD[i] = -1;
		}
	}

	for (auto& b : root.f.files)
	{
		if (b.getName() + "." + b.getExt() == name)
		{
			std::cout << "Poprzedni rozmiar: " << b.getRozmiar() << std::endl;
			b.setRozmiar(dane.length() + 32);
			std::cout << "Obecny rozmiar: " << b.getRozmiar() << std::endl;
			break;
		}
	}
}

void Disk::wypiszBlokIndeksowy()
{
	int index;
	std::cin >> index;
	std::cout << "Wypisuje zawartosc bloku indeksowego nr " + to_string(index) << std::endl;
	if (index != -1)
	{
		for (int i = index * 32; i < (index * 32) + 32; i++)
		{
			if (this->HDD[i] == -1) std::cout << '-';
			else
			{
				std::cout << static_cast<int>(this->HDD[i]) << " ";
			}
		}
		std::cout << std::endl;
	}
}

void Disk::wypiszBlokIndeksowyPliku()
{
	std::string fname;
	//std::cout << "Prosze podac nazwe pliku: ";
	std::cin >> fname;
	//std::cout << std::endl;
	int index = this->root.f.fileExists(fname);
	if (index == -1)
	{
		std::cout << "Plik o podanej nazwie " << fname << " nie istnieje." << std::endl;
		return;
	}

	std::cout << "Wypisuje zawartosc bloku indeksowego pliku " << fname << " o bloku indeksowym nr" << to_string(index)
		<< std::endl;
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		if (this->HDD[i] == -1) std::cout << '-';
		else
		{
			std::cout << static_cast<int>(this->HDD[i]) << " ";
		}
	}
	std::cout << std::endl;
}

void Disk::wypiszKatalog()
{
	this->root.f.showFiles();
}

void Disk::sciezkaDoPliku()
{
	std::string name;
	//std::cout << "Prosze podac nazwe pliku: ";
	std::cin >> name;
	//std::cout << std::endl;
	std::string path;
	if (root.f.fileExists(name) != -1)
	{
		std::cout << root.getName() + ":\\" + name << std::endl;
		return;
	}

	std::cout << "Plik o podanej nazwie nie istnieje." << std::endl;
}

void Disk::zmienUprawnienia()
{
	std::string name;
	//std::cout << "Prosze podac nazwe pliku: ";
	std::cin >> name;
	//std::cout << std::endl;
	std::string a;
	//std::cout << "Prosze podac nowy poziom dostepu: ";
	std::cin >> a;
	//std::cout << std::endl;
	int al = stoi(a);
	if (al > 5)
	{
		std::cout << "Podano zbyt wysoki poziom." << std::endl;
		return;
	}
	std::string comp;
	if (root.f.fileExists(name) == -1)
	{
		std::cout << "Brak pliku o podanej nazwie " << name << std::endl;
		return; // Brak pliku
	}
	if (Acl::getUserPermissions() >= 4)
	{
		for (std::vector<File>::iterator it = root.f.files.begin(); it != root.f.files.end(); ++it)
		{
			comp += (*it).getName() + "." + (*it).getExt();
			if (comp == name)
			{
				(*it).setAccessLevel(al);
				std::cout << "Zmieniono poziom dostepu do pliku " << name << " na " << a << std::endl;
				return;
			}
			comp = "";
		}
	}
	else
	{
		std::cout << "Brak uprawnien." << std::endl;
	}
}

void Disk::formatuj()
{
	//Acl acl = Acl();
	if (Acl::getUserPermissions() == 5)
	{
		root.f.openFiles.clear();
		root.f.files.clear();
		for (int i = 0; i < 1024; i++)
		{
			HDD[i] = -1;
		}
		for (int i = 0; i < 32; i++)
		{
			zajeBloki[i] = false;
		}
		Acl::AclList.clear();
	}
	else
	{
		std::cout << "Brak uprawnien" << std::endl;
	}
}

void Disk::miejsce()
{
	int rozm = 0;
	for (auto& b : root.f.files)
	{
		rozm += b.getRozmiar();
	}
	std::cout << "Obecny rozmiar plikow na dysku: " << rozm << std::endl;
	int i = 1024 - rozm;
	double procent = rozm / 1024.00;
	for (rozm = rozm / 8; rozm > 0; rozm--)
	{
		std::cout << char(178);
	}
	for (i = i / 8; i > 0; i--)
	{
		std::cout << char(176);
	}
	std::cout << std::setprecision(4) << procent * 100 << "%" << std::endl;
}

void Disk::pokazzajete()
{
	for (auto e : zajeBloki)
	{
		if (e)
		{
			std::cout << "1";
		}
		else
		{
			std::cout << "0";
		}
	}
	std::cout << std::endl;
}
