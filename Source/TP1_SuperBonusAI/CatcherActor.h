// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "Components/SteeringBehaviorComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperFlipbookComponent.h"

#include "FallingObjectActor.h"
#include "ThrowerActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatcherActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectCatched,AActor*,CatchedActor);


UCLASS()
class TP1_SUPERBONUSAI_API ACatcherActor : public APawn
{
	GENERATED_BODY()
	
	//J'aurai pu faire un héritage ...
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision; //pas obligé
	
	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* SpriteComponent;
	
	UPROPERTY(VisibleAnywhere)
	class USteeringBehaviorComponent* SteeringBehaviorComponent;
	
	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* FloatingPawnMovement;

	TArray<AActor*> targetArray = {};
	
	UPROPERTY(EditAnywhere, Category="Initialisation")
	AThrowerActor* ThrowerActor = nullptr;
	
	FVector SpawnPosition;
	
	UFUNCTION()
	void AddNewTarget(AActor* target);
	
	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);
	
	FVector ReturnToSpawnPoint();
	
	void ChangeSpriteRotation(float velocity);
	
public:	
	// Sets default values for this actor's properties
	ACatcherActor();
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnObjectCatched OnObjectCatched;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
