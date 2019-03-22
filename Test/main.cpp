#include "user/User.hpp"
#include "file/Disk.hpp"
Disk HDD = Disk();


void check_maciej(std::string temp)
{
	if (temp == "cr") {
		User::createUser();
	}
	else if (temp == "prcr") {
		User::printCurrentLoggedUser();
	}
	else if (temp == "li") {
		User::logIn();
	}
	else if (temp == "du") {
		cout << "Podaj nazwe uzytkownika do usuniecia: ";
		string wejscie;
		cin >> wejscie;
		cout << endl;
		User::deleteUser(wejscie);
	}
	else if (temp == "vul") {
		User::viewUserList();
	}
	else if (temp == "vsul") {
		User::viewStandardUserGroup();
	}
	else if (temp == "vaul") {
		User::viewAdminUserGroup();
	}
	else if (temp == "autsg") {
		cout << "Podaj uzytkownika do dodania: ";
		string wejscie;
		cin >> wejscie;
		cout << endl;
		User::addUserToStandardUserGroup(wejscie);
	}
	else if (temp == "autag") {
		cout << "Podaj uzytkownika do dodania: ";
		string wejscie;
		cin >> wejscie;
		cout << endl;
		User::addUserToAdminGroup(wejscie);
	}
	else if (temp == "val") {
		Acl::viewAclList();
	}
	else if (temp == "vfa") {
		cout << "Podaj nazwe pliku: ";
		string wejscie;
		cin >> wejscie;
		cout << endl;
		Acl::viewFileAcl(wejscie);
	}
	else if (temp == "sap") {
		cout << "Podaj nazwe pliku: ";
		string wejscie;
		cin >> wejscie;
		cout << endl;
		Acl::setAdditionalPermissions(wejscie);
	}
}

void check_andrzej(std::string inst)
{
	if(inst == "mkf")
	{
		HDD.dodajDane();
	}
	else if(inst == "mef")
	{
		HDD.dodajpPlik();
	}
	else if (inst == "pb")
	{
		HDD.wypiszBlok();
	}
	else if (inst == "hdd")
	{
		HDD.wypiszDysk();
	}
	else if (inst == "pf")
	{
		HDD.wypiszPlik();
	}
	else if (inst == "af")
	{
		HDD.dopiszDoPliku();
	}
	else if (inst == "rmf")
	{
		HDD.usunPlik();
	}
	else if (inst == "owf")
	{
		HDD.nadpiszPlik();
	}
	else if (inst == "pib")
	{
		HDD.wypiszBlokIndeksowy();
	}
	else if (inst == "pfib")
	{
		HDD.wypiszBlokIndeksowyPliku();
	}
	else if (inst == "dir")
	{
		HDD.wypiszKatalog();
	}
	else if (inst == "fpath")
	{
		HDD.sciezkaDoPliku();
	}
	else if (inst == "cp")
	{
		HDD.zmienUprawnienia();
	}
	else if (inst == "format")
	{
		HDD.formatuj();
	}
	else if (inst == "size")
	{
		HDD.miejsce();
	}
	else if (inst == "free")
	{
		HDD.pokazzajete();
	}
}


bool interpret()
{
	std::string instruction;
	std::cout << ">> ";
	std::cin >> instruction;
	

	check_maciej(instruction);
	check_andrzej(instruction);
	if(instruction == "exit")
	{
		return false;
	}
	return true;
}

int main()
{
	User::UserStart();


	/*
	HDD.dodajDane("dupa.txt", "123123123123");
	User::setCurrentLoggedUser(guest->getSID());
	Acl::viewAclList();
	HDD.wypiszPlik("dupa.txt");
	HDD.usunPlik("dupa.txt");
	Acl::viewAclList();
	User::setCurrentLoggedUser(admin->getSID());
	HDD.zmienUprawnienia("dupa.txt", 0);
	Acl::viewAclList();
	User::setCurrentLoggedUser(guest->getSID());
	HDD.wypiszPlik("dupa.txt");
	Acl::viewAclList();
	User *usr = new User();
	usr->createUser();
	User::viewStandardUserGroup();
	User::viewUserList();
	(*acl).setAdditionalPermissions("dupa.txt");
	std::cin.get();
	*/
while (interpret());
	
		cin.ignore(2);
	return 0;
}
