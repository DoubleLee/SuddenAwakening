#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <utility>
#include <string>
#include <memory>

typedef unsigned int ResourceID;

template< typename Type >
class ResourceManager
{
public:
	void LoadResource( const std::string & file, ResourceID id );

	Type & GetResource( ResourceID id ) const;

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
		throw std::runtime_error("Resource map already has this id. " + std::to_string(id) );
		}

	// attempt to load
	if ( !pResource->loadFromFile( file ) )
		{
		throw std::runtime_error("Failed to load " + file );
		}

	// time to insert into map
	auto pairCheck = mResourceMap.insert( std::make_pair(id, std::move(pResource) )  );

	if ( !pairCheck.second )
		{
		throw std::runtime_error("Failed to insert resource into map. " + file );
		}

	}

template< typename Type >
Type & ResourceManager<Type>::GetResource(ResourceID id) const
	{
	auto iterCheck = mResourceMap.find(id);
	if ( iterCheck == mResourceMap.end() )
		{
		throw std::runtime_error("Failed to find the resource id in the map. " + std::to_string(id) );
		}

	return *((*iterCheck).second.get());
	}

template< typename Type >
void ResourceManager<Type>::ClearAll()
	{
	mResourceMap.clear();
	}

#endif // RESOURCEMANAGER_HPP
