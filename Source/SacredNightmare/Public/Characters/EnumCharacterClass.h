#pragma once

#include "EnumCharacterClass.generated.h"

UENUM(BlueprintType)
enum class EPlayerClassType : uint8
{
	ENone			UMETA(DisplayName = "None"),
	EHero			UMETA(DisplayName = "Hero")
};
