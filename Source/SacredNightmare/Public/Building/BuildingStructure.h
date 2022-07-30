#pragma once

#include "BuildingStructure.generated.h"

USTRUCT(BlueprintType)
struct FBuildingStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="NeedItem")
	FName ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="NeedItem")
	int Count;
	
};

