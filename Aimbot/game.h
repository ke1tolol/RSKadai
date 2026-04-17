#pragma once

struct Vector2 {
	float x;
	float y;

	Vector2 operator-(Vector2 ape)
	{
		return { x - ape.x, y - ape.y};
	}

	Vector2 operator+(Vector2 ape)
	{
		return { x + ape.x, y + ape.y};
	}

	Vector2 operator/(float ape)
	{
		return { x / ape, y / ape };
	}
};

namespace Game {
	bool AimKeyPressed() {
		std::string serialData = pArduino->GetSerial();

		if (serialData.empty()) return false;

		int SerialInt = std::stoi(serialData);

		return SerialInt > 0;
	}

	void Aim(float smooth) {
		Vector2 EnemyPos = pMem->Read<Vector2>(pMem->BaseAddress + Offsets::EnemyPosition);
		Vector2 AimPos = pMem->Read<Vector2>(pMem->BaseAddress + Offsets::AimPosition);

		Vector2 Delta = EnemyPos - AimPos;

		pMem->Write<Vector2>(pMem->BaseAddress + Offsets::AimPosition, AimPos + (Delta/smooth));
	}
}