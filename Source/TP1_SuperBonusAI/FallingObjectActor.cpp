// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingObjectActor.h"

// Sets default values
AFallingObjectActor::AFallingObjectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite Component"));
	
	RootComponent = SpriteComponent;
}

// Called when the game starts or when spawned
void AFallingObjectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFallingObjectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

