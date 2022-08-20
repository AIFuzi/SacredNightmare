#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SACREDNIGHTMARE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PlayerAssets")
	class USpringArmComponent* PlayerSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PlayerAssets")
	class UCameraComponent* PlayerCamera;

	UFUNCTION(Unreliable, Server, WithValidation, Category="Movement")
	void Server_StartSprint();

	UFUNCTION(Unreliable, Server, WithValidation, Category="Movement")
	void Server_StopSprint();

	UFUNCTION(Unreliable, NetMulticast, WithValidation, Category="Movement")
	void Multicast_UpdateCurrentSpeed(float UpdateSpeed);

private:

	void MoveForward(float Value);
	void MoveRight(float Value);

	void StartSprint();
	void StopSprint();
	
};
