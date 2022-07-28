#pragma once

#include "ItemStructure.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	int MiningCondition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	int ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	float RegenRate;
	
};