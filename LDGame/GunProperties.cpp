#include "GunProperties.h"
#include "MathHelper.h"
#include "BulletTypeDataManager.h"

#include <assert.h>

const float MIN_BULLET_DELAY = 100;
const float MAX_BULLET_DELAY = 100;

const unsigned int MAX_BULLET_COUNT = 3;

GunProperties GunProperties::createRandomProperties()
{
	unsigned int bulletType = BulletTypeDataManager::Get()->getRandomBulletTypeID(true);
	const BulletTypeData &bulletTypeData = BulletTypeDataManager::Get()->getBulletTypeData(bulletType);

	unsigned int numBullets = ceil(MathHelper::randomFloatInRange(bulletTypeData.minPerShot, bulletTypeData.maxPerShot));
	float spread = MathHelper::randomFloatInRange(bulletTypeData.minBulletSpread, bulletTypeData.maxBulletSpread);
	float accuracy = MathHelper::randomFloatInRange(bulletTypeData.minBulletAccuracyOffset, bulletTypeData.maxBulletAccuracyOffset);

	assert(numBullets > 0 && numBullets <= MAX_BULLET_COUNT);

	std::vector<unsigned int> bulletTypes;
	std::vector<float> bulletOffsets;
	std::vector<float> bulletRandomSpread;
	for(unsigned int bulletIndex = 0; bulletIndex < numBullets; ++ bulletIndex)
	{
		//bullet type
		bulletTypes.push_back(bulletType);
		
		//bullet accuracy
		bulletRandomSpread.push_back(accuracy);

		//bullet offset
		if(numBullets == 1)
		{
			bulletOffsets.push_back(0.0f);
		}
		else if(numBullets == 2)
		{
			switch(bulletIndex)
			{
				case 0:
					bulletOffsets.push_back(-spread);
					break;
				case 1:
					bulletOffsets.push_back(spread);
					break;
			}
		}
		else if(numBullets == 3)
		{
			switch(bulletIndex)
			{
				case 0:
					bulletOffsets.push_back(0.0f);
					break;
				case 1:
					bulletOffsets.push_back(-spread);
					break;
				case 2:
					bulletOffsets.push_back(spread);
					break;
			}
		}
	}

	float bulletDelay = MathHelper::randomFloatInRange(MIN_BULLET_DELAY, MAX_BULLET_DELAY) * bulletTypeData.delayMultiplier;

	return GunProperties(bulletDelay, bulletTypes, bulletOffsets, bulletRandomSpread);
}

GunProperties::GunProperties(float shotDelay, const std::vector<unsigned int> &bulletTypes, const std::vector<float> &bulletOffsets, const std::vector<float> &bulletRandomSpread) : _shotDelay(shotDelay),
																																													_bulletTypes(bulletTypes),
																																													_bulletOffsets(bulletOffsets),
																																													_bulletRandomSpread(bulletRandomSpread),
																																													_numBullets(bulletTypes.size())
{
}

GunProperties::~GunProperties()
{
}

float GunProperties::shotDelay()
{
	return _shotDelay;
}

const std::vector<unsigned int> &GunProperties::bulletTypes()
{
	return _bulletTypes;
}

const std::vector<float> &GunProperties::bulletOffsets()
{
	return _bulletOffsets;
}

const std::vector<float> &GunProperties::bulletRandomSpread()
{
	return _bulletRandomSpread;
}

unsigned int GunProperties::numBullets()
{
	return _numBullets;
}