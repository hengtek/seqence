#include "../Util/vector3.hpp"
#include "../Entitas/Pool.hpp"


namespace Entitas
{


	class Rotation : public IComponent
	{
	public:
		void Reset(float vy)
		{
			v = vy;
		}


		float v;
	};
}