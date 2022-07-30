#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building/BuildingStructure.h"
#include "BuildingActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnBuildingInWorld);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnPreviewBuilding);

UCLASS()
class SACREDNIGHTMARE_API ABuildingActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ABuildingActor();

protected:

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="BuildingInfo")
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="BuildingInfo")
	class UBoxComponent* BuildingCollision;

	UPROPERTY(BlueprintAssignable, Category="BuildingInfo")
	FSpawnBuildingInWorld OnSpawnBuildingInWorld;

	UPROPERTY(BlueprintAssignable, Category="BuildingInfo")
	FSpawnPreviewBuilding OnSpawnPreviewBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BuildingInfo")
	TArray<FBuildingStruct> NeedItemForBuild;
	
	UPROPERTY(ReplicatedUsing = OnRep_PlayerOwner)
	class APlayerCharacter* PlayerOwner;

	UFUNCTION()
	void OnRep_PlayerOwner();

	UFUNCTION(BlueprintPure, Category="BuildingInfo")
	APlayerCharacter* GetPlayerOwner() const;
	
};
