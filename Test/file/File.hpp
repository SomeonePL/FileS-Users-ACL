#pragma once
#ifndef File_H
#define File_H
#include "../file/Inc.hpp"

class File
{
private:
	std::string name;
	std::string ext;
	int indexBlock;
	int acl;
	int rozmiar;
public:
	File(std::string);
	File() = default;
	~File();
	std::string getName();
	bool setName(std::string newname);
	std::string getExt();
	bool setExt(std::string newext);
	int getIndexBlock();
	bool setIndexBlock(int newiblock);
	int getAccessLevel();
	bool setAccessLevel(int newAL);
	int getRozmiar();
	bool setRozmiar(int rozm);
	void addRozmiar(int rozm);

	std::string getSpecName(std::string);
};

#endif