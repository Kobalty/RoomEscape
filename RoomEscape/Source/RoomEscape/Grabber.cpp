// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	

	UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting for duty..tolotaly not pervy :P")); // just lets me know the Grabber is ready to go. Putting a ";" causes this not to work.
	
}

void UGrabber::FirstPlayerViewReport()// should tidy up some clutter
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(FirstPlayerLocation, FirstPlayerRotation);// this allows me to get a return of location and rotation need to find something to sotre it in tho. has to be ticked otherwise it displays intilaised or first called values.
	FString FirstPlayerLocationLog = FirstPlayerLocation.ToString();// allows the FPLocation to be outputted as a string
	FString FirstPlayerRotationLog = FirstPlayerRotation.ToString();

	UE_LOG(LogTemp, Warning, TEXT("Player Location is %s"), *FirstPlayerLocationLog);
	UE_LOG(LogTemp, Warning, TEXT("Player Rotation is %s"), *FirstPlayerRotationLog);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FirstPlayerViewReport();
	// ...
}

