//
//
//

#pragma once
#include <lua.hpp>
#include "LuaGate.hpp"
#include "Models/Vector2.hpp"
#include <vector>

namespace BBM
{
	class LuaMap {
		public:
			//! @brief ctor
			LuaMap();

			//! @brief dtor
			~LuaMap();

			//! @brief Clear danger map
			void clearDanger(void);

			//! @brief set dangerlevel at xpos ypos
			bool setDanger(int xpos, int ypos, int dangerLevel);

			//! @brief A star pathfinding between two points
			std::vector<Vector2f> pathfind(Vector2f, Vector2f) const;

			//! @brief push table of table of the map
			static int getMap(lua_State *L);

			//! @brief push table of table of the danger map
			static int getDanger(lua_State *L);

			//! @brief get array of nodes, path from a to b
			static int getPath(lua_State *L);

			//! @brief get closest safe space of player
			static int getClosestSafeSpace(lua_State *L);

			std::vector<std::vector<int>> _map;
			std::vector<std::vector<int>> _danger;
		private:
			//! @brief unwind path for a_star
			std::vector<Vector2f> fillPath(std::vector<Vector2f> &path, 
			std::unordered_map<Vector2f, Vector2f> &cameFrom, Vector2f node) const;

			//! @brief get neighbors of node for a_star
			std::vector<Vector2f> getNeighbors(Vector2f node) const;

			std::vector<Vector2f> _dirs = {
				Vector2f(1, 0), Vector2f(-1, 0), Vector2f(0, 1), Vector2f(0, -1)
			};
	};
}

namespace std
{
	template<>
	struct hash<BBM::Vector2f>
	{
		typedef BBM::Vector2f argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const &in) const
		{
			return in.x + in.y;
		}
	};
}
