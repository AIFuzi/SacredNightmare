#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingActor.generated.h"

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
};
