#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEnded);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SACREDNIGHTMARE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	FTimerHandle RegenHealthTimer;

	void RegenHealth();

public:	

	UHealthComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float MaxHealth;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float RegenHealthRate;
	
	UPROPERTY(BlueprintAssignable, Category="Health")
	FHealthEnded OnHealthEndedEvent;

	UFUNCTION(BlueprintCallable, Category="Health")
	void GetDamage(float Damage);

	UFUNCTION(Unreliable, Server, WithValidation, Category="Health")
	void Server_GetDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category="Health")
	void StartRegenHealth();

	UFUNCTION(BlueprintCallable, Category="Health")
	void StopRegenHealth();

	UFUNCTION(Unreliable, Server, WithValidation, Category="Health")
	void Server_RegenHealth();
};








