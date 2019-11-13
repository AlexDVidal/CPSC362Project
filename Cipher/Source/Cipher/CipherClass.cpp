// Fill out your copyright notice in the Description page of Project Settings.

#include "Cipher.h"
#include "CipherClass.h"



// Sets default values
ACipherClass::ACipherClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACipherClass::BeginPlay(RotorVersion version)
{
	Super::BeginPlay();
	position = 0;

	switch (version) {
	default:
	case IV:
		rotationPoints.push_back('J' - 'A');
		//std::string fMp = "ESOVPZJAYQUIRHXLNFTGKDCMWB";
		strcpy(forwardMap, "ESOVPZJAYQUIRHXLNFTGKDCMWB");
		//forwardMap = "ESOVPZJAYQUIRHXLNFTGKDCMWB";
		break;

	case V:
		rotationPoints.push_back('Z' - 'A');
		//forwardMap[] = "VZBRGITYUPSDNHLXAWMJQOFECK";
		strcpy(forwardMap, "VZBRGITYUPSDNHLXAWMJQOFECK");
		break;

	case VI:
		rotationPoints.push_back('Z' - 'A');
		rotationPoints.push_back('M' - 'A');
		//forwardMap = "JPGVOUMFYQBENHZRDKASXLICTW";
		strcpy(forwardMap, "JPGVOUMFYQBENHZRDKASXLICTW");
		break;

	case VII:
		rotationPoints.push_back('Z' - 'A');
		rotationPoints.push_back('M' - 'A');
		//forwardMap = "NZJHGRCXMYSWBOUFAIVLPEKQDT";
		strcpy(forwardMap, "NZJHGRCXMYSWBOUFAIVLPEKQDT");
		break;

	case VIII:
		rotationPoints.push_back('Z' - 'A');
		rotationPoints.push_back('M' - 'A');
		//forwardMap = "FKQHTLXOCBJSPDZRAMEWNIUYGV";
		strcpy(forwardMap, "FKQHTLXOCBJSPDZRAMEWNIUYGV");
		break;
	}
	
}

// Called every frame
void ACipherClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACipherClass::rotate() {
	if (++position > FACE_COUNT)
		position = 0;
	for (int i = 0; i < rotationPoints.size(); i++) {
		if (rotationPoints[i] == position)
			return true;
	}
	return false;
}

void ACipherClass::setPosition(char newPos) {
	int n = toupper(newPos) - 'A';
	if (newPos > FACE_COUNT)
		return;
	position = newPos;
}

char ACipherClass::getPosition() {
	return position + 'A';
}

//Absolute means a refernce scheme that does not change even as rotors move
//Here an input of 'A' always means the top space, an ouput of 'A' means the top
//space, regardless of the rotor's current position.
char ACipherClass::encodeCharAbsolute(char c) {
	char ret;
	unsigned int n = toupper(c) - 'A';
	n += position;
	n = n % FACE_COUNT;
	ret = forwardMap[n];
	ret -= position;
	if (ret < 'A')
		ret = 'Z' - ('A' - ret);
	return ret;
}

RotorAction ACipherClass::absoluteRotorAction(RotorAction r) {
	RotorAction ret = { false, NULL };
	if (r.rotate) {
		ret.rotate = this->rotate();
	}
	ret.character = encodeCharAbsolute(r.character);
	return ret;
}

