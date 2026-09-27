// Fill out your copyright notice in the Description page of Project Settings.

#include "ThrowerActor.h"


// Sets default values
AThrowerActor::AThrowerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement"));
	SteeringBehaviorComponent = CreateDefaultSubobject<USteeringBehaviorComponent>(TEXT("Steering Behavior"));
	PaperSpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite Component"));
	
	RootComponent = PaperSpriteComponent;
}

// Called when the game starts or when spawned
void AThrowerActor::BeginPlay()
{
	Super::BeginPlay();
	
	TargetPos = GetActorLocation();
	
	SelectNewPos();
}

// Called every frame
void AThrowerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector SeekPosition = SteeringBehaviorComponent->Seek(TargetPos);
	
	ChangeSpriteRotation(SeekPosition.X);
	
	AddMovementInput(SeekPosition,DeltaTime);
	
	if (GetActorLocation().Distance(GetActorLocation(),TargetPos) < 10) // A améliorer
	{
		LaunchObject();
	}
}

void AThrowerActor::LaunchObject()
{
	SelectNewPos();
	
	FVector Location = GetActorLocation() + (-GetActorUpVector() * 20); //Could and Should be in a variable 
	
	if (!ActorToSpawn)
		return;
	
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, FRotator(0, 0, 0));
	
	OnObjectSpawn.Broadcast(SpawnedActor);
	
}

void AThrowerActor::SelectNewPos()
{
	int NewPosX = FMath::RandRange(MinRange,MaxRange);
	
	while (abs(NewPosX - TargetPos.X) < MinDistanceBeetweenLaunch)
		NewPosX = FMath::RandRange(MinRange,MaxRange);
	
	TargetPos.X = NewPosX;
}

void AThrowerActor::ChangeSpriteRotation(float velocity)
{
	if (velocity < 0)
		PaperSpriteComponent->SetRelativeRotation(FRotator(0,0,0));
	else
		PaperSpriteComponent->SetRelativeRotation(FRotator(0,180,0));
}





