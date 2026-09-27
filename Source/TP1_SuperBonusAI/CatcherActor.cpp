// Fill out your copyright notice in the Description page of Project Settings.


#include "CatcherActor.h"


ACatcherActor::ACatcherActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collision"));
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite Component"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement"));
	SteeringBehaviorComponent = CreateDefaultSubobject<USteeringBehaviorComponent>(TEXT("Steering Behavior"));
	
	RootComponent = BoxCollision;
	SpriteComponent->SetupAttachment(BoxCollision);

}

// Called when the game starts or when spawned
void ACatcherActor::BeginPlay()
{
	Super::BeginPlay();
	
	this->OnActorBeginOverlap.AddDynamic(this, &ACatcherActor::OnOverlap);
	
	SpawnPosition = GetActorLocation(); //Could be improved by calculating the center position rather than just taking the spawnPoint
	
	if (!ThrowerActor)
		return;
	
	ThrowerActor->OnObjectSpawn.AddDynamic(this,&ACatcherActor::AddNewTarget);
}

// Called every frame
void ACatcherActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (targetArray.Num() != 0)
	{
		FVector TargetPos = targetArray[0]->GetActorLocation();
		FVector MyPos = GetActorLocation();
		
		FVector SeekPosition = SteeringBehaviorComponent->Seek(TargetPos);
		
		SeekPosition.Y = 0.0f;
		SeekPosition.Z = 0.0f;
		
		ChangeSpriteRotation(SeekPosition.X);
		
		AddMovementInput(SeekPosition, DeltaTime);
		
		
		if (TargetPos.Z <= MyPos.Z) // on peut rajouté une marge
		{
			targetArray.RemoveAt(0);
		}
		
	}
	else
	{
		FVector SeekPosition = ReturnToSpawnPoint();
		
		SeekPosition.Y = 0.0f;
		SeekPosition.Z = 0.0f;
		
		ChangeSpriteRotation(SeekPosition.X);
		
		AddMovementInput(SeekPosition, DeltaTime);
	}

}

void ACatcherActor::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (AFallingObjectActor* FallingActor = Cast<AFallingObjectActor>(OtherActor))
	{
		targetArray.Remove(FallingActor);
		
		OnObjectCatched.Broadcast(OtherActor);
		
		FallingActor->Destroy();
		
	}
}

FVector ACatcherActor::ReturnToSpawnPoint() //Not really useful right now
{
	return SteeringBehaviorComponent->Seek(SpawnPosition);
}

void ACatcherActor::ChangeSpriteRotation(float velocity)
{
	if (velocity < 0)
		SpriteComponent->SetRelativeRotation(FRotator(0,180,0));
	else
		SpriteComponent->SetRelativeRotation(FRotator(0,0,0));
}

void ACatcherActor::AddNewTarget(AActor* target)
{
	targetArray.Add(target); //It will resize the Array every time I could allocate memory to the array
}

