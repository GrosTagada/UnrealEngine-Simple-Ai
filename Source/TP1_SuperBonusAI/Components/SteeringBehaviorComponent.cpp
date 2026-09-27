// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringBehaviorComponent.h"

FVector USteeringBehaviorComponent::Seek(const FVector target)
{
	
	FVector vDesired = target - GetOwner()->GetActorLocation();
	
	vDesired.Normalize();
	
	vDesired *= maxSpeed;
	
	FVector vOwner = GetOwner()->GetVelocity();
	
	FVector vSteering = vDesired - vOwner;
	
	vSteering = vSteering.GetClampedToMaxSize(maxSpeed);
	
	return vSteering;
}

// Sets default values for this component's properties
USteeringBehaviorComponent::USteeringBehaviorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USteeringBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USteeringBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



