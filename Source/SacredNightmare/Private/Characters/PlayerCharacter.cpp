#include "Characters/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PlayerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	PlayerSpringArm->SetupAttachment(RootComponent);
	//PlayerSpringArm->SetupAttachment(GetMesh());
	PlayerSpringArm->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(PlayerSpringArm);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);
}

void APlayerCharacter::MoveForward(float Value)
{
	if(Controller && Value != 0.f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(FRotator(0.f, Rotation.Yaw, 0.f)).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if(Controller && Value != 0.f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(FRotator(0.f, Rotation.Yaw, 0.f)).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::StartSprint()
{
	Server_StartSprint();
}

void APlayerCharacter::StopSprint()
{
	Server_StopSprint();
}

void APlayerCharacter::Server_StartSprint_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	Multicast_UpdateCurrentSpeed(RunSpeed);
}

bool APlayerCharacter::Server_StartSprint_Validate()  { return true; }

void APlayerCharacter::Server_StopSprint_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	Multicast_UpdateCurrentSpeed(WalkingSpeed);
}

bool APlayerCharacter::Server_StopSprint_Validate() { return true; }

void APlayerCharacter::Multicast_UpdateCurrentSpeed_Implementation(float UpdateSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = UpdateSpeed;
}

bool APlayerCharacter::Multicast_UpdateCurrentSpeed_Validate(float UpdateSpeed) { return true; }
