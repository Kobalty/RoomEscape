// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsComponent();

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>(); /// look for attached input component

	if (InputComponent)
	{
		// do nothing if found
		UE_LOG(LogTemp, Warning, TEXT("Input Component found for: %s "), *GetOwner()->GetName());

		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); /// this is the function to actually do something with the action mappings (button presses) *this* referrs to this component, 
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabReleased); /// this sees if the grab has been released.
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No input Component found for: %s "), *GetOwner()->GetName());
	}
}

void UGrabber::FindPhysicsComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); /// Look for attached physics handle

	if (PhysicsHandle) /// Test the above statement works
	{
		// if found do nothing
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle found for: %s "), *GetOwner()->GetName()); // logs out the warning if no physics handle is found and then specifies fo which object aka owner it failed for.

	}

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed "));
}

void UGrabber::GrabReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released "));
}


void UGrabber::FirstPlayerViewReport()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(FirstPlayerLocation, FirstPlayerRotation);/// passes two empty variables into the funcion and returns them with values this also a "top down"search. has to be ticked otherwise it displays intilaised or first called values.
	
	/// **Edited out for my sanity ** UE_LOG(LogTemp, Warning, TEXT("Location:  %s  Rotation: %s "),*FirstPlayerLocation.ToString(), *FirstPlayerRotation.ToString()); // moved these onto one line. quick note that ToString works with vectors and rotator!
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FirstPlayerViewReport(); // going to disable this for the time being as its shitting up my log * dsiabling this kills the draw debug line

	/// just temp to get the line trace drawn from player view point TODO tidy up later.

	FVector LineTraceEnd = FirstPlayerLocation + FirstPlayerRotation.Vector() *Reach;

	DrawDebugLine(GetWorld(), FirstPlayerLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0, 10.f);

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// lince trace aka (ray-cast) out to reach distance.
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(OUT Hit, FirstPlayerLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	AActor *ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("You Hit:  %s  "), *ActorHit->GetName());
	}
	// ...
}



