// Copyright Erik 2020


#include "PickUps.h"
#include "InventoryComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickUps::APickUps()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = MeshComp;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickUps::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUps::AddToInv(ACharacter_BuildingESC* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Add to inventory"));
	if (Player)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerHere"));
		InvenComp = Player->PlayerInventoryComp;
		if (InvenComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("ARE YOU REALLY?!"));
			InvenComp->AddItemToInventory(this);
		}
	}
}



