// Copyright Erik 2020


#include "DoorOpenByKey.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "Components/BoxComponent.h"


// Sets default values
ADoorOpenByKey::ADoorOpenByKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	KeyMesh->SetupAttachment(DoorMesh);

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->InitBoxExtent(FVector(100, 100, 150));
	CollisionComp->SetupAttachment(DoorMesh);

}

// Called when the game starts or when spawned
void ADoorOpenByKey::BeginPlay()
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
	
}

// Called every frame
void ADoorOpenByKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (OpenTheDoor)
	{
		if (OpenAngle != 0.f)
		{
			OpenDoor(DeltaTime);
		}
		if (OpenUp != 0.f)
		{
			OpenUpwards(DeltaTime);
		}
	}
}

void ADoorOpenByKey::CheckPlayerInventory(ACharacter_BuildingESC* Player)
{
	if (Player)
	{
		if (NeededKey.Num() == 0)
		{
			return;
		}
		InvenComp = Player->PlayerInventoryComp;
		if (InvenComp)
		{
			for (class APickUps* Key : NeededKey)
			{
				if (!InvenComp->CheckInventory(Key))
				{
					DoIHaveAllKeys.Add(false);
					break;
				}
				else
				{
					DoIHaveAllKeys.Add(true);
				}
			}
			if(!DoIHaveAllKeys.Contains(false))
			{
				OpenTheDoor = true;
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Door Opened"), true, { 1.5, 1.5 });
				}
				InvenComp->RemoveItemFromInventory();
				/*for (class APickUps* Key : NeededKey)
				{
					if (Key == nullptr)
					{
						if (GEngine)
						{
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Key dissaperred somehow "), true, { 1.5, 1.5 });
						}
					}
					InvenComp->RemoveItemFromInventory(Key);
				}*/
			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("More keys are needed"), true, { 1.5, 1.5 });
				}
				if (!AudioComponent2) { return; }
				else { AudioComponent2->Play(); }

			}
		}
	}
	DoIHaveAllKeys.Empty();
}

void ADoorOpenByKey::OpenDoor(float delta)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, delta, DoorOpenSpeed);
	FRotator DoorRotation = DoorMesh->GetRelativeRotation();
	//AddRotation = -1 * delta * 80;

	DoorRotation.Yaw = CurrentYaw;
	DoorMesh->SetRelativeRotation(DoorRotation);

	if (!AudioComponent1) { return; }
	if (!OpenDoorSound)
	{
		AudioComponent1->Play();
		OpenDoorSound = true;
	}

	/*if (FMath::IsNearlyEqual(CurrentYaw, OpenAngle, 1.f))
	{

	}
	else
	{
		FRotator NewRotation = FRotator(0.f, AddRotation, 0.0f);
		DoorMesh->AddRelativeRotation(NewRotation);
	}*/
}

void ADoorOpenByKey::OpenUpwards(float delta)
{
	CurrentZ = FMath::FInterpTo(CurrentZ, OpenUp, delta, DoorOpenSpeed);
	FVector DoorLocation = DoorMesh->GetRelativeLocation();
	//AddRotation = -1 * delta * 80;

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



