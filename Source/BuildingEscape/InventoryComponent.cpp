// Copyright Erik 2020

#include "InventoryComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupPlayerInput();
}

void UInventoryComponent::SetupPlayerInput()
{
	PlayerInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("ShowInventory", IE_Pressed, this, &UInventoryComponent::ShowInventoryComp);
	}
}


void UInventoryComponent::AddItemToInventory(APickUps* Item)
{
	Items.Add(Item);
	FString ItemPickedUp = "Item picked up: " + Item->GetName();
	FVector2D SizeOfMessage = { 1.5f, 1.5f };
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, *ItemPickedUp, true, SizeOfMessage);
	}
	Item->Destroy();
}

void UInventoryComponent::RemoveItemFromInventory()
{
	Items.Empty();
	/*if (Item != nullptr)
	{
		FString ItemRemoved = "Item removed: " + Item->GetName();
		FVector2D SizeOfMessage = { 1.5f, 1.5f };
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, *ItemRemoved, true, SizeOfMessage);
		Items.Remove(Item);
	}*/
}

bool UInventoryComponent::CheckInventory(APickUps* Item)
{
	if (Items.Num() == 0) { return false; }

	if (Item == nullptr)
	{ 
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Key removed"), true, { 1.5f, 1.5f });
		}
		return true; 
	}
	
	if (Items.Contains(Item))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Key removed"), true, { 1.5f, 1.5f });
		}
		return true;
	}

	return false;
}


void UInventoryComponent::ShowInventoryComp()
{
	FVector2D SizeOfMessage = { 1.5f, 1.5f };
	
	if (Items.Num() == 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, TEXT("INVENTORY IS EMPTY!"), true, SizeOfMessage);
		}
	}
	else
	{
	
		for (class APickUps* item : Items)
		{
			FString ItemInArray = item->GetName();
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, *ItemInArray, true, SizeOfMessage);
			}
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, TEXT("INVENTORY: "), true, SizeOfMessage);
	}
}

