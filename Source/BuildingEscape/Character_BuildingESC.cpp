// Copyright Erik 2020


#include "Character_BuildingESC.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "InventoryComponent.h"
#include "Engine.h"

// Sets default values
ACharacter_BuildingESC::ACharacter_BuildingESC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(RootComponent);

	SprintSpeedMulti = 1.6f;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

// Called to bind functionality to input
void ACharacter_BuildingESC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("CrouchDown", IE_Pressed, this, &ACharacter_BuildingESC::CrouchDown);
	PlayerInputComponent->BindAction("CrouchDown", IE_Released, this, &ACharacter_BuildingESC::CrouchUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACharacter_BuildingESC::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACharacter_BuildingESC::EndSprint);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_BuildingESC::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_BuildingESC::MoveRight);

	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &ACharacter_BuildingESC::BeginPickUp);
	PlayerInputComponent->BindAction("PickUp", IE_Released, this, &ACharacter_BuildingESC::EndPickUp);

	PlayerInputComponent->BindAction("ShowInventory", IE_Pressed, this, &ACharacter_BuildingESC::ShowInventory);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAtRate", this, &ACharacter_BuildingESC::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACharacter_BuildingESC::LookUpRate);
}

void ACharacter_BuildingESC::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACharacter_BuildingESC::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ACharacter_BuildingESC::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACharacter_BuildingESC::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACharacter_BuildingESC::StartSprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMulti;
}

void ACharacter_BuildingESC::EndSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMulti;
}

void ACharacter_BuildingESC::CrouchDown()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Crouching"));
	}
	Crouch();
}

void ACharacter_BuildingESC::CrouchUp()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Stopped Crouching"));
	}
	UnCrouch();
}

void ACharacter_BuildingESC::BeginPickUp()
{
	bIsPickingUp = true;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("PickUp Pressed"));
	}
}

void ACharacter_BuildingESC::EndPickUp()
{
	bIsPickingUp = false;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("PickUp Released"));
	}
}

void ACharacter_BuildingESC::ShowInventory()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("This is your inventory"));
	}
	UInventoryComponent::ShowInventoryComp();

}

