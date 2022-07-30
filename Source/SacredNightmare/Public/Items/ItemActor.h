#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStructure.h"
#include "ItemActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemMiningCooldownStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemMiningCooldownFinish);

UCLASS()
class SACREDNIGHTMARE_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AItemActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ItemActor")
	class UBoxComponent* ItemBoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ItemActor")
	class UStaticMeshComponent* ItemStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	FItemStruct ItemStruct;

	UPROPERTY(BlueprintAssignable, Category="ItemInfo")
	FItemMiningCooldownStart OnItemMiningCooldownStart;

	UPROPERTY(BlueprintAssignable, Category="ItemInfo")
	FItemMiningCooldownFinish OnItemMiningCooldownFinish;

	UFUNCTION(BlueprintPure, Category="ItemInfo")
	int GetCurrentCondition() const;

	UFUNCTION(BlueprintCallable, Category="ItemInfo")
	void UpdateCondition();

	UFUNCTION(Unreliable, Server, WithValidation, Category="ItemInfo")
	void Server_UpdateCondition();

	UFUNCTION(BlueprintPure, Category="ItemInfo")
	bool GetIsCooldown() const;
	
private:

	UPROPERTY(Replicated)
	int CurrentMiningCondition;

	bool IsMiningCooldown;
	void ClearCooldown();
	FTimerHandle CooldownTimer;
	
};
