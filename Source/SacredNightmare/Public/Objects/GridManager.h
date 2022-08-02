#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

UCLASS()
class SACREDNIGHTMARE_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	

	AGridManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid", meta=(ExposeOnSpawn = "true"))
	int GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid", meta=(ExposeOnSpawn = "true"))
	int WorldGridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid", meta=(ExposeOnSpawn = "true"))
	TSubclassOf<AActor> GridCell;

	UFUNCTION(BlueprintCallable, Category="Grid")
	void CreateGridWorld();

	UFUNCTION(BlueprintPure, Category="Grid")
	FVector GetClosestGridPosition(FVector InPosition);
	
private:

	UPROPERTY()
	TArray<AActor*> GridArray;
	
};
