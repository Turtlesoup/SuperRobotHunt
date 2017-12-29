#ifndef GUN_PROPERTIES_H
#define GUN_PROPERTIES_H

#include <vector>

class GunProperties
{
	public:
		static GunProperties createRandomProperties();
		GunProperties(float shotDelay, const std::vector<unsigned int> &bulletTypes, const std::vector<float> &bulletOffsets, const std::vector<float> &bulletRandomSpread);
		virtual ~GunProperties();
		float shotDelay();
		const std::vector<unsigned int> &bulletTypes();
		const std::vector<float> &bulletOffsets();
		const std::vector<float> &bulletRandomSpread();
		unsigned int numBullets();
	private:
		float _shotDelay;
		std::vector<unsigned int> _bulletTypes;
		std::vector<float> _bulletOffsets;
		std::vector<float> _bulletRandomSpread;
		unsigned int _numBullets;
};

#endif