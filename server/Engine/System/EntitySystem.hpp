#include <iostream>
#include "../Component/Attribute.hpp"
#include "../Component/Rotation.hpp"
#include "../Component/Position.hpp"
#include "../Entitas/ISystem.hpp"


namespace Entitas
{

	class EntitySystem : public IInitializeSystem, public IExecuteSystem, public ISetPoolSystem {

	public:
		void SetPool(Pool* pool) {
			_group = pool->GetGroup(Matcher_AllOf(Attribute));
			_pool = pool;
		}

		void Initialize() {
			player = _pool->CreateEntity();
			vector3 p;
			p.x = 1;
			player->Add<Rotation>();
			player->Add<Position>(p);
			player->Add<Attribute>(2, 1, 2, 3);
			player->OnEntityReleased += OnEntityDestroy;
		}

		void Execute() {
			for (auto &e : _group.lock()->GetEntities()) {
				auto attr = e->Get<Attribute>();
				if (e->Has<Position>())
				{
					auto pos = e->Get<Position>();
					e->Replace<Position>(pos->pos.x, pos->pos.y, pos->pos.z);
					std::cout << e->Get<Position>()->pos.y << std::endl;
				}
				else
				{
					printf("no postion exist");
				}
			}
		}

		void OnEntityDestroy(Entity* entity)
		{
			// sync to server
		}

		void UpdatePosition()
		{

		}


	private:
		Pool* _pool;
		std::weak_ptr<Group> _group;
		std::shared_ptr<Entity> player;
	};

}