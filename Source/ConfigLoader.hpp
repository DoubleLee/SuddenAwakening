#pragma once

#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <string>
using std::string;

/**
 * @brief The ConfigLoader class, loads it's data from the passed in file and path.
 * The class loads and holds this data temporarily for initialization of the engine.
 * It should only exist durning construction of the engine.
 */
class ConfigLoader
{
public:
	/**
	 * @brief ConfigLoader Empty, sets some default values.
	 */
	ConfigLoader();

	/**
	 * @brief ConfigLoader will load from the xml file within the ctor.
	 * Calls LoadFromFile
	 * @param file The file name and path to load from xml.
	 */
	ConfigLoader(const string & file);

	/**
	 * @brief LoadFromFile loads the xml file and path sent in.
	 * @param file The file name and path.
	 */
	void LoadFromFile( const string & file );

	/**
	 * @brief GetScreenWidth getter for screen width.
	 * @return The screen width.
	 */
	int GetScreenWidth() const;

	/**
	 * @brief GetScreenHeight getter for the screen height.
	 * @return The screen height.
	 */
	int GetScreenHeight() const;

	/**
	 * @brief GetMapTileSize getter for the map's tile size, every sprite should be this size.
	 * @return The maps tile size.
	 */
	int GetMapTileSize() const;

	/**
	 * @brief GetWindowTitle getter for the windows title string
	 * @return The title for the window.
	 */
	const string & GetWindowTitle() const;

	/**
	 * @brief GetFontButtonFile getter for the file name and path of the button font.
	 * @return The file name and path for the button font.
	 */
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
