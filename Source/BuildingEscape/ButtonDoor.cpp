// Copyright Erik 2020


#include "ButtonDoor.h"

// Sets default values
AButtonDoor::AButtonDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
}

// Called when the game starts or when spawned
void AButtonDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = DoorMesh->GetRelativeRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	InitialZ = DoorMesh->GetRelativeLocation().Z;
	CurrentZ = InitialZ;
	OpenUp += InitialZ;

	this->GetComponents<UAudioComponent>(Sounds);

	for (UAudioComponent* audio : Sounds)
	{
		if (AudioComponent1 == nullptr)
		{
			AudioComponent1 = audio;
		}
		else
		{
			AudioComponent2 = audio;
		}
	}
	
	//AudioComponent2 = this->FindComponentByClass<UAudioComponent>();
}

// Called every frame
void AButtonDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	if (HasAllButtonPressed.Num() == Buttons.Num())
	{
		if (HasAllButtonPressed == Buttons)
		{
			if (!DoorHasBeenOpened)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("DOOR OPENED!"), true, { 2.f ,2.f });
				}
				DoorHasBeenOpened = true;
			}
			if (OpenAngle != 0.f)
			{
				OpenDoor(DeltaTime);
				HasAllButtonPressed.Empty();
				Buttons.Empty();
			}
			if (OpenUp != 0.f)
			{
				OpenUpwards(DeltaTime);
				HasAllButtonPressed.Empty();
				Buttons.Empty();
			}
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("WRONG SEQUENCE, Try again!"), true, {2.f ,2.f });
			}
			HasAllButtonPressed.Empty();
			if (!AudioComponent2)
			{
				return;
			}
			else
			{
				AudioComponent2->Play();
			}
		}
		
	}
}

void AButtonDoor::OpenDoor(float delta)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, delta, DoorOpenSpeed);
	FRotator DoorRotation = DoorMesh->GetRelativeRotation();
	DoorRotation.Yaw = CurrentYaw;
	DoorMesh->SetRelativeRotation(DoorRotation);

	/*CurrentYaw = DoorMesh->GetRelativeRotation().Yaw;
	if (OpenAngle < 0)
		AddRotation = -1 * delta * 80;
	else if (OpenAngle > 0)
		AddRotation = 1 * delta * 80;

	if (FMath::IsNearlyEqual(CurrentYaw, OpenAngle, 1.f))
	{

	}
	else
	{
		FRotator NewRotation = FRotator(0.f, AddRotation, 0.0f);
		DoorMesh->AddRelativeRotation(NewRotation);
	}*/

	if (!AudioComponent1) { return; }
	if (!OpenDoorSound)
	{
		AudioComponent1->Play();
		OpenDoorSound = true;
	}
}

void AButtonDoor::OpenUpwards(float delta)
{

	CurrentZ = FMath::FInterpTo(CurrentZ, OpenUp, delta, DoorOpenSpeed);
	FVector DoorLocation = DoorMesh->GetRelativeLocation();
	DoorLocation.Z = CurrentZ;
	DoorMesh->SetRelativeLocation(DoorLocation);

	if (!AudioComponent1) { return; }
	if (!OpenDoorSound)
	{
		AudioComponent1->Play();
		OpenDoorSound = true;
	}

	/*CurrentZ = DoorMesh->GetRelativeLocation().Z;

	AddZ = 1 * delta * 80;

	if (FMath::IsNearlyEqual(CurrentZ, OpenUp, 1.f))
	{

	}
	else
	{
		FVector NewVector = FVector(0.f, 0.f, AddZ);
		DoorMesh->AddRelativeLocation(NewVector);
	}*/
}

