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
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(FirstPlayerLocation, FirstPlayerRotation);// passes two empty variables into the funcion and returns them with values this also a "top down"search. has to be ticked otherwise it displays intilaised or first called values.
	
	UE_LOG(LogTemp, Warning, TEXT("Location:  %s  Rotation: %s "),*FirstPlayerLocation.ToString(), *FirstPlayerRotation.ToString()); // moved these onto one line. quick note that ToString works with vectors and rotators!
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FirstPlayerViewReport();

	// just temp to get the lince trace drawn from player view point TODO tidy up later.

	FVector LineTraceEnd = FirstPlayerLocation + FVector(0.0f, 0.0f, 40.0f);

	DrawDebugLine(GetWorld(), FirstPlayerLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0, 10.f);
	// ...
}

