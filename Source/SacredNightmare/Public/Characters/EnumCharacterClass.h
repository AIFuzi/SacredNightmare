#pragma once

#include "EnumCharacterClass.generated.h"

UENUM(BlueprintType)
enum class EPlayerClassType : uint8
{
	EHuman				UMETA(DisplayName = "Human"),
	EArcher				UMETA(DisplayName = "Archer"),
	ESwordsman			UMETA(DisplayName = "Swordsman"),
	EMage				UMETA(DisplayName = "Mage")
};
