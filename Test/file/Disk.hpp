#pragma once
#ifndef Disk_h
#define Disk_h
#include "../file/Directory.hpp"

class Disk
{
private:
	char HDD[1024];
	bool zajeBloki[32];
public:
	Disk();
	~Disk();
	Directory root;
	void pobierzBlok(int index);
	void wypiszPlik(int index);
	bool czyZaj(int index);
	int znajdzWolny(int index);
	bool open(std::string name);
	bool close(std::string name);
	bool status(std::string name);
	bool czyMozna(std::string fname);
	bool czyMoznaCZ(std::string fname);
	/*
	virtual void Disk::wypiszBlok(int index);
	void dodajpPlik(std::string name); // Przeciazona funkcja dla assemblera nie dla uzytkownika
	virtual void Disk::nadpiszPlik(std::string name, std::string dane);
	virtual void Disk::dopiszDoPliku(std::string name, std::string dane);
	virtual void Disk::wypiszPlik(std::string name);
	virtual void Disk::usunPlik(std::string name);
	*/
	// Do uzytku uzytkownika V
	void dodajDane();
	void dodajpPlik();
	void wypiszBlok();
	void wypiszDysk();
	void wypiszPlik();
	void dopiszDoPliku();
	void usunPlik();
	void nadpiszPlik();
	void wypiszBlokIndeksowy();
	void wypiszBlokIndeksowyPliku();
	void wypiszKatalog();
	void sciezkaDoPliku();
	void zmienUprawnienia();
	void formatuj();
	void miejsce();
	void pokazzajete();
};
#endif