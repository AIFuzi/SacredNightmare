#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class SACREDNIGHTMARE_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeaponActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(ReplicatedUsing = OnRep_WeaponOwner)
	class APlayerCharacter* WeaponOwner;

	UFUNCTION()
	void OnRep_WeaponOwner();

};
