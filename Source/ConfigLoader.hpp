#pragma once

#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <string>
using std::string;

class ConfigLoader
{
public:
	ConfigLoader();
	ConfigLoader(const string & file);

	void LoadFromFile( const string & file );

	// Game Settings
	int GetScreenWidth() const;
	int GetScreenHeight() const;
	int GetMapTileSize() const;
	const string & GetWindowTitle() const;
	const string & GetFontButtonFile() const;

private:
	// Game Settings
	int mScreenWidth;
	int mScreenHeight;
	int mMapTileSize;
	string mWindowTitle;
	string mFontButtonFile;
};

#endif // CONFIGLOADER_H
