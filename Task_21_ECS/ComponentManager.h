#pragma once

#include "Components.h"

#include <iostream>
#include <vector>
#include <unordered_map>


using ComponentMap = std::unordered_map <size_t, Component*>;
using EntityHasComponentBool = std::unordered_map <size_t, bool>;

using EntityHasComponent = std::unordered_map <uint32_t, EntityHasComponentBool>;
using EntityComponents = std::unordered_map<uint32_t, ComponentMap>;

using NumOfComponents = std::unordered_map<size_t, uint32_t>;


class ComponentManager
{
public:

	template <typename T, typename... TArgs>
	T* AddComponent(uint32_t entity_id, TArgs&&... mArgs)
	{
		if (!entityHasComponent[entity_id][typeid(T).hash_code()])
		{	
			entityComponents[entity_id][typeid(T).hash_code()]= new T(std::forward<TArgs>(mArgs)...);  //create new component and add to map
			entityComponents[entity_id][typeid(T).hash_code()]->entity= entity_id;                     //set entity id of component
			entityHasComponent[entity_id][typeid(T).hash_code()] = true;                               //set entity has component to true
			numOfComponents[typeid(T).hash_code()]++;												   //increment number of components of this type
			
			return dynamic_cast<T*>(entityComponents[entity_id][typeid(T).hash_code()]);			   //return pointer to component
		}
		else
		{
			std::cout << "Entity already has component" << std::endl;
			return nullptr;
		}
	}


	template <typename T>                            //return a specified component from a single entity
	T* GetComponent(uint32_t entity_id)
	{
		if (entityHasComponent[entity_id][typeid(T).hash_code()])                   //check if entity has component
		{ 
			return dynamic_cast<T*>(entityComponents[entity_id][typeid(T).hash_code()]);          //return pointer to component
		}
		else
		{
			std::cout << "Entity does not have component" << std::endl;
			return nullptr;
		}
	}


	template <typename T>                               //get all components of a specified type
	std::vector<T*> GetAllComponentsOfType()
	{		
		std::vector<T*> allComponentsOfType{};

		for (auto & e : entityComponents)
		{
			if (entityHasComponent[e.first][typeid(T).hash_code()])              //check if entity has component
			{
				allComponentsOfType.push_back(dynamic_cast<T*>(e.second[typeid(T).hash_code()]));             //add component to vector
			}
		}
		
		if (allComponentsOfType.size() > 0)
		{
			return allComponentsOfType;
		}
		else
		{
			std::cout << "No entities have this component" << std::endl;
			return allComponentsOfType;
		}
	}

	template <typename T>
	bool hasComponent(uint32_t entity_id) 
	{
		bool res = entityHasComponent[entity_id][typeid(T).hash_code()];
		return res;
	}


	void RemoveAllComponents(uint32_t entity_id)  //remove all components from a single entity
	{
		for (auto & e : entityComponents[entity_id])
		{
			numOfComponents[e.first]--;
			delete e.second;
		}
		entityComponents.erase(entity_id);
	}

	template <typename T>
	uint32_t NumOfComponentType()
	{
		return numOfComponents[typeid(T).hash_code()];
	}


private:
	EntityHasComponent entityHasComponent; //map key = entity id, value = map of components. map key = component type, value = bool
	EntityComponents entityComponents; // map key = entity id, value = map of components. map key = component type, value = component
	NumOfComponents numOfComponents; //map key = component type, value = number of components of that type
};