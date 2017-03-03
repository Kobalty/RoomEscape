// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	FRotator StartRotation = Owner->GetActorRotation().Add(0, 50, 0);// sets the value of StartRotaion

	Owner->SetActorRotation(StartRotation);// Feeds the new FRotator StartRoation into this function and works.
	

	

	FString OwnerRotation = *Owner->GetActorRotation().ToString();// allows the rotation to be outputted to the log.

	UE_LOG(LogTemp, Warning, TEXT("Rotation is %s"), *OwnerRotation);


	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
