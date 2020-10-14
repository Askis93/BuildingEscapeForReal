// Copyright Erik 2020


#include "DoorOpenByKey.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"


// Sets default values
ADoorOpenByKey::ADoorOpenByKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;


	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->InitBoxExtent(FVector(100, 100, 150));
	CollisionComp->SetupAttachment(DoorMesh);

	
	
	//OpenUp = 0.f;
	
	
}

// Called when the game starts or when spawned
void ADoorOpenByKey::BeginPlay()
{
	Super::BeginPlay();	

	InitialYaw = this->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	InitialYaw = this->GetActorLocation().Z;
	CurrentZ = InitialZ;
	OpenUp += InitialZ;
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
		if (!NeededKey)
		{
			return;
		}
		UE_LOG(LogTemp, Error, TEXT("WILL THIS PLEASE WORK!"));
		InvenComp = Player->PlayerInventoryComp;
		if (InvenComp)
		{
			
			UE_LOG(LogTemp, Error, TEXT("CHECKING FOR KEY"));
			if (InvenComp->CheckInventory(NeededKey))
			{
				InvenComp->RemoveItemFromInventory(NeededKey);
				OpenTheDoor = true;
			}
		}
	}

}

void ADoorOpenByKey::OpenDoor(float delta)
{
	CurrentYaw = DoorMesh->GetRelativeRotation().Yaw;

	AddRotation = -1 * delta * 80;

	if (FMath::IsNearlyEqual(CurrentYaw, OpenAngle, 1.f))
	{

	}
	else
	{
		FRotator NewRotation = FRotator(0.f, AddRotation, 0.0f);
		DoorMesh->AddRelativeRotation(NewRotation);
	}
}

void ADoorOpenByKey::OpenUpwards(float delta)
{
	CurrentZ = DoorMesh->GetRelativeLocation().Z;

	AddZ = 1 * delta * 80;

	if (FMath::IsNearlyEqual(CurrentZ, OpenUp, 1.f))
	{

	}
	else
	{
		FVector NewVector = FVector(0.f, 0.f, AddZ);
		DoorMesh->AddRelativeLocation(NewVector);
	}
	
}



