#pragma once

#include "BuildingStructure.generated.h"

USTRUCT(BlueprintType)
struct FBuildingStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NeedItem")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NeedItem")
	int Count;
	
};

