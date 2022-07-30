#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnBuildingInWorld);

UCLASS()
class SACREDNIGHTMARE_API ABuildingActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ABuildingActor();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="BuildingInfo")
	class UStaticMeshComponent* BuildingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="BuildingInfo")
	class UBoxComponent* BuildingCollision;

	UPROPERTY(BlueprintAssignable, Category="BuildingInfo")
	FSpawnBuildingInWorld OnSpawnBuildingInWorld;
};
