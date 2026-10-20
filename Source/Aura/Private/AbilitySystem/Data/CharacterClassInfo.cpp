// Copyright Ryan Flores :)


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetDefaultInfo(ECharacterClass CharacterClass) const
{
	return ClassDefaults.FindChecked(CharacterClass);
}
