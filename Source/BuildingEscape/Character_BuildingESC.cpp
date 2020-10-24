// Copyright Erik 2020


#include "Character_BuildingESC.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Engine.h"

//Components
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"

//Own gamefiles
#include "LineTracer.h"
#include "PickUps.h"
#include "ButtonActor.h"



// Sets default values
ACharacter_BuildingESC::ACharacter_BuildingESC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComp->SetupAttachment(RootComponent);
	CameraComp->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	CameraComp->bUsePawnControlRotation = true;

	/*CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);*/

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(CameraComp);

	LineTraceComp = CreateDefaultSubobject<ULineTracer>(TEXT("LineTraceComponent"));

	PlayerInventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapsule"));
	TriggerCapsule->InitCapsuleSize(55.0f, 96.0f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_BuildingESC::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &ACharacter_BuildingESC::OnOverlapEnd);

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

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACharacter_BuildingESC::Interact);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAtRate", this, &ACharacter_BuildingESC::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACharacter_BuildingESC::LookUpRate);

	
}

UInventoryComponent* ACharacter_BuildingESC::GetInventoryComp()
{
	if (PlayerInventoryComp)
	UE_LOG(LogTemp, Warning, TEXT("InventCOMPSET!"));
	return PlayerInventoryComp;
}


void ACharacter_BuildingESC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->GetClass()->IsChildOf(ADoorOpenByKey::StaticClass())))
	{
		CurrentDoor = Cast<ADoorOpenByKey>(OtherActor);
	}
}

void ACharacter_BuildingESC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		CurrentDoor = nullptr;
	}
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
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Crouching"));
	//}
	Crouch();
}

void ACharacter_BuildingESC::CrouchUp()
{
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Stopped Crouching"));
	//}
	UnCrouch();
}

void ACharacter_BuildingESC::BeginPickUp()
{
	bIsPickingUp = true;
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("PickUp Pressed"));
	}*/
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);
	
	FVector Start = PlayerViewpointLocation;
	FVector End = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * 250.f;
	AActor* Actor = LineTraceComp->LineTraceSingle(Start, End, true);
	if (Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT ACTOR: %s"), *Actor->GetName());
		if (class APickUps* PickUp = Cast<APickUps>(Actor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor is a pickup"));
			PickUp->AddToInv(this);
		}
		else if (class AButtonActor* Button = Cast<AButtonActor>(Actor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor is a button"));
			Button->PressButton(this);
		}
		// Add For Grabber
	}
}
void ACharacter_BuildingESC::Interact()
{
	if (CurrentDoor)
	{
		CurrentDoor->CheckPlayerInventory(this);
	}
}


