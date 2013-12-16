#pragma once

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <utility>
#include <string>
#include <memory>

#include "Exceptions.hpp"

typedef unsigned int ResourceID;

/**
 * @brief ResourceManager is simple class for managing resources.
 *
 * It will take in a file name and path, and an integer ID to associate with that resource.
 *
 * If LoadResource loads the resource successfully you may then get a reference to it by calling GetResource(id).
 *
 * If loading was not successful the class will throw an exception.
 *
 * Resource IDs should be unique.
 */
template< typename Type >
class ResourceManager
{
public:
	/**
	 * @brief LoadResource is where resources are loaded and associated with an integer ID.
	 * @param file The file name and path to the resource for loading.
	 * @param id The integer ID to associate with this resource.
	 */
	void LoadResource( const std::string & file, ResourceID id );

	/**
	 * @brief GetResource is where you can get a reference to a loaded resource.  If an ID requested was not found it will throw an exception.
	 * @param id The integer ID requested.
	 * @return A reference to the resource.
	 */
	Type & GetResource( ResourceID id ) const;

	/**
	 * @brief ClearAll immediately destructs all the resources in this manager.
	 */
	void ClearAll();

protected:
	std::map<ResourceID, std::unique_ptr<Type> > mResourceMap;
};

template< typename Type >
void ResourceManager<Type>::LoadResource(const std::string & file, ResourceID id)
	{
	std::unique_ptr<Type> pResource ( new Type() );

	// Check to see if the id is already in the map
	auto iterCheck = mResourceMap.find(id);
	if ( iterCheck != mResourceMap.end() )
		{
		ThrowRuntimeException("Resource map already has this id. ID = " + std::to_string(id) )
		}

	// attempt to load
	if ( !pResource->loadFromFile( file ) )
		{
		ThrowRuntimeException("Failed to load " + file )
		}

	// time to insert into map
	auto pairCheck = mResourceMap.insert( std::make_pair(id, std::move(pResource) )  );

	if ( !pairCheck.second )
		{
		ThrowRuntimeException("Failed to insert resource into map. " + file )
		}

	}

template< typename Type >
Type & ResourceManager<Type>::GetResource(ResourceID id) const
	{
	auto iterCheck = mResourceMap.find(id);
	if ( iterCheck == mResourceMap.end() )
		{
		ThrowRuntimeException("Failed to find the resource id in the map. " + std::to_string(id) )
		}

	return *((*iterCheck).second.get());
	}

template< typename Type >
void ResourceManager<Type>::ClearAll()
	{
	mResourceMap.clear();
	}

#endif // RESOURCEMANAGER_HPP
