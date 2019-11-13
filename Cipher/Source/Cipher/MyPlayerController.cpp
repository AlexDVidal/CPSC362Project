//// Fill out your copyright notice in the Description page of Project Settings.
#include "MyPlayerController.h"
#include <vector>
#include <string>

////Rotor logic


struct RotorAction{
	char character;
	bool rotate;
};

#define FACE_COUNT 26
class Rotor {
public:
	Rotor(RotorVersion version) {
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

	bool rotate() {
		if (++position > FACE_COUNT)
			position = 0;
		for (int i = 0; i < rotationPoints.size(); i++) {
			if (rotationPoints[i] == position)
				return true;
		}
		return false;
	}

	void setPosition(char newPos) {
		int n = toupper(newPos) - 'A';
		if (newPos > FACE_COUNT)
			return;
		position = newPos;
	}

	char getPosition() {
		return position + 'A';
	}

	//Absolute means a refernce scheme that does not change even as rotors move
	//Here an input of 'A' always means the top space, an ouput of 'A' means the top
	//space, regardless of the rotor's current position.
	char encodeCharAbsolute(char c) {
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

	RotorAction absoluteRotorAction(RotorAction r) {
		RotorAction ret = { false, NULL };
		if (r.rotate) {
			ret.rotate = this->rotate();
		}
		ret.character = encodeCharAbsolute(r.character);
		return ret;
	}

private:
	unsigned int position;

	//rotationPoints stores the position *after which* a rotation
	//is sent to the next rotor. I.E. if a rotor transfers rotation
	//going from Z to A then rotationPoints will store A
	std::vector<unsigned int> rotationPoints;

	char forwardMap[FACE_COUNT + 1];
	char backwardMap[FACE_COUNT + 1];
};