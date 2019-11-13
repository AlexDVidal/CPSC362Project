// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <string>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CipherClass.generated.h"


#define FACE_COUNT 26

enum RotorVersion {
	IV = 4,
	V = 5,
	VI = 6,
	VII = 7,
	VIII = 8
};

struct RotorAction {
	char character;
	bool rotate;
};




UCLASS()
class CIPHER_API ACipherClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACipherClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay(RotorVersion version) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool rotate();
	void setPosition(char newPos);
	char getPosition();
	char encodeCharAbsolute(char c);
	RotorAction absoluteRotorAction(RotorAction r);

	
	UPROPERTY(EditAnywhere)
	unsigned int position;

	//rotationPoints stores the position *after which* a rotation
	//is sent to the next rotor. I.E. if a rotor transfers rotation
	//going from Z to A then rotationPoints will store A
	std::vector<unsigned int> rotationPoints;

	char forwardMap[FACE_COUNT + 1];
	char backwardMap[FACE_COUNT + 1];

};