#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStructure.h"
#include "ItemActor.generated.h"

UCLASS()
class SACREDNIGHTMARE_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AItemActor();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ItemActor")
	class UBoxComponent* ItemBoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ItemActor")
	class UStaticMeshComponent* ItemStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	FItemStruct ItemStruct;

	UFUNCTION(BlueprintPure, Category="ItemInfo")
	int GetCurrentCondition();
	
private:

	int CurrentMiningCondition;
	
};
